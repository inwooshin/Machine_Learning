#include <stdio.h>
#include <math.h>
#define w_range 10
#define bias 1
#define eta 0.9

//������ w_range �� ���� ������ ������ ������ ���� �� �ִ�. bias �� ���Կ��θ� 1(�ϴ� ��)�� 0(���ϴ� ��)���� ��Ÿ����. 
//eta �� ���� ������ �����Ѵ�.

//w���� ���Ƿ� �����ߴ�. 
double w1_input[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w2_input[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w_output[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w_bias[11] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5};

//U�� ���� w �� ������ �Ļ��Ǵ� ������ �ʱ� �������� ������ ���̹Ƿ� 0���� ���´�.
double U[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double delta[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

double err = 0;

void EBP(double x1, double x2, double t) {
	double S = 0, S_output = 0; 
	//input ���� �߰� ���̾���� w ���� ���Ѵ�.
	for (int i = 0; i < w_range; i++) {
		S = x1* w1_input[i] + x2 * w2_input[i];
		if(bias == 1) S += w_bias[i]; //���̾�� ����� ��쿡�� ���̾ ���� S�� �����ش�.

		//�߰����̾��� �� S ���� ���� ������ U ���� ���Ѵ�.
		U[i] = 1 / (1 + exp(-S));

		//���� U ���� ���� ��´��� S ���� ���Ѵ�.
		S_output += U[i] * w_output[i];
	}

	//���̾�� �Է��� ��쿡�� ��´��� S ���� ���̾�� w���� �����ش�.
	if (bias == 1) S_output += w_bias[w_range];
	
	//���� ��´��� S������ ��´��� U ���� ���Ѵ�.
	U[w_range] = 1 / (1 + exp(-S_output));
	
	//error ���� �� epoch(50��)�� ����ϱ� ������ += �� ����ؼ� 50���� �����ش�.
	err += fabs(t - U[w_range]);

	//���� U ���� ���� t ���� ���� ��´��� delta ���� ���Ѵ�.
	delta[w_range] = (t - U[w_range]) * U[w_range] * (1 - U[w_range]);

	//��´��� delta ���� ���� �߰� ���̾��� ������ �ش��ϴ� delta ���� ���Ѵ�.
	for (int i = w_range - 1; i >= 0; i--) {
		delta[i] = U[i] * (1 - U[i]) * delta[w_range] * w_output[i];
	}

	//���� ��Ÿ�� ������ ��� w�� ��ȭ���� �����ش�.
	for (int i = 0; i < w_range; i++) {
		w_output[i] = w_output[i] + eta * delta[w_range] * U[i];
		w1_input[i] = w1_input[i] + eta * delta[i] * x1;
		w2_input[i] = w2_input[i] + eta * delta[i] * x2;
		w_bias[i] = w_bias[i] + eta * delta[i];
	}

	//��´ܿ� ����� bias�� w ���� ��ȭ���� �����ش�.
	w_bias[w_range] += eta * delta[w_range];
}

int GridTest(double x1, double x2) {
	double S = 0, S_output = 0;
	double U_tmp[11] = { 0,0,0,0,0,0,0,0,0,0,0 };

	//x1,x2 �� �н��� ���� ���� w �� ������ S ���� ���ϰ� �� ���� �ش��ϴ� U ���� ���Ѵ�.
	//�� ���ڿ� ���� �׽�Ʈ�̱� ������ �������� U�� �ƴ�, U_tmp ��� �迭�� ���� �Լ��� �����ؼ� ����Ѵ�.
	for (int i = 0; i < w_range; i++) {
		if (bias == 1) S = x1 * w1_input[i] + x2 * w2_input[i] + w_bias[i];
		else S = x1 * w1_input[i] + x2 * w2_input[i];

		U_tmp[i] = 1 / (1 + exp(-S));
	}

	//��´��� S �� ���Ѵ�.
	for (int i = 0; i < w_range; i++) {
		S_output += U_tmp[i] * w_output[i];
	}

	//���̾�� ���� �ÿ� ���̾ ���� S���� �����ش�.
	if (bias == 1) S_output += w_bias[w_range];

	//�� ������ ��´��� U�� ���Ѵ�.
	U_tmp[w_range] = 1 / (1 + exp(-S_output));
	
	//U ���� 0.5 ���� ũ�ų� ���� ��쿡�� 1�� �����ϰ� �׷��� ���� ��� 0�� �����Ѵ�
	if (U_tmp[w_range] > 0.5 || fabs(U_tmp[w_range] - 0.5) < 0.000001) return 1;
	else return 0;
}


int main() {
	//�������� ���� ���ϰ�, �н���ų ��ǲ�����͸� ���� ����, �����׽�Ʈ�� �ؼ� ������� ������ ������ open �Ѵ�.
	FILE* errFd = fopen("error.txt", "w"), *fin = fopen("fin.txt", "r"), *grid = fopen("grid.txt", "w");	

	double x1 = 0, x2 = 0, t = 0;
	int once = 0, grid_t = 0, count1 = 0, count2 = 0, gridError = 0;

	//fin.txt ���Ͽ��� �׽�Ʈ ���� �о�� 200���� epoch��ŭ�� ����ģ��.
	for (int i = 0; i < 200; i++) {
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
	for(int i = 0; i < w_range; i++){
		printf("W%d%d : %lf\n", i + 3, 0, w_bias[i]);
		printf("W%d%d : %lf\n", i + 3, 1, w1_input[i]);
		printf("W%d%d : %lf\n", i + 3, 2, w2_input[i]);;
	}

	//���� �߰� layer �� ������ w ���� ����� ���Ŀ� output �ʿ� ����� w ���� ����Ѵ�.
	for (int i = 0; i < w_range; i++) {
		printf("W%d,%d : %lf\n", w_range + 3, i + 3, w_output[i]);
	}

	//�����׽�Ʈ�� �����Ѵ�. ������ x�� -2 to 3, y�� -3 to 2 �̴�. 0.5 �� �������� �Ѵ�.
	//����� �� ��ǥ�� �׿� �ش��ϴ� ������ �������� ���� ��� ���̴�.
	for (double j = 2; j >= -3; j -= 0.5) {
		for (double i = -2; i <= 3; i += 0.5) {
			fprintf(grid,"%lf %lf %d\n", i, j,GridTest(i, j));
		}
	}

	fclose(grid);

	FILE* gridCheck = fopen("grid.txt", "r");

	// �����׽�Ʈ�� ���� �� ���� ����� �������� Ȯ���Ѵ�. �׸��� error ���� �ִ� �ش� ��ǥ�� ����Ѵ�.
	while (fscanf(gridCheck, "%lf %lf %d\n", &x1, &x2, &grid_t) != EOF) {
		if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && grid_t == 1) {}
		else if (grid_t == 1) {
			if (once == 0) { //1���� Wrong...! �� ����ϵ��� �Ѵ�.
				printf("\nWrong...!\n");
				once = 1;
			}
			gridError++;	
			printf("x1 : %lf, x2 : %lf, t : %d", x1, x2, t);
		}
		else if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && grid_t == 0) {
			if (once == 0) {
				printf("\nWrong...!\n");
				once = 1;
			}
			gridError++;
			printf("x1 : %lf, x2 : %lf, t : %d", x1, x2, t);
		}
	}

	//�����׽�Ʈ �� ��ü error �� ������ ����Ѵ�.
	printf("grid error : %d\n", gridError);

	fclose(gridCheck);
	fclose(fin);

	return 0;
}