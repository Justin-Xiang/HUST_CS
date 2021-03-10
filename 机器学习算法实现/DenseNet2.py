from tensorflow.contrib.learn.python.learn.datasets.mnist import read_data_sets
import tensorflow as tf


def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.01)
    return tf.Variable(initial)


def bias_variable(shape):
    initial = tf.constant(0.01, shape=shape)
    return tf.Variable(initial)


def conv2d(input, in_features, out_features, kernel_size, with_bias=False):
    W = weight_variable([kernel_size, kernel_size, in_features, out_features])
    conv = tf.nn.conv2d(input, W, [1, 1, 1, 1], padding='SAME')
    if with_bias:
        return conv + bias_variable([out_features])
    return conv


def avg_pool(input, s):
    return tf.nn.avg_pool(input, [1, s, s, 1], [1, s, s, 1], 'SAME')


def batch_activ_conv(current, in_features, out_features, kernel_size, is_training, keep_prob):
    current = tf.contrib.layers.batch_norm(current, scale=True, is_training=is_training, updates_collections=None)
    current = tf.nn.relu(current)
    current = conv2d(current, in_features, out_features, kernel_size)
    current = tf.nn.dropout(current, keep_prob)
    return current


# 定义稠密神经网络的稠密块
def block(input, layers, in_features, growth, is_training, keep_prob):
    current = input
    features = in_features
    for idx in range(layers):
        tmp = batch_activ_conv(current, features, growth, 3, is_training, keep_prob)
        current = tf.concat((current, tmp), axis=3)
        features += growth
    return current, features


mnist = read_data_sets("MNIST_data/", one_hot=True)

inputs_ = tf.placeholder(tf.float32, (None, 28, 28, 1), name='inputs_')
y = tf.placeholder(tf.float32, [None, 10])

keep_prob = tf.placeholder(tf.float32)
# is_training = tf.placeholder("bool", shape=[])
is_training = True
sess = tf.InteractiveSession()

x = tf.reshape(inputs_, (-1, 28, 28, 1))
conv1 = conv2d(x, 1, 16, 3)
# 这里操作后变成28*28*16
current, features = block(conv1, layers=4, in_features=16, growth=12, is_training=is_training, keep_prob=keep_prob)
current = batch_activ_conv(current, features, features, 1, is_training=is_training, keep_prob=keep_prob)
current = avg_pool(current, 2)

current, features = block(current, layers=4, in_features=features, growth=12, is_training=is_training,
                          keep_prob=keep_prob)
current = batch_activ_conv(current, features, features, 1, is_training=is_training, keep_prob=keep_prob)
current = avg_pool(current, 2)

current, features = block(current, layers=4, in_features=features, growth=12, is_training=is_training,
                          keep_prob=keep_prob)
current = tf.contrib.layers.batch_norm(current, scale=True, is_training=is_training, updates_collections=None)
current = tf.nn.relu(current)
# current = avg_pool(current, 8)
current = avg_pool(current, 2)
final_dim = features
label_count = 1024
flat = tf.reshape(current, [-1, 4 * 4 * final_dim])
Wfc = weight_variable([4 * 4 * final_dim, label_count])
bfc = bias_variable([label_count])

h_fc1 = tf.nn.relu(tf.matmul(flat, Wfc) + bfc)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)
w_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])

ys_ = tf.matmul(h_fc1_drop, w_fc2) + b_fc2

# 建立损失函数，在这里采用交叉熵函数
cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y, logits=ys_))

train_step = tf.train.AdamOptimizer(1e-3).minimize(cross_entropy)
correct_prediction = tf.equal(tf.argmax(ys_, 1), tf.argmax(y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
# 初始化变量

sess.run(tf.global_variables_initializer())

print("start")
for i in range(2000):
    batch = mnist.train.next_batch(100)
    input = batch[0].reshape((-1, 28, 28, 1))
    if i % 100 == 0:
        train_accuracy = accuracy.eval(feed_dict={
            inputs_: input, y: batch[1], keep_prob: 1.0})
        print("step %d, training accuracy %g" % (i, train_accuracy))
    train_step.run(feed_dict={x: input, y: batch[1], keep_prob: 1.0})
