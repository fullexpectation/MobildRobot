# 这是真实机器人的建图与导航操作（Ubuntu22.04的ROS2humble版本）
详情小车资料请见https://bingda.yuque.com/staff-hckvzc/uynkv1/fgkpmgrgm1zrtreq
## 1. Cartographer建图
```bash
ros2 launch robot_navigation_ros2 robot_lidar.launch.py 
```
```bash
ros2 launch robot_navigation_ros2 cartographer.launch.py
```
```bash
ros2 launch robot_navigation_ros2 rviz_slam.launch.py
```
保存地图
```bash
cd ~/ros2_ws/src/bingda_ros2_demos/robot_navigation_ros2/map/
ros2 run nav2_map_server map_saver_cli -f map
cd ~/ros2_ws/
colcon build --packages-select robot_navigation_ros2 --symlink-install
```
## 2. Navigation2
```bash
ros2 launch robot_navigation_ros2 robot_lidar.launch.py 
```
```bash
ros2 launch robot_navigation_ros2 navigation.launch.py
```
```bash
ros2 launch robot_navigation_ros2 rviz_navigation.launch.py
```
