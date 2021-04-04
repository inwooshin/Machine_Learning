#include <stdio.h>
#include <math.h>

float w1, w2, thres;
float before = 0;

int AND_OR(float x1, float x2, int t[], int i) {
	int result = 0;
	
	if (w1 * x1 + w2 * x2 > thres || fabs(w1 * x1 + w2 * x2 - thres) < 0.000001) result = 1;
	else result = 0;

	if (result == t[i]) return 1;
	else if (result == 1) {
		if (w1 != 0) w1 /= 2;
		if (w2 != 0) w2 /= 2;
	}
	else if (result == 0) {
		if (w1 != 0) w1 *= 1.5;
		if (w2 != 0) w2 *= 1.5;
	}

	return 0;
}

/*
int PlayPerceptron() {
	int result = 0;

	for (float x2 = 2; x2 >= -2.000001; x2 -= 0.1) {
		for (float x1 = -2; x1 <= 2.000001; x1 += 0.1) {
			result = 0;
			if (before != x2) { before = x2; printf("\n"); }
			if (w1 * x1 + w2 * x2 >= thres) result = 1;
			printf("%d  ", result);
		}
	}

	return result;
}
*/

int main(void) {

	int check = 0, count = 0, and_or = 0;

	printf("w1, w2, threshold의 값을 입력하시오 : ");
	scanf("%f %f %f", &w1, &w2, &thres);
	
	printf("OR(0) 혹은 AND(1) 연산을 선택하세요 : ");
	scanf("%d", &and_or);

	//t[0]이면 or, t[1]이면 and를 사용할 수 있도록함
	// (0, 0), (0, 1), (1, 0), (1, 1) 의 결과 기대값
	int t[2][4] = { {0,1,1,1}, {0,0,0,1} };
	float x[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} };
	
	printf("\n입력 좌표 : %f * x1 + %f * x2 = %f", w1, w2, thres);

	//PlayPerceptron();

	if (and_or == 0) printf("\n\nOR 연산 시작\n");
	else printf("\n\nAND 연산 시작\n");
	
	while (check != 4) {
		check = 0;
		for (int i = 0; i < 4; i++) {
			check += AND_OR(x[i][0], x[i][1], t[and_or], i);
		}
		count++;
		if (check == 4) {
			if (and_or == 0) { 
				printf("\nOR 성립!"); 
				printf("\nw1 = %f, w2 = %f, thres = %f", w1, w2, thres);
				printf("\nOR로 변환한 좌표 : "); 
			}
			else {
				printf("\nAND 성립");
				printf("\nw1 = %f, w2 = %f, thres = %f", w1, w2, thres);
				printf("\nAND로 변환한 좌표 : ");
			}

			printf("%f * x1 + %f * x2 = %f", w1, w2, thres);
		}
		if (count >= 100) {
			printf("연산에 실패했습니다.");
			break;
		}
	}

	//PlayPerceptron();

	return 0;
}