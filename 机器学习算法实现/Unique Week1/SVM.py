'''
SVM对数学要求实在有点高
自己完全手动写束手无策
只好在网上看一行懂一行写一行
加上自己的注释
'''
import numpy as np
#python中的cvxopt库
#求解凸优化二次规划问题
import cvxopt
import cvxopt.solvers


class SVC(object):
    def __init__(self, kernel='linear', C=1.0, sigma=1.0, **kwargs):
        #调用核函数
        if kernel not in ['linear', 'gaussian']:
            raise ValueError("Now only support linear and gaussian kernel")
        elif kernel == 'linear':
            kernel_fn = Kernel.linear()
        else:
            kernel_fn = Kernel.gaussian(sigma)
        #初始化参数
        self.kernel = kernel_fn  # kernel func
        self.C = C
        self._predictor = None

    def fit(self, X, y):
        # 获取拉格朗日乘子
        lagr = self._lagr_multiplier(X, y)
        self._predictor = self._fit(X, y, lagr)

    def predict(self, X):
        return self._predictor.predict(X)

    def _fit(self, X, y, lagr, support_vector_threhold=1e-5):
        # 支持向量
        support_vectors_id = lagr > support_vector_threhold
        support_lagr = lagr[support_vectors_id]
        support_vectors = X[support_vectors_id]
        support_vector_tags = y[support_vectors_id]

        # 计算偏差
        bias = np.mean([y_k - Predictor(kernel=self.kernel,
                                        bias=0.0,
                                        W=support_lagr,
                                        support_vectors=support_vectors,
                                        support_vector_tags=support_vector_tags).predict(x_k) for (y_k, x_k) in
                        zip(support_vector_tags, support_vectors)])

        return Predictor(kernel=self.kernel,
                         bias=bias,
                         W=support_lagr,
                         support_vectors=support_vectors,
                         support_vector_tags=support_vector_tags)

    def _lagr_multiplier(self, X, y):
        samples, features = X.shape

        k = self._mapping(X)
        # 二次规划
        P = cvxopt.matrix(np.outer(y, y) * k)
        q = cvxopt.matrix(-1 * np.ones(samples))

        G_std = cvxopt.matrix(np.diag(np.ones(samples) * -1))
        h_std = cvxopt.matrix(np.zeros(samples))

        # a_i \leq C
        G_slack = cvxopt.matrix(np.diag(np.ones(samples)))
        h_slack = cvxopt.matrix(np.ones(samples) * self.C)

        G = cvxopt.matrix(np.vstack((G_std, G_slack)))
        h = cvxopt.matrix(np.vstack((h_std, h_slack)))

        # y = y.reshape((1, y.shape[0]))
        A = cvxopt.matrix(y, (1, samples))
        b = cvxopt.matrix(0.0)

        solution = cvxopt.solvers.qp(P, q, G, h, A, b)
        # lagr multiplier
        return np.ravel(solution['x'])

    def _mapping(self, X):
        samples, features = X.shape
        k = np.zeros((samples, samples))
        # 空间映射
        for i, xi in enumerate(X):
            for j, xj in enumerate(X):
                k[i, j] = self.kernel(xi, xj)
        return k


class Predictor(object):
    def __init__(self,
                 kernel,
                 bias,
                 W,
                 support_vectors,
                 support_vector_tags):
        self._kernel = kernel
        self._bias = bias
        self._W = W
        self._support_vectors = support_vectors
        self._support_vector_tags = support_vector_tags
        assert len(support_vectors) == len(support_vector_tags)
        assert len(W) == len(support_vector_tags)

    def softmax(self, x):
        #计算x中每组分数的softmax值
        x = np.array(x)
        x = np.exp(x)
        x.astype('float32')
        if x.ndim == 1:
            sumcol = sum(x)
            for i in range(x.size):
                x[i] = x[i] / float(sumcol)
        if x.ndim > 1:
            sumcol = x.sum(axis=0)
            for row in x:
                for i in range(row.size):
                    row[i] = row[i] / float(sumcol[i])
        return x

    def predict(self, x):
        result = self._bias
        for z_i, x_i, y_i in zip(self._W,
                                 self._support_vectors,
                                 self._support_vector_tags):
            result += z_i * y_i * self._kernel(x_i, x)
        return np.sign(result).item()


class Kernel(object):
    # 线性核
    @staticmethod
    def linear():
        return lambda X, y: np.inner(X, y)

    # 高斯核
    @staticmethod
    def gaussian(sigma):
        return lambda X, y: np.exp(-np.sqrt(np.linalg.norm(X - y) ** 2 / (2 * sigma ** 2)))