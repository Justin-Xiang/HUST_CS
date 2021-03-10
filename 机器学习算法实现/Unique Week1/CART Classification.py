# 引用库
import pandas as pd
import numpy as np
from collections import Counter
class CART():
    def __init__(self):
        pass

    def calcGini(self,dataSet):
        # 统计数据集中的label
        y_labels = []
        for i in range(len(dataSet)):
            y_labels.append(dataSet[i][0])
        y_counts = len(dataSet)
        y_p = {}
        gini = 1.0
        # 计算数据集中每一种label分类的概率
        for y_label in y_labels:
            y_p[y_label] = y_labels.count(y_label) / y_counts
        # 获得label中的唯一值
        labellist = set(y_labels)
        # 计算基尼值
        for label in labellist:
            gini -= y_p[label] ** 2
        return gini

    def splitDataSet(self,dataSet, i, value, types=1):
        subDataSet = []
        # 如果用该特征进行划分
        if types == 1:
            for data in dataSet:
                if data[i] == value:
                    subDataSet.append(data)
        # 如果用不等于value的进行划分
        else:
            for data in dataSet:
                if data[i] != value:
                    subDataSet.append(data)
        return subDataSet, len(subDataSet)

    def chooseBestFeature(self,dataSet, types='Gini'):
        # 计算数据集总数
        numtotal = len(dataSet)
        # 计算feature数
        numfeatures = len(dataSet[0]) - 1
        # 初始化参数
        bestfeature = -1
        # 初始化参数，计算每一列X的每一种特征的基尼指数
        columnfeagini = {}
        for i in range(1, numfeatures + 1):
            prob = {}
            featlist = [data[i] for data in dataSet]
            # 计算该列各特征的数量
            prob = dict(Counter(featlist))
            # 循环该列的特征
            for value in prob.keys():
                # 防止特殊情况的出现
                feaGini = 0.0
                bestflag = 1.000001
                # 获取划分后的数据
                subDataSet1, sublen1 = CART.splitDataSet(dataSet, i, value, 1)
                subDataSet2, sublen2 = CART.splitDataSet(dataSet, i, value, 2)
                # 判断按此特征划分gini值是否全为0
                if (sublen1 / numtotal) * CART(subDataSet1) == 0:
                    bestflag = 1
                feaGini += (sublen2 / numtotal) * CART(subDataSet1) + (sublen2 / numtotal) * CART((subDataSet2))
                columnfeagini["%d_%s" % (i, value)] = feaGini * bestflag
        # 找到最小的gini值所对应的数据
        bestfeature = min(columnfeagini, key=columnfeagini.get)
        return bestfeature, columnfeagini

    def createTree(self,dataSet, features, types='Gini'):
        all_label = []
        for i in range(len(dataSet)):
            all_label.append(dataSet[i][0])
        # 得到所有唯一的label
        y_label = list(set(all_label))
        # 若全为同一类，不需要再划分
        if len(y_label) == 1:
            return y_label[0]
        # 若为空，也不需要再划分
        elif len(dataSet[0]) == 1:
            lebelCount = {}
            labelCount = dict(Counter(y_label))
            return max(labelCount, key=labelCount.get)
        # 按CART算法计算特征集中各特征对特征集的gini，选择gini值最小的特征进行划分
        bestfeature, columnfeagini = CART.chooseBestFeature(dataSet, types)
        # 最佳特征
        bestfeaturelabel = features[int(bestfeature.split('_')[0])]
        # 构建树
        decisiontree = {bestfeaturelabel: {}}
        # 删去已经划分的feature
        del (features[int(bestfeature.split('_')[0])])
        y_label_split = []
        # 划分后分析哪一个属于叶节点
        for i in dataSet:
            if str(bestfeature.split('_')[1]) in i:
                y_label_split.append(i[0])
        print(y_label_split)
        y_labels_grp = dict(Counter(y_label_split))
        print(y_labels_grp)
        # 获得划分后概率最大的y分类
        y_leaf = max(y_labels_grp, key=y_labels_grp.get)
        # 设定左枝叶子值
        decisiontree[bestfeaturelabel][bestfeature.split('_')[1]] = y_leaf
        dataSetNew = np.delete(dataSet, int(bestfeature.split('_')[0]), axis=1)
        subfeatures = features[:]
        # CART数只能有两棵树
        y1 = y_label[0]
        y2 = y_label[1]
        if y_leaf == y1:
            decisiontree[bestfeaturelabel][y2] = {}
            decisiontree[bestfeaturelabel][y2] = CART.createTree(dataSetNew, subfeatures, types)
        elif y_leaf == y2:
            decisiontree[bestfeaturelabel][y1] = {}
            decisiontree[bestfeaturelabel][y1] = CART.createTree(dataSetNew, subfeatures, types)
        return decisiontree