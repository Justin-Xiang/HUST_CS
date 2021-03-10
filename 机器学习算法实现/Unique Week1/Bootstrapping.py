from numpy import *
import numpy as np
def Bootstrapping(dataset):
    datasize = len(dataset)
    boots= []
    for i in range(datasize):
        boots.append(np.floor(np.random.random()*datasize))
    wantedlist=[]
    for i in range(datasize):
        wantedlist.append(dataset[int(boots[i])])
    #去掉重复取的元素
    setlist = set(wantedlist)
    targetlist = list(setlist)
    print(targetlist)
    return

'''
X = [1,10,23,421,12,42,99,13,28,49,21,20,47,87,77]
Bootstrapping(X)
'''