import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

x_data = np.linspace(-0.5,0.5,200)[:,np.newaxis]
noise = np.random.normal(0,0.02,x_data.shape)
y_data = np.square(x_data) +noise

x = tf.placeholder(tf.float32,[None,1])
y = tf.placeholder(tf.float32,[None,1])

W1 = tf.Variable(tf.random_normal([1,10]))
b1 = tf.Variable(tf.zeros([1,10]))

wx_plus_b1 = tf.matmul(x,W1)+b1
l1 = tf.nn.tanh(wx_plus_b1)

w2 = tf.Variable(tf.random_normal([10,1]))
b2 = tf.Variable(tf.zeros([1,1]))

wx_plus_b2 = tf.matmul(l1,w2) +b2
predict = tf.nn.tanh(wx_plus_b2)

loss = tf.reduce_mean(tf.square(y-predict))

train = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

with tf.Session() as sess:
    predict_y = None
    sess.run(tf.global_variables_initializer())
    for i in range(2000):
        sess.run(train,feed_dict={x:x_data,y:y_data})

    predict_y = sess.run(predict,feed_dict={x:x_data})
    plt.figure()
    plt.scatter(x_data,y_data)
    plt.plot(x_data,predict_y,'b',lw = 5)
    plt.show()