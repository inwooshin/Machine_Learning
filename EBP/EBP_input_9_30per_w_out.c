#include <stdio.h>
#include <math.h>
#include <time.h>

//���� ���̾��� ��, input �� ��(n), output�� ��, bias ����, eta ���θ� �����Ѵ�.
int hidden = 4;
int n = 10;
int output_count = 2;
int bias = 1;
double eta = 0.025;

int max = 900;
int ErrCount = 0;
int WeightCount = 0;

int allLine = 2257;

//1 - 10 ��° ���̾������ ������ ���ڸ� ������ �� �ִ�.
int hidden_N[10] = { 15,15,15,15,15,15,15,15,15,15 };

double w[10][15] = { {0,}, };
double w_middle[10][15][15] = { { {0,},} , };
double w_last[2][15] = { { 0,} , };
double w_bias[10][15] = { {0,}, };
double w_bias_output[2] = { 0, };

//evaluation Error�� ���� EBP error �� ���� �����ϴ� �����̴�.
double err = 0, evaErr = 0;

//���� U�� delta�� ����
double U[10][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, };
double U_last[2] = { 0 , 0 };
double delta[10][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, };
double last_delta[2] = { 0, 0 };

FILE* weightWrite, * WeightRead;

void EBP(double x[], double t[]) {
	double S = 0, S_output = 0;
	double S_middle[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	//input���� ù��° ���̾�� ���� w ���� �̿��� S������ U ���� ���Ѵ�.
	for (int i = 0; i < hidden_N[0]; i++) {
		S = 0;
		for (int j = 0; j < n; j++) {
			S += x[j] * w[j][i];
		}
		if (bias == 1) S += w_bias[0][i];

		U[0][i] = 1 / (1 + exp(-S));
	}

	//�����̾ �ش��ϴ� u ���� 1��° ���̾��� �������� ������� ���Ѵ�.
	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i + 1]; j++) {
			S = 0;
			for (int k = 0; k < hidden_N[i]; k++) {
				S += U[i][k] * w_middle[i][k][j];
			}
			if (bias == 1) S += w_bias[i + 1][j];

			U[i + 1][j] = 1 / (1 + exp(-S));
		}
	}

	//output �� u ���� ���Ѵ�.
	for (int i = 0; i < output_count; i++) {
		S = 0;
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			S += U[hidden - 1][j] * w_last[i][j];
		}
		if (bias == 1) S += w_bias_output[i];

		U_last[i] = 1 / (1 + exp(-S));
	}

	//output�� ��Ÿ���� ���Ѵ�.
	for (int i = 0; i < output_count; i++) {
		last_delta[i] = (t[i] - U_last[i]) * U_last[i] * (1 - U_last[i]);
		err += fabs(t[i] - U_last[i]);
	}

	//�� �������� hidden ���̾� delta ���� ���Ѵ�.
	for (int i = 0; i < hidden_N[hidden - 1]; i++) {
		double allDelta = 0;
		for (int j = 0; j < output_count; j++) {
			allDelta += last_delta[j] * w_last[j][i];
		}
		delta[hidden - 1][i] = U[hidden - 1][i] * (1 - U[hidden - 1][i]) * allDelta;
	}

	//������ ���̾������ ù��° ���̾���� delta ���� ���Ѵ�.
	for (int i = hidden - 1; i > 0; i--) {
		for (int j = 0; j < hidden_N[i - 1]; j++) {
			double allDelta = 0;
			for (int k = 0; k < hidden_N[i]; k++) {
				allDelta += delta[i][k] * w_middle[i - 1][j][k];\
			}
			delta[i - 1][j] = U[i - 1][j] * (1 - U[i - 1][j]) * allDelta;
		}
	}

	//���� delta ������ input�� ù���̾��� w ���� ��ȭ��Ų��.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < hidden_N[0]; j++) {
			if (w[i][j] >= 0.000001) w[i][j] += eta * delta[0][j] * x[i];
		}
	}

	//���� ���̾� ������ w ���� ��ȭ��Ű�� �ش�Ǵ� bias �� w ���� ��ȭ��Ų��.
	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i]; j++) {
			for (int k = 0; k < hidden_N[i + 1]; k++) {
				if (w_middle[i][j][k] >= 0.000001) w_middle[i][j][k] += eta * delta[i + 1][k] * U[i][j];
			}
			if (w_bias[i][j] >= 0.000001) w_bias[i][j] += eta * delta[i][j];
		}
	}

	//�� ������ ���� ���̾ weight �� �ٲ��ش�.
	for (int i = 0; i < hidden_N[hidden - 1]; i++) {
		if (w_bias[hidden - 1][i] >= 0.000001) w_bias[hidden - 1][i] += eta * delta[hidden - 1][i];
	}

	//output ���� ������ ���̾������ weight ���� ��ȭ��Ų��. �׸��� output ��
	// ����Ǿ��ִ� bias �� ���� ������Ų��.
	for (int i = 0; i < output_count; i++) {
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			if (w_last[i][j] >= 0.000001)w_last[i][j] += eta * last_delta[i] * U[hidden - 1][j];
		}
		if (w_bias_output[i] >= 0.000001) w_bias_output[i] += eta * last_delta[i];
	}
}

