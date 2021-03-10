#引用库
import random
import operator
from numpy import *
import numpy as np
def hold_out(traindata,labeldata,size):    #size为训练数据占总数据的比
    datasize=len(traindata)                #总数据数
    features = len(traindata[0])           #一行有多少数据
    traindatasize = int(datasize*size)
    drange=range(1,datasize+1)
    testlist = np.random.choice(drange, traindatasize)     #随机生成数据
    Wanted_traindata=np.zeros((traindatasize,features))    #初始化
    Wanted_trainlabeldata=[]
    Wanted_testdata=np.zeros((datasize-traindatasize,features))
    Wanted_testlabeldata=[]
    for i ,j in zip(testlist,range(traindatasize)):         #循环
            Wanted_traindata[j:]=traindata[i,:]
            Wanted_trainlabeldata.append(labeldata[i])
    for i , j in zip(range(datasize),range(datasize-traindatasize)):
            if i not in testlist:
                Wanted_testdata[j,:]=traindata[i,:]
                Wanted_testlabeldata.append(labeldata[i])

    return Wanted_traindata,Wanted_trainlabeldata,Wanted_testdata,Wanted_testlabeldata


#测试
'''
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
dataset, labelset = datasetMatrix(r'C:\Users\DELL\Desktop\Unique Spring\iris.data')
data1,data2,data3,data4=hold_out(dataset,labelset,0.6)
print(data1)
print("-------")
print(data4)
print("---------")
'''