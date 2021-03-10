import tensorflow  as tf

y = tf.constant(3, dtype=tf.float32)
x = tf.placeholder(dtype=tf.float32)
W = tf.Variable(2, dtype=tf.float32)

p = W * x

loss = tf.square(p - y)
g = tf.gradients(loss, W)
Beita = 0.8
LR = tf.constant(0.01, dtype=tf.float32)

init = tf.group(tf.global_variables_initializer(), tf.local_variables_initializer())

update = tf.train.MomentumOptimizer(LR, Beita).minimize(loss)

with tf.Session() as sess:
    sess.run(init)
    sess.run(tf.global_variables_initializer())
    sess.run(tf.local_variables_initializer())
    print(sess.run([g, p, W], {x: 1}))
    for i in range(100):
        _W, _g, _loss = sess.run([W, g, loss], feed_dict={x: 1})
        print("variable is W:", _W, "g is:", _g, "loss is:", _loss)

        sess.run([update], feed_dict={x: 1})
