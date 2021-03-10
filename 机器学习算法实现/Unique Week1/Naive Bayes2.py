#coding:utf-8
# 极大似然估计  朴素贝叶斯算法
import pandas as pd
import numpy as np
import random

class NaiveBayes(object):

    def classify(self, trainData, labels, features):
        #求labels中每个label的先验概率
        labels = list(labels)    #转换为list类型
        P_y = {}       #存入label的概率
        for label in labels:
            P_y[label] = labels.count(label)/float(len(labels))   # p = count(y) / count(Y)

        #求label与feature同时发生的概率
        P_xy = {}
        x_index=[]
        for y in P_y.keys():
            y_index = [i for i, label in enumerate(labels) if label == y]  # labels中出现y值的所有数值的下标索引
            for j in range(len(features)):      # features[0] 在trainData[:,0]中出现的值的所有下标索引
                #x_index = [i for i, feature in enumerate(trainData[:,j]) if feature == features[j]]
                for i ,feature in enumerate(trainData[:j]):
                    if feature == features[j]:
                        x_index.append(i)
                xy_count = len(set(x_index) & set(y_index))   # set(x_index)&set(y_index)列出两个表相同的元素
                pkey = str(features[j]) + '*' + str(y)
                P_xy[pkey] = xy_count / float(len(labels))

        #求条件概率
        P = {}
        for y in P_y.keys():
            for x in features:
                pkey = str(x) + '|' + str(y)
                P[pkey] = P_xy[str(x)+'*'+str(y)] / float(P_y[y])    #P[X1/Y] = P[X1Y]/P[Y]


        F = {}
        for y in P_y:
            F[y] = P_y[y]
            for x in features:
                F[y] = F[y]*P[str(x)+'|'+str(y)]     #P[y/X] = P[X/y]*P[y]/P[X]，分母相等，比较分子即可，所以有F=P[X/y]*P[y]=P[x1/Y]*P[x2/Y]*P[y]
        print(F)
        features_label = max(F, key=F.get)  #概率最大值对应的类别
        return features_label

def cleanTitanic():
    data_raw = pd.read_csv(r"C:\Users\DELL\Desktop\Unique Spring\titanictrain.csv")
    data_validata = pd.read_csv(r"C:\Users\DELL\Desktop\Unique Spring\titanictrain.csv")
    data_raw.isnull().sum()
    data_copy = data_raw.copy(deep=True)
    data_cleaner = [data_copy, data_validata]
    for dataset in data_cleaner:
        dataset['Age'].fillna(dataset['Age'].median(), inplace=True)
        dataset['Embarked'].fillna(dataset['Embarked'].mode()[0], inplace=True)
        dataset.drop(['Cabin', 'Ticket', 'Fare', 'Name'], axis=1, inplace=True)
        dataset['FamilySize'] = dataset['SibSp'] + dataset['Parch'] + 1
        # We set IsAlone to 1/True for everyone and then change it to 0/False depending on their FamilySize.
        dataset['IsAlone'] = 'Y'
        dataset['IsAlone'].loc[dataset['FamilySize'] > 1] = 'N'
        dataset.drop(['SibSp', 'Parch','Age'], axis=1, inplace=True)
        dataset['Pclass'].loc[dataset['Pclass'] == 1] = 'A'
        dataset['Pclass'].loc[dataset['Pclass'] == 2] = 'B'
        dataset['Pclass'].loc[dataset['Pclass'] == 3] = 'C'
        dataset['FamilySize'].loc[dataset['FamilySize'] <= 2] = 'Small'
        dataset['FamilySize'].loc[dataset['FamilySize'] == 4] = 'Large'





    data_clean, data_validate = data_cleaner

    return data_clean


def createdataset():
    data = cleanTitanic()
    trainlist = data.values.tolist()
    labellist = [example[1] for example in trainlist]
    list1 = np.insert(trainlist, 7, values=labellist, axis=1)
    targetlist1 = np.delete(list1, 0, axis=1)
    targetlist2 = np.delete(targetlist1, 0, axis=1)
    targetlist = np.delete(targetlist2, 5, axis=1)
    return targetlist,labellist

traindata ,labellist= createdataset()
randdata=np.arange(traindata.shape[0])
np.random.shuffle(randdata)
testdata=traindata[randdata[0:30]]
nb = NaiveBayes()
features=['A' 'female' 'C' 'Small' 'Y']
nb.classify(traindata,labellist,features)
#for i in range(30):
  #  x = random.randint(0,30)
