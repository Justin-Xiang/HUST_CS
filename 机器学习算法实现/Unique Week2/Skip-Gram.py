# 导入库
import collections
import math
import os
import random
import zipfile
import numpy as np
import urllib
import tensorflow as tf
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt



# 使用tf.compat.as_str将数据转成单词的列表
# 通过程序输出单词列表的长度
def read_data(filename):
    with zipfile.ZipFile(filename) as f:
        data = tf.compat.as_str(f.read(f.namelist()[0])).split()
    return data


words = read_data('D:\\tensorflow_datasets\\text8.zip')
print('Data size', len(words))

# 创建vocabulary词汇表
vocabulary_size = 50000


def built_dataset(words):
    count = [['UNK', -1]]
    # 使用collections.Counter统计单词列表中单词的频数
    # 使用most_common取top 50000频数的单词作为vocabulary
    count.extend(collections.Counter(words).most_common(vocabulary_size - 1))
    dictionary = dict()
    # 再创建一个dict将vocabulary放入dictionary中
    for word, _ in count:
        dictionary[word] = len(dictionary)
    data = list()
    unk_count = 0
    for word in words:
        # 遍历单词列表
        # 判断是否出现在dictionary中
        # 如果是则转换为其编号
        # 否则转为编号0
        if word in dictionary:
            index = dictionary[word]
        else:
            index = 0
            unk_count += 1
        data.append(index)
    # 最后返回转换后的编码，每个单词频数统计，词汇表及其反转的形式
    count[0][1] = unk_count
    reverse_dictionary = dict(zip(dictionary.values(), dictionary.keys()))
    return data, count, dictionary, reverse_dictionary


data, count, dictionary, reverse_dictionary = built_dataset(words)

# 删除原始单词列表以节约内存
del words

# 打印vocabulary中最高频出现的词汇及数量
print('Most common words (+UNK)', count[:5])
print('Sample data', data[:10], [reverse_dictionary[i] for i in data[:10]])

data_index = 0


# 定义函数generate_batch来生成训练用的batch数据
# batch_size为batch的大小
# num_skips为对每个单词生成多少个样本
# skip_window指单词最远可以联系的距离
# 且不能大于skip_window值的两倍
def generate_batch(batch_size, num_skips, skip_window):
    # 声明为全局变量使其可以再函数中被修改
    global data_index

    assert batch_size % num_skips == 0
    assert num_skips <= 2 * skip_window
    # 将batch和labels初始化为数组
    batch = np.ndarray(shape=(batch_size), dtype=np.int32)
    labels = np.ndarray(shape=(batch_size, 1), dtype=np.int32)
    # 定义span为某个单词创建相关样本时使用到的单词数量
    # 包括目标单词本身和它前后的单词
    span = 2 * skip_window + 1
    # 在对deque使用append添加变量时只会保留最后插入的span个变量
    buffer = collections.deque(maxlen=span)

    for _ in range(span):
        # 从data_index开始讲span个单词读入buffer
        buffer.append(data[data_index])
        data_index = (data_index + 1) % len(data)
    for i in range(batch_size // num_skips):
        # 循环生成样本
        target = skip_window
        targets_to_avoid = [skip_window]
        for j in range(num_skips):
            while target in targets_to_avoid:
                target = random.randint(0, span - 1)
            targets_to_avoid.append(target)
            batch[i * num_skips + j] = buffer[skip_window]
            labels[i * num_skips + j, 0] = buffer[target]
        buffer.append(data[data_index])
        data_index = (data_index + 1) % len(data)
    return batch, labels

#简单测试
batch, labels = generate_batch(batch_size=8, num_skips=2, skip_window=1)
for i in range(8):
    print(batch[i], reverse_dictionary[batch[i]], '->', labels[i, 0], reverse_dictionary[labels[i, 0]])


batch_size = 128
#embedding_size即将单词转为稠密变量的维度
embedding_size = 128
# skip_window设为1代表只能紧跟紧邻的两个单词生成样本
skip_window = 1
#num_skips即对每个目标单词提取的样本数，设为2
num_skips = 2
#生成验证数据
#valid_size指用来抽取的验证单词数
valid_size = 16
#valid_window指只从频数最高的100个单词中抽取
valid_window = 100
#进行随机抽取
valid_examples = np.random.choice(valid_window, valid_size, replace=False)
#作为负样本的噪音单词的数量
num_sampled = 64

graph = tf.Graph()
with graph.as_default():
    train_inputs = tf.placeholder(tf.int32, shape=[batch_size])
    train_labels = tf.placeholder(tf.int32, shape=[batch_size, 1])
    #将前面随机产生的valid_examples转为constant
    valid_dataset = tf.constant(valid_examples, dtype=tf.int32)
    #限定在cpu上执行
    with tf.device('/cpu:0'):
        #随机生成所有单词的词向量
        embeddings = tf.Variable(tf.random_uniform([vocabulary_size, embedding_size], -1.0, 1.0))
        embed = tf.nn.embedding_lookup(embeddings, train_inputs)
        #初始化权重参数和biases
        nce_weights = tf.Variable(
            tf.truncated_normal([vocabulary_size, embedding_size], stddev=1.0 / math.sqrt(embedding_size)))
        nce_biases = tf.Variable(tf.zeros([vocabulary_size]))
    #损失函数
    loss = tf.reduce_mean(tf.nn.nce_loss(weights=nce_weights, biases=nce_biases, labels=train_labels, inputs=embed,
                                         num_sampled=num_sampled, num_classes=vocabulary_size))
    optimizer = tf.train.GradientDescentOptimizer(1.0).minimize(loss)
    norm = tf.sqrt(tf.reduce_sum(tf.square(embeddings), 1, keep_dims=True))
    normalized_embeddings = embeddings / norm
    valid_embeddings = tf.nn.embedding_lookup(normalized_embeddings, valid_dataset)
    similarity = tf.matmul(valid_embeddings, normalized_embeddings, transpose_b=True)
    init = tf.global_variables_initializer()

num_steps = 100001

with tf.Session(graph=graph) as session:
    init.run()
    print("Initialized")

    average_loss = 0
    for step in range(num_steps):
        batch_inputs, batch_labels = generate_batch(batch_size, num_skips, skip_window)
        feed_dict = {train_inputs: batch_inputs, train_labels: batch_labels}

        _, loss_val = session.run([optimizer, loss], feed_dict=feed_dict)

        average_loss += loss_val
        #每两千次循环，计算一下平均loss
        if step % 2000 == 0:
            if step > 0:
                average_loss /= 2000
            print("Average loss at step", step, ":", average_loss)
            average_loss = 0
        #每10000次循环，计算一次验证单词与全部单词的相似度
        if step % 10000 == 0:
            sim = similarity.eval()
            for i in range(valid_size):
                valid_word = reverse_dictionary[valid_examples[i]]
                top_k = 8
                nearest = (-sim[i, :]).argsort()[1:top_k + 1]
                log_str = "Nearest to %s:" % valid_word
            for k in range(top_k):
                close_word = reverse_dictionary[nearest[k]]
                log_str = "%s %s," % (log_str, close_word)
            print(log_str)

    final_embeddings = normalized_embeddings.eval()

#定义一个可视化效果的函数
def plot_with_labels(low_dim_embs,labels,filename='result.png'):
    plt.figure(figsize =(18,18))
    for i , label in enumerate(labels):
        x , y = low_dim_embs[i,:]
        plt.scatter(x,y)
        plt.annotate(label,xy=(x,y),xytext = (5,2),textcoords='offset points',ha='right',va='bottom')
    plt.savefig(filename)


tsne = TSNE(perplexity=30,n_components=2,init='pca',n_iter=5000)
plot_only = 100
low_dim_embs = tsne.fit_transform(final_embeddings[:plot_only,:])
labels = [reverse_dictionary[i] for i in range(plot_only)]
plot_with_labels(low_dim_embs,labels)
