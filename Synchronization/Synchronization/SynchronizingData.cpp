#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include "tools.h"

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

int main()
{
	char buff[2][255];
	char *timeStamp[2];//��¼����ʱ���
	
	char *file1 = "\\Data\\������갴��ʱ���.txt";
	char *file2 = "\\Data\\kinectʱ�������.txt";
	char *file3 = "\\Data\\appwatchʱ���&����.txt";

	int *total = NULL;
	total = new int[50];
	sum_frames1(file3, total);//appwatch
	sum_frames2(file2, total);//kinect
	printf("%d\n", total[0]);
	
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
