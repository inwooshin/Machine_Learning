from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

x = list(map(lambda i: round(i), np.arange(-10,10,step = 0.5)))
y = list(map(lambda i: round(i), np.arange(-10,10,step = 0.5)))

mini = 0.000001
w1, w2, thres = (1, -1, 8)
n = 0.01
t = [[0,1,1,1], [0,0,0,1]]
xx = [[0,0], [0,1], [1,0], [1,1]]
or_and = 0
wcount = 2

font1 = {'family': 'serif',
      'color':  'black',
      'weight': 'bold',
      'size': 14}

def perceptron(t):
    global w1, w2, thres, wcount
    check = 0 
    error = 0
    for i in range(0,4):
        y = 0
        if(w1 * xx[i][0] + w2 * xx[i][1] > thres or \
            abs(w1 * xx[i][0] + w2 * xx[i][1] - thres) < 0.000001):
            y = 1

        if(y == t[i]):
            check += 1

        w1 = w1 + (n * (t[i] - y) * xx[i][0])
        w2 = w2 + (n * (t[i] - y) * xx[i][1])
        error += 0.5 * (t[i] - y)

    if(check == 4): 
        plt.text(w1 - 0.7,w2 + 0.02,'{}'.format(wcount), fontdict = font1)
        return check
    plt.scatter(w1,w2)
    #plt.text(w1,w2 + 0.02,'{}'.format(wcount), fontdict = font1)
    wcount += 1

    return check

'''
def line(x1, x2):
    plt.plot(x1,x2, "b-", label = (str(w1) + ' * ' + \
        'x1 + ' + str(w2) + ' * ' + 'x2 = ' + str(round(thres,1))), visible = True)
'''

# round ver
x1 = list(map(lambda i: round((thres - w2 * i) / w1, 4), np.arange(-3.1,3.1,step = 0.1)))
x2 = list(map(lambda i: round((thres - w1 * i) / w2, 4), x1))

''' no round
x1 = list(map(lambda i: (thres - weight2 * i) / weight1, np.arange(-2.1,2.1,step = 0.1)))
x2 = list(map(lambda i: (thres - weight1 * i) / weight2, x1))
'''

#r 로 하면은 선, ro 라고 하면 점이된다.
#line(x1, x2)
plt.plot([-12, 12], [0,0], "k", [0,0], [-12,12], "k", linewidth = 2)
plt.xlabel("w1")
plt.ylabel('w2')
plt.title("delta rule")

plt.scatter(w1,w2)
plt.text(w1 - 0.7,w2+0.02,'1', fontdict = font1)

check = 0
count = 0
while check != 4:
    check = 0
    check = perceptron(t[or_and])
    count += 1
    if count >= 10000:
        plt.text(0, 0,'fault', fontdict = font1)
        break

plt.text(0.2, 0.3,'{} x1 + {} x2 = {}'.format(round(w1, 3), round(w2, 3), round(thres, 3)), fontdict = font1)

plt.xticks(np.linspace(x[0], x[-1], 41))
plt.yticks(np.linspace(y[0], y[-1], 41))
#plt.legend(loc = 'upper right', edgecolor = 'k', framealpha = 1.0)
plt.grid(True, dashes = (2,2))
plt.show()