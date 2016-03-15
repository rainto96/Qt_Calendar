
class Lunaryear
{
private:
	int solar_year , lunar_year ;
	char solar_month, lunar_month;
	int solar_day, lunar_day;
    long int lunar_info[999];
	char get_leap_month(int lunar_year) //ȷ���Ƿ����ũ�������� ����������
	{
		return lunar_info[lunar_year - 1900] & 0xf;
	}
	//---------------------------------------------
	char get_leap_month_day(int lunar_year)  //����������,�������µ�����,30?29
	{
		if (get_leap_month(lunar_year))
			return(((lunar_info[lunar_year - 1900]) & 0x10000) ? 30 : 29);
		else
			return(0);
	}
	//---------------------------------------------
	char get_lunar_month_total(int lunar_year, char lunar_month) //ȷ��ũ����������,30?29
	{
		return((lunar_info[lunar_year - 1900] & (0x10000 >> lunar_month)) ? 30 : 29);
	}
	//---------------------------------------------
	int get_lunar_year_total(int lunar_year) // ũ������������,354?355 384 383
	{
		/*sum=12*29 */   //12���� 29��һ��
		int sum = 348;
		int i;
		for (i = 0x8000; i > 0x8; i >>= 1)
			sum += (lunar_info[lunar_year - 1900] & i) ? 1 : 0;  //�Ѵ��µ�1�ӽ�ȥ
		return(sum + get_leap_month_day(lunar_year));    //�ж������Ƿ�������
	}
	//---------------------------------------------
	//#############################################

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//---------------------------------------------

	int leap(int year)  //�ж��Ƿ�Ϊ����
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return 366;
		else
			return 365;
	}

	//--------------------------------------
	char day(int year, char month) //�жϵ��굱������
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
	//����1900.1.1 ��  �������µ�����
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
