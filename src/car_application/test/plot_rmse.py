import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 加载数据
odom_df = pd.read_csv('pose_record_20250513_184953.csv')
amcl_df = pd.read_csv('amcl_pose_20250513_184959.csv')

# 对AMCL轨迹插值，使其时间戳对齐到里程计时间
interp_amcl = pd.DataFrame()
interp_amcl['time'] = odom_df['time']
interp_amcl['x'] = np.interp(odom_df['time'].values, amcl_df['time'].values, amcl_df['x'].values)
interp_amcl['y'] = np.interp(odom_df['time'].values, amcl_df['time'].values, amcl_df['y'].values)

# 计算RMSE
rmse = np.sqrt(np.mean((odom_df['x'].values - interp_amcl['x'].values)**2 + (odom_df['y'].values - interp_amcl['y'].values)**2))
print(f"RMSE误差: {rmse:.3f} 米")

# 绘图
plt.figure(figsize=(10, 8))
plt.plot(odom_df['x'].values, odom_df['y'].values, '-o', color='blue', markersize=2, label='Odometry')
plt.plot(interp_amcl['x'].values, interp_amcl['y'].values, '-o', color='green', markersize=2, label='AMCL (Interpolated)')
plt.title(f"AMCL与里程计轨迹对比图（RMSE = {rmse:.3f} m）")
plt.xlabel("X 位置 (m)")
plt.ylabel("Y 位置 (m)")
plt.axis('equal')
plt.grid(True)
plt.legend()
plt.savefig("rmse_trajectory_comparison.png", dpi=300)
plt.show()
