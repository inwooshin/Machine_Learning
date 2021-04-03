#include <stdio.h>
#include <math.h>

double Min = 0.000001;
double before = 0;

// x2 = -x1 + 0.1 즉, x1 + x2 = 0.1 을 임의로 사용하였다.
int perceptron(double x1, double x2) {
	int y = 0;
	if (x1 + x2 > 0.1) y = 1;
	if (before != x2) { before = x2; printf("\n"); }
	
	// fabs 는 절댓값을 나타내는 함수이다.
	// x1 와 x2 를 더한 값에서 0.1을 뺀 값이 같다고 해도 0.0 으로 떨어지는 것이 아닌
	// 0.000000000000000056 같이 쓰레기 값을 남긴다. 
	// x1, x2 둘 중 어느 수의 쓰레기 값이 클지 모르기 때문에
	// - 가 나올 수도 있어 절댓값을 해주고,
	// 이 쓰레기 값을 0.000001 보다 작은 값을 쓰레기 값으로 규정하고
	// 결과 값이 0.000001 보다 작은 경우에는 같은 것으로 규정한다.
	// 그 반대는 크거나 같은 경우인데, 이러한 경우는 같지 않은 것이다.
	if (fabs(x1 + x2 - 0.1) < Min) y = 1;
	printf("%d  ", y);
	return y;
}

int main(void) {

	// 구간 테스트 자료 입력하기
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