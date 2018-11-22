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

/*时间增加1秒
Times add_one_second1(Times oldTime)
{
	if (oldTime.Second < 59) {
		oldTime.Second++;
		return oldTime;
	}
	else {
		oldTime.Second = 0 ;
		if (oldTime.Min < 59) {
			oldTime.Min++;
		}
		else {
			oldTime.Min = 0;
			if (oldTime.Hour < 24) {
				oldTime.Hour++;
			}
			else {
				oldTime.Hour = 0;
			}
		}
	}
}*/


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