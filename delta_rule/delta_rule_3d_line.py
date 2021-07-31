from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

mini = 0.000001
t = [[0,1,1,1], [0,0,0,1]]
xx = [[0,0], [0,1], [1,0], [1,1]]
y = 0
w1_list = []
w2_list = []
error_list = []
t_list, y_list = [], []

#설정해야 하는 값
or_and = 0
n = 0.1
#격자 구간 및 범위
from_range,to_range, sep = -10, 10, 1

#창 사이즈 규격 및 3d 설정
plt.rcParams["figure.figsize"] = (20, 20)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

#y의 값을 공식으로 도출하고, w1, w2의 값을 공식으로 또한 도출한다.
#그 값으로 error 의 값을 도출한다.
def perceptron(t, w1, w2, error_tmp):
    global thres, wcount, t_list, y_list, y
    check = 0 
    error = 0
    for i in range(0,4):
        y = w1 * xx[i][0] + w2 * xx[i][1]

        w1 = w1 + (n * (t[i] - y) * xx[i][0])
        w2 = w2 + (n * (t[i] - y) * xx[i][1])
        error += 0.5 * (t[i] - y) * (t[i] - y)
        
    #error 를 tmp 라는 list 에 넣는다.
    error_tmp.append(error)

check = 0
count = 0

#w1,w2 의 격자테스트를 실행한다.
#w2 가 -10, 10 구간의 w1, w2, error 의 값을 w1_tmp, w2_tmp, error_tmp 에 넣는다.
#w1 이 증가될 때까지만 w1_tmp, w2_tmp 를 넣고 (즉 한 줄을 넣는 것이다.) 
#w1 이 증가되면 초기화된 w1_tmp, w2_tmp, error_tmp 배열에 w1, w2, error 값을 넣도록 한다    
for w1_for in np.arange(-10,10,0.5):
    #w1_tmp, w2_tmp, error_tmp 배열을 형성한다.
    w1_tmp = []
    w2_tmp = []
    error_tmp = []
    for w2_for in np.arange(-10,10,0.5):
        #w1_tmp, w2_tmp 배열에 w1, w2 격자 값을 입력한다.
        w1_tmp.append(w1_for)
        w2_tmp.append(w2_for)
        check = 0
        #perceptron 함수로 error 값을 도출해 error_tmp 에 넣는다.
        perceptron(t[or_and],w1_for, w2_for, error_tmp)
    #w1_list 배열에 w1_tmp 배열을 넣는다.
    w1_list.append(w1_tmp)
    #w2_list 배열에 w2_tmp 배열을 넣는다.
    w2_list.append(w2_tmp)
    #error_list 배열에 error_tmp 배열을 넣는다.
    error_list.append(error_tmp)

#z축의 직선을 그린다.
for i in range(len(w1_list)):
    ax.plot(w1_list[i], w2_list[i], error_list[i], color = 'k')

w1_list = np.array(w1_list).transpose()
w2_list = np.array(w2_list).transpose()
error_list = np.array(error_list).transpose()

#x축의 직선을 그린다.
for i in range(len(w1_list)):
    ax.plot(w1_list[i], w2_list[i], error_list[i], color = 'k')

#각 축의 이름을 설정해준다.
ax.set_xlabel('W1 axis')
ax.set_ylabel('W2 axis')
ax.set_zlabel('Error axis')

#격자 20개로 x,y,z 축 나눔을 해준 것이다.
ax.set_xlim(from_range, to_range)
ax.set_ylim(from_range, to_range)
ax.set_zlim(0, 200)

ax.set_xticks(list(np.arange(from_range,to_range,sep)))
ax.set_yticks(list(np.arange(from_range,to_range,sep)))
ax.set_zticks(list(np.arange(0,200, 10)))

#그래프를 띄운다.
plt.show()