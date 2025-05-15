import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseWithCovarianceStamped

import csv
from datetime import datetime
import os

class PoseRecorder(Node):
    def __init__(self):
        super().__init__('pose_recorder')

        # QoS Profile for Best Effort
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )

        # Set up CSV file
        timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
        self.filename = f'pose_record_{timestamp}.csv'
        self.file = open(self.filename, mode='w', newline='')
        self.writer = csv.writer(self.file)
        self.writer.writerow(['source', 'time', 'x', 'y', 'yaw'])

        # Subscriptions
        self.create_subscription(
            Odometry,
            '/odom',
            self.odom_callback,
            qos_profile
        )

        self.create_subscription(
            PoseWithCovarianceStamped,
            '/amcl_pose',
            self.amcl_callback,
            10  # AMCL 通常使用 Reliable，默认即可
        )

        self.get_logger().info(f'CSV 数据将保存到: {os.path.abspath(self.filename)}')

    def odom_callback(self, msg):
        time = self.get_clock().now().to_msg().sec + self.get_clock().now().to_msg().nanosec * 1e-9
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        yaw = self.get_yaw_from_quaternion(msg.pose.pose.orientation)
        self.writer.writerow(['odom', time, x, y, yaw])

    def amcl_callback(self, msg):
        time = self.get_clock().now().to_msg().sec + self.get_clock().now().to_msg().nanosec * 1e-9
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        yaw = self.get_yaw_from_quaternion(msg.pose.pose.orientation)
        self.writer.writerow(['amcl', time, x, y, yaw])

    def get_yaw_from_quaternion(self, q):
        # Convert quaternion to yaw
        import math
        siny_cosp = 2 * (q.w * q.z + q.x * q.y)
        cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z)
        return math.atan2(siny_cosp, cosy_cosp)

    def destroy_node(self):
        self.file.close()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = PoseRecorder()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('中断退出，关闭CSV文件')
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
