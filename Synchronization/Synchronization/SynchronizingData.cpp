#include "stdio.h"
#include "iostream"
#include "stdlib.h"

#include "tools.h"
#include "CubicSpline.h"
using namespace std;

/*��ȡ������갴����Ӧʱ���*/
void get_time(char *timeStamp[2], char buff[2][255], char *file, int begin, int end)
{	
	FILE *fp = NULL;
	fp = fopen(file, "r");
	
	//��ʼʱ��
	for (int i = 1; i <= begin; i++) {
		fgets(buff[0], 255, (FILE*)fp);
	}
	timeStamp[0] = buff[0];
	//����ʱ��
	for (int i = 1; i <=  end - begin; i++) {
		fgets(buff[1], 255, (FILE*)fp);
	}
	timeStamp[1] = buff[1];

	fclose(fp);
}

/*��ȡ��Ӧʱ���������*/
void adjust_data(char *timeStamp[2],char buff[255], char *fileRead, char *fileWrite)
{
	FILE *fRead = NULL;
	FILE *fWrite = NULL;

	fRead = fopen(fileRead, "r");
	fWrite = fopen(fileWrite, "a");

	while (true)
	{
		fgets(buff, 255, (FILE*)fRead);
		char *temp = buff;
		//�ж��Ƿ�������ʱ����ڵ����ݣ��ǵĻ�д���ļ�
		if (compare_time(timeStamp[0], temp)>= 1 && compare_time(timeStamp[1], temp) <= 1) {
			fprintf(fWrite, "%s", temp);
		}
		//��ȡ��������������ʱ��㣬��ֹѭ��
		if (compare_time(timeStamp[1], temp) == 2) {
			break;
		}
	}	
	fclose(fRead);
	fclose(fWrite);
}

int get(char *file, float *yArray)
{
	FILE *fp = NULL;
	fp = fopen(file, "r");

	char buff[255], *temp;
	temp = buff;
	if (fp == NULL) {
		printf("Failure\n");
	}
	int i = 0;
	while (fgets(buff, 255, (FILE*)fp) != NULL) {
		*(yArray + i) = atof((temp + 11));
		i++;
	}
	
	printf("yArray's size: %d\n", i);
	fclose(fp);
	return i;
}

int main()
{
	char *file3 = "Data\\appwatchʱ���&����.txt";
	float yArray[100], xArray[100], *yArr;
	yArr = yArray;
	int size = get(file3, yArr);
	printf("%f\n", yArray[0]);
	for (int i = 0; i < size; i++) {
		xArray[i] = i;
	}
	CubicSpline cs;

	//float x1[] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
	//float y1[] = { 0.0f, 100.0f, 50.0f, 100.0f, 50.0f, 200.0f };
	//int size = 6;

	cs.Initialize(xArray, yArray, size);

	for (float i = 0.0f; i < size-1; i += 0.0125f) {
		cout << i << ", " << cs.Interpolate(i) << std::endl;
	}

	//double xArr[4] = {};
	//double yArr[4] = {};
	////����4���ڵ�����
	//cout << "����������4���ڵ������:" << endl;
	//for (int i = 0; i<4; i++)
	//	cin >> xArr[i] >> yArr[i];

	////����Ҫ���Ľڵ�ĺ�����
	//cout << "������Ҫ���Ľڵ�ĺ�����:";
	//double x;
	//cin >> x;
	//double y = 0;
	//for (int i = 0; i<4; i++)
	//	y += Lx(i, x, xArr)*yArr[i];
	//printf("x=%lfʱ��y=%lf\n", x, y);

	//char buff[2][255];
	//char *timeStamp[2];//��¼����ʱ���
	//
	//char *file1 = "Data\\������갴��ʱ���.txt";
	//char *file2 = "Data\\kinectʱ�������.txt";
	//char *file3 = "Data\\appwatchʱ���&����.txt";

	//int *total = NULL;
	//total = new int[50];
	//sum_frames1(file3, total);//appwatch
	//sum_frames2(file2, total);//kinect
	//printf("%d\n", total[0]);
	
	//clean_data(file2, file3, 23);
	
	//char *temp1 = "2018-11-08 17:21:25.636206";
	//char *temp2 = "2018-11-08 16:21:25.637206";
	//printf("%d\n", strncmp(temp1, temp2, 23));

	//getTime(timeStamp, buff, file1, 2, 8);
	//Times time = calibrateDate(buff[0]);
	//printf("%d-%d-%d %d:%d:%d.%d\n", time.Year, time.Mon, time.Day, time.Hour, time.Min, time.Second, time.mSecond);


	//char *temp = strtok(timeStamp[0], " ");
	//temp = strtok(NULL,  " ");
	//printf("%s\n", temp);

	
	//adjustData(timeStamp, buff[0], file2, file3);

	//Times time;
	//time = stamp2standard(1477478145);
	//printf("%d-%d-%d %d:%d:%d\n", time.Year, time.Mon, time.Day, time.Hour, time.Min, time.Second);
		
	system("pause");
	return 0;
}
