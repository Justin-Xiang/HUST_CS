import numpy as np

X = np.mat([1, 2, 3]).reshape(3, 1)
Y = np.mat([5, 10, 15]).reshape(3, 1)
theta = 1
alpha = 0.1
for i in range(100):
    theta = theta + np.sum(alpha*(Y-np.dot(X,theta))*X.reshape(1,3))/3
print(theta)
