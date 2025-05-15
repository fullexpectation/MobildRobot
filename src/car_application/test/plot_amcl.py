import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ✅ 第一步：读取 CSV 文件
df = pd.read_csv("amcl_pose_20250513_184959.csv")  # 文件名换成你自己的

# ✅ 第二步：打印列名确保无误
print("列名：", df.columns)

# ✅ 第三步：清洗数据（去除NaN）
df = df.dropna(subset=["x", "y", "yaw"])

# ✅ 第四步：确保为浮点类型
df["x"] = df["x"].astype(float)
df["y"] = df["y"].astype(float)
df["yaw"] = df["yaw"].astype(float)

# ✅ 第五步：绘图
plt.figure(figsize=(8, 6))
plt.plot(df["x"].values, df["y"].values, '-o', color='green', markersize=2, label='AMCL Trajectory')

# ✅ 加方向箭头
for i in range(0, len(df), max(1, len(df)//20)):
    x = df["x"].iloc[i]
    y = df["y"].iloc[i]
    yaw = df["yaw"].iloc[i]
    dx = 0.1 * np.cos(yaw)
    dy = 0.1 * np.sin(yaw)
    plt.arrow(x, y, dx, dy, head_width=0.05, head_length=0.05, fc='red', ec='red')

plt.xlabel("X 位置 (m)")
plt.ylabel("Y 位置 (m)")
plt.title("AMCL 轨迹图")
plt.legend()
plt.grid()
plt.axis('equal')
plt.savefig("amcl_trajectory_plot.png", dpi=300)
plt.show()
