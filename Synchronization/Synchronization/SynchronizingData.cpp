#include "iostream"
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

/*ʱ����Ƚ�*/
int compare_time(char *time1, char *time2) //strncmp(time1, time2, 24);
{
	int len = strlen(time1) > strlen(time2) ? strlen(time2) : strlen(time1);
	for (int i = 0; i < len; i++) {
		if (time1[i] != '-' && time1[i] != '/' ) {
			if (time1[i] > time2[i]) {
				return 0;//time1ʱ����
			}
			else if (time1[i] < time2[i]) {
				return 2;//time1ʱ����
			}
			else {
				continue;
			}
		}
	}
	return 1;//ʱ�����
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

}

char *replaceCH(char buff[255])
{
	char *str = buff;
	int len = strlen(str);
	
	printf("%d\n", len);

	return str;
}

void sum_total_frame(char *file, int *totalFrame)
{
	char buff[255], *temp;
	FILE *fp = NULL;
	fp = fopen(file, "r");
	Times time;
	while (fgets(buff, 255, (FILE*)fp) != NULL) {
		time = char2time(buff);
		add_one_second(time);
	}



	fgets(buff, 255, (FILE*)fp);
	temp = buff;

	int i = atoi((temp + 18));


	*(temp + 18) = 'a';

	printf("%d\n", i);
}


int main()
{
	char buff[2][255];
	char *timeStamp[2];//��¼����ʱ���
	
	char *file1 = "D:\\Data\\������갴��ʱ���.txt";
	char *file2 = "D:\\Data\\kinectʱ�������.txt";
	char *file3 = "D:\\Data\\kinectʱ�������_New.txt";

	clean_data(file2, file3, 23);
	

	//getTime(timeStamp, buff, file1, 2, 8);
	//Times time = calibrateDate(buff[0]);
	//printf("%d-%d-%d %d:%d:%d.%d\n", time.Year, time.Mon, time.Day, time.Hour, time.Min, time.Second, time.mSecond);


	//char *temp = strtok(timeStamp[0], " ");
	//temp = strtok(NULL,  " ");
	//printf("%s\n", temp);

	
	//adjustData(timeStamp, buff[0], file2, file3);

	Times time;
	time = stamp2standard(1477478145);
	printf("%d-%d-%d %d:%d:%d\n", time.Year, time.Mon, time.Day, time.Hour, time.Min, time.Second);


	
	system("pause");
	return 0;
}
