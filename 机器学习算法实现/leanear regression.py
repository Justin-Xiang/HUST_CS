# -*- coding: utf-8 -*-
"""
Created on Thu Aug 30 09:40:50 2018
@author: 96jie
"""

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# 数据
num_points = 1000
vectors_set = []
for i in range(num_points):
    x1 = np.random.normal(0.0, 0.55)
    y1 = x1 * 0.1 + 0.3 + np.random.normal(0.0, 0.03)
    vectors_set.append([x1, y1])
x = [v[0] for v in vectors_set]
y = [v[1] for v in vectors_set]
# 随机生成theta
theta = tf.Variable(tf.random_uniform([2], -1, 1), name='theta')
# 计算损失
y11 = theta[0] * x + theta[1]
loss = tf.reduce_mean(tf.square(y11 - y), name='loss')
# 梯度下降
optimizer = tf.train.GradientDescentOptimizer(0.01)
# 训练得到最小梯度
train = optimizer.minimize(loss, name='train')

sess = tf.Session()
init = tf.global_variables_initializer()
sess.run(init)
# 迭代
for step in range(1000):
    sess.run(train)
print(sess.run(theta))

plt.figure(figsize=(35, 35))
plt.scatter(x, y, marker='o')
plt.plot(x, sess.run(y11))
plt.xticks(fontsize=40)
plt.yticks(fontsize=40)
plt.xlabel('特征X', fontsize=40)
plt.ylabel('Y', fontsize=40)
plt.title('结果', fontsize=40)
plt.savefig("tf结果.jpg")
plt.show()