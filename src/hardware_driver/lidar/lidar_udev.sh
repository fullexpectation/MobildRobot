#!/bin/bash
# 该脚本的主要功能是配置udev规则以识别特定的USB设备，并为这些设备设置权限和符号链接，最后重新加载和重启udev服务以应用更改。
echo  'KERNEL=="ttyUSB*", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE:="0777", SYMLINK+="lidar"' >/etc/udev/rules.d/lidar_cp210x.rules
echo  'KERNEL=="ttyUSB*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE:="0777", SYMLINK+="lidar"' >/etc/udev/rules.d/lidar_ch34x.rules
echo  'KERNEL=="ttyACM*", ATTRS{idVendor}=="2e3c", ATTRS{idProduct}=="5740", MODE:="0777", GROUP:="dialout",  SYMLINK+="lidar"' >/etc/udev/rules.d/nvilidar_usb.rules

systemctl daemon-reload
service udev reload
sleep 1
service udev restart