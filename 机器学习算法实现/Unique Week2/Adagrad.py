import tensorflow as tf

y = tf.constant(3,dtype = tf.float32)
x = tf.placeholder(dtype = tf.float32)
W = tf.Variable(2,dtype=tf.float32)

p=W *x

loss = tf.square(p-y)
g = tf.gradients(loss,W)
LR = tf.constant(0.6,dtype = tf.float32)
optimizer = tf.train.AdagradOptimizer(LR)
update = optimizer.minimize(loss)
init  = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)

    for i in range(20):
        _W,_loss,_g = sess.run([W,loss,g],feed_dict={x:1})
        print("variable is W:",_W,"g:",_g,"loss:",_loss)

        sess.run([update],feed_dict={x:1})