#include "ShowNowTime.h"
#include <cstdlib>
#include <time.h>
#include <stdio.h>
int ShowNowTime::getYear()
{
    time_t t = time(0);
	char tmp[64];
   strftime( tmp, sizeof(tmp), "%Y",localtime(&t) );
	return atoi(tmp);
}
int ShowNowTime::getMonth()
{
    time_t t = time(0);
	char tmp[64];
   strftime( tmp, sizeof(tmp), "%m",localtime(&t) );
	return atoi(tmp);
}
int ShowNowTime::getDay()
{
    time_t t = time(0);
	char tmp[64];
   strftime( tmp, sizeof(tmp), "%d",localtime(&t) );
	return atoi(tmp);
}
int ShowNowTime::getHour()
{
    time_t t = time(0);
	char tmp[64];
   strftime( tmp, sizeof(tmp), "%H",localtime(&t) );
	return atoi(tmp);
}
int ShowNowTime::getMinite()
{
    time_t t = time(0);
	char tmp[64];
   strftime( tmp, sizeof(tmp), "%M",localtime(&t) );
	return atoi(tmp);
}
int ShowNowTime::getSecond()
{
    time_t t = time(0);
	char tmp[64];
   strftime( tmp, sizeof(tmp), "%S",localtime(&t) );
	return atoi(tmp);
}
/*size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm *timeptr);
根据格式字符串生成字符串。
struct tm *localtime(const time_t *timer);
取得当地时间，localtime获取的结果由结构tm返回
返回的字符串可以依下列的格式而定：
%a 星期几的缩写。Eg:Tue
%A 星期几的全名。 Eg: Tuesday
%b 月份名称的缩写。
%B 月份名称的全名。
%c 本地端日期时间较佳表示字符串。
%d 用数字表示本月的第几天 (范围为 00 至 31)。日期
%H 用 24 小时制数字表示小时数 (范围为 00 至 23)。
%I 用 12 小时制数字表示小时数 (范围为 01 至 12)。
%j 以数字表示当年度的第几天 (范围为 001 至 366)。
%m 月份的数字 (范围由 1 至 12)。
%M 分钟。
%p 以 ''AM'' 或 ''PM'' 表示本地端时间。
%S 秒数。
%U 数字表示为本年度的第几周，第一个星期由第一个周日开始。
%W 数字表示为本年度的第几周，第一个星期由第一个周一开始。
%w 用数字表示本周的第几天 ( 0 为周日)。
%x 不含时间的日期表示法。
%X 不含日期的时间表示法。 Eg: 15:26:30
%y 二位数字表示年份 (范围由 00 至 99)。
%Y 完整的年份数字表示，即四位数。 Eg:2008
%Z(%z) 时区或名称缩写。Eg:中国标准时间
%% % 字符。*/
