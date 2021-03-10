import tensorflow as tf
from numpy.random import RandomState

batch_size = 8
W1 = tf.Variable(tf.random_normal([2, 3], stddev=1, seed=1))
W2 = tf.Variable(tf.random_normal([3, 1], stddev=1, seed=1))

print("数据优化前：")
print("W1:",W1)
print("W2:",W2)
x = tf.placeholder(tf.float32, shape=(None, 2), name='x_input')

y_ = tf.placeholder(tf.float32, shape=(None, 1), name='y_input')

hidden = tf.matmul(x, W1)

out_put = tf.matmul(hidden, W2)

loss = -tf.reduce_mean(y_ * tf.log(tf.clip_by_value(out_put, 1e-10, 1.0)))

train_step = tf.train.AdamOptimizer(0.001).minimize(loss)

rdm = RandomState(1)
dataset_size = 128
X = rdm.rand(dataset_size, 2)
Y = [[int(x1 + x2 < 1)] for (x1, x2) in X]

with tf.Session() as sess:
    init_op = tf.global_variables_initializer()
    sess.run(init_op)
    print(sess.run(W1))
    print(sess.run(W2))
    STEPS = 5000
    for i in range(STEPS):
        start = (i * batch_size) % dataset_size
        end = min(start + batch_size, dataset_size)
        sess.run(train_step, feed_dict={x: X[start:end], y_: Y[start:end]})
        if i % 100 == 0:
            total_loss = sess.run(loss, feed_dict={x: X, y_: Y})
            print("After %d steps,loss is %g" % (i, total_loss))
    print("数据优化后：")
    print("W1:", sess.run(W1))
    print("W2:", sess.run(W2))