int GridTest(double x[], double t[], int evaluation) {
	double S = 0, S_output = 0;
	double U_tmp[10][15] = { {0,}, {0,} };
	double U_last_tmp[2] = { 0, };

	//input���� ù��° ���̾�� ���� w ���� �̿��� S������ U ���� ���Ѵ�.
	for (int i = 0; i < hidden_N[0]; i++) {
		S = 0;
		for (int j = 0; j < n; j++) {
			S += x[j] * w[j][i];
		}
		if (bias == 1) S += w_bias[0][i];

		U_tmp[0][i] = 1 / (1 + exp(-S));
	}

	//�����̾ �ش��ϴ� u ���� 1��° ���̾��� �������� ������� ���Ѵ�.
	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i + 1]; j++) {
			S = 0;
			for (int k = 0; k < hidden_N[i]; k++) {
				S += U_tmp[i][k] * w_middle[i][k][j];
			}
			if (bias == 1) S += w_bias[i + 1][j];

			U_tmp[i + 1][j] = 1 / (1 + exp(-S));
		}
	}

	//output �� u ���� ���Ѵ�.
	for (int i = 0; i < output_count; i++) {
		S = 0;
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			S += U_tmp[hidden - 1][j] * w_last[i][j];
		}
		if (bias == 1) S += w_bias_output[i];

		U_last_tmp[i] = 1 / (1 + exp(-S));
	}

	int y = 0;

	if (U_last_tmp[0] > 0.5 || fabs(U_last_tmp[0] - 0.5) < 0.000001) y = 1;
	else y = 0;

	//evaluation Test �� �ƴϰ� �����׽�Ʈ�� ��쿡��, y ���� �����Ѵ�.
	if (evaluation == 0) return y;

	//evaluation Test�̸� Error�� ���� ������Ű�� �Լ��� �����Ѵ�.
	evaErr += fabs(t[0] - U_last_tmp[0]);

	return 0;
}

//-2 ~ 2 ������ weight ���� �����Ѵ�.
double rate() {
	return (double)(rand() % 20) / 10 - 1.0;
}

void writeChoose(int write, double* weight_tmp) {
	if (write == 1) {
		fprintf(weightWrite, "%lf\n", *weight_tmp);
	}
	else if (write == 2) {
		fscanf(WeightRead, "%lf\n", weight_tmp);
		if (fabs(*weight_tmp) < 0.3) *weight_tmp = 0;
	}
	else *weight_tmp = rate();
}

//weight �� �����ϰ� �����Ѵ�. seed ���� 1�� �־���.
void set_w(int write) {
	srand(1);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < hidden_N[0]; j++) {
			writeChoose(write, &w[i][j]);
		}
	}

	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i]; j++) {
			for (int k = 0; k < hidden_N[i + 1]; k++) {
				writeChoose(write, &w_middle[i][j][k]);
			}
		}
	}

	for (int i = 0; i < output_count; i++) {
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			writeChoose(write, &w_last[i][j]);
		}
	}

	for (int i = 0; i < hidden; i++) {
		for (int j = 0; j < hidden_N[i]; j++) {
			writeChoose(write, &w_bias[i][j]);
		}
	}

	for (int i = 0; i < output_count; i++) {
		writeChoose(write, &w_bias_output[i]);
	}
}

void getEvaRealData(FILE* fin, FILE* eva, FILE* realData) {
	double x_tmp[9], t_tmp[2];
	int randIn = 0;

	while (fscanf(fin, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x_tmp[0], &x_tmp[1], &x_tmp[2], &x_tmp[3], &x_tmp[4],
		&x_tmp[5], &x_tmp[6], &x_tmp[7], &x_tmp[8], &t_tmp[0]) != EOF) {
		if (rand() % 5 == 0 && randIn < allLine / 10) {
			fprintf(eva, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", x_tmp[0], x_tmp[1], x_tmp[2], x_tmp[3], x_tmp[4],
				x_tmp[5], x_tmp[6], x_tmp[7], x_tmp[8], t_tmp[0]);
			randIn++;
		}
		else fprintf(realData, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", x_tmp[0], x_tmp[1], x_tmp[2], x_tmp[3], x_tmp[4],
			x_tmp[5], x_tmp[6], x_tmp[7], x_tmp[8], t_tmp[0]);
	}

	fclose(realData);
	fclose(eva);
}

void getETC(FILE* architecture, FILE* parameter) {
	fscanf(architecture, "%d, %d, %d, %d, %d, %d", &n, &hidden_N[0], &hidden_N[1], &hidden_N[2], &hidden_N[3], &output_count);
	fscanf(parameter, "%lf\n%d\n%d", &eta, &ErrCount, &WeightCount);

	fclose(architecture);
	fclose(parameter);
}

//������ ��������ϸ� 
//1. TrainingData0612 ��������
//2. TestData0612.txt ���� ��� �ִ��� ������
//3. max ������
//4. outputData.dat ���Ͽ� ��ǥ�� �־���ϴ���

//set_w 0 rand, 1�̸� weight�� ���� ���ִ� ��, 2�� ������ w���� �����ϴ� ���̴�.
int main() {
	//w���� [15][15] �� �迭�̹Ƿ� ���� �������ش�.
	FILE* architecture = fopen("architecture.dat", "r"), * parameter = fopen("parameter.dat", "r"),
		* fin = fopen("TrainingData0612.txt", "r");
	FILE* eva = fopen("evaData.txt", "w"), * realData = fopen("realData.txt", "w");

	int randIn = 0, onLearning = 0, weightSelect = 0, weightNumber;

	//get evaData.txt ����, realData.txt ����!
	getEvaRealData(fin, eva, realData);
	realData = fopen("realData.txt", "r");
	eva = fopen("evaData.txt", "r");

	//architecture�� parameter���Ͽ��� ���� �о�´�.
	getETC(architecture, parameter);

	printf("test(0) or �н�(1) : ");
	scanf("%d", &onLearning);

	if (onLearning == 1) {
		printf("Weight ���� ���� ������(0) or rand(1) : ");
		scanf("%d", &weightSelect);

		if (weightSelect == 1) {
			set_w(0); //0�̸� random���� weight ����
		}
		else if (weightSelect == 0) {
			printf("Weight�� �����ϼ���! : ");
			scanf("%d", &weightNumber);

			//�Է��� epoch ��°�� weight �� �о����
			char tmp[200];
			sprintf(tmp, "C:\\Users\\dkrle\\source\\repos\\ML_test\\ML_test\\weight\\weight%d.dat", weightNumber);
			WeightRead = fopen(tmp, "r");

			set_w(2); //�о�� weight �� �ʱ�ȭ�Ѵ�.

			//test�� ���ؼ� ��ó���� weight ���� ����Ѵ�.
			weightWrite = fopen("match.dat", "w");
			set_w(1); //write�� ���ٶ��� 1���̴�.

			fclose(weightWrite);
			fclose(WeightRead);
		}
	}
	else if (onLearning == 0) {
		printf("Test�� Weight�� �Է��ϼ���! : ");
		scanf("%d", &weightNumber);

		char tmp[200];
		sprintf(tmp, "C:\\Users\\dkrle\\source\\repos\\ML_test\\ML_test\\weight\\weight%d.dat", weightNumber);

		WeightRead = fopen(tmp, "r");

		set_w(2); //weight �� �о�� weight �� �����Ѵ�.

		fclose(WeightRead);
	}

	double x[10] = { 0, }, x2 = 0, t[2] = { 0 };
	time_t current;
	struct tm* timer;

	if (onLearning == 1) {
		FILE* errFd = fopen("error.dat", "w");

		for (int i = 1; i <= max; i++) {
			rewind(realData); //������ ó������ ���� �� �ֵ��� �����͸� ó������ �����ش�.
			err = 0;
			int all = 0;
			while (fscanf(realData, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5],
				&x[6], &x[7], &x[8], &t[0]) != EOF) {
				EBP(x, t);
				all++;
			}

			current = time(NULL);
			timer = localtime(&current);

			if (i % ErrCount == 0) {
				fprintf(errFd, "%d %lf %d:%d:%d:%d:%d:%d\n", i, err / all, timer->tm_year + 1900, timer->tm_mon + 1, timer->tm_mday,
					timer->tm_hour, timer->tm_min, timer->tm_sec); //1 epoch �������� ������ error.txt �� ���ش�.
			}

			if (i % WeightCount == 0) {
				char WeightFileName[200];
				sprintf(WeightFileName, "C:\\Users\\dkrle\\source\\repos\\ML_test\\ML_test\\weight\\weight%d.dat", i);

				weightWrite = fopen(WeightFileName, "w");
				set_w(1);

				fclose(weightWrite);
			}
		}

		fclose(errFd);
	}
	else if (onLearning == 0) { //Test! ���� Eva Data �� �� Weight�� ����
		FILE* testData = fopen("TestData0612.txt", "r"), * outputData = fopen("output.dat", "w");

		//��� ������ %lf �� ,&t[0] �߰�!
		while (fscanf(testData, "%lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x[0], &x[1], &x[2], &x[3], &x[4],
			&x[5], &x[6], &x[7], &x[8]) != EOF) {
			//fprintf(outputData, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %d\n", x[0], x[1], x[2], x[3], x[4],
			//	x[5], x[6], x[7], x[8], GridTest(x, t, 0));
			fprintf(outputData, "%d\n", GridTest(x, t, 0));
		}

		fclose(outputData);
		fclose(testData);
	}

	FILE* evErrFile = fopen("evaErr.txt", "w");

	for (int i = WeightCount; i <= max; i += WeightCount) {

		char WeightFileName[200];
		sprintf(WeightFileName, "C:\\Users\\dkrle\\source\\repos\\ML_test\\ML_test\\weight\\weight%d.dat", i);

		WeightRead = fopen(WeightFileName, "r");

		set_w(2);

		fclose(WeightRead);

		rewind(eva);
		evaErr = 0;
		while (fscanf(eva, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x[0], &x[1], &x[2], &x[3], &x[4],
			&x[5], &x[6], &x[7], &x[8], &t[0]) != EOF) {
			//evaData.txt ���Ͽ��� �׽�Ʈ ������ �о�ͼ� Error ���� ���Ѵ�.
			GridTest(x, t, 1);
		}
		fprintf(evErrFile, "%d %lf\n", i, evaErr / (allLine / 10));
	}

	fclose(eva);
	fclose(realData);
	fclose(fin);
	fclose(evErrFile);

	return 0;
}
