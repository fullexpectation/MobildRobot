#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <math.h>

#define RAD2DEG(x) ((x)*180./M_PI)
/* 
 * 该函数用于处理接收到的激光扫描数据，并打印相关信息。
 * 包括帧ID、角度范围以及每个角度对应的测量距离。
*/
static void scanCb(sensor_msgs::msg::LaserScan::SharedPtr scan) {
  // 计算激光扫描数据点的数量
  int count = scan->scan_time / scan->time_increment;
  // 打印激光扫描的帧ID及数据点数量
  printf("[SLLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
  // 打印激光扫描的角度范围（从弧度转换为角度）
  printf("[SLLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min),
         RAD2DEG(scan->angle_max));
  // 遍历所有数据点，打印每个角度及其对应的测量距离
  for (int i = 0; i < count; i++) {
    float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
    printf("[SLLIDAR INFO]: angle-distance : [%f, %f]\n", degree, scan->ranges[i]);
  }
}

/**
 * 主函数，初始化ROS2节点并订阅激光扫描数据
 * 
 * 该函数完成以下任务：
 * 1. 初始化ROS2环境；
 * 2. 创建一个名为"sllidar_client"的节点；
 * 3. 订阅名为"scan"的激光扫描话题，并将回调函数设置为scanCb；
 * 4. 进入主循环，等待并处理消息；
 * 5. 在程序结束时关闭ROS2环境。
 * 
 * argc 命令行参数个数
 *  argv 命令行参数数组
 * 返回0表示正常退出
 */
int main(int argc, char **argv) {
  // 初始化ROS2环境
  rclcpp::init(argc, argv);
  // 创建ROS2节点
  auto node = rclcpp::Node::make_shared("sllidar_client");
  // 订阅激光扫描话题，指定回调函数为scanCb
  auto lidar_info_sub = node->create_subscription<sensor_msgs::msg::LaserScan>(
                        "scan", rclcpp::SensorDataQoS(), scanCb);
  // 进入主循环，等待并处理消息
  rclcpp::spin(node);
  // 关闭ROS2环境
  rclcpp::shutdown();


  return 0;
}
