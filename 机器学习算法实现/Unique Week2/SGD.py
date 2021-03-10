import tensorflow as tf

#定义一个变量用于计算滑动平均
v1 = tf.Variable(0,dtype=tf.float32)

#定义神经网络中迭代的轮数，用于动态控制衰减率
step = tf.Variable(0,trainable=False)

ema = tf.train.ExponentialMovingAverage(0.99,step)

#定义一个更新变量滑动平均的操作，每次执行这个操作，变量都会被更新
maintain_average_op = ema.apply([v1])

with tf.Session() as sess:
    #初始化所有变量
    init_op = tf.global_variables_initializer()
    sess.run(init_op)

    #获取滑动平均之后变量的值
    print(sess.run([v1,ema.average(v1)]))

    #更新v1到5
    sess.run(tf.assign(v1,5))
    #更新v1的滑动平均值
    sess.run(maintain_average_op)
    print(sess.run([v1,ema.average(v1)]))

    #更新step
    sess.run(tf.assign(step,10000))
    sess.run(tf.assign(v1,10))

    #更新滑动平均值
    sess.run(maintain_average_op)
    print(sess.run([v1,ema.average(v1)]))

    #再次更新
    sess.run(maintain_average_op)
    print(sess.run([v1,ema.average(v1)]))