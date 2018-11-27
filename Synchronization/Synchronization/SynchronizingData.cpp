#include "stdio.h"
#include "iostream"
#include "stdlib.h"

#include "CubicSpline.h"
using namespace std;

int add_one(char &ten, char &unit)
{
	if (unit == '9') {
		unit = '0';
		if (ten == '5') {
			ten = '0';
			return 1;//�н�λ
		}
		else {
			ten += 1;
			return 0;//�޽�λ
		}
	}
	else {
		unit += 1;
		return 0;//�޽�λ
	}
}
/*ʱ������1��*/
void add_one_second(char buff[255])
{
	char *time = buff;
	int hour = atoi((time + 11));

	int temp = add_one(buff[17], buff[18]);
	if (temp == 1) {
		temp = add_one(buff[14], buff[15]);
		if (temp == 1) {
			if (hour < 23) {
				add_one(buff[11], buff[12]);
			}
			else {
				*(time + 11) = '0';
				*(time + 12) = '0';
			}
		}
	}
}


/*��ȡ������갴����Ӧʱ���*/
void time_on_click(char mouse_click_time[2][50], char *file, int begin, int end)
{	
	printf("Loading Dynamic capture time...\n");
	FILE *fp = NULL;
	fp = fopen(file, "r");
	char buff[255];
	//��ʼʱ��
	for (int i = 1; i <= begin; i++) {
		fgets(buff, 255, (FILE*)fp);
	}
	strcpy(mouse_click_time[0], buff + 3);
	//����ʱ��
	for (int i = 1; i <=  end - begin; i++) {
		fgets(buff, 255, (FILE*)fp);
	}
	strcpy(mouse_click_time[1], buff + 3);
	printf("Begin��%s", mouse_click_time[0]);
	printf("end��%s", mouse_click_time[1]);
	printf("===================================================\n");
	fclose(fp);
}

/*��ȡ��Ӧʱ���������*/
void adjust_kinect_data(char mouse_click_time[2][50], char *read_data, char *read_stamp, char *write)
{
	printf("Adjust Kinect Time...\n");
	FILE *f_read1 = NULL;
	FILE *f_read2 = NULL;
	FILE *f_write = NULL;
	f_read1 = fopen(read_data, "r");
	f_read2 = fopen(read_stamp, "r");
	f_write = fopen(write, "w");

	char buff_time[50],buff_data[2000];
	while (true)
	{
		if (fgets(buff_data, 2000, (FILE*)f_read1) != NULL && fgets(buff_time, 50, (FILE*)f_read2)) {
			//�ж��Ƿ�������ʱ����ڵ����ݣ��ǵĻ�д���ļ�
			if (strncmp(mouse_click_time[0], buff_time, 23) <= 0
				&& strncmp(mouse_click_time[1], buff_time, 23) >= 0) {
				char buf[30] = { '\0' };
				strncat(buf, buff_time, 23);//�ַ���ƴ��
				fprintf(f_write, "%s %s", buf, buff_data);
			}
			//��ȡ��������������ʱ��㣬��ֹѭ��
			if (strncmp(mouse_click_time[1], buff_time, 23) == -1) {
				break;
			}
		}
	}	
	printf("Finished!!!\n");
	printf("===================================================\n");
	fclose(f_read1);
	fclose(f_read2);
	fclose(f_write);
}

/*
ͳ��ÿ���������
*file: �ļ�·��
*total_samples������洢ÿ���������

return total_samples����
*/
int sum_frames(char *file, int *total_samples)
{
	FILE *fp = NULL;
	fp = fopen(file, "r");

	char buff[2][2000], *temp1, *temp2;
	temp1 = buff[0];
	temp2 = buff[1];

	fgets(buff[0], 2000, (FILE*)fp);
	add_one_second(buff[0]);

	int i = 1, j = 0;
	while (fgets(buff[1], 2000, (FILE*)fp) != NULL) {
		if (strncmp(temp1, temp2, 23) >= 0) {
			i++;
		}
		else {
			//printf("NO.%d Second: %dFrames\n", j + 1, i);
			*(total_samples + j) = i;
			j++;
			i = 1;
			add_one_second(buff[0]);
		}
	}
	*(total_samples + j) = i;
	//printf("NO.%d Second: %dFrames\n", j + 1, i);
	//printf("total %d Seconds!\n", j + 1);
	fclose(fp);
	return j + 1;//��ʱ��j+1��
}

int get_col_data(char *file, double yArrays[80][1500])
{
	FILE *fp = NULL;
	fp = fopen(file, "r");
	char buff_data[2500];

	int cow = 0;//��¼����
	while (fgets(buff_data, 2000, (FILE*)fp) != NULL) {
		const char ch = ' ';
		//��ȥǰ�������� 1������/ 2��ʱ��
		char *col = strchr(buff_data, ch);
		col = strchr(col + 1, ch);
		col = col + 1;//ÿ�е����м��Ժ�����

		char buff[20] = { '\0' };
		int n = 0, m = 0;
		while (true) {
			if (col[n] == ' ') {
				strncpy(buff, col, n + 1);
				yArrays[m][cow] = atof(buff);
				m++;
				//printf("target _ %f\n", atof(buff));
				col = strchr(col, ch);
				col = col + 1;
				n = 0;
			}
			else if (col[n] == '\n') {
				strncpy(buff, col, n);
				yArrays[m][cow] = atof(buff);
				//printf("target _ %f\n", atof(buff));
				m++;
				break;
			}
			else {
				n++;
			}
		}
		cow++;
	}

	//printf("target _ %g\n", yArrays[0][cow-1]);
	fclose(fp);
	return cow;
}

void cublic_spline_resamples(double yArrays[75][1500], int size, float new_hz, int old_hz)
{
	FILE *f_write[75];
	int i = 0;
	for (int n = 0; n < 1; n++) {
		char filename[30];
		sprintf(filename, "Kinect\\col_%d.txt", n + 1);
		f_write[n] = fopen(filename, "a+");

		double xArrays[1500];
		for (int i = 0; i < size; i++) {
			xArrays[i] = i;
		}

		CubicSpline cs;
		cs.Initialize(xArrays, yArrays[n], size);

		double time = (double)pow(new_hz  , -1) * old_hz;
		for (double k = 0.0f; k <= size - 1; k += time) {
			//fprintf(f_write[n], "%g\n", cs.Interpolate(k));
			cout << k << ", " << cs.Interpolate(k) << std::endl;
			i++;
		}
		printf("No.%d col! %d lines\n", n + 1, i);
		printf("=======================\n");
		fclose(f_write[n]);
	}
}

int main()
{
	char *file1 = "Data\\mouse_click_on_170447.txt";
	char *file2 = "Data\\kinect_on_1705_data.txt";
	char *file3 = "Data\\kinect_on_1705_stamp.txt";
	char *file4 = "Data\\kinect_on_1705.txt";

	////char mouse_click_time[2][50];//�����ʱ��ʱ���
	////time_on_click(mouse_click_time, file1, 4, 5);

	////adjust_kinect_data(mouse_click_time, file2, file3, file4);

	int *total_frames = NULL;
	total_frames = new int[500];
	int total_seconds = sum_frames(file4, total_frames);//kinect

	double yArray[80][1500];
	int size = get_col_data(file4, yArray);

	cublic_spline_resamples(yArray, size, 60, 30);
	
	//
	//// system("mkdir lalal");
	system("pause");
	return 0;
}
