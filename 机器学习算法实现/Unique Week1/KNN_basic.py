# 库的引用
from numpy import *
import numpy as np
import random  # 用于生成随机测试数据
import operator
import matplotlib.pyplot as plt


# 封装KNN算法
class KNN:
    def __init__(self, k):
        self._dataset = None
        self._labelset = None
        self.k = k

    def collectdata(self, dataset, labelset):
        self._dataset = dataset
        self._labelset = labelset
        return self

    def predict(self, prediction):
        datasetsize = self._dataset.shape[0]  # 计算数据集行数
        vectordistance1 = tile(prediction, (datasetsize, 1)) - self._dataset  # 计算欧式距离
        vectordistance2 = vectordistance1 ** 2  # 平方
        sumdistance = vectordistance2.sum(axis=1)  # 每行相加
        distance = sumdistance ** 0.5  # 得欧氏距离
        sortdistance = distance.argsort()  # 返回从小到大的索引
        labelcount = {}
        for i in range(self.k):  # 统计前K个数据
            votelabel = self._labelset[sortdistance[i]]
            labelcount[votelabel] = labelcount.get(votelabel, 0) + 1
        sortedlabelcount = sorted(labelcount.items(), key=operator.itemgetter(1), reverse=True)  # 从大到小排序
        return sortedlabelcount[0][0]


def PCA(dataset, K):
    mean = np.array([np.mean(i) for i in dataset.T])  # 计算特征平均值
    centreMatrix = dataset - mean  # 得到中心化矩阵
    num = np.shape(centreMatrix)[0]  # 计算样本总数
    convarianceMatrix = np.dot(centreMatrix.T, centreMatrix) / (num - 1)  # 得到协方差矩阵
    feature, vectorfeature = np.linalg.eig(convarianceMatrix)  # 得到特征值和特征向量
    indexlist = np.argsort(-1 * feature)  # 得到降序的索引序列
    transMatrixT = [vectorfeature[:, indexlist[i]] for i in range(K)]
    transMatrix = np.transpose(transMatrixT)  # 得到转换矩阵
    targetMatrix = np.dot(dataset, transMatrix)  # 得到降维矩阵
    return targetMatrix


def datasetMatrix(filename):  # 格式化数据
    file = open(filename)
    MatrixLines = file.readlines()
    numLines = len(MatrixLines)
    targetMatrix = zeros((numLines, 4))  # 得到以零填充的矩阵
    labelVector = []
    index = 0
    for line in MatrixLines:
        line = line.strip()  # 删除所有回车符
        listLine = line.split(',')  # 删除所有逗号
        targetMatrix[index, :] = listLine[0:4]  # 存储特征的矩阵
        labelVector.append(listLine[-1])  # 存储label的矩阵
        index += 1
    return targetMatrix, labelVector


def iris_evaluate():
    totalsize = len(dataset)  # 得到整个数据集大小
    testlist = random.sample(range(1, totalsize + 1), 30)  # 随机生成30个测试数据
    n = 0
    for i in testlist:
        guess = KNNtest1.predict(dataset[i, :])
        fact = labelset[i]
        print("测试结果为%s,真实结果为%s" % (guess, fact))
        if guess == fact:  # 比较，进行评估
            n += 1.0
    accuracy = n / 30
    print("正确率为%f%%" % (100 * accuracy))


def irisshow(dataset):  # 可视化
    type1 = plt.scatter(dataset[:50, 0], dataset[0:50, 1], color='r', marker='o')
    type2 = plt.scatter(dataset[50:100, 0], dataset[50:100, 1], color='g', marker='x')
    type3 = plt.scatter(dataset[100:150, 0], dataset[100:150, 1], color='b', marker='+')
    plt.show()


# 导入数据集
dataset, labelset = datasetMatrix(r'C:\Users\DELL\Desktop\Unique Spring\iris.data')

# 选取K=3
KNNtest1 = KNN(3)
KNNtest1.collectdata(dataset, labelset)

# 进行评估
iris_evaluate()

# PCA降维
wantedMatrix = PCA(dataset, 2)
# 可视化
irisshow(wantedMatrix)
