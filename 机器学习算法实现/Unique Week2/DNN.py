import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
'''
参考教程：莫烦Python
'''
def add_layer(inputs,in_size,out_size,activation_function=None):
    with tf.name_scope('layer'):
        with tf.name_scope('weights'):
            Weights = tf.Variable(tf.random_normal([in_size,out_size]))
        with tf.name_scope('biases'):
            biases = tf.Variable(tf.zeros([1,out_size])+0.1)
        with tf.name_scope('Wx_plus_b'):
            Wx_plus_b = tf.matmul(inputs,Weights) + biases
        if activation_function is None:
            out_puts = Wx_plus_b
        else:
            out_puts = activation_function(Wx_plus_b)
        return out_puts

x_data = np.linspace(-1,1,300,dtype = np.float32)[:,np.newaxis]

#添加noise是为了模拟真实数据
noise = np.random.normal(0,0.05,x_data.shape).astype(np.float32)

y_data = np.square(x_data) - 0.5 +noise

with tf.name_scope('inputs'):
    xs = tf.placeholder(tf.float32,[None,1],name = 'x_input')
    ys = tf.placeholder(tf.float32,[None,1],name = 'y_input')



l1 = add_layer(xs,1,10,activation_function = tf.nn.relu)
prediction = add_layer(l1,10,1,activation_function=None)

with tf.name_scope('loss'):
    loss = tf.reduce_mean(tf.reduce_sum(tf.square(ys-prediction),reduction_indices=[1]))

with tf.name_scope('train_step'):
    train_step = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

init = tf.global_variables_initializer()


sess = tf.Session()

#这里是因为跟着教程使用了tensorboard可视化
writer = tf.summary.FileWriter('logs/',sess.graph)

sess.run(init)


for i in range(1000):
    sess.run(train_step,feed_dict={xs:x_data,ys:y_data})

    if i % 20 ==0:

        print(sess.run(loss,feed_dict={xs:x_data,ys:y_data}))





