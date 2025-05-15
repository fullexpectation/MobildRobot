

#include "sl_lidar_driver.h"
#include "hal/abs_rxtx.h"
#include "hal/socket.h"

// 声明命名空间sl
namespace sl {
     // 定义SerialPortChannel类，继承自ISerialPortChannel接口
    class SerialPortChannel : public ISerialPortChannel
    {
    public:
    // 构造函数，初始化串口设备路径和波特率
        SerialPortChannel(const std::string& device, int baudrate) :_rxtxSerial(rp::hal::serial_rxtx::CreateRxTx())
        {
            _device = device;
            _baudrate = baudrate;
        }
        // 析构函数，释放资源
        ~SerialPortChannel()
        {
            if (_rxtxSerial)
                delete _rxtxSerial;
        }
        // 绑定串口设备和波特率
        bool bind(const std::string& device, sl_s32 baudrate)
        {
            _closePending = false;
            return _rxtxSerial->bind(device.c_str(), baudrate);
        }
        // 打开串口
        bool open()
        {
            if(!bind(_device, _baudrate))
                return false;
            return _rxtxSerial->open();
        }
        // 关闭串口
        void close()
        {
            _closePending = true;
            _rxtxSerial->cancelOperation();
            _rxtxSerial->close();
        }
        // 清空串口缓冲区
        void flush()
        {
            _rxtxSerial->flush(0);
        }
        // 等待数据到达
        sl_result waitForDataExt(size_t& size_hint, sl_u32 timeoutInMs)
        {
            _word_size_t result;
            size_t size_holder;
            size_hint = 0;

            if (_closePending) return  RESULT_OPERATION_TIMEOUT;

            if (!_rxtxSerial->isOpened()) {
                return RESULT_OPERATION_FAIL;
            }

            result = _rxtxSerial->waitfordata(1, timeoutInMs, &size_holder);
            size_hint = size_holder;
            if (result == (_word_size_t)rp::hal::serial_rxtx::ANS_DEV_ERR)
                return RESULT_OPERATION_FAIL;
            if (result == (_word_size_t)rp::hal::serial_rxtx::ANS_TIMEOUT)
                return RESULT_OPERATION_TIMEOUT;

            return RESULT_OK;
        }
        // 等待指定数量的数据到达
        bool waitForData(size_t size, sl_u32 timeoutInMs, size_t* actualReady)
        {
            if (_closePending) return false;
            return (_rxtxSerial->waitfordata(size, timeoutInMs, actualReady) == rp::hal::serial_rxtx::ANS_OK);
        }
        // 写数据到串口
        int write(const void* data, size_t size)
        {
           return _rxtxSerial->senddata((const sl_u8 * )data, size);
        }
        // 从串口读数据
        int read(void* buffer, size_t size)
        {
            size_t lenRec = 0;
            lenRec = _rxtxSerial->recvdata((sl_u8 *)buffer, size);
            return (int)lenRec;
        }
        // 清空读缓存
        void clearReadCache()
        {
           
        }
        // 设置DTR信号
        void setDTR(bool dtr)
        {
            dtr ? _rxtxSerial->setDTR() : _rxtxSerial->clearDTR();
            // printf("Set DTR \r\n");
        }
        // 获取通道类型
        int getChannelType() {
            return CHANNEL_TYPE_SERIALPORT;
        }

    private:
        rp::hal::serial_rxtx  * _rxtxSerial; // 串口通信对象
        bool _closePending; // 标记是否待关闭
        std::string _device; // 设备路径
        int _baudrate; // 波特率

    };
    // 创建串口通道
    Result<IChannel*> createSerialPortChannel(const std::string& device, int baudrate)
    {
        return new  SerialPortChannel(device, baudrate);
    }

}