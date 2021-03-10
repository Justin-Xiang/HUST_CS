import numpy as np
import random
import matplotlib.pyplot as plt
#from sklearn import datasets   构造数据集
class DBSCAN:
    def __init__(self):
        pass

    def dbscan(self,dataset,eps,min_pts):
        self.dataset=dataset
        self.eps = eps
        self.min_pts = min_pts
        # 初始化
        k = -1
        neighbourpts = []
        wantedpts = []
        visited = []
        size = [i for i in range(len(dataset))]
        noiselist =  [ -1 for i in range(len(dataset))]
        while len(size) > 0:
            #随机上选择一个对象x
            x = random.choice(size)
            size.remove(x)
            visited.append(x)
            neighbourpts = self.findneighbour(x, dataset, eps)
            if len(neighbourpts) < min_pts:
                noiselist[x] = -1    #标记为噪音
            #如果x的邻域内至少有min_pts个对象
            else:
                k=k+1
                #noiselist为一个标记列表，直接进行赋值
                noiselist[x] = k
                #对于neighbourps中的每一个点
                for i in neighbourpts:
                    if i not in visited:
                        size.remove(i)
                        #标记已经visit
                        visited.append(i)
                        wantedpts = self.findneighbour(i,dataset,eps)
                        if len(wantedpts) >= min_pts:
                            for x in wantedpts:
                                if x not in neighbourpts:
                                    neighbourpts.append(x)
                        #如果不是任何簇的成员，添加到c
                        if(noiselist[i]==-1):
                            noiselist[i] = k
        return noiselist



    def findneighbour(self,x,dataset,eps):
        wantlist = []
        for i in range(dataset.shape[0]):  #计算欧式距离
            distance = np.sqrt(np.sum(np.square(dataset[x]-dataset[i])))
            if(distance<=eps):      #得到eps距离内的所有数据
                wantlist.append(i)
        return wantlist


#可视化
'''
x, y = datasets.make_blobs(n_samples=400, n_features=2, centers=[[-1, -1], [0, 0], [1, 1], [2, 2]],cluster_std=[0.4, 0.2, 0.2, 0.2])
eps=0.08
min_Pts=10
DB=DBSCAN()
M=DB.dbscan(x,eps,min_Pts)
plt.figure(figsize=(12, 9), dpi=80)
colors = ['b','g','r','orange']
for i in range(len(y)):
    if y[i] == 0:
        plt.scatter(x[i:, 0], x[i:, 1],c=colors[0])
    elif y[i] == 1:
        plt.scatter(x[i:, 0], x[i:, 1], c=colors[1])
    elif y[i] == 2:
        plt.scatter(x[i:, 0], x[i:, 1], c=colors[2])
    elif y[i] == 3:
        plt.scatter(x[i:, 0], x[i:, 1], c=colors[3])
plt.show()
'''
