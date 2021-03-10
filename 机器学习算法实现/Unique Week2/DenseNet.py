import tensorflow as tf
import tflearn

class DenseNet(object):
    def __init__(self,growth_rate_K,is_training,dropout_rate):
        self.growth_rate_K = growth_rate_K
        self.is_training = is_training
        self.dropout_rate = dropout_rate

    def BatchNormalization(self,x,is_training):
        return tf.layers.batch_normalization(x,training=is_training)

    def Conv2d(self,input, out_channel, kernel, stride=1):
        return tf.layers.conv2d(inputs=input, filters=out_channel, kernel_size=kernel, strides=stride, padding='SAME')

    def AvgPooling(self,input, pool_size=2, stride=2, padding='VALID'):
        return tf.layers.average_pooling2d(inputs=input, pool_size=pool_size, strides=stride, padding=padding)

    def MaxPooling(self,input, pool_size=2, stride=2, padding='VALID'):
        return tf.layers.max_pooling2d(inputs=input, pool_size=pool_size, strides=stride, padding=padding)

    def DropOut(self,x,dropout_rate,is_training):
        return tf.layers.dropout(x,rate=dropout_rate,training=is_training)

    def BottleneckLayer(self,input):
        layer1x1_BN = self.BatchNormalization(input,self.is_training)
        layer1x1_relu = tf.nn.relu(layer1x1_BN)
        layer1x1_conv = self.Conv2d(input=layer1x1_relu,out_channel=4 * self.growth_rate_K,kernel=1)
        layer1x1_dropout = self.DropOut(layer1x1_conv,dropout_rate=self.dropout_rate,is_training=self.is_training)

        layer3x3_BN = self.BatchNormalization(layer1x1_dropout,self.is_training)
        layer3x3_relu = tf.nn.relu(layer3x3_BN)
        layer3x3_conv = self.Conv2d(input=layer3x3_relu,out_channel=self.growth_rate_K,kernel=3)
        layer3x3_dropout = self.DropOut(layer3x3_conv,dropout_rate=self.dropout_rate,is_training=self.is_training)
        return layer3x3_dropout

    def CreateBlock(self,input,layers):
        all_features = [input]
        for i in range(layers):
            result = tf.concat(all_features,axis=3)
            result = self.BottleneckLayer(result)
            all_features.append(result)
        result = tf.concat(all_features,axis=3)
        return result

    def DenseNet121(self,inputX):
        input = self.Conv2d(inputX, out_channel=2 * self.growth_rate_K, kernel=7, stride=2)
        MaxPool3x3 = self.MaxPooling(input, pool_size=3, stride=2, padding='SAME')

        """Block_1"""
        block_1 = self.CreateBlock(MaxPool3x3, layers=6)
        block_1_conv = self.Conv2d(block_1, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_1_avg_pool = self.AvgPooling(block_1_conv, pool_size=2, stride=2)

        """Block_2"""
        block_2 = self.CreateBlock(block_1_avg_pool, 12)
        block_2_conv = self.Conv2d(block_2, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_2_avg_pool = self.AvgPooling(block_2_conv, pool_size=2, stride=2)

        """block_3"""
        block_3 = self.CreateBlock(block_2_avg_pool, 24)
        block_3_conv = self.Conv2d(block_3, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_3_avg_pool = self.AvgPooling(block_3_conv, pool_size=2, stride=2, padding='SAME')

        """Block_4"""
        block_4 = self.CreateBlock(block_3_avg_pool, 16)
        block_4_conv = self.Conv2d(block_4, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        Global_avg_pool = tflearn.layers.conv.global_avg_pool(block_4_conv)

        return Global_avg_pool

    def DenseNet169(self,inputX):
        input = self.Conv2d(inputX, out_channel=2 * self.growth_rate_K, kernel=7, stride=2)
        MaxPool3x3 = self.MaxPooling(input, pool_size=3, stride=2, padding='SAME')

        """Block_1"""
        block_1 = self.CreateBlock(MaxPool3x3, layers=6)
        block_1_conv = self.Conv2d(block_1, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_1_avg_pool = self.AvgPooling(block_1_conv, pool_size=2, stride=2)

        """Block_2"""
        block_2 = self.CreateBlock(block_1_avg_pool, 12)
        block_2_conv = self.Conv2d(block_2, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_2_avg_pool = self.AvgPooling(block_2_conv, pool_size=2, stride=2)

        """block_3"""
        block_3 = self.CreateBlock(block_2_avg_pool, 32)
        block_3_conv = self.Conv2d(block_3, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_3_avg_pool = self.AvgPooling(block_3_conv, pool_size=2, stride=2, padding='SAME')

        """Block_4"""
        block_4 = self.CreateBlock(block_3_avg_pool, 32)
        block_4_conv = self.Conv2d(block_4, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        Global_avg_pool = tflearn.layers.conv.global_avg_pool(block_4_conv)

        return Global_avg_pool

    def DenseNet201(self,inputX):
        input = self.Conv2d(inputX, out_channel=2 * self.growth_rate_K, kernel=7, stride=2)
        MaxPool3x3 = self.MaxPooling(input, pool_size=3, stride=2, padding='SAME')

        """Block_1"""
        block_1 = self.CreateBlock(MaxPool3x3, layers=6)
        block_1_conv = self.Conv2d(block_1, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_1_avg_pool = self.AvgPooling(block_1_conv, pool_size=2, stride=2)

        """Block_2"""
        block_2 = self.CreateBlock(block_1_avg_pool, 12)
        block_2_conv = self.Conv2d(block_2, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_2_avg_pool = self.AvgPooling(block_2_conv, pool_size=2, stride=2)

        """block_3"""
        block_3 = self.CreateBlock(block_2_avg_pool, 48)
        block_3_conv = self.Conv2d(block_3, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_3_avg_pool = self.AvgPooling(block_3_conv, pool_size=2, stride=2, padding='SAME')

        """Block_4"""
        block_4 = self.CreateBlock(block_3_avg_pool, 32)
        block_4_conv = self.Conv2d(block_4, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        Global_avg_pool = tflearn.layers.conv.global_avg_pool(block_4_conv)

        return Global_avg_pool

    def DenseNet264(self,inputX):
        input = self.Conv2d(inputX, out_channel=2 * self.growth_rate_K, kernel=7, stride=2)
        MaxPool3x3 = self.MaxPooling(input, pool_size=3, stride=2,padding='SAME')

        """Block_1"""
        block_1 = self.CreateBlock(MaxPool3x3,layers=6)
        block_1_conv = self.Conv2d(block_1, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_1_avg_pool = self.AvgPooling(block_1_conv, pool_size=2, stride=2)

        """Block_2"""
        block_2 = self.CreateBlock(block_1_avg_pool,12)
        block_2_conv = self.Conv2d(block_2, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_2_avg_pool = self.AvgPooling(block_2_conv, pool_size=2, stride=2)

        """block_3"""
        block_3 = self.CreateBlock(block_2_avg_pool,64)
        block_3_conv = self.Conv2d(block_3, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        block_3_avg_pool = self.AvgPooling(block_3_conv, pool_size=2, stride=2,padding='SAME')

        """Block_4"""
        block_4 = self.CreateBlock(block_3_avg_pool,48)
        block_4_conv = self.Conv2d(block_4, out_channel=2 * self.growth_rate_K, kernel=1, stride=1)
        Global_avg_pool = tflearn.layers.conv.global_avg_pool(block_4_conv)

        return Global_avg_pool

    def CreateNet(self):
        pass

import tensorflow as tf
old_v = tf.logging.get_verbosity()
tf.logging.set_verbosity(tf.logging.ERROR)
from tensorflow.examples.tutorials.mnist import input_data

def weights(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

mnist = input_data.read_data_sets('../MNIST_data', one_hot=True)
tf.logging.set_verbosity(old_v)

input_x = tf.placeholder(tf.float32,[None,28*28])
input_y = tf.placeholder(tf.float32,[None,10])
reshape = tf.reshape(input_x, [-1, 28, 28, 1])
training = tf.placeholder(tf.bool)
drouout = tf.placeholder(tf.float32)
y = DenseNet(growth_rate_K=16,is_training=training,dropout_rate=drouout).DenseNet169(reshape)

w_out = weights([int(y.shape[1]),10])
b_out = bias([10])
output = tf.matmul(y,w_out) + b_out

batch_size = 200
learning_rate = 1e-4
training_epoch = 100
total_batch = int(mnist.train.num_examples / batch_size)

cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=input_y, logits=output))

update_ops = tf.get_collection(tf.GraphKeys.UPDATE_OPS)
with tf.control_dependencies(update_ops):
    train_step = tf.train.AdamOptimizer(learning_rate).minimize(cross_entropy)

correct_prediction = tf.equal(tf.argmax(output, 1), tf.argmax(input_y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

saver = tf.train.Saver()
sess = tf.InteractiveSession()
sess.run(tf.global_variables_initializer())
saver.restore(sess,'./DenseNet_MNIST/model')

for epoch in range(training_epoch):
    test_dic = {
        input_x: mnist.test.images,
        input_y: mnist.test.labels,
        training: False,
        drouout: 0.2
    }
    test_accuracy = accuracy.eval(session=sess,
                                  feed_dict=test_dic)
    print('******\tepoch {}, testing accuracy: {}\t******'.format(epoch, test_accuracy))
    for i in range(total_batch):
        batch = mnist.train.next_batch(batch_size)
        train_dic = {
            input_x:batch[0],
            input_y:batch[1],
            training:True,
            drouout:0.2
        }
        train_step.run(session=sess, feed_dict=train_dic)
        if i % 100 == 0:
            cost = sess.run(cross_entropy,feed_dict=train_dic)
            print('After {} training , cost in train data: {}'.format(i,cost))