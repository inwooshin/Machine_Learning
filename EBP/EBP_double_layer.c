#include <stdio.h>
#include <math.h>
#define w_first 3
#define w_second 15
#define bias 1
#define eta 0.2

//������ w_range �� ���� ������ ������ ������ ���� �� �ִ�. 
//bias �� ���Կ��θ� 1(�ϴ� ��)�� 0(���ϴ� ��)���� ��Ÿ����. 
//eta �� ���� ������ �����Ѵ�.

//w���� ���Ƿ� �����ߴ�. 
double w[2][15] = { {1.5, 1.4, 1.3, 1.2, 1.1, 1.5, 1.4, 1.3, 1.2, 1.1, 1.5, 1.4, 1.3, 1.2, 1.1},
						{-1.5, -1.4, -1.3, -1.2, -1.1, -1.0, -0.9,-0.8, -0.7, -0.6, -0.5, -1.6, -1.7, -1.8, -1.9} };
double w_middle[15][15] = { {1.1, 1.2, 1.3, 1.4, 1.5, 1.1, 1.2, 1.3, 1.4, 1.5, 1.1, 1.2, 1.3, 1.4, 1.5},
						{ -1.1, -1.2, -1.3, -1.4, -1.5, -1.1, -1.2, -1.3, -1.4, -1.5, -1.1, -1.2, -1.3, -1.4, -1.5},
					{1.5, 1.4, 1.3, 1.2, 1.1, 1.5, 1.4, 1.3, 1.2, 1.1, 1.5, 1.4, 1.3, 1.2, 1.1},};
double w_last[15] = { 0.5, -0.4, 0.3, -0.2, 0.1, -0.2, -0.3, 0.4, -0.5, 0.6, -0.7, 0.8, -0.9, 1.0, -1.1 };
double w_bias[2][15] = { {-2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6},
						{-2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6} };
double w_bias_output = -3;
//U�� ���� w �� ������ �Ļ��Ǵ� ������ �ʱ� �������� ������ ���̹Ƿ� 0���� ���´�.
double U[2][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
double last_U = 0;

double delta[2][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
double last_delta = 0;

double err = 0;

void EBP(double x1, double x2, double t) {
	double S = 0, S_output = 0; 
	double S_middle[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	//input ���� �߰� ���̾���� w ���� ���Ѵ�.
	for (int i = 0; i < w_first; i++) {
		S = x1* w[0][i] + x2 * w[1][i];
		if(bias == 1) S += w_bias[0][i]; //���̾�� ����� ��쿡�� ���̾ ���� S�� �����ش�.

		//�߰����̾��� �� S ���� ���� ������ U ���� ���Ѵ�.
		U[0][i] = 1 / (1 + exp(-S));
	}

	for (int i = 0; i < w_second; i++) {
		for (int j = 0; j < w_first; j++) {
			//���� U ���� ���� ��´��� S ���� ���Ѵ�.
			S_middle[i] += U[0][j] * w_middle[j][i];
		}
		//���̾�� �Է��� ��쿡�� ��´��� S ���� ���̾�� w���� �����ش�.
		if (bias == 1) S_middle[i] += w_bias[1][i];
		
		U[1][i] = 1 / (1 + exp(-S_middle[i]));
		S_output += U[1][i] * w_last[i];
	}

	if (bias == 1) S_output += w_bias_output;
	
	last_U = 1 / (1 + exp(-S_output));

	//error ���� �� epoch(50��)�� ����ϱ� ������ += �� ����ؼ� 50���� �����ش�.
	err += fabs(t - last_U);

	//���� U ���� ���� t ���� ���� ��´��� delta ���� ���Ѵ�.
	last_delta = (t - last_U) * last_U * (1 - last_U);

	//��´��� delta ���� ���� �߰� ���̾��� ������ �ش��ϴ� delta ���� ���Ѵ�.
	for (int i = 0; i < w_second; i++) {
		delta[1][i] = U[1][i] * (1 - U[1][i]) * last_delta * w_last[i];
	}
	
	for (int i = 0; i < w_first; i++){
		double allDelta = 0;
		for (int j = 0; j < w_second; j++){
			allDelta += delta[1][j] * w_middle[i][j];
		}
		delta[0][i] = U[0][i] * (1 - U[0][i]) * allDelta;
	}

	//���� ��Ÿ�� ������ ��� w�� ��ȭ���� �����ش�.
	for (int i = 0; i < w_first; i++) {
		for (int j = 0; j < w_second; j++) {
			w_middle[i][j] += eta * delta[1][j] * U[0][i];
		}
		w[0][i] += eta * delta[0][i] * x1;
		w[1][i] += eta * delta[0][i] * x2;
		w_bias[0][i] += eta * delta[0][i];
	}

	for (int i = 0; i < w_second; i++) {
		w_last[i] += eta * last_delta * U[1][i];
		w_bias[1][i] += eta * delta[1][i];
	}

	//��´ܿ� ����� bias�� w���� ��ȭ���� �����ش�.
	w_bias_output += eta * last_delta;
}

/*
int GridTest(double x1, double x2) {
	double S = 0, S_output = 0;
	double U_tmp[11] = { 0,0,0,0,0,0,0,0,0,0,0 };

	//x1,x2 �� �н��� ���� ���� w �� ������ S ���� ���ϰ� �� ���� �ش��ϴ� U ���� ���Ѵ�.
	//�� ���ڿ� ���� �׽�Ʈ�̱� ������ �������� U�� �ƴ�, U_tmp ��� �迭�� ���� �Լ��� �����ؼ� ����Ѵ�.
	for (int i = 0; i < w_first; i++) {
		if (bias == 1) S = x1 * w1_input[i] + x2 * w2_input[i] + w_bias[i];
		else S = x1 * w1_input[i] + x2 * w2_input[i];

		U_tmp[i] = 1 / (1 + exp(-S));
	}

	//��´��� S �� ���Ѵ�.
	for (int i = 0; i < w_first; i++) {
		S_output += U_tmp[i] * w_output[i];
	}

	//���̾�� ���� �ÿ� ���̾ ���� S���� �����ش�.
	if (bias == 1) S_output += w_bias[w_first];

	//�� ������ ��´��� U�� ���Ѵ�.
	U_tmp[w_first] = 1 / (1 + exp(-S_output));
	
	//U ���� 0.5 ���� ũ�ų� ���� ��쿡�� 1�� �����ϰ� �׷��� ���� ��� 0�� �����Ѵ�
	if (U_tmp[w_range] > 0.5 || fabs(U_tmp[w_range] - 0.5) < 0.000001) return 1;
	else return 0;
}
*/

void set_w() {
	if (w_first > 3) {
		for (int i = 3; i < w_first; i++) {
			printf("%d, ", i);
			for (int j = 0; j < w_second; j++) {
				w_middle[i][j] = w_middle[i % 2 + 1][j] + (0.05 * (i % 5));
				printf("%.2f ", w_middle[i][j]);
			}
			printf("\n");
		}
	}
}

int main() {

	set_w();

	//�������� ���� ���ϰ�, �н���ų ��ǲ�����͸� ���� ����, �����׽�Ʈ�� �ؼ� ������� ������ ������ open �Ѵ�.
	FILE* errFd = fopen("error.txt", "w"), *fin = fopen("fin.txt", "r"), *grid = fopen("grid.txt", "w");	

	double x1 = 0, x2 = 0, t = 0;
	int once = 0, grid_t = 0, count1 = 0, count2 = 0, gridError = 0;

	//fin.txt ���Ͽ��� �׽�Ʈ ���� �о�� 200���� epoch��ŭ�� ����ģ��.
	for (int i = 0; i < 400; i++) {
		rewind(fin);
		err = 0;
		while (fscanf(fin, "%lf %lf %lf\n", &x1, &x2, &t) != EOF) {
			EBP(x1, x2, t);
		}
		//�� epoch ������ error ���� ����Ѵ�.
		fprintf(errFd, "%lf\n", err);
	}

	fclose(errFd);

	//w30 w31 w32 w40 w41 w42 ������ �� �� �ֵ��� ���� ����Ѵ�.
	for(int i = 0; i < w_first; i++){
		printf("W%d%d : %lf\n", i + 3, 0, w_bias[0][i]);
		printf("W%d%d : %lf\n", i + 3, 1, w[0][i]);
		printf("W%d%d : %lf\n", i + 3, 2, w[1][i]);
	}

	for (int i = 0; i < w_first; i++) {
		printf("W%d%d : %lf\n", w_first + 3 + i, 0, w_bias[0][i]);
		for (int j = 0; j < w_second; j++) {
			printf("W%d%d : %lf\n", w_first + 3 + i, j + 3, w_middle[i][j]);
		}
	}

	//���� �߰� layer �� ������ w ���� ����� ���Ŀ� output �ʿ� ����� w ���� ����Ѵ�.
	for (int i = 0; i < w_second; i++) {
		printf("W%d,%d : %lf\n", w_first + w_second + 3, w_first + 3 + i, w_last[i]);
	}

	//�����׽�Ʈ�� �����Ѵ�. ������ x�� -2 to 3, y�� -3 to 2 �̴�. 0.5 �� �������� �Ѵ�.
	//����� �� ��ǥ�� �׿� �ش��ϴ� ������ �������� ���� ��� ���̴�.
	/*
	for (double j = 2; j >= -3; j -= 0.5) {
		for (double i = -2; i <= 3; i += 0.5) {
			fprintf(grid,"%lf %lf %d\n", i, j,GridTest(i, j));
		}
	}
	*/

	/*
	fclose(grid);

	FILE* gridCheck = fopen("grid.txt", "r");

	// �����׽�Ʈ�� ���� �� ���� ����� �������� Ȯ���Ѵ�. 
	//�׸��� error ���� �ִ� �ش� ��ǥ�� ����Ѵ�.
	while (fscanf(gridCheck, "%lf %lf %d\n", &x1, &x2, &grid_t) != EOF) {
		if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && grid_t == 1) {}
		else if (grid_t == 1) {
			if (once == 0) { //1���� Wrong...! �� ����ϵ��� �Ѵ�.
				printf("\nWrong...!\n");
				once = 1;
			}
			gridError++;	
			printf("x1 : %lf, x2 : %lf, t : %d\n", x1, x2, t);
		}
		else if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && grid_t == 0) {
			if (once == 0) {
				printf("\nWrong...!\n");
				once = 1;
			}
			gridError++;
			printf("x1 : %lf, x2 : %lf, t : %d\n", x1, x2, t);
		}
	}

	//�����׽�Ʈ �� ��ü error �� ������ ����Ѵ�.
	printf("grid error : %d\n", gridError);

	fclose(gridCheck);
	*/
	fclose(fin);


	return 0;
}