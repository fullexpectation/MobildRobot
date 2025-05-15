import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseWithCovarianceStamped
import csv
import os
from datetime import datetime

class AmclPoseRecorder(Node):
    def __init__(self):
        super().__init__('amcl_pose_recorder')
        self.subscription = self.create_subscription(
            PoseWithCovarianceStamped,
            '/amcl_pose',
            self.listener_callback,
            10)
        
        # 自动创建 CSV 文件
        now = datetime.now().strftime("%Y%m%d_%H%M%S")
        self.filename = f"amcl_pose_{now}.csv"
        self.file = open(self.filename, 'w', newline='')
        self.writer = csv.writer(self.file)
        self.writer.writerow(["time", "x", "y", "yaw"])
        self.get_logger().info(f"Recording to {self.filename}")

    def listener_callback(self, msg):
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y

        # 四元数转 yaw 角
        import math
        q = msg.pose.pose.orientation
        siny_cosp = 2.0 * (q.w * q.z + q.x * q.y)
        cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z)
        yaw = math.atan2(siny_cosp, cosy_cosp)

        t = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
        self.writer.writerow([t, x, y, yaw])

    def destroy_node(self):
        self.file.close()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = AmclPoseRecorder()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('Keyboard interrupt, exiting...')
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
