#include <stdio.h>
#include <math.h>
#define w_range 3
#define bias 0
#define eta 0.9

double w1_input[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w2_input[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w_output[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w_bias[11] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };

double U[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double delta[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

FILE* errFd;
double err = 0;

void EBP(double x1, double x2, double t) {
	double S = 0, S_output = 0;
	for (int i = 0; i < w_range; i++) {
		if(bias == 1) S = x1* w1_input[i] + x2 * w2_input[i] + w_bias[i];
		else S = x1* w1_input[i] + x2 * w2_input[i];

		U[i] = 1 / (1 + exp(-S));
	}

	for (int i = 0; i < w_range; i++) {
		S_output += U[i]* w_output[i];
	}

	if (bias == 1) S_output += w_bias[w_range];
	
	U[w_range] = 1 / (1 + exp(-S_output));
	
	err += fabs(t - U[w_range]);

	delta[w_range] = (t - U[w_range]) * U[w_range] * (1 - U[w_range]);

	for (int i = w_range - 1; i >= 0; i--) {
		delta[i] = U[i] * (1 - U[i]) * delta[w_range] * w_output[i];
	}

	for (int i = 0; i < w_range; i++) {
		w_output[i] = w_output[i] + eta * delta[w_range] * U[i];
		w1_input[i] = w1_input[i] + eta * delta[i] * x1;
		w2_input[i] = w2_input[i] + eta * delta[i] * x2;
		w_bias[i] = w_bias[i] + eta * delta[i];
	}
	w_bias[w_range] += eta * delta[w_range];
}

int GridTest(double x1, double x2) {
	double S = 0, S_output = 0;
	double U_tmp[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0; i < w_range; i++) {
		if (bias == 1) S = x1 * w1_input[i] + x2 * w2_input[i] + w_bias[i];
		else S = x1 * w1_input[i] + x2 * w2_input[i];

		U_tmp[i] = 1 / (1 + exp(-S));
	}

	for (int i = 0; i < w_range; i++) {
		S_output += U_tmp[i] * w_output[i];
	}
	if (bias == 1) S_output += w_bias[w_range];

	U_tmp[w_range] = 1 / (1 + exp(-S_output));

	printf("%lf %lf : %lf\n",x1,x2, U_tmp[w_range]);

	if (U_tmp[w_range] > 0.5) return 1;
	else return 0;
}


int main() {
	errFd = fopen("error.txt", "w");

	FILE* fout = fopen("testFile.txt", "r");

	double x1 = 0, x2 = 0, t = 0;

	int count1 = 0, count2 = 0;

	for (int i = 1; i <= 400; i++) {
		rewind(fout);
		err = 0;
		while (fscanf(fout, "%lf %lf %lf\n", &x1, &x2, &t) != EOF) {
			EBP(x1, x2, t);
		}
		fprintf(errFd, "%lf\n", err);
	}

	fclose(fout);

	for (int i = 0; i < w_range; i++) {
		printf("W%d%d : %lf\n", i + 3, 1, w1_input[i]);
		printf("W%d%d : %lf\n", i + 3, 2, w2_input[i]);;
	}

	for (int i = 0; i < w_range; i++) {
		printf("W%d,%d : %lf\n", w_range + 3, i + 3, w_output[i]);
	}

	fclose(errFd);

	FILE* grid = fopen("grid.txt", "w");

	for (double j = 2; j >= -3; j -= 0.5) {
		for (double i = -2; i <= 3; i += 0.5) {
			fprintf(grid,"%lf %lf %d\n", i, j,GridTest(i, j));
		}
	}

	fclose(grid);

	FILE* gridCheck = fopen("grid.txt", "r");

	while (fscanf(gridCheck, "%lf %lf %lf\n", &x1, &x2, &t) != EOF) {
		if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && fabs(t - 1) < 0.000001) {
			count1++;
		}
		else if (t < 0.000001) count2++;
		else printf("x1 : %lf, x2 : %lf, t : %d\n", x1, x2, t);
	}
	printf("count1 : %d, count0 : %d\n", count1, count2);

	fclose(gridCheck);

	return 0;
}