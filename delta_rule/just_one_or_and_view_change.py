from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
import time

mini = 0.000001
t = [[0,1,1,1], [0,0,0,1]]
x = [[0,0], [0,1], [1,0], [1,1]]
w1_list = []
w2_list = []
error_list = []
t_list, y_list = [], []
error = 0

#설정해야 하는 값
or_and = 0
n = 0.1
#격자 구간 및 범위
from_range,to_range, sep = -10, 10, 1

#창 사이즈 규격 및 3d 설정
plt.rcParams["figure.figsize"] = (20, 20)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def and_or(w1, w2):
    global x, n, or_and, error_list
    error_list = np.zeros_like(w1)
    for i in range(4):
        y = w1 * x[i][0] + w2 * x[i][1]
        
        error_list += 0.5 * (y - t[or_and][i]) ** 2

w1 = np.arange(-10,10.5,0.5)
w2 = np.arange(-10,10.5,0.5)
w1, w2 = np.meshgrid(w1, w2)
and_or(w1, w2)

surf = ax.plot_surface(w1, w2, error_list, rstride = 2, cstride = 2,\
     cmap = cm.RdPu, linewidth=0.3, edgecolor = 'k', antialiased=True)

#각 축의 이름을 설정해준다.
ax.set_xlabel('W1 axis')
ax.set_ylabel('W2 axis')
ax.set_zlabel('Error axis')

#격자 20개로 x,y,z 축 나눔을 해준 것이다.
ax.set_xlim(from_range, to_range)
ax.set_ylim(from_range, to_range)
ax.set_zlim(0, 300)

ax.set_xticks(list(np.arange(from_range,to_range,sep)))
ax.set_yticks(list(np.arange(from_range,to_range,sep)))
ax.set_zticks(list(np.arange(0,325, 25)))

#fig.colorbar(surf, ax=ax, shrink=0.5, aspect=5)

def add_point(event):
    if event.inaxes != ax:
        return

    # button 1: 마우스 좌클릭
    if event.button == 1:   
        ax.view_init(0, 0)
        print("왼쪽")
 
    # button 3: 마우스 우클릭 시 기존 입력값 삭제
    if event.button == 3:
        ax.view_init(45, 45)
        print("오른쪽")
 
    # 마우스 중간버튼 클릭 시 종료하기
    if event.button == 2:
        ax.view_init(90, 90)
        print("중간")
    
    plt.ion()

fig.canvas.mpl_connect("button_press_event", add_point)

plt.show()
