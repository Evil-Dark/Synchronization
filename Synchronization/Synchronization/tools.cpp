#include "tools.h"
#include "time.h"
#include "iostream"

/*将时间戳转为标准时间*/
Times stamp2standard(int stampTime)
{
	time_t tick = (time_t)stampTime;
	struct tm tm;
	char s[100];
	Times standard;

	tm = *localtime(&tick);
	strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);

	standard.Year = atoi(s);
	standard.Mon = atoi(s + 5);
	standard.Day = atoi(s + 8);
	standard.Hour = atoi(s + 11);
	standard.Min = atoi(s + 14);
	standard.Second = atoi(s + 17);

	printf("%d\n", strlen(s));

	return standard;
}

/*将时间字符串转换为time结构体形式*/
Times char2time(char buff[255])
{
	char temp1[4], temp2[2], temp3[3];

	Times standard;
	for (int i = 0; i < 4; i++) {
		temp1[i] = buff[i];
	}
	standard.Year = atoi(temp1);
	for (int i = 0; i < 2; i++) {
		temp2[i] = buff[5 + i];
	}
	standard.Mon = atoi(temp2);
	for (int i = 0; i < 2; i++) {
		temp2[i] = buff[8 + i];
	}
	standard.Day = atoi(temp2);
	for (int i = 0; i < 2; i++) {
		temp2[i] = buff[11 + i];
	}
	standard.Hour = atoi(temp2);
	for (int i = 0; i < 2; i++) {
		temp2[i] = buff[14 + i];
	}
	standard.Min = atoi(temp2);
	for (int i = 0; i < 2; i++) {
		temp2[i] = buff[17 + i];
	}
	standard.Second = atoi(temp2);
	for (int i = 0; i < 3; i++) {
		temp3[i] = buff[20 + i];
	}
	standard.mSecond = atoi(temp3);
	return standard;
}

int add_one(char &ten, char &unit)
{
	if (unit == '9') {
		unit = '0';
		if (ten == '5') {
			ten = '0';
			return 1;//有进位
		}
		else {
			ten += 1;
			return 0;//无进位
		}
	}
	else {
		unit += 1;
		return 0;//无进位
	}
}
/*时间增加1秒*/
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

/*清洗数据，除去不需要的内容*/
void clean_data(char* file, char *file_new, int len)
{
	FILE *fRead = NULL;
	FILE *fWrite = NULL;
	char buff[255];

	fRead = fopen(file, "r");
	fWrite = fopen(file_new, "a");
	int i = 0;
	while (fgets(buff, 255, (FILE*)fRead) != NULL)
	{
		i++;
		char buf[255] = { '\0' };
		strncat(buf, buff, len);//字符串拼接
		fprintf(fWrite, "%s\n", buf);
	}
}

/*时间戳比较*/
int compare_time(char *time1, char *time2) //strncmp(time1, time2, 24);
{
	int len = strlen(time1) > strlen(time2) ? strlen(time2) : strlen(time1);
	for (int i = 0; i < len; i++) {
		if (time1[i] != '-' && time1[i] != '/') {
			if (time1[i] > time2[i]) {
				return 0;//time1时间晚
			}
			else if (time1[i] < time2[i]) {
				return 2;//time1时间早
			}
			else {
				continue;
			}
		}
	}
	return 1;//时间相等
}

/*帧数统计 for applewatch*/
void sum_frames1(char *file, int *totalFrames)
{
	FILE *fp = NULL;
	fp = fopen(file, "r");

	char buff[2][255], *temp1, *temp2;
	temp1 = buff[0];
	temp2 = buff[1];

	fgets(buff[0], 255, (FILE*)fp);
	int i = 1, j = 0, k = 1;

	while (fgets(buff[k], 255, (FILE*)fp) != NULL) {
		if (atoi((temp1 + 0)) == atoi((temp2 + 0))) {
			i++;
		}
		else {
			printf("NO.%d Second: %dFrames\n", j+1, i);
			k = k == 1 ? 0 : 1;
			*(totalFrames + j) = i;
			j++;
			i = 1;
		}
	}
	*(totalFrames + j) = i;
	printf("NO.%d Second: %dFrames\n", j + 1, i);
	printf("total %d Seconds!\n", j+1);
	fclose(fp);
}

/*帧数统计 for kinect*/
void sum_frames2(char *file, int *totalFrames)
{
	FILE *fp = NULL;
	fp = fopen(file, "r");

	char buff[2][255], *temp1, *temp2;
	temp1 = buff[0];
	temp2 = buff[1];

	fgets(buff[0], 255, (FILE*)fp);
	add_one_second(buff[0]);

	int i = 1, j = 0;
	while (fgets(buff[1], 255, (FILE*)fp) != NULL) {
		if (strncmp(temp1, temp2, 23) == 1) {
			i++;
		}
		else {
			printf("NO.%d Second: %dFrames\n", j+1, i);
			*(totalFrames + j) = i;
			j++;
			i = 1;
			add_one_second(buff[0]);
		}
	}
	*(totalFrames + j) = i;
	printf("NO.%d Second: %dFrames\n", j + 1, i);
	printf("total %d Seconds!\n", j+1);
	fclose(fp);
}