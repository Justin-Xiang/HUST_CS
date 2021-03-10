import numpy as np
import pandas as pd
from numpy import dot

dataset = pd.read_csv('C:\\Users\\57105\\Desktop\\data.csv')  # 读入数据
X = dataset.iloc[:, 2: 5]  # x为所有行，2到4列
Y = dataset.iloc[:, 1]  # y为所有行，第1列
theta = np.array([1.0, 1.0, 1.0]).reshape(3, 1)  # theta初始值
alpha = 0.1  # 学习率
temp = theta
X0 = X.iloc[:, 0].values.reshape(60, 1)
X1 = X.iloc[:, 1].values.reshape(60, 1)
X2 = X.iloc[:, 2].values.reshape(60, 1)
Y = Y.values.reshape(60, 1)
for i in range(1000):  # 这里特别注意，在完成一次循环后，整体更新theta
    temp[0] = theta[0] + alpha * np.sum((Y - dot(X, theta)) * X0) / 60.0
    temp[1] = theta[1] + alpha * np.sum((Y - dot(X, theta)) * X1) / 60.0
    temp[2] = theta[2] + alpha * np.sum((Y - dot(X, theta)) * X2) / 60.0
    theta = temp
print(theta)
