#include <stdio.h>
#include <math.h>

float w1 = 0, w2 = 0, n = 0.01, thres = 3;
float before = 0, error = 0;

//AND �� OR �� ���߾ �����ϰ� �ϴ� �Լ�
int AND_OR(int x1, int x2, int t[], int i) {
	//�Լ��� ȣ���Ҷ����� y�� ���� �޶� ȣ���� ������ �����ϵ��� �Ѵ�.
	float bef_y = w1 * x1 + w2 * x2;
	float y = 0;

	//if then �� �������� ���� �ʰ� ������ ����Ѵ�.
	if (bef_y > thres || fabs(bef_y - thres) < 0.000001) y = 1;

	//if then �� ����� �ƴ� ���� �������� ����ȭ��Ų��.
	w1 = w1 + (n * (t[i] - y) * x1);
	w2 = w2 + (n * (t[i] - y) * x2);

	//������ �� ���� �����Ѵ� for ���� 0~3 ���� �� 4���� ��Ʈ�� error �� ���� ��������.
	error += (t[i] - y) * (t[i] - y) * 0.5;

	return y == t[i];
}
int main(void) {
	int check = 0, count = 0, and_or = 0;
	
	//w1, w2 �� ����
	printf("w1, w2�� ���� �Է��Ͻÿ� : ");
	scanf("%f %f", &w1, &w2);
	
	//���� ����
	printf("OR(0) Ȥ�� AND(1) Ȥ�� EX-OR(2) ������ �����ϼ��� : ");
	scanf("%d", &and_or);

	int t[3][4] = { {0,1,1,1}, {0,0,0,1}, {0,1,1,0} }; // OR, AND, EX-OR logic
	int x[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} }; // x1, x2 �Է�
	
	// �Է��� w1, w2 �� ������ �� �Լ��� �����ش�.
	printf("\n�Է� ��ǥ : %f * x1 + %f * x2 = y", w1, w2);
	
	//� ������ �ν��ϰ� �����ϴ��� �����ش�.
	if (and_or == 0) printf("\n\nOR ���� ����\n");
	else if(and_or == 1) printf("\n\nAND ���� ����\n");
	else if(and_or == 2) printf("\n\nAND ���� ����\n");
	
	//while ������ w1, w2 �� ������ ��� ���ļ� error�� ���� �پ�鵵�� 300�� �����Ѵ�.
	while (check != 4) {
		//�� �� cycle ���� error�� ���� for������ 4���� �����ϰ� ���� w1, w2 ���꿡�� �ʱ�ȭ�ȴ�.
		error = 0, check = 0;
		//4���� w1, w2 ���� �� 4�� ���� ������ error �� ������ ���Ѵ�.
		for (int i = 0; i < 4; i++) {
			check += AND_OR(x[i][0], x[i][1], t[and_or], i);
		}
		printf("w1 = %f, w2 = %f, error = %f\n", w1, w2, error);

		count++;
		//300 ���� ������ �ݺ����� �ߴ��Ѵ�.
		if (count >= 300) {
			break;
		}
	}

	//���������� ����� w1, w2 �� ���� ��Ÿ����.
	printf("\n%.3f * x1 + %.3f * x2, error = %f, count = %d", w1, w2, error, count);
	
	return 0;
}