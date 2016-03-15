
class Lunaryear
{
private:
	int solar_year , lunar_year ;
	char solar_month, lunar_month;
	int solar_day, lunar_day;
    long int lunar_info[999];
	char get_leap_month(int lunar_year) //确定是否存在农历的闰月 并返回闰月
	{
		return lunar_info[lunar_year - 1900] & 0xf;
	}
	//---------------------------------------------
	char get_leap_month_day(int lunar_year)  //若存在闰月,返回闰月的天数,30?29
	{
		if (get_leap_month(lunar_year))
			return(((lunar_info[lunar_year - 1900]) & 0x10000) ? 30 : 29);
		else
			return(0);
	}
	//---------------------------------------------
	char get_lunar_month_total(int lunar_year, char lunar_month) //确定农历当月天数,30?29
	{
		return((lunar_info[lunar_year - 1900] & (0x10000 >> lunar_month)) ? 30 : 29);
	}
	//---------------------------------------------
	int get_lunar_year_total(int lunar_year) // 农历当年总天数,354?355 384 383
	{
		/*sum=12*29 */   //12个月 29天一月
		int sum = 348;
		int i;
		for (i = 0x8000; i > 0x8; i >>= 1)
			sum += (lunar_info[lunar_year - 1900] & i) ? 1 : 0;  //把大月的1加进去
		return(sum + get_leap_month_day(lunar_year));    //判断这年是否有闰月
	}
	//---------------------------------------------
	//#############################################

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//---------------------------------------------

	int leap(int year)  //判断是否为闰年
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return 366;
		else
			return 365;
	}

	//--------------------------------------
	char day(int year, char month) //判断当年当月天数
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			return 31;
		if (month == 4 || month == 6 || month == 9 || month == 11)
			return 30;
		if (month == 2 && leap(year) == 366)
			return 29;
		else
			return 28;
	}
	//-------------------------------------------
	//计算1900.1.1 到  输入年月的天数
	int get_solar_total(int solar_year, char solar_month)
	{
		int total;
		int temp_num;
		total = 0;
		for (temp_num = 1900; temp_num < solar_year; temp_num++)
			total += leap(temp_num);
		for (temp_num = 1; temp_num < solar_month; temp_num++)
			total += day(solar_year, temp_num);
		return total;
	}
public:
	Lunaryear();
    char  solar_lunar(int kp_year, char kp_month, char kp_day);


};
