#include <stdio.h>
#include <math.h>

double Min = 0.000001;
double before = 0;

// x2 = -x1 + 0.1 ��, x1 + x2 = 0.1 �� ���Ƿ� ����Ͽ���.
void perceptron(double x1, double x2) {
	int y = 0;
	if (before != x2) { before = x2; printf("\n"); }
	if (x1 + x2 > 0.1) y = 1;

	// fabs �� ������ ��Ÿ���� �Լ��̴�.
	// x1 �� x2 �� ���� ������ 0.1�� �� ���� ���ٰ� �ص� 0.0 ���� �������� ���� �ƴ�
	// 0.000000000000000056 ���� ������ ���� �����. 
	// x1, x2 �� �� ��� ���� ������ ���� Ŭ�� �𸣱� ������
	// - �� ���� ���� �־� ������ ���ְ�,
	// �� ������ ���� 0.000001 ���� ���� ���� ������ ������ �����ϰ�
	// ��� ���� 0.000001 ���� ���� ��쿡�� ���� ������ �����Ѵ�.
	// �� �ݴ�� ũ�ų� ���� ����ε�, �̷��� ���� ���� ���� ���̴�.
	if (fabs(x1 + x2 - 0.1) < Min) y = 1;

	//printf("%.1lf - (%.1f, %.1f) = %d\n",x1 + x2, x1, x2, y);
	printf("%d   ", y);
}

int main(void) {

	// ���� �׽�Ʈ �ڷ� �Է��ϱ�
	FILE* fd = fopen("testFile.txt", "w");

	for (double x2 = 1; x2 >= -1; x2 = x2 - 0.1) {
		for (double x1 = -1; x1 <= 1; x1 = x1 + 0.1) {
			fprintf(fd, "%lf %lf\n", x1, x2);
		}
	}

	fclose(fd);

	FILE* fout = fopen("testFile.txt", "r");

	int i = 1;
	double x1, x2;
	//int id = fscanf(fd, "%lf %lf\n", &x, &y);
	//printf("id : %d, x : %.1lf, y : %.1lf", id, x, y);

	while (fscanf(fout, "%lf %lf\n", &x1, &x2) != EOF) {
		//printf("%d : %.1lf %.1lf\n", i++, x1, x2);
		perceptron(x1, x2);
	}

	fclose(fout);
}