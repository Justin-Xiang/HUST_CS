class NaiveBayes:
    def __init__(self,traindata,testdata):
        NaiveBayes.traindata = traindata
        NaiveBayes.testdata = testdata

    def train(self):
        #计算训练集长度
        len_traindata = len(NaiveBayes.traindata)
        #训练集标签
        traindata_label = []
        for i in range(len_traindata):
            traindata_label.append(NaiveBayes.traindata[i][-1])
        #去掉重复的
        traindata_label_one = set(traindata_label)
        #初始化每个标签出现概率为0
        label_probility={}
        for label in traindata_label_one:
            label_probility[label] = 0
        for label in traindata_label_one:
            for totallabel in traindata_label:
                if label == totallabel:
                    label_probility[label] = label_probility[label]  + 1

        #得到想要的概率
        for label in traindata_label_one:
            label_probility[label] = label_probility[label]/len_traindata

        feature_label = {}
        for label in traindata_label_one:
            feature_label[label] = 0
        for data in NaiveBayes.traindata:
            for label in traindata_label_one:
                for i in range(len(data)):
                    feature_1 = data[i]
                    feature_label[label][feature_1] = 0
        return feature_label

    def predict(self):
        #对测试集的每一个数据
        for data in NaiveBayes.testdata:
            #每一个标签
            for label in self.train().traindata_label_one:
                #每一个特征
                for i in range(data):
                    #判断出现次数
                    for data_i in range(len(NaiveBayes.traindata)):
                        if label == NaiveBayes.traindata[data_i][-1] and NaiveBayes.traindata[data_i][i] == data[i]:
                            self.train().feature_label[label][data[i]] = self.train().feature_label[label][data[i]] + 1

        print(self.train().feature_label)

        for data in NaiveBayes.testdata:
            init_probility = 0
            init_label = NaiveBayes.traindata[0][-1]
            #对每一个标签
            for label in self.train().traindata_label_one:
                k = 1
                for feature in range(len(data)):
                     k = k * self.train().feature_label[label][data[feature]] / (self.train().label_probility[label]*self.train().len_traindata)
                k = k *self.train().label_probility[label]
                if k > init_probility:
                    init_probility = k
                    init_lalbel = label

            print("最终分类为%s",label)







