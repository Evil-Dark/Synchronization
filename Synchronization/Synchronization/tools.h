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

void add_one_second(char buff[255]);

void clean_data(char* file, char *file_new, int len);

int compare_time(char *time1, char *time2);

void sum_frames1(char *file, int *totalFrames);

void sum_frames2(char *file, int *totalFrames);

#endif
