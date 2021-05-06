import numpy as np
import matplotlib.pyplot as plt

file = open('grid.txt', 'r')

x = file.readlines()


font1 = {'family': 'serif',
      'color':  'black',
      'weight': 'bold',
      'size': 14}

x1_input = []
x2_input = []
t = []

for i in x:
    tmp = i.split(' ')
    x1_input.append(float(tmp[0]))
    x2_input.append(float(tmp[1]))
    t.append(int(tmp[2]))

print(x1_input)
print(x2_input)
print(t)

def gridTest(x1, x2):
    global w1_input, w2_input, w_output

def EBP():
    global x1_input, x2_input
    for i in range(len(x1_input)):
        if t[i] == 0:
            plt.plot(x1_input[i], x2_input[i], "ko", markersize = 5, visible = True)
        else :
            plt.plot(x1_input[i], x2_input[i], "bo", markersize = 5, visible = True)


def line(x1, x2):
    plt.plot(x1,x2, "b-", visible = True)

# round ver
x1 = np.arange(-3.1,3.1,step = 0.1)
x2 = np.full((x1.size), -0.5)

line(x1, x2)

x1 = np.arange(-3.1,3.1,step = 0.1)
x2 = list(map(lambda i: i + 1, x1))

line(x1, x2)

x1 = np.arange(-3.1,3.1,step = 0.1)
x2 = list(map(lambda i: -i + 2, x1))

#r 로 하면은 선, ro 라고 하면 점이된다.
line(x1, x2)
plt.plot([-4, 4], [0,0], "k", [0,0], [-4,4], "k", linewidth = 2)
plt.xlabel("x1")
plt.ylabel('x2')
plt.title("EBP, HW #6,7")

EBP()

plt.xticks(np.linspace(-2, 3, 11))
plt.yticks(np.linspace(-2, 2, 9))
plt.grid(True, dashes = (2,2))
plt.show()