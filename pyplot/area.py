from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

mini = 0.000001
t = [[0,1,1,1], [0,0,0,1]]
xx = [[0,0], [0,1], [1,0], [1,1]]
y = 0
or_and = 0
w1_list = []
w2_list = []
error_list = []
t_list, y_list = [], []

#설정해야 하는 값
w1, w2 = (2, 2)
n = 0.1
from_range,to_range, sep = -10, 10, 1

def perceptron(t, w1, w2):
    global thres, wcount, w1_list, w2_list, error_list, t_list, y_list, y
    check = 0 
    error = 0
    for i in range(0,4):
        y = w1 * xx[i][0] + w2 * xx[i][1]

        w1 = w1 + (n * (t[i] - y) * xx[i][0])
        w2 = w2 + (n * (t[i] - y) * xx[i][1])
        error += 0.5 * (t[i] - y) * (t[i] - y)
        
    error_list.append(error)
    print("w1 = %f, w2 = %f, error = %f"%(w1,w2,error))

check = 0
count = 0

for w1_for in np.arange(-10,10,0.5):
    for w2_for in np.arange(-10,10, 0.5):
        print("앙!")

'''
for i in range(10):
    for j in range(10):
        print("앙")
'''

a = [[1,2],[3,4]]
b = [[1,2], [3,4]]
c = [[2,-1], [-3,4]]
print(a)
print(b)
print(c)

np.array(a).transpose()
np.array(b).transpose()
np.array(c).transpose()

print(a)
print(b)
print(c)