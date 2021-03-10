import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


# 失败的数据处理
# 用这种方法不知道为什么最后概率一直为0
# 并且对于Age这一数据无法进行处理
# 还要学习
# def cleanTitanic():
#    data_raw = pd.read_csv(r"C:\Users\DELL\Desktop\Unique Spring\titanictrain.csv")
#    data_validata = pd.read_csv(r"C:\Users\DELL\Desktop\Unique Spring\titanictrain.csv")
#    data_raw.isnull().sum()
#    data_copy = data_raw.copy(deep=True)
#    data_cleaner = [data_copy, data_validata]
#    for dataset in data_cleaner:
#        dataset['Age'].fillna(dataset['Age'].median(), inplace=True)
#        dataset['Embarked'].fillna(dataset['Embarked'].mode()[0], inplace=True)
#        dataset.drop(['Cabin', 'Ticket', 'Fare', 'Name'], axis=1, inplace=True)
#        dataset['FamilySize'] = dataset['SibSp'] + dataset['Parch'] + 1
#        # We set IsAlone to 1/True for everyone and then change it to 0/False depending on their FamilySize.
#        dataset['IsAlone'] = 'Y'
#        dataset['IsAlone'].loc[dataset['FamilySize'] > 1] = 'N'
#        dataset.drop(['SibSp', 'Parch','Age'], axis=1, inplace=True)
#        dataset['Pclass'].loc[dataset['Pclass'] == 1] = 'A'
#        dataset['Pclass'].loc[dataset['Pclass'] == 2] = 'B'
#        dataset['Pclass'].loc[dataset['Pclass'] == 3] = 'C'
#        dataset['FamilySize'].loc[dataset['FamilySize'] <= 2] = 'Small'
#        dataset['FamilySize'].loc[dataset['FamilySize'] == 4] = 'Large'
#    data_clean, data_validate = data_cleaner
#    return data_clean

# 正经处理开始
# 0:passengerID   删去
# 1:Survived    label
# 2:Pclass       保留
# 3:Name         保留
# 4:Sex          保留，为了处理，将male设为1，female设为0
# 5:Age          保留，为了处理，以20，60为界，对缺失值填入28
# 6:Sibsp        兄弟姐妹/配偶数量
# 7:Parch        父母/孩子数量    与Sibsp可一起处理
# 8:Ticket       删去
# 9:Fare         保留，参考网上以64为界
# 10:Cabin       客舱号码，删去
# 11:Embarked    登船港口，删去

def cleantraintitanic(filename):
    #读取文件
    data_raw = pd.read_csv(filename)
    #list化
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
        #性别
        if data[2] == 'male':
            data[2] = 1
        else:
            data[2] = 0
        #年龄
        if data[3] != '':
            data[3] = float(data[3])
        else:
            data[3] = None
        data[4] = int(data[4])
        data[5] = float(data[5])
    for data in data_list:
        if data[3] is None:
            data[3] = 28
        if data[3] <= 20:
            data[3] = 0
        elif data[3] > 20 and data[3] <= 60:
            data[3] = 1
        else:
            data[3] = 2
        if data[4] < 2:  # 即Alone
            data[4] = 0
        else:
            data[4] = 1
        if data[5] < 64:
            data[5] = 0
        else:
            data[5] = 1
    print(data_list)
    return data_list


# 数据处理完成
class NaiveBayes:
    def __init__(self):
        pass

    def train(self, traindata):
        size = len(traindata)
        # 存储概率数据
        p = []
        for i in range(size):
            p.append([])
        survived = 0
        for data in traindata:
            if data[0] == 1:
                survived += 1
        death = size - survived
        p_sur = survived / size
        p_dea = death / size
        p[0].append(p_sur)
        p[0].append(p_dea)
        # pclass
        f1 = 0
        f0 = 0
        s1 = 0
        s0 = 0
        t1 = 0
        t0 = 0
        for data in traindata:
            if data[0] == 1 and data[1] == 1:
                f1 += 1
            elif data[0] == 0 and data[1] == 1:
                f0 += 1
            elif data[0] == 1 and data[1] == 2:
                s1 += 1
            elif data[0] == 0 and data[1] == 2:
                s0 += 1
            elif data[0] == 1 and data[1] == 3:
                t1 += 1
            elif data[0] == 0 and data[1] == 3:
                t0 += 1
        p[1].append(f1 / survived)
        p[1].append(f0 / death)
        p[1].append(s1 / survived)
        p[1].append(s0 / death)
        p[1].append(t1 / survived)
        p[1].append(t0 / death)
        # sex
        f1 = 0
        f0 = 0
        s1 = 0
        s0 = 0
        for data in traindata:
            if data[0] == 1 and data[2] == 1:
                f1 += 1
            elif data[0] == 0 and data[2] == 1:
                f0 += 1
            elif data[0] == 1 and data[2] == 0:
                s1 += 1
            elif data[0] == 0 and data[2] == 0:
                s0 += 1
        p[2].append(f1 / survived)
        p[2].append(f0 / death)
        p[2].append(s1 / survived)
        p[2].append(s0 / death)
        # Age
        f1 = 0
        f0 = 0
        s1 = 0
        s0 = 0
        t1 = 0
        t0 = 0
        for data in traindata:
            if data[0] == 1 and data[3] == 1:
                f1 += 1
            elif data[0] == 0 and data[3] == 1:
                f0 += 1
            elif data[0] == 1 and data[3] == 2:
                s1 += 1
            elif data[0] == 0 and data[3] == 2:
                s0 += 1
            elif data[0] == 1 and data[3] == 3:
                t1 += 1
            elif data[0] == 0 and data[3] == 3:
                t0 += 1
        p[3].append(f1 / survived)
        p[3].append(f0 / death)
        p[3].append(s1 / survived)
        p[3].append(s0 / death)
        p[3].append(t1 / survived)
        p[3].append(t0 / death)
        # Sibsp+Parch
        f1 = 0
        f0 = 0
        s1 = 0
        s0 = 0
        for data in traindata:
            if data[0] == 1 and data[4] == 1:
                f1 += 1
            elif data[0] == 0 and data[4] == 1:
                f0 += 1
            elif data[0] == 1 and data[4] == 0:
                s1 += 1
            elif data[0] == 0 and data[4] == 0:
                s0 += 1
        p[4].append(f1 / survived)
        p[4].append(f0 / death)
        p[4].append(s1 / survived)
        p[4].append(s0 / death)
        # Fare
        f1 = 0
        f0 = 0
        s1 = 0
        s0 = 0
        for data in traindata:
            if data[0] == 1 and data[5] == 1:
                f1 += 1
            elif data[0] == 0 and data[5] == 1:
                f0 += 1
            elif data[0] == 1 and data[5] == 0:
                s1 += 1
            elif data[0] == 0 and data[5] == 0:
                s0 += 1
        p[5].append(f1 / survived)
        p[5].append(f0 / death)
        p[5].append(s1 / survived)
        p[5].append(s0 / death)

        return p

    def predict(self, testdata, p):
        # 存储预测结果
        result = []
        # 存储存活概率
        p_survied = []
        for data in testdata:
            p1 = p[0][0]
            p0 = p[0][1]
            # pclass
            if data[1] == 1:
                p1 *= p[1][0]
                p0 *= p[1][1]
            elif data[1] == 2:
                p1 *= p[1][2]
                p0 *= p[1][3]
            elif data[1] == 3:
                p1 *= p[1][4]
                p0 *= p[1][5]
            # sex
            if data[2] == 1:
                p1 *= p[2][0]
                p0 *= p[2][1]
            elif data[2] == 0:
                p1 *= p[2][2]
                p0 *= p[2][3]
            # Age
            if data[3] == 0:
                p1 *= p[3][0]
                p0 *= p[3][1]
            elif data[3] == 1:
                p1 *= p[3][2]
                p0 *= p[3][3]
            elif data[3] == 2:
                p1 *= p[3][4]
                p0 *= p[3][5]
            # Sibsp+Parch
            if data[4] == 0:
                p1 *= p[4][0]
                p0 *= p[4][1]
            elif data[4] == 1:
                p1 *= p[4][2]
                p0 *= p[4][3]
            # fare
            if data[5] == 1:
                p1 *= p[5][0]
                p0 *= p[5][1]
            else:
                p1 *= p[5][2]
                p0 *= p[5][3]
            p_survied.append(p1)
            if p1 > p0:
                result.append(1)
            else:
                result.append(0)

        return p_survied, result

#accuracy很好理解
def calaccuracy(result, testdata):
    n = 0
    for i in range(len(result)):
        if testdata[i][0] == result[i]:
            n += 1
    accuracy = n / len(result)
    print("accuracy的值为", accuracy)

#F1_score根据公式计算
def calF1_score(result, testdata):
    TP = 0  # 预测为正，实际为正
    FP = 0  # 预测为正，实际为负
    FN = 0  # 预测为负，实际为正
    for i in range(len(result)):
        if testdata[i][0] == 1:
            if result[i] == 1:
                #计数
                TP += 1
            elif result[i] == 0:
                FN += 1
        elif testdata[i][0] == 0:
            if result[i] == 1:
                FP += 1
    #公式
    F1_score = 2 * TP / (2 * TP + FP + FN)
    print("F1_score的值为", F1_score)


def draw_ROC_AUC(p_survived,testdata, result):
    TP = 0
    TN = 0
    for data in testdata:
        if data[0] == 1:
            TP += 1
        else:
            TN += 1
    for i in range(len(testdata)):
        p_survived[i] = [p_survived[i]]
        p_survived[i].append(testdata[i][0])
        p_survived[i].append(result[i])
    p_survived = sorted(p_survived, reverse=True)
    #将TPR和FPR建为list，便于后续作图用
    TPR = [0]
    FPR = [0]
    lens = len(p_survived)
    for i in range(1, lens):
        if p_survived[i][1] == 1:
            FPR.append(FPR[i - 1])
            TPR.append(TPR[i - 1] + 1 / TP)

        elif p_survived[i][1] == 0:
            FPR.append(FPR[i - 1] + 1 / TN)
            TPR.append(TPR[i - 1])

    TPR.append(1)
    FPR.append(1)

    auc = 0
    for i in range(len(FPR) - 1):
        #计算公式
        auc += (FPR[i + 1] - FPR[i]) * (TPR[i] + TPR[i + 1])
    auc = auc / 2

    print("AUC的值为", auc)

    fpr = np.array(FPR)
    tpr = np.array(TPR)

    plt.title("ROC curve")
    plt.xlabel("False Positive Rate")
    plt.ylabel("True Positive Rate")

    plt.plot(fpr, tpr)
    plt.show()




traindata = cleantraintitanic(r'C:\\Users\\DELL\\Desktop\\Unique Spring\\titanictrain.csv')
testdata = cleantraintitanic(r'C:\\Users\\DELL\\Desktop\\Unique Spring\\titanic_test.csv')
nb = NaiveBayes()
p = nb.train(traindata)
p_survived, result = nb.predict(testdata, p)
calaccuracy(result, testdata)
calF1_score(result, testdata)
draw_ROC_AUC(p_survived,testdata, result)

