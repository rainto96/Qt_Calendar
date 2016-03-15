#include<lunaryear.h>
Lunaryear::Lunaryear()
{
	solar_year = 0;  lunar_year = 0;
	solar_month = 0;  lunar_month = 0;
	solar_day = 0;  lunar_day = 0;
    lunar_info[999] =
	{
		0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554, 0x056a0, 0x09ad0, 0x055d2,
		0x04ae0, 0x0a5b6, 0x0a4d0, 0x0d250, 0x1d255, 0x0b540, 0x0d6a0, 0x0ada2, 0x095b0, 0x14977,
		0x04970, 0x0a4b0, 0x0b4b5, 0x06a50, 0x06d40, 0x1ab54, 0x02b60, 0x09570, 0x052f2, 0x04970,
		0x06566, 0x0d4a0, 0x0ea50, 0x06e95, 0x05ad0, 0x02b60, 0x186e3, 0x092e0, 0x1c8d7, 0x0c950,
		0x0d4a0, 0x1d8a6, 0x0b550, 0x056a0, 0x1a5b4, 0x025d0, 0x092d0, 0x0d2b2, 0x0a950, 0x0b557,
		0x06ca0, 0x0b550, 0x15355, 0x04da0, 0x0a5b0, 0x14573, 0x052b0, 0x0a9a8, 0x0e950, 0x06aa0,
		0x0aea6, 0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260, 0x0f263, 0x0d950, 0x05b57, 0x056a0,
		0x096d0, 0x04dd5, 0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250, 0x0d558, 0x0b540, 0x0b6a0, 0x195a6,
		0x095b0, 0x049b0, 0x0a974, 0x0a4b0, 0x0b27a, 0x06a50, 0x06d40, 0x0af46, 0x0ab60, 0x09570,  //1980
		0x04af5, 0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58, 0x055c0, 0x0ab60, 0x096d5, 0x092e0,
		0x0c960, 0x0d954, 0x0d4a0, 0x0da50, 0x07552, 0x056a0, 0x0abb7, 0x025d0, 0x092d0, 0x0cab5,  //2004 
		0x0a950, 0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9, 0x04ba0, 0x0a5b0, 0x15176, 0x052b0, 0x0a930,
		0x07954, 0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6, 0x0a4e0, 0x0d260, 0x0ea65, 0x0d530, //2028
		0x05aa0, 0x076a3, 0x096d0, 0x04bd7, 0x04ad0, 0x0a4d0, 0x1d0b6, 0x0d250, 0x0d520, 0x0dd45,
		0x0b5a0, 0x056d0, 0x055b2, 0x049b0, 0x0a577, 0x0a4b0, 0x0aa50, 0x1b255, 0x06d20, 0x0ada0,
		0x14b63
	};
}


char Lunaryear::solar_lunar(int kp_year, char kp_month, char kp_day)
{
	int total_day = 0;/*记录农历1900.1.1日到今天相隔的天数 */
	char run_yue_flag = 0, run_yue = 0, year_flag = 0;

	if (kp_year<1900 || kp_year>2050 || kp_month > 12 || kp_month == 0 || (kp_year == 1900 && kp_month == 1))
		return 0;
	if (kp_day > day(kp_year, kp_month) || kp_day == 0)
		return 0;

	total_day = get_solar_total(kp_year, kp_month) + kp_day - 30; /* 阳历从1900.1.31(农历1900.1.1)到今天的总天数(减30 实际少了一天)。 */
	lunar_year = 1900;
	while (total_day > 385) //385大于一年  留出一年多的时间用于条件计算
	{
		total_day -= get_lunar_year_total(lunar_year); //
		lunar_year++;
	}
	if (total_day > get_lunar_year_total(lunar_year))  //排除lunar_year有闰月的情况
	{
		total_day -= get_lunar_year_total(lunar_year);
		lunar_year++;
	}
	run_yue = get_leap_month(lunar_year);  //当前闰哪个月
	if (run_yue)
		run_yue_flag = 1; //有闰月则一年为13个月
	else
		run_yue_flag = 0;  //没闰月则一年为12个月

	if (total_day == 0)   //刚好一年
	{
		lunar_day = get_lunar_month_total(lunar_year, 12);
		lunar_month = 12;
	}
	else
	{
		lunar_month = 1;
		while (lunar_month <= 12)
		{
			if (run_yue_flag == 1 && lunar_month == (run_yue + 1))  //闰月处理
			{
				if (total_day > get_leap_month_day(lunar_year))
				{
					total_day -= get_leap_month_day(lunar_year);  //该年闰月天数

				}
				//lunar_month--;
				run_yue_flag = 0;
				continue;

			}
			if (total_day > get_lunar_month_total(lunar_year, lunar_month))
			{
				total_day = total_day - get_lunar_month_total(lunar_year, lunar_month);  //该年该月天数
				lunar_month++;
			}
			else
			{
				lunar_day = total_day;
				break;
			}
		}
	}
}
