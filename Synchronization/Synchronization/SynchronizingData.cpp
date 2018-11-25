#include "stdio.h"
#include "iostream"
#include "stdlib.h"

#include "tools.h"
#include "CubicSpline.h"
using namespace std;

/*获取动捕鼠标按键对应时间段*/
void get_time(char *timeStamp[2], char buff[2][255], char *file, int begin, int end)
{	
	FILE *fp = NULL;
	fp = fopen(file, "r");
	
	//开始时间
	for (int i = 1; i <= begin; i++) {
		fgets(buff[0], 255, (FILE*)fp);
	}
	timeStamp[0] = buff[0];
	//结束时间
	for (int i = 1; i <=  end - begin; i++) {
		fgets(buff[1], 255, (FILE*)fp);
	}
	timeStamp[1] = buff[1];

	fclose(fp);
}

/*截取对应时间段内数据*/
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
		//判断是否在两个时间点内的数据，是的话写入文件
		if (compare_time(timeStamp[0], temp)>= 1 && compare_time(timeStamp[1], temp) <= 1) {
			fprintf(fWrite, "%s", temp);
		}
		//读取的数据晚于两个时间点，终止循环
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
	char *file3 = "Data\\appwatch时间戳&数据.txt";
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
	////输入4个节点坐标
	//cout << "请依次输入4个节点的坐标:" << endl;
	//for (int i = 0; i<4; i++)
	//	cin >> xArr[i] >> yArr[i];

	////输入要求解的节点的横坐标
	//cout << "请输入要求解的节点的横坐标:";
	//double x;
	//cin >> x;
	//double y = 0;
	//for (int i = 0; i<4; i++)
	//	y += Lx(i, x, xArr)*yArr[i];
	//printf("x=%lf时，y=%lf\n", x, y);

	//char buff[2][255];
	//char *timeStamp[2];//记录动捕时间段
	//
	//char *file1 = "Data\\动捕鼠标按键时间戳.txt";
	//char *file2 = "Data\\kinect时间戳样本.txt";
	//char *file3 = "Data\\appwatch时间戳&数据.txt";

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
