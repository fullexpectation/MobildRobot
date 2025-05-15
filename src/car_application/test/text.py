import pandas as pd

df = pd.read_csv("cmd_vel.csv", header=None, skiprows=1)
print(df.head(10))
print("\n列数：", df.shape[1])
