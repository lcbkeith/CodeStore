/********************************************************************
created:	2015/06/08 16:04
filename: 	test.cpp
author:	 	Keith

purpose:	固定格式的字符串，转换成time_t
*********************************************************************/

#include <wchar.h>
#include <time.h>
#include <string>

//20:00:00
time_t FormatTime2(const char * szTime)
{
	tm tm1;
	time_t time1;
	time(&time1);
	localtime_s(&tm1, &time1);

	sscanf_s(szTime, "%d:%d:%d",
		&tm1.tm_hour,
		&tm1.tm_min,
		&tm1.tm_sec);

	// 	tm1.tm_year;
	// 	tm1.tm_mon ++ ;
	tm1.tm_isdst = -1;
	time1 = mktime(&tm1);
	return time1;
}

void main1()
{
	std::string time_s = "20:00:00";
	time_t time = FormatTime2(time_s.c_str());
	printf("time = %d \n", time);
}