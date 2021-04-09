#include <stdio.h>
#include <math.h>

float thres = 0, n = 0.01;
float before = 0, error = 0;

//AND �� OR �� ���߾ �����ϰ� �ϴ� �Լ�
int AND_OR(int x1, int x2,float w1, float w2, int t[], int i) {
	//�Լ��� ȣ���Ҷ����� y�� ���� �޶� ȣ���� ������ �����ϵ��� �Ѵ�.
	int y = 0;

	//if then �� �������� ���� �ʰ� ������ ����Ѵ�.
	y = w1 * x1 + w2 * x2;

	//if then �� ����� �ƴ� ���� �������� ����ȭ��Ų��.
	w1 = w1 + (n * (t[i] - y) * x1);
	w2 = w2 + (n * (t[i] - y) * x2);

	//������ �� ���� �����Ѵ� for ���� 0~3 ���� �� 4���� ��Ʈ�� error �� ���� ��������.
	error += (t[i] - y) * (t[i] - y) * 0.5;

	return 0;
}


int main(void) {

	int check = 0, count = 0, and_or = 0;

	//delta rule �� ���� �����ϱ� ���ؼ� ������ �����ش�.
	FILE* fd = fopen("delta_rule.txt", "w");

	printf("OR(0) Ȥ�� AND(1) Ȥ�� EX-OR(2) ������ �����ϼ��� : ");
	scanf("%d", &and_or);

	//or and ex-or ��밪�� �־��� �� x�� ��ǥ�� ���߹迭�� �����ؼ� ����ȭ�Ѵ�.
	int t[3][4] = { {0,1,1,1}, {0,0,0,1}, {0,1,1,0} }; // OR, AND, EX-OR logic
	int x[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} }; // x1, x2 �Է�

	if (and_or == 0) printf("\n\nOR ���� ����\n");
	else if (and_or == 1) printf("\n\nAND ���� ����\n");
	else if (and_or == 2) printf("\n\nAND ���� ����\n");

	//������ -10, 10 ������ ��ǥ�� �ΰ� ���� for���� �����ؼ� error�� �����׽�Ʈ�� �����Ѵ�.
	for(float w1_for = 10 ; w1_for >= -10 ; w1_for -= 0.5){
		for (float w2_for = 10; w2_for >= -10; w2_for -= 0.5) {
			error = 0; //4���� ��Ʈ�� ������ ���� ���� w1,w2 �� ��ǥ�� ��Ÿ�����ϱ� ������ �ʱ�ȭ�Ѵ�.
			for (int i = 0; i < 4; i++) {
				//�Է��� and �Ǵ� or �� ���߾ error ���� ���ϴ� and or �Լ��� ȣ���Ѵ�.
				AND_OR(x[i][0], x[i][1], w1_for, w2_for, t[and_or], i);
			}
			
			//error ���� w1, w2 ���� ����ϰ� ���Ͽ� �����Ѵ�.
			printf("w1 = %f, w2 = %f, err = %f\n", w1_for, w2_for, error);
			fprintf(fd,"%f %f %f\n", w1_for, w2_for, error);
		}
	}


	return 0;
}