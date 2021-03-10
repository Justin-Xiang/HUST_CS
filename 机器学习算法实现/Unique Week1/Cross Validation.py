from numpy import *
import numpy as np
def Cross_Validation(dataset, K):
    sizeofdata = len(dataset)
    single = int(sizeofdata/K)
    #因为要轮流进行测试，不能用random函数
    for i in range(K):
        traindata = dataset[:i*single]+dataset[(i+1)*single:]
        testdata = dataset[i*single:(i+1)*single]
        print("训练数据为：",traindata)
        print("测试数据为：",testdata)
        print("-----------------")
    return

#测试
'''
dataset=[1,2,3,4,5,6,7,8,9,10]
Cross_Validation(dataset,2)
'''