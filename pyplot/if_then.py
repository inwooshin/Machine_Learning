import numpy as np
import matplotlib.pyplot as plt

x = list(map(lambda i: round(i), np.arange(-2.1,2.1,step = 0.1)))
y = list(map(lambda i: round(i), np.arange(-2.1,2.1,step = 0.1)))

mini = 0.000001
weight1, weight2, thres = (8, 8, 0.3)

font1 = {'family': 'serif',
      'color':  'black',
      'weight': 'bold',
      'size': 14}

def perceptron(w1, w2, x1, x2):
    if(w1 * x1 + w2 * x2 > thres or abs(w1 * x1 + w2 * x2 - thres) < 0.000001):
        plt.plot(x1, x2, "co", markersize = 6, visible = True)
    else:
        plt.plot(x1, x2, "yo", markersize = 6, visible = True)
    if (abs(x1 - 1.0) < mini or abs(x1) < mini) and \
        (abs(x2 - 1.0) < mini  or abs(x2) < mini):
        plt.text(x1,x2+0.02,'({},{})'.format(round(x1), round(x2)), fontdict = font1)
        plt.plot(x1, x2, "ko", markersize = 10, fillstyle = 'none')

def line(x1, x2):
    plt.plot(x1,x2, "b-", label = (str(weight1) + ' * ' + \
        'x1 + ' + str(weight2) + ' * ' + 'x2 = ' + str(round(thres,1))), visible = True)

# round ver
x1 = list(map(lambda i: round((thres - weight2 * i) / weight1, 4), np.arange(-3.1,3.1,step = 0.1)))
x2 = list(map(lambda i: round((thres - weight1 * i) / weight2, 4), x1))

''' no round
x1 = list(map(lambda i: (thres - weight2 * i) / weight1, np.arange(-2.1,2.1,step = 0.1)))
x2 = list(map(lambda i: (thres - weight1 * i) / weight2, x1))
'''

#r 로 하면은 선, ro 라고 하면 점이된다.
line(x1, x2)
plt.plot([-2, 2], [0,0], "k", [0,0], [-2,2], "k", linewidth = 2)
plt.xlabel("x1")
plt.ylabel('x2')
plt.title("perceptron ex2")

for x2 in np.arange(2.0,-2.1,-0.1):
    for x1 in np.arange(-2.0, 2.1, 0.1):
        perceptron(weight1, weight2,x1,x2)

plt.xticks(np.linspace(x[0], x[-1], 41))
plt.yticks(np.linspace(y[0], y[-1], 41))
plt.legend(loc = 'upper right', edgecolor = 'k', framealpha = 1.0)
plt.grid(True, dashes = (2,2))
plt.show()