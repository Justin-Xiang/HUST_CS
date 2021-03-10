import tensorflow as tf
import matplotlib.pyplot as plt
mnist = tf.keras.datasets.mnist
(x_train,y_train),(x_test,y_test) = mnist.load_data()
plt.imshow(x_train[0])
plt.imshow(x_train[0],camp=plt.cm.binary)
