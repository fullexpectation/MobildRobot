#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <std_srvs/srv/empty.hpp>
#include "sl_lidar.h"
#include "math.h"

#include <signal.h>

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

#define DEG2RAD(x) ((x)*M_PI/180.)

#define ROS2VERSION "1.0.1"

using namespace sl;
// 全局标志，用于指示程序是否需要退出
bool need_exit = false;
/*  
此类封装了 RPLidar 的功能，包括初始化、参数配置、电机控制、扫描数据获取和发布。
它继承自 rclcpp::Node，支持通过 ROS2 发布激光雷达扫描数据。
*/
class SLlidarNode : public rclcpp::Node
{
  public:
  /*  
  构造函数
  初始化节点并创建用于发布激光扫描数据的主题。
  */
    SLlidarNode()
    : Node("sllidar_node")
    {

      scan_pub = this->create_publisher<sensor_msgs::msg::LaserScan>("scan", rclcpp::QoS(rclcpp::KeepLast(10)));
      
    }

  private:  
  /*  
  初始化参数
  配置激光雷达的通信参数（如串口、TCP、UDP）和其他运行参数。
  */  
    void init_param()
    {
        // 声明默认参数
        this->declare_parameter<std::string>("channel_type","serial");
        this->declare_parameter<std::string>("tcp_ip", "192.168.0.7");
        this->declare_parameter<int>("tcp_port", 20108);
        this->declare_parameter<std::string>("udp_ip","192.168.11.2");
        this->declare_parameter<int>("udp_port",8089);
        this->declare_parameter<std::string>("serial_port", "/dev/ttyUSB0");
        this->declare_parameter<int>("serial_baudrate",1000000);
        this->declare_parameter<std::string>("frame_id","laser_frame");
        this->declare_parameter<bool>("inverted", false);
        this->declare_parameter<bool>("angle_compensate", false);
        this->declare_parameter<std::string>("scan_mode",std::string());
        this->declare_parameter<float>("scan_frequency",10);
        //BingDa Robot
        this->declare_parameter<bool>("smart_control",false);
        
        // 获取实际参数值
        this->get_parameter_or<std::string>("channel_type", channel_type, "serial");
        this->get_parameter_or<std::string>("tcp_ip", tcp_ip, "192.168.0.7"); 
        this->get_parameter_or<int>("tcp_port", tcp_port, 20108);
        this->get_parameter_or<std::string>("udp_ip", udp_ip, "192.168.11.2"); 
        this->get_parameter_or<int>("udp_port", udp_port, 8089);
        this->get_parameter_or<std::string>("serial_port", serial_port, "/dev/ttyUSB0"); 
        this->get_parameter_or<int>("serial_baudrate", serial_baudrate, 1000000/*256000*/);//ros run for A1 A2, change to 256000 if A3
        this->get_parameter_or<std::string>("frame_id", frame_id, "laser_frame");
        this->get_parameter_or<bool>("inverted", inverted, false);
        this->get_parameter_or<bool>("angle_compensate", angle_compensate, false);
        this->get_parameter_or<std::string>("scan_mode", scan_mode, std::string());
        if(channel_type == "udp")
            this->get_parameter_or<float>("scan_frequency", scan_frequency, 20.0);
        else
            this->get_parameter_or<float>("scan_frequency", scan_frequency, 10.0);
        //BingDa Robot
        this->get_parameter_or<bool>("smart_control", smart_control, false);
    }
    /*
      获取激光雷达设备信息
      drv 激光雷达驱动实例
      return true 成功获取设备信息
      return false 获取设备信息失败
    */
    bool getSLLIDARDeviceInfo(ILidarDriver * drv)
    {
        sl_result     op_result;
        sl_lidar_response_device_info_t devinfo;

        op_result = drv->getDeviceInfo(devinfo);
        if (SL_IS_FAIL(op_result)) {
            if (op_result == SL_RESULT_OPERATION_TIMEOUT) {
                RCLCPP_ERROR(this->get_logger(),"Error, operation time out. SL_RESULT_OPERATION_TIMEOUT! ");
            } else {
                RCLCPP_ERROR(this->get_logger(),"Error, unexpected error, code: %x",op_result);
            }
            return false;
        }

        // print out the device serial number, firmware and hardware version number..
        char sn_str[37] = {'\0'}; 
        for (int pos = 0; pos < 16 ;++pos) {
            sprintf(sn_str + (pos * 2),"%02X", devinfo.serialnum[pos]);
        }
        RCLCPP_INFO(this->get_logger(),"SLLidar S/N: %s",sn_str);
        RCLCPP_INFO(this->get_logger(),"Firmware Ver: %d.%02d",devinfo.firmware_version>>8, devinfo.firmware_version & 0xFF);
        RCLCPP_INFO(this->get_logger(),"Hardware Rev: %d",(int)devinfo.hardware_version);
        return true;
    }
    /*  
    检查激光雷达健康状态
    drv 激光雷达驱动实例
    return true 设备健康状态正常
    return false 设备健康状态异常
    */
    bool checkSLLIDARHealth(ILidarDriver * drv)
    {
        sl_result     op_result;
        sl_lidar_response_device_health_t healthinfo;
        op_result = drv->getHealth(healthinfo);
        if (SL_IS_OK(op_result)) { 
            RCLCPP_INFO(this->get_logger(),"SLLidar health status : %d", healthinfo.status);
            switch (healthinfo.status) {
                case SL_LIDAR_STATUS_OK:
                    RCLCPP_INFO(this->get_logger(),"SLLidar health status : OK.");
                    return true;
                case SL_LIDAR_STATUS_WARNING:
                    RCLCPP_INFO(this->get_logger(),"SLLidar health status : Warning.");
                    return true;
                case SL_LIDAR_STATUS_ERROR:
                    RCLCPP_ERROR(this->get_logger(),"Error, SLLidar internal error detected. Please reboot the device to retry.");
                    return false;
                default:
                    RCLCPP_ERROR(this->get_logger(),"Error, Unknown internal error detected. Please reboot the device to retry.");
                    return false;

            }
        } else {
            RCLCPP_ERROR(this->get_logger(),"Error, cannot retrieve SLLidar health code: %x", op_result);
            return false;
        }
    }
    /*  
    停止电机服务回调
    req 请求对象（未使用）
    res 响应对象（未使用）
    return true 成功停止电机
    return false 停止电机失败
    */
    bool stop_motor(const std::shared_ptr<std_srvs::srv::Empty::Request> req,
                    std::shared_ptr<std_srvs::srv::Empty::Response> res)
    {
        (void)req;
        (void)res;

        if(!drv)
            return false;

        RCLCPP_DEBUG(this->get_logger(),"Stop motor");
        drv->setMotorSpeed(0);
        return true;
    }
    /*  
    启动电机服务回调
    req 请求对象（未使用）
    res 响应对象（未使用）
    return true 成功启动电机
    return false 启动电机失败
    */
    bool start_motor(const std::shared_ptr<std_srvs::srv::Empty::Request> req,
                    std::shared_ptr<std_srvs::srv::Empty::Response> res)
    {
        (void)req;
        (void)res;

        if(!drv)
           return false;
        if(drv->isConnected())
        {
            RCLCPP_DEBUG(this->get_logger(),"Start motor");
            sl_result ans=drv->setMotorSpeed();
            if (SL_IS_FAIL(ans)) {
                RCLCPP_WARN(this->get_logger(), "Failed to start motor: %08x", ans);
                return false;
            }
        
            ans=drv->startScan(0,1);
            if (SL_IS_FAIL(ans)) {
                RCLCPP_WARN(this->get_logger(), "Failed to start scan: %08x", ans);
            }
        } else {
            RCLCPP_INFO(this->get_logger(),"lost connection");
            return false;
        }

        return true;
    }
    /*  
    获取节点角度
    node 节点数据
    return float 节点角度
    */
    static float getAngle(const sl_lidar_response_measurement_node_hq_t& node)
    {
        return node.angle_z_q14 * 90.f / 16384.f;
    }
    /*  
    发布激光扫描数据
    pub 发布器实例
    nodes 节点数据数组
    node_count 节点数量
    start 开始时间
    scan_time 扫描时间
    inverted 是否反转
    angle_min 最小角度
    angle_max 最大角度
    max_distance 最大距离
    frame_id 坐标系 ID
    */
    void publish_scan(rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr& pub,
                  sl_lidar_response_measurement_node_hq_t *nodes,
                  size_t node_count, rclcpp::Time start,
                  double scan_time, bool inverted,
                  float angle_min, float angle_max,
                  float max_distance,
                  std::string frame_id)
    {
        static int scan_count = 0;
        auto scan_msg = std::make_shared<sensor_msgs::msg::LaserScan>();

        scan_msg->header.stamp = start;
        scan_msg->header.frame_id = frame_id;
        scan_count++;

        bool reversed = (angle_max > angle_min);
        if ( reversed ) {
            scan_msg->angle_min =  M_PI - angle_max;
            scan_msg->angle_max =  M_PI - angle_min;
        } else {
            scan_msg->angle_min =  M_PI - angle_min;
            scan_msg->angle_max =  M_PI - angle_max;
        }
        scan_msg->angle_increment = (scan_msg->angle_max - scan_msg->angle_min) / (double)(node_count-1);

        scan_msg->scan_time = scan_time;
        scan_msg->time_increment = scan_time / (double)(node_count-1);
        scan_msg->range_min = 0.05;
        scan_msg->range_max = max_distance;//8.0;

        scan_msg->intensities.resize(node_count);
        scan_msg->ranges.resize(node_count);
        bool reverse_data = (!inverted && reversed) || (inverted && !reversed);
        if (!reverse_data) {
            for (size_t i = 0; i < node_count; i++) {
                float read_value = (float) nodes[i].dist_mm_q2/4.0f/1000;
                if (read_value == 0.0)
                    scan_msg->ranges[i] = std::numeric_limits<float>::infinity();
                else
                    scan_msg->ranges[i] = read_value;
                scan_msg->intensities[i] = (float) (nodes[i].quality >> 2);
            }
        } else {
            for (size_t i = 0; i < node_count; i++) {
                float read_value = (float)nodes[i].dist_mm_q2/4.0f/1000;
                if (read_value == 0.0)
                    scan_msg->ranges[node_count-1-i] = std::numeric_limits<float>::infinity();
                else
                    scan_msg->ranges[node_count-1-i] = read_value;
                scan_msg->intensities[node_count-1-i] = (float) (nodes[i].quality >> 2);
            }
        }

        pub->publish(*scan_msg);
    }
public:
    /*  
    主工作循环
    初始化参数、连接激光雷达、启动扫描并持续发布数据。
    return int 返回值，成功为 0，失败为负数
    */    
    int work_loop()
    {   
        // 初始化参数     
        init_param();
        // 定义变量存储SDK版本信息
        int ver_major = SL_LIDAR_SDK_VERSION_MAJOR;
        int ver_minor = SL_LIDAR_SDK_VERSION_MINOR;
        int ver_patch = SL_LIDAR_SDK_VERSION_PATCH;
        // 输出ROS2包和SLLIDAR SDK的版本信息
        RCLCPP_INFO(this->get_logger(),"SLLidar running on ROS2 package SLLidar.ROS2 SDK Version:" ROS2VERSION ", SLLIDAR SDK Version:%d.%d.%d",ver_major,ver_minor,ver_patch);
        // 定义变量存储操作结果
        sl_result     op_result;

        // 创建驱动实例
        drv = *createLidarDriver();
        IChannel* _channel;
        // 根据配置创建相应的通信通道
        if(channel_type == "tcp"){
            _channel = *createTcpChannel(tcp_ip, tcp_port);
        }
        else if(channel_type == "udp"){
            _channel = *createUdpChannel(udp_ip, udp_port);
        }
        else{
            _channel = *createSerialPortChannel(serial_port, serial_baudrate);
        }
        // 尝试连接雷达设备
        if (SL_IS_FAIL((drv)->connect(_channel))) {
            // 连接失败时输出错误信息并返回
            if(channel_type == "tcp"){
                RCLCPP_ERROR(this->get_logger(),"Error, cannot connect to the ip addr  %s with the tcp port %s.",tcp_ip.c_str(),std::to_string(tcp_port).c_str());
            }
            else if(channel_type == "udp"){
                RCLCPP_ERROR(this->get_logger(),"Error, cannot connect to the ip addr  %s with the udp port %s.",udp_ip.c_str(),std::to_string(udp_port).c_str());
            }
            else{
                RCLCPP_ERROR(this->get_logger(),"Error, cannot bind to the specified serial port %s.",serial_port.c_str());            
            }
            delete drv;
            return -1;
        }


        // 创建停止和启动电机的服务
        stop_motor_service = this->create_service<std_srvs::srv::Empty>("stop_motor",  
                                std::bind(&SLlidarNode::stop_motor,this,std::placeholders::_1,std::placeholders::_2));
        start_motor_service = this->create_service<std_srvs::srv::Empty>("start_motor", 
                                std::bind(&SLlidarNode::start_motor,this,std::placeholders::_1,std::placeholders::_2));
        // 设置电机速度
        drv->setMotorSpeed();

        // 启动扫描
        LidarScanMode current_scan_mode;
        // 根据配置的扫描模式启动扫描
        if (scan_mode.empty()) {
            op_result = drv->startScan(false /* not force scan */, true /* use typical scan mode */, 0, &current_scan_mode);
        } else {
            std::vector<LidarScanMode> allSupportedScanModes;
            op_result = drv->getAllSupportedScanModes(allSupportedScanModes);

            if (SL_IS_OK(op_result)) {
                sl_u16 selectedScanMode = sl_u16(-1);
                for (std::vector<LidarScanMode>::iterator iter = allSupportedScanModes.begin(); iter != allSupportedScanModes.end(); iter++) {
                    if (iter->scan_mode == scan_mode) {
                        selectedScanMode = iter->id;
                        break;
                    }
                }

                if (selectedScanMode == sl_u16(-1)) {
                    RCLCPP_ERROR(this->get_logger(),"scan mode `%s' is not supported by lidar, supported modes:", scan_mode.c_str());
                    for (std::vector<LidarScanMode>::iterator iter = allSupportedScanModes.begin(); iter != allSupportedScanModes.end(); iter++) {
                        RCLCPP_ERROR(this->get_logger(),"\t%s: max_distance: %.1f m, Point number: %.1fK",  iter->scan_mode,
                                iter->max_distance, (1000/iter->us_per_sample));
                    }
                    op_result = SL_RESULT_OPERATION_FAIL;
                } else {
                    op_result = drv->startScanExpress(false /* not force scan */, selectedScanMode, 0, &current_scan_mode);
                }
            }
        }
        // 如果扫描启动成功，进行相关配置
        if(SL_IS_OK(op_result))
        {
            // 计算每圈的点数和角度补偿系数
            //default frequent is 10 hz (by motor pwm value),  current_scan_mode.us_per_sample is the number of scan point per us
            int points_per_circle = (int)(1000*1000/current_scan_mode.us_per_sample/scan_frequency);
            angle_compensate_multiple = points_per_circle/360.0  + 1;
            if(angle_compensate_multiple < 1) 
            angle_compensate_multiple = 1.0;
            max_distance = (float)current_scan_mode.max_distance;
            // 输出当前扫描模式的信息
            RCLCPP_INFO(this->get_logger(),"current scan mode: %s, sample rate: %d Khz, max_distance: %.1f m, scan frequency:%.1f Hz, ", 
                                current_scan_mode.scan_mode,(int)(1000/current_scan_mode.us_per_sample+0.5),max_distance, scan_frequency);
        }
        else
        {
            // 扫描启动失败时输出错误信息
            RCLCPP_ERROR(this->get_logger(),"Can not start scan: %08x!", op_result);
        }
        // 启动电机智能控制
        //start lidar rotate BingDa
        if(smart_control)
        {
            RCLCPP_INFO(this->get_logger(),"RPLidar A1 Super,Support Motor Smart Control");
            drv->setDTR(true);        
        } 
        // 主循环，获取并发布扫描数据
        rclcpp::Time start_scan_time;
        rclcpp::Time end_scan_time;
        double scan_duration;
        while (rclcpp::ok() && !need_exit) {
            sl_lidar_response_measurement_node_hq_t nodes[8192];
            size_t   count = _countof(nodes);

            start_scan_time = this->now();
            op_result = drv->grabScanDataHq(nodes, count);
            end_scan_time = this->now();
            scan_duration = (end_scan_time - start_scan_time).seconds();

            if (op_result == SL_RESULT_OK) {
                op_result = drv->ascendScanData(nodes, count);
                float angle_min = DEG2RAD(0.0f);
                float angle_max = DEG2RAD(360.0f);
                if (op_result == SL_RESULT_OK) {
                    if (angle_compensate) {
                        //const int angle_compensate_multiple = 1;
                        const int angle_compensate_nodes_count = 360*angle_compensate_multiple;
                        int angle_compensate_offset = 0;
                        auto angle_compensate_nodes = new sl_lidar_response_measurement_node_hq_t[angle_compensate_nodes_count];
                        memset(angle_compensate_nodes, 0, angle_compensate_nodes_count*sizeof(sl_lidar_response_measurement_node_hq_t));

                        size_t i = 0, j = 0;
                        for( ; i < count; i++ ) {
                            if (nodes[i].dist_mm_q2 != 0) {
                                float angle = getAngle(nodes[i]);
                                int angle_value = (int)(angle * angle_compensate_multiple);
                                if ((angle_value - angle_compensate_offset) < 0) angle_compensate_offset = angle_value;
                                for (j = 0; j < angle_compensate_multiple; j++) {
                                    int angle_compensate_nodes_index = angle_value-angle_compensate_offset + j;
                                    if(angle_compensate_nodes_index >= angle_compensate_nodes_count)
                                        angle_compensate_nodes_index = angle_compensate_nodes_count - 1;
                                    angle_compensate_nodes[angle_compensate_nodes_index] = nodes[i];
                                }
                            }
                        }
    
                        publish_scan(scan_pub, angle_compensate_nodes, angle_compensate_nodes_count,
                                start_scan_time, scan_duration, inverted,
                                angle_min, angle_max, max_distance,
                                frame_id);

                        if (angle_compensate_nodes) {
                            delete[] angle_compensate_nodes;
                            angle_compensate_nodes = nullptr;
                        }
                    } else {
                        // 找到第一个和最后一个有效点
                        int start_node = 0, end_node = 0;
                        int i = 0;
                        // find the first valid node and last valid node
                        while (nodes[i++].dist_mm_q2 == 0);
                        start_node = i-1;
                        i = count -1;
                        while (nodes[i--].dist_mm_q2 == 0);
                        end_node = i+1;

                        angle_min = DEG2RAD(getAngle(nodes[start_node]));
                        angle_max = DEG2RAD(getAngle(nodes[end_node]));

                        publish_scan(scan_pub, &nodes[start_node], end_node-start_node +1,
                                start_scan_time, scan_duration, inverted,
                                angle_min, angle_max, max_distance,
                                frame_id);
                    }
                } else if (op_result == SL_RESULT_OPERATION_FAIL) {
                    // 所有点数据无效时直接发布
                    float angle_min = DEG2RAD(0.0f);
                    float angle_max = DEG2RAD(359.0f);
                    publish_scan(scan_pub, nodes, count,
                                start_scan_time, scan_duration, inverted,
                                angle_min, angle_max, max_distance,
                                frame_id);
                }
            }
            // 处理ROS2事件
            rclcpp::spin_some(shared_from_this());
        }

        // 停止电机和扫描
        drv->setMotorSpeed(0);
        drv->stop();
        RCLCPP_INFO(this->get_logger(),"Stop motor");

        return 0;
    }

  private:
    // 激光扫描数据发布者
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr scan_pub;
    // 启动电机服务
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr start_motor_service;
    // 停止电机服务
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr stop_motor_service;
    // 通道类型，如串口、TCP、UDP等
    std::string channel_type;
    // TCP IP地址
    std::string tcp_ip;
    // UDP IP地址
    std::string udp_ip;
    // 串口端口
    std::string serial_port;
    // TCP 端口号，默认为20108
    int tcp_port = 20108;
    // UDP 端口号，默认为8089
    int udp_port = 8089;
    // 串口波特率，默认为115200
    int serial_baudrate = 115200;
    // 激光扫描数据的参考帧
    std::string frame_id;
    // 激光数据是否反转
    bool inverted = false;
    // 是否进行角度补偿
    bool angle_compensate = true;
    // 最大测量距离
    float max_distance = 8.0;
    // 角度补偿的倍数，表示每1度进行一次补偿
    size_t angle_compensate_multiple = 1;//it stand of angle compensate at per 1 degree
    // 扫描模式
    std::string scan_mode;
    // 扫描频率
    float scan_frequency;
    // 是否启用智能控制
    bool smart_control = false;
    // 激光雷达驱动接口指针
    ILidarDriver * drv;    
};
/**
 * 信号处理函数，用于设置退出标志
 * @param sig 接收到的信号编号，这里未使用
 * 此函数被设计为一个信号处理函数，当程序接收到特定信号时，它会将全局变量need_exit设置为true
 * 表明程序需要退出这是通过修改全局变量need_exit来实现的，该变量的作用是通知程序的其他部分
 * 准备退出程序这个函数的设计遵循了信号处理函数的一般原则，即尽快返回，避免进行复杂操作
 */
void ExitHandler(int sig)
{
    // 忽略传入的信号编号，防止未使用变量编译器警告
    (void)sig;
    // 设置需要退出的标志为true
    need_exit = true;
}


int main(int argc, char * argv[])
{
    // 初始化ROS 2客户端库
    rclcpp::init(argc, argv); 
    // 创建SLlidarNode对象
    auto sllidar_node = std::make_shared<SLlidarNode>();
    // 设置信号中断处理函数
    signal(SIGINT,ExitHandler);
    // 进入主循环
    int ret = sllidar_node->work_loop();
    // 关闭ROS 2客户端库
    rclcpp::shutdown();
    return ret;
}

