#include <stdio.h>
#include <math.h>

float w1 = 0, w2 = 0, thres = 0;
float before = 0;

int AND_OR(int x1, int x2, int t[], int i) {
	int result = 0;
	
	if (w1 * x1 + w2 * x2 > thres || fabs(w1 * x1 + w2 * x2 - thres) < 0.000001) result = 1;
	else result = 0;

	if (result == t[i]) return 1;
	else if (result == 1) {
		if (x1 != 0) w1 /= 2;
		if (x2 != 0) w2 /= 2;
	}
	else if (result == 0) {
		if (x1 != 0) w1 *= 1.5;
		if (x2 != 0) w2 *= 1.5;
	}

	return 0;
}

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

int main(void) {

	int check = 0, count = 0, and_or = 0;

	printf("w1, w2, threshold�� ���� �Է��Ͻÿ� : ");
	scanf("%f %f %f", &w1, &w2, &thres);
	
	printf("OR(0) Ȥ�� AND(1) Ȥ�� EX-OR(2) ������ �����ϼ��� : ");
	scanf("%d", &and_or);

	int t[3][4] = { {0,1,1,1}, {0,0,0,1}, {0,1,1,0} }; // OR, AND, EX-OR logic
	int x[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} }; // x1, x2 �Է�
	
	printf("\n�Է� ��ǥ : %f * x1 + %f * x2 = %f", w1, w2, thres);

	if (and_or == 0) printf("\n\nOR ���� ����\n");
	else if(and_or == 1) printf("\n\nAND ���� ����\n");
	else if(and_or == 2) printf("\n\nAND ���� ����\n");
	
	while (check != 4) {
		check = 0;
		for (int i = 0; i < 4; i++) {
			check += AND_OR(x[i][0], x[i][1], t[and_or], i);
		}
		count++;
		if (check == 4) {
			if (and_or == 0) { 
				printf("\nOR ����!"); 
				printf("\nw1 = %f, w2 = %f, thres = %f", w1, w2, thres);
				printf("\nOR�� ��ȯ�� ��ǥ : "); 
			}
			else {
				printf("\nAND ����");
				printf("\nw1 = %f, w2 = %f, thres = %f", w1, w2, thres);
				printf("\nAND�� ��ȯ�� ��ǥ : ");
			}

			printf("%f * x1 + %f * x2 = %f", w1, w2, thres);
		}
		if (count >= 100) {
			printf("���꿡 �����߽��ϴ�.");
			break;
		}
	}

	PlayPerceptron();

	return 0;
}