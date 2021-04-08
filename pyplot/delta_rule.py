from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
import pickle

w1_list = []
w2_list = []
error_list = []
w1, w2, error = (0.0, 0.0, 0.0)
plt.rcParams["figure.figsize"] = (20, 20)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

f = open("delta_rule.txt", "r")

w1_tmp = []
w2_tmp = []
error_tmp = []
before, once = 0.0, 0
from_range, to_range, sep = -10, 10, 1

length = len(f.readlines())

f.close

f = open("delta_rule.txt", "r")

for i in range(length):
    w = f.readline()
    print(w)
    print(w[0])
    print(w[1])
    print(w[2])
    '''
    w1_tmp.append(w.split())
    if once == 0:
        before = w2
        once = 1
    w2_tmp.append(w.split())
    error_tmp.append(w.split())
    if(before != w2):
        before = w2
        w1_list.append(w1_tmp)
        w2_list.append(w2_tmp)
        error_list.append(error_tmp)
        w1_tmp.clear()
        w2_tmp.clear()
        error_tmp.clear()
    '''
    
    
for i in range(len(w1_list)):
    ax.plot(w1_list[i], w2_list[i], error_list[i], color = 'k')

w1_list = np.array(w1_list).transpose()
w2_list = np.array(w2_list).transpose()
error_list = np.array(error_list).transpose()

for i in range(len(w1_list)):
    ax.plot(w1_list[i], w2_list[i], error_list[i], color = 'k')

ax.set_xlabel('W1 axis')
ax.set_ylabel('W2 axis')
ax.set_zlabel('Error axis')

#격자 20개로 x,y,z 축 나눔
ax.set_xlim(from_range, to_range)
ax.set_ylim(from_range, to_range)
ax.set_zlim(0, 200)

ax.set_xticks(list(np.arange(from_range,to_range,sep)))
ax.set_yticks(list(np.arange(from_range,to_range,sep)))
ax.set_zticks(list(np.arange(0,200, 10)))

plt.show()