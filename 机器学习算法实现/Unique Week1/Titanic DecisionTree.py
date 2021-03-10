# 引用库
import pandas as pd
import random
import numpy as np
import matplotlib.pyplot as plt
from collections import Counter
# 计算基尼值
def calcGini(dataSet):
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


# 划分数据集
def splitDataSet(dataSet, i, value, types=1):
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


# 计算基尼指数，选择最好的特征
def chooseBestFeature(dataSet, types='Gini'):
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
            subDataSet1, sublen1 = splitDataSet(dataSet, i, value, 1)
            subDataSet2, sublen2 = splitDataSet(dataSet, i, value, 2)
            # 判断按此特征划分gini值是否全为0
            if (sublen1 / numtotal) * calcGini(subDataSet1) == 0:
                bestflag = 1
            feaGini += (sublen2 / numtotal) * calcGini(subDataSet1) + (sublen2 / numtotal) * calcGini((subDataSet2))
            columnfeagini["%d_%s" % (i, value)] = feaGini * bestflag
    # 找到最小的gini值所对应的数据
    bestfeature = min(columnfeagini, key=columnfeagini.get)
    return bestfeature, columnfeagini


def createTree(dataSet, features, types='Gini'):
    all_label = []
    for i in range(len(traindata)):
        all_label.append(traindata[i][0])
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
    bestfeature, columnfeagini = chooseBestFeature(dataSet, types)
    # 最佳特征
    bestfeaturelabel = features[int(bestfeature.split('_')[0])]
    # 构建树
    decisiontree = {bestfeaturelabel: {}}
    # 删去已经划分的feature
    del (features[int(bestfeature.split('_')[0])])
    y_label_split = []
    # 划分后分析哪一个属于叶节点
    for i in traindata:
        if str(bestfeature.split('_')[1]) in i:
            y_label_split.append(i[0])
    y_labels_grp = dict(Counter(y_label_split))
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
        decisiontree[bestfeaturelabel][y2] = createTree(dataSetNew, subfeatures, types)
    elif y_leaf==y2:
        decisiontree[bestfeaturelabel][y1] = {}
        decisiontree[bestfeaturelabel][y1] = createTree(dataSetNew, subfeatures, types)
    return decisiontree

'''
《机器学习实战》上的可视化树的函数
理解后就贴过来了
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
def getNumLeafs(myTree):
    # 初始化树的叶子节点个数
    numLeafs = 0
    # myTree.keys()获取树的非叶子节点'no surfacing'和'flippers'
    # list(myTree.keys())[0]获取第一个键名'no surfacing'
    firstStr = list(myTree.keys())[0]
    # 通过键名获取与之对应的值，即{0: 'no', 1: {'flippers': {0: 'no', 1: 'yes'}}}
    secondDict = myTree[firstStr]
    # 遍历树，secondDict.keys()获取所有的键
    for key in secondDict.keys():
        # 判断键是否为字典，键名1和其值就组成了一个字典，如果是字典则通过递归继续遍历，寻找叶子节点
        if type(secondDict[key]).__name__ == 'dict':
            numLeafs += getNumLeafs(secondDict[key])
        # 如果不是字典，则叶子结点的数目就加1
        else:
            numLeafs += 1
    # 返回叶子节点的数目
    return numLeafs


def getTreeDepth(myTree):
    # 初始化树的深度
    maxDepth = 0
    # 获取树的第一个键名
    firstStr = list(myTree.keys())[0]
    # 获取键名所对应的值
    secondDict = myTree[firstStr]
    # 遍历树
    for key in secondDict.keys():
        # 如果获取的键是字典，树的深度加1
        if type(secondDict[key]).__name__ == 'dict':
            thisDepth = 1 + getTreeDepth(secondDict[key])
        else:
            thisDepth = 1
        # 去深度的最大值
        if thisDepth > maxDepth: maxDepth = thisDepth
    # 返回树的深度
    return maxDepth


# 设置画节点用的盒子的样式
decisionNode = dict(boxstyle="sawtooth", fc="0.8")
leafNode = dict(boxstyle="round4", fc="0.8")
# 设置画箭头的样式    http://matplotlib.org/api/patches_api.html#matplotlib.patches.FancyArrowPatch
arrow_args = dict(arrowstyle="<-")


# 绘图相关参数的设置
def plotNode(nodeTxt, centerPt, parentPt, nodeType):
    # annotate函数是为绘制图上指定的数据点xy添加一个nodeTxt注释
    # nodeTxt是给数据点xy添加一个注释，xy为数据点的开始绘制的坐标,位于节点的中间位置
    # xycoords设置指定点xy的坐标类型，xytext为注释的中间点坐标，textcoords设置注释点坐标样式
    # bbox设置装注释盒子的样式,arrowprops设置箭头的样式
    
    figure points:表示坐标原点在图的左下角的数据点
    figure pixels:表示坐标原点在图的左下角的像素点
    figure fraction：此时取值是小数，范围是([0,1],[0,1]),在图的左下角时xy是（0,0），最右上角是(1,1)
    其他位置是按相对图的宽高的比例取最小值
    axes points : 表示坐标原点在图中坐标的左下角的数据点
    axes pixels : 表示坐标原点在图中坐标的左下角的像素点
    axes fraction : 与figure fraction类似，只不过相对于图的位置改成是相对于坐标轴的位置
    createPlot.ax1.annotate(nodeTxt, xy=parentPt, \
                            xycoords='axes fraction', xytext=centerPt, textcoords='axes fraction', \
                            va="center", ha="center", bbox=nodeType, arrowprops=arrow_args)


# 绘制线中间的文字(0和1)的绘制
def plotMidText(cntrPt, parentPt, txtString):
    xMid = (parentPt[0] - cntrPt[0]) / 2.0 + cntrPt[0]  # 计算文字的x坐标
    yMid = (parentPt[1] - cntrPt[1]) / 2.0 + cntrPt[1]  # 计算文字的y坐标
    createPlot.ax1.text(xMid, yMid, txtString)


# 绘制树
def plotTree(myTree, parentPt, nodeTxt):
    # 获取树的叶子节点
    numLeafs = getNumLeafs(myTree)
    # 获取树的深度
    depth = getTreeDepth(myTree)
    # firstStr = myTree.keys()[0]
    # 获取第一个键名
    firstStr = list(myTree.keys())[0]
    # 计算子节点的坐标
    cntrPt = (plotTree.xoff + (1.0 + float(numLeafs)) / 2.0 / plotTree.totalW, \
              plotTree.yoff)
    # 绘制线上的文字
    plotMidText(cntrPt, parentPt, nodeTxt)
    # 绘制节点
    plotNode(firstStr, cntrPt, parentPt, decisionNode)
    # 获取第一个键值
    secondDict = myTree[firstStr]
    # 计算节点y方向上的偏移量，根据树的深度
    plotTree.yoff = plotTree.yoff - 1.0 / plotTree.totalD
    for key in secondDict.keys():
        if type(secondDict[key]).__name__ == 'dict':
            # 递归绘制树
            plotTree(secondDict[key], cntrPt, str(key))
        else:
            # 更新x的偏移量,每个叶子结点x轴方向上的距离为 1/plotTree.totalW
            plotTree.xoff = plotTree.xoff + 1.0 / plotTree.totalW
            # 绘制非叶子节点
            plotNode(secondDict[key], (plotTree.xoff, plotTree.yoff), \
                     cntrPt, leafNode)
            # 绘制箭头上的标志
            plotMidText((plotTree.xoff, plotTree.yoff), cntrPt, str(key))
    plotTree.yoff = plotTree.yoff + 1.0 / plotTree.totalD


# 绘制决策树，inTree的格式为{'no surfacing': {0: 'no', 1: {'flippers': {0: 'no', 1: 'yes'}}}}


def createPlot(inTree):
    # 新建一个figure设置背景颜色为白色
    fig = plt.figure(1, facecolor='white')
    # 清除figure
    fig.clf()
    axprops = dict(xticks=[], yticks=[])
    # 创建一个1行1列1个figure，并把网格里面的第一个figure的Axes实例返回给ax1作为函数createPlot()
    # 的属性，这个属性ax1相当于一个全局变量，可以给plotNode函数使用
    createPlot.ax1 = plt.subplot(111, frameon=False, **axprops)
    # 获取树的叶子节点
    plotTree.totalW = float(getNumLeafs(inTree))
    # 获取树的深度
    plotTree.totalD = float(getTreeDepth(inTree))
    # 节点的x轴的偏移量为-1/plotTree.totlaW/2,1为x轴的长度，除以2保证每一个节点的x轴之间的距离为1/plotTree.totlaW*2
    plotTree.xoff = -0.5 / plotTree.totalW
    plotTree.yoff = 1.0
    plotTree(inTree, (0.5, 1.0), '')
    plt.show()
'''
# 同样的，对泰坦尼克数据集进行处理
# 因为CART是二叉树，所以随便笼统的归为2类
# 所以准确度比较低
def cleantraintitanic(filename):
    data_raw = pd.read_csv(filename)
    data_list = data_raw.values.tolist()
    print(data_list)
    for i in range(len(data_list)):
        # 删掉ID
        del (data_list[i][0])
        # 删掉name
        del (data_list[i][2])
        # 将兄弟姐妹与配偶的数量相加
        data_list[i][4] += data_list[i][5]
        # 删掉后一项
        del (data_list[i][5])
        # 删掉Ticket
        del (data_list[i][5])
        # 删掉Cabin
        del (data_list[i][-2])
        # 删掉Embarked
        del (data_list[i][-1])
    # 开始进行离散和归一化

    for data in data_list:
        data[0] = int(data[0])
        data[1] = int(data[1])
        # 对pclass分为2类
        if data[1] <= 2:
            data[1] = 'lowpclass'
        else:
            data[1] = 'highclass'
        # 为了便于处理，统一变为0，1
        if data[3] != '':
            data[3] = float(data[3])
        else:
            data[3] = None
        data[4] = int(data[4])
        data[5] = float(data[5])
    for data in data_list:
        if data[3] is None:
            data[3] = 28
        # 对年龄
        if data[3] <= 40:
            data[3] = 'NotOld'
        else:
            data[3] = 'Old'
        # 对同行人数
        if data[4] < 2:
            data[4] = 'Alone'
        else:
            data[4] = 'NotAlone'
        # 对船费
        if data[5] < 64:
            data[5] = 'Cheap'
        else:
            data[5] = 'Expensive'

    print(data_list)

    return data_list

traindata = cleantraintitanic(r'C:\\Users\\DELL\\Desktop\\Unique Spring\\titanictrain.csv')
features = ['survive', 'pclass', 'sex', 'age', 'sib', 'fare']
data = createTree(traindata, features, 'Gini')
print(data)
#createPlot(datanew)
