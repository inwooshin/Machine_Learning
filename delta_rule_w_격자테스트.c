#include <stdio.h>
#include <math.h>

float thres = 0, n = 0.01;
float before = 0, error = 0;

//AND 와 OR 에 맞추어서 부합하게 하는 함수
int AND_OR(int x1, int x2,float w1, float w2, int t[], int i) {
	//함수를 호출할때마다 y의 값이 달라서 호출할 때마다 생성하도록 한다.
	int y = 0;

	//if then 의 형식으로 하지 않고 공식을 사용한다.
	y = w1 * x1 + w2 * x2;

	//if then 의 방식이 아닌 밑의 공식으로 간략화시킨다.
	w1 = w1 + (n * (t[i] - y) * x1);
	w2 = w2 + (n * (t[i] - y) * x2);

	//에러의 총 값을 저장한다 for 문이 0~3 까지 총 4번씩 세트로 error 의 값이 더해진다.
	error += (t[i] - y) * (t[i] - y) * 0.5;

	return 0;
}


int main(void) {

	int check = 0, count = 0, and_or = 0;

	//delta rule 의 값을 저장하기 위해서 파일을 열어준다.
	FILE* fd = fopen("delta_rule.txt", "w");

	printf("OR(0) 혹은 AND(1) 혹은 EX-OR(2) 연산을 선택하세요 : ");
	scanf("%d", &and_or);

	//or and ex-or 기대값과 주어질 각 x의 좌표를 이중배열로 선언해서 간단화한다.
	int t[3][4] = { {0,1,1,1}, {0,0,0,1}, {0,1,1,0} }; // OR, AND, EX-OR logic
	int x[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} }; // x1, x2 입력

	if (and_or == 0) printf("\n\nOR 연산 시작\n");
	else if (and_or == 1) printf("\n\nAND 연산 시작\n");
	else if (and_or == 2) printf("\n\nAND 연산 시작\n");

	//각각의 -10, 10 까지의 좌표를 두고 이중 for문을 연산해서 error의 격자테스트를 수행한다.
	for(float w1_for = 10 ; w1_for >= -10 ; w1_for -= 0.5){
		for (float w2_for = 10; w2_for >= -10; w2_for -= 0.5) {
			error = 0; //4번의 세트를 더해준 값을 각각 w1,w2 의 좌표에 나타내야하기 때문에 초기화한다.
			for (int i = 0; i < 4; i++) {
				//입력한 and 또는 or 에 맞추어서 error 값을 구하는 and or 함수를 호출한다.
				AND_OR(x[i][0], x[i][1], w1_for, w2_for, t[and_or], i);
			}
			
			//error 값과 w1, w2 값을 출력하고 파일에 저장한다.
			printf("w1 = %f, w2 = %f, err = %f\n", w1_for, w2_for, error);
			fprintf(fd,"%f %f %f\n", w1_for, w2_for, error);
		}
	}


	return 0;
}