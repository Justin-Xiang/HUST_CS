import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
class CART():
    def __init__(self):
        pass

    def err(self,dataSet):
        # return sum((dataSet[:,-1]- dataSet[:,-1].mean())**2) # 最原始的写法
        return np.var(dataSet[:, -1]) * dataSet.shape[0]  # 均方差*数据总条数

    # 划分数据集，按出入的数据列fea，数据值value将数据划分为两部分
    def splitDataSet(self,dataSet, fea, value):
        dataSet1 = dataSet[dataSet[:, fea] <= value]
        dataSet2 = dataSet[dataSet[:, fea] > value]
        return dataSet1, dataSet2

    # 选择最好的特征划分数据集，min_sample每次划分后每部分最少的数据条数，epsilon误差下降阈值，值越小划分的决策树越深
    def chooseBestFeature(self,dataSet, min_sample=4, epsilon=0.5):
        features = dataSet.shape[1] - 1  # x特征列数量
        sErr = CART.err(dataSet)  # 整个数据集的损失
        minErr = np.inf
        bestColumn = 0  # 划分最优列
        bestValue = 0  # 划分最优的值
        nowErr = 0  # 当前平方误差
        if len(np.unique(dataSet[:, -1].T.tolist())) == 1:  # 数据全是一类的情况下 返回
            return None, np.mean(dataSet[:, -1])
        for fea in range(1, features + 1):  # 按x特征列循环
            for row in range(0, dataSet.shape[0]):  # 遍历每行数据，寻找最优划分
                dataSet1, dataSet2 = CART.splitDataSet(dataSet, fea, dataSet[row, fea])  # 获得切分后的数据
                if len(dataSet1) < min_sample or len(dataSet2) < min_sample:  # 按行遍历时总会有一些划分得到的集合不满足最小数据条数约束，跳过此类划分
                    continue
                nowErr = CART.err(dataSet1) + CART.err(dataSet2)  # 计算当前划分的平方误差
                if nowErr < minErr:  # 判断获得最优切分值
                    minErr = nowErr
                    bestColumn = fea
                    bestValue = dataSet[row, fea]
        if (sErr - minErr) < epsilon:  # 当前误差下降较小时，返回
            return None, np.mean(dataSet[:, -1])
        # 当前最优划分集合
        dataSet1, dataSet2 = CART.splitDataSet(dataSet, bestColumn, bestValue)
        if len(dataSet1) < min_sample or len(dataSet2) < min_sample:  # 如果划分的数据集很小，返回
            return None, np.mean(dataSet[:, -1])
        return bestColumn, bestValue

    def createTree(self,dataSet):
        bestColumn, bestValue = CART.chooseBestFeature(dataSet)
        if bestColumn == None:  # 所有列均遍历完毕，返回
            return bestValue
        retTree = {}  # 决策树
        retTree['spCol'] = bestColumn  # 最优分割列
        retTree['spVal'] = bestValue  # 最优分割值
        lSet, rSet = CART.splitDataSet(dataSet, bestColumn, bestValue)  # 按当前最优分割列级值划分为左右2枝
        retTree['left'] = CART.createTree(lSet)  # 迭代继续划分左枝
        retTree['right'] = CART.createTree(rSet)  # 迭代继续划分右枝
        return retTree

