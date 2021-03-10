from math import log
import numpy as np
import random as rd
class node:
    #树的节点的类
    def __init__(self, fea=-1, value=None, results=None, right=None, left=None):
        self.fea = fea  # 用于切分数据集的属性的列索引值
        self.value = value  # 设置划分的值
        self.results = results  # 存储叶节点所属的类别
        self.right = right  # 右子树
        self.left = left  # 左子树
def random_forest_training(data_train, trees_num):
    #构建随机森林
    #data_train(list):训练数据
    #trees_num(int):分类树的个数
    #trees_result(list):每一棵树的最好划分
    #trees_feature(list):每一棵树中对原始特征的选择
    trees_result = []  # 构建好每一棵树的最好划分
    trees_feature = []
    n = np.shape(data_train)[1]  # 样本的维数
    if n > 2:
        k = int(log(n - 1, 2)) + 1  # 设置特征的个数
    else:
        k = 1
    # 开始构建每一棵树
    for i in range(trees_num):
        # 1、随机选择m个样本, k个特征
        data_samples, feature = choose_samples(data_train, k)
        # 2、构建每一棵分类树
        tree = build_tree(data_samples)
        # 3、保存训练好的分类树
        trees_result.append(tree)
        # 4、保存好该分类树使用到的特征
        trees_feature.append(feature)

    return trees_result, trees_feature
def cal_gini_index(data):
    #计算给定数据集的Gini指数
    total_sample = len(data)  # 样本的总个数
    if len(data) == 0:
        return 0
    label = []
    # 统计数据集中不同标签的个数
    for i in range(total_sample):
        label.append(data[0])
    label_counts=list(set(label))
    # 计算数据集的Gini指数
    gini = 0
    for label in label_counts:
        gini = gini + pow(label_counts[label], 2)
    gini = 1 - float(gini) / pow(total_sample, 2)
    return gini
def split_tree(data, fea, value):
    #根据特征fea中的值value将数据集data划分成左右子树
    #data(list):数据集
    #fea(int):待分割特征的索引
     #value(float):待分割的特征的具体值
    #(set1,set2)(tuple):分割后的左右子树
    set_1 = []
    set_2 = []
    for x in data:
        if x[fea] >= value:
            set_1.append(x)
        else:
            set_2.append(x)
    return (set_1, set_2)
def choose_samples(data, k):
    #data(list):原始数据集
    #k(int):选择特征的个数
    # data_samples(list):被选择出来的样本
    #feature(list):被选择的特征index
    m, n = np.shape(data)  # 样本的个数和样本特征的个数
    # 1、选择出k个特征的index
    feature = []
    for j in range(k):
        feature.append(rd.randint(0, n - 2))  # n-1列是标签
    # 2、选择出m个样本的index
    index = []
    for i in range(m):
        index.append(rd.randint(0, m - 1))
    # 3、从data中选择出m个样本的k个特征，组成数据集data_samples
    data_samples = []
    for i in range(m):
        data_tmp = []
        for fea in feature:
            data_tmp.append(data[index[i]][fea])
        data_tmp.append(data[index[i]][-1])
        data_samples.append(data_tmp)
    return data_samples, feature


def build_tree(data):
    #构建树
    #data(list):训练样本
    #node:树的根结点
    # 1、计算当前的Gini指数
    currentGini = cal_gini_index(data)

    bestGain = 0.0
    bestCriteria = None  # 存储最佳切分属性以及最佳切分点
    bestSets = None  # 存储切分后的两个数据集

    feature_num = len(data[0]) - 1  # 样本中特征的个数
    # 2、找到最好的划分
    for fea in range(0, feature_num):
        # 2.1、取得fea特征处所有可能的取值
        feature_values = {}  # 在fea位置处可能的取值
        for sample in data:  # 对每一个样本
            feature_values[sample[fea]] = 1  # 存储特征fea处所有可能的取值

        # 2.2、针对每一个可能的取值，尝试将数据集划分，并计算Gini指数
        for value in feature_values.keys():  # 遍历该属性的所有切分点
            # 2.2.1、 根据fea特征中的值value将数据集划分成左右子树
            (set_1, set_2) = split_tree(data, fea, value)
            # 2.2.2、计算当前的Gini指数
            nowGini = float(len(set_1) * cal_gini_index(set_1) +
                            len(set_2) * cal_gini_index(set_2)) / len(data)
            # 2.2.3、计算Gini指数的增加量
            gain = currentGini - nowGini
            # 2.2.4、判断此划分是否比当前的划分更好
            if gain > bestGain and len(set_1) > 0 and len(set_2) > 0:
                bestGain = gain
                bestCriteria = (fea, value)
                bestSets = (set_1, set_2)

    # 3、判断划分是否结束
    if bestGain > 0:
        right = build_tree(bestSets[0])
        left = build_tree(bestSets[1])
        return node(fea=bestCriteria[0], value=bestCriteria[1],
                    right=right, left=left)
    else:
        return node(results=data[0])  # 返回当前的类别标签作为最终的类别标