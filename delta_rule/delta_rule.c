#include <stdio.h>
#include <math.h>

float w1 = 0, w2 = 0, n = 0.01, thres = 3;
float before = 0, error = 0;

//AND 와 OR 에 맞추어서 부합하게 하는 함수
int AND_OR(int x1, int x2, int t[], int i) {
	//함수를 호출할때마다 y의 값이 달라서 호출할 때마다 생성하도록 한다.
	float bef_y = w1 * x1 + w2 * x2;
	float y = 0;

	//if then 의 형식으로 하지 않고 공식을 사용한다.
	if (bef_y > thres || fabs(bef_y - thres) < 0.000001) y = 1;

	//if then 의 방식이 아닌 밑의 공식으로 간략화시킨다.
	w1 = w1 + (n * (t[i] - y) * x1);
	w2 = w2 + (n * (t[i] - y) * x2);

	//에러의 총 값을 저장한다 for 문이 0~3 까지 총 4번씩 세트로 error 의 값이 더해진다.
	error += (t[i] - y) * (t[i] - y) * 0.5;

	return y == t[i];
}
int main(void) {
	int check = 0, count = 0, and_or = 0;
	
	//w1, w2 값 설정
	printf("w1, w2의 값을 입력하시오 : ");
	scanf("%f %f", &w1, &w2);
	
	//연산 선택
	printf("OR(0) 혹은 AND(1) 혹은 EX-OR(2) 연산을 선택하세요 : ");
	scanf("%d", &and_or);

	int t[3][4] = { {0,1,1,1}, {0,0,0,1}, {0,1,1,0} }; // OR, AND, EX-OR logic
	int x[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} }; // x1, x2 입력
	
	// 입력한 w1, w2 의 값으로 한 함수를 보여준다.
	printf("\n입력 좌표 : %f * x1 + %f * x2 = y", w1, w2);
	
	//어떤 연산을 인식하고 시작하는지 보여준다.
	if (and_or == 0) printf("\n\nOR 연산 시작\n");
	else if(and_or == 1) printf("\n\nAND 연산 시작\n");
	else if(and_or == 2) printf("\n\nAND 연산 시작\n");
	
	//while 문으로 w1, w2 의 공식을 계속 거쳐서 error의 값이 줄어들도록 300번 연산한다.
	while (check != 4) {
		//각 한 cycle 마다 error의 값은 for문으로 4번을 연산하고 다음 w1, w2 연산에서 초기화된다.
		error = 0, check = 0;
		//4번의 w1, w2 연산 및 4번 연산 동안의 error 의 총합을 구한다.
		for (int i = 0; i < 4; i++) {
			check += AND_OR(x[i][0], x[i][1], t[and_or], i);
		}
		printf("w1 = %f, w2 = %f, error = %f\n", w1, w2, error);

		count++;
		//300 번이 넘으면 반복문을 중단한다.
		if (count >= 300) {
			break;
		}
	}

	//최종적으로 수행된 w1, w2 의 값을 나타낸다.
	printf("\n%.3f * x1 + %.3f * x2, error = %f, count = %d", w1, w2, error, count);
	
	return 0;
}