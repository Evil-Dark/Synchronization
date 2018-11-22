#pragma once

#ifndef __TOOLS_H_
#define __TOOLS_H_

typedef struct times
{
	int Year;
	int Mon;
	int Day;
	int Hour;
	int Min;
	int Second;
	int mSecond;
}Times;

Times stamp2standard(int stampTime);

Times char2time(char buff[255]);

Times add_one_second(Times oldTime);

char *time2char(Times time);

void clean_data(char* file, char *file_new, int len);



#endif
