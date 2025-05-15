import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# === 读取 CSV 文件 ===
df = pd.read_csv("pose_record_20250513_184953.csv")

# 修正列名空格问题
df.columns = df.columns.str.strip()

# === 筛选 odom 数据 ===
odom_df = df[df["source"] == "odom"]

# === 转换为浮点型以防万一 ===
odom_df["x"] = odom_df["x"].astype(float)
odom_df["y"] = odom_df["y"].astype(float)
odom_df["yaw"] = odom_df["yaw"].astype(float)

# === 绘图 ===
plt.figure(figsize=(8, 6))
plt.plot(odom_df["x"].values, odom_df["y"].values, '-o', color='blue', markersize=3, label='Odometry Trajectory')

# 加入朝向箭头
for i in range(0, len(odom_df), max(1, len(odom_df)//10)):
    x, y, yaw = odom_df.iloc[i][["x", "y", "yaw"]]
    dx = np.cos(yaw) * 0.1
    dy = np.sin(yaw) * 0.1
    plt.arrow(x, y, dx, dy, head_width=0.03, head_length=0.05, fc='red', ec='red')

plt.title("小车里程计轨迹图")
plt.xlabel("X 坐标 (m)")
plt.ylabel("Y 坐标 (m)")
plt.axis('equal')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("trajectory_plot.png", dpi=300)
plt.show()
