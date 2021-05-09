import numpy as np
import matplotlib.pyplot as plt

#격자테스트를 한 파일을 읽어온다.
file = open('grid.txt', 'r')

#x 변수에 파일에서 한줄씩 배열의 한 인수로 읽어온다.
x = file.readlines()
x1_input = []
x2_input = []
t = []

#각 줄마다 띄어쓰기로 잘라서 tmp 배열에 할당한다.
for i in x:
    tmp = i.split(' ')
    x1_input.append(float(tmp[0]))
    x2_input.append(float(tmp[1]))
    t.append(int(tmp[2]))

#격자 테스트 한 값을 토대로 각 좌표에 해당하는 기대값으로 점을 찍는다
#기대값이 0이면 검은색의 점, 기대값이 1이면 하늘색의 점을 찍는다.
def EBP():
    global x1_input, x2_input
    for i in range(len(x1_input)):
        if t[i] == 0:
            plt.plot(x1_input[i], x2_input[i], "ko", markersize = 5, visible = True)
        else :
            plt.plot(x1_input[i], x2_input[i], "co", markersize = 5, visible = True)

#x1, x2 배열에 해당하는 선을 그려준다.
def line(x1, x2):
    plt.plot(x1,x2, "b-", visible = True)

#x2 = -0.5 의 그래프를 그린다.
x1 = np.arange(-3.1,3.1,step = 0.1)
x2 = np.full((x1.size), -0.5)

line(x1, x2)

#x1 - x2 = -1 의 그래프를 그린다.
x1 = np.arange(-3.1,3.1,step = 0.1)
x2 = list(map(lambda i: i + 1, x1))

line(x1, x2)

#x1 + x2 = 2 의 그래프를 그린다.
x1 = np.arange(-3.1,3.1,step = 0.1)
x2 = list(map(lambda i: -i + 2, x1))

line(x1, x2)

#x축과 y 축을 그려준다.
plt.plot([-4, 4], [0,0], "k", [0,0], [-4,4], "k", linewidth = 2)
#x축의 이름을 x1 으로 y축의 이름을 x2 로 설정한다.
plt.xlabel("x1")
plt.ylabel('x2')

#제목을 설정한다.
plt.title("EBP, HW #6,7")

#함수를 호출해서 격자테스트해서 나온 txt 파일의 값으로 그래프에 점을 찍는다.
EBP()

#각 격자 눈금을 얼마나 줄지 설정한다. 0.5 로 설정한 것이다.
plt.xticks(np.linspace(-2, 3, 11))
plt.yticks(np.linspace(-2, 2, 9))

#눈금을 어떤 식으로 줄 것인지 설정한다. dashes 의 값은 얼마나 눈금이
#띄엄띄엄 있는지를 설정해주는 값이다.
#True 값은 눈금을 형성할지 말지를 고르는 값이다. False 를 하면 눈금을
#지울 수 있다.
plt.grid(True, dashes = (2,2))
plt.show()