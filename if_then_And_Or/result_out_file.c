#include <stdio.h>
#include <math.h>

double Min = 0.000001;
double before = 0;

// x2 = -x1 + 0.1 ��, x1 + x2 = 0.1 �� ���Ƿ� ����Ͽ���.
int perceptron(double x1, double x2) {
	int y = 0;
	if (x1 + x2 > 0.1) y = 1;
	if (before != x2) { before = x2; printf("\n"); }
	
	// fabs �� ������ ��Ÿ���� �Լ��̴�.
	// x1 �� x2 �� ���� ������ 0.1�� �� ���� ���ٰ� �ص� 0.0 ���� �������� ���� �ƴ�
	// 0.000000000000000056 ���� ������ ���� �����. 
	// x1, x2 �� �� ��� ���� ������ ���� Ŭ�� �𸣱� ������
	// - �� ���� ���� �־� ������ ���ְ�,
	// �� ������ ���� 0.000001 ���� ���� ���� ������ ������ �����ϰ�
	// ��� ���� 0.000001 ���� ���� ��쿡�� ���� ������ �����Ѵ�.
	// �� �ݴ�� ũ�ų� ���� ����ε�, �̷��� ���� ���� ���� ���̴�.
	if (fabs(x1 + x2 - 0.1) < Min) y = 1;
	printf("%d  ", y);
	return y;
}

int main(void) {

	// ���� �׽�Ʈ �ڷ� �Է��ϱ�
	FILE* fd = fopen("test.txt", "w");

	for (double x2 = 1; x2 >= -1; x2 = x2 - 0.1) {
		for (double x1 = -1; x1 <= 1; x1 = x1 + 0.1) {
			fprintf(fd, "%.1lf %.1lf\n", x1, x2);
		}
	}

	fclose(fd);

	FILE* fout = fopen("test.txt", "r"), * fw = fopen("output.txt", "w");

	double x1, x2;

	while (fscanf(fout, "%lf %lf\n", &x1, &x2) != EOF) {
		int y = perceptron(x1, x2);
		fprintf(fw, "%d\n", y);
	}

	fclose(fout);
	fclose(fw);
}