#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include<vector>
#include<string>
#include<ctime>

using namespace std;

class clsDate
{

private:
	
	int _Day;
	int _Month;
	int _Year;
	enum enDays { eSun = 0, eMon = 1, eTue = 2, eWed = 3, eThu = 4, eFri = 5, eSat = 6 };

public:


	clsDate()
	{
		CurrentDate();
	}

	clsDate(string Date)
	{
		StringToDate(Date);
	}

	clsDate(int Day, int Month, int Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	vector <string> SplitString(string Date, string Delim = "/")
	{
		vector <string> vDate;
		string StoringDate = "";
		int pos = 0;

		while ((pos = Date.find(Delim)) != Date.npos)
		{
			StoringDate = Date.substr(0, pos);
			if (StoringDate != "")
				vDate.push_back(StoringDate);
			Date.erase(0, pos + Delim.length());
		}

		if (Date != "")
			vDate.push_back(Date);
		return vDate;
	}

	void StringToDate(string sDate)
	{
		vector <string> vDate = SplitString(sDate);

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	
	static bool IsLeapYear(short Year)
	{
		return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
	}

	bool  IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInMonth(short Year, short Month)
	{
		if (Month < 1 || Month > 12)
		{
			return 0;
		}
		short arrMonthDay[12] = { 31, 28 , 31 , 30 , 31 ,30 , 31 , 31 , 30 , 31 , 30 , 31 };
		return (Month == 2) ? IsLeapYear(Year) ? 29 : 28 : arrMonthDay[Month - 1];
	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date._Day == NumberOfDaysInMonth(Date._Year, Date._Month)) ? true : false;
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12) ? true : false;
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	void IncreasingDateOneDay()
	{
		if (IsLastDayInMonth())
		{
			_Day = 1;
			if (IsLastMonthInYear(_Month))
			{
				_Month = 1;
				_Year++;
			}
			else
				_Month++;
		}
		else
		{
			_Day++;
		}
	}

	void IncreasingDateByXDays(short Days)
	{
		for (short i = 1; i <= Days; i++)
		{
			IncreasingDateOneDay();
		}
	}

	void IncreasingDateByOneWeek()
	{
		for (short i = 1; i <= 7; i++)
		{
			IncreasingDateOneDay();
		}
	}

	void IncreasingDateByXWeeks(short numWeeks)
	{
		for (short i = 1; i <= numWeeks; i++)
		{
			IncreasingDateByOneWeek();
		}
	}

	void IncreasingDateByOneMonth()
	{
		if (IsLastMonthInYear())
		{
			_Month = 1;
			_Year++;
		}
		else
			_Month++;

		short MonthNumber = NumberOfDaysInMonth();
		if (_Day > MonthNumber)
		{
			_Day = MonthNumber;
		}
	}

	void IncreasingDateByXMonths( short NumberOFMonths)
	{
		for (short i = 1; i <= NumberOFMonths; i++)
		{
			 IncreasingDateByOneMonth();
		}
	}

	void IncreasingDateByOneYear()
	{
		_Year += 1;
		if (_Month == 2 && _Day == 29)
		{

			if (!IsLeapYear(_Year))
			{

				_Day = 28;
			}
		}
	}

	void IncreasingDateByXYears( short NumberOfYears)
	{
		for (short i = 1; i <= NumberOfYears; i++)
		{
			IncreasingDateByOneYear();
		}
	}

	void IncreasingDateByOneDecade()
	{
		_Year += 10;

		if (_Month == 2 && _Day == 29)
		{
			if (!IsLeapYear(_Year))
				_Day = 28;
		}
	}

	void IncreasingDateByXDecades( short DecadesNum)
	{
		for (short i = 1; i <= DecadesNum * 10; i++)
		{
			IncreasingDateByOneYear();
		}
	}

	void IncreasingDateByOneCentury()
	{
		_Year += 100;
		if (_Month == 2 && _Day == 29)
		{

			if (!IsLeapYear(_Year))
			{
				_Day = 28;
			}
		}
	}

	void IncreaseDateByOneMillennium()
	{
		_Year += 1000;
	}

	static short DaysFromTheBeginigOfYear(clsDate cDate)
	{
		short NumberOfDays = 0;
		for (short i = 1; i < cDate._Month; i++)
		{
			NumberOfDays += NumberOfDaysInMonth(cDate._Year, i);
		}
		NumberOfDays += cDate._Day;
		return NumberOfDays;
	}

	short DaysFromTheBeginigOfYear()
	{
		return DaysFromTheBeginigOfYear(*this);
	}

	static string DayNameInWeekByOrder(short DayOrder)
	{
		string dayName[7] = { "Sun" , "Mon" , "Tue" , "Wed" ,"Thu" , "Fri" , "Sat" };
		return dayName[DayOrder];
	}

	static short DayOrderByGregorianCalendar(clsDate cDate)
	{
		short a, y, m, d;
		a = ((14 - cDate._Month) / (12));

		y = cDate._Year - a;
		m = cDate._Month + (12 * a) - 2;
		d = ((cDate._Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);
		return d;
	}

	short DayOrderByGregorianCalendar()
	{
		return DayOrderByGregorianCalendar(*this);
	}

	static bool IsEndOfWeek(short DayOrder)
	{
		return (DayOrder == enDays::eSat) ? true : false;
	}

	static bool IsWeekend(short DayOrder)
	{
		return (DayOrder == enDays::eFri || DayOrder == enDays::eSat) ? true : false;
	}

	static bool IsBusinessDay(short DayOrder)
	{
		return (!IsWeekend(DayOrder));
	}

	static short DaysUntilTheEndOfWeek(short DayOrder)
	{
		return (7 - (DayOrder + 1));
	}

	static short DaysUntilTheEndOfYears(clsDate cDate)
	{
		return (IsLeapYear(cDate._Year)) ? 366 - DaysFromTheBeginigOfYear(cDate) : 365 - DaysFromTheBeginigOfYear(cDate);
	}

	short DaysUntilTheEndOfYears()
	{
		return DaysUntilTheEndOfYears(*this);
	}

	void CurrentDate()
	{
		time_t t = time(0);
		tm* Time = localtime(&t);
		_Year = Time->tm_year + 1900;
		_Month = Time->tm_mon + 1;
		_Day = Time->tm_mday;
	}

	static bool IsDateBeforeDate2(clsDate Date1, clsDate Date2)
	{
		return  (Date1._Year < Date2._Year) ? true : (Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month) ? true : (Date1._Month == Date2._Month) ? (Date1._Day < Date2._Day) : false : false;
	}

	bool IsDateBeforeDate2(clsDate Date)
	{
		return IsDateBeforeDate2(*this, Date);
	}

	static short GetDifferenceBetweenDates(clsDate cDate1, clsDate cDate2, bool IncludeDay = false)
	{
		short DiffNum = 0;
		while (IsDateBeforeDate2(cDate1, cDate2))
		{
			DiffNum++;
			cDate1.IncreasingDateOneDay();
		}
		return (IncludeDay) ? ++DiffNum : DiffNum;
	}

	short GetDifferenceBetweenDates(clsDate cDate2, bool IncludeDay = false)
	{
		return GetDifferenceBetweenDates(*this, cDate2 , IncludeDay);
	}

	static short CalculatingActualVicationDays(clsDate StartVicationDate, clsDate EndVicationDate, short DayVacationStarts)
	{
		short ActualVicationDays = 0;
		short DaysDifferenceBetweenDates = GetDifferenceBetweenDates(StartVicationDate, EndVicationDate);
		short Counter = DayVacationStarts;
		for (short i = 1; i <= DaysDifferenceBetweenDates; i++)
		{
			if (Counter == 7)
				Counter = 0;
			if (!IsWeekend(Counter))
			{
				ActualVicationDays++;

			}
			Counter++;
		}
		return ActualVicationDays;
	}

	short CalculatingActualVicationDays(clsDate EndVicationDate, short DayVacationStarts)
	{
		return CalculatingActualVicationDays(*this, EndVicationDate, DayVacationStarts);
	}

	clsDate DateVacationEnd(clsDate sDateFrom, short VicationDays)
	{

		short Counter = 0;
		while (IsWeekend(sDateFrom._Day))
		{
			sDateFrom. IncreasingDateOneDay();
		}

		for (short i = 1; i <= VicationDays + Counter; i++)
		{
			if (IsWeekend(sDateFrom._Day))
				Counter++;
			sDateFrom. IncreasingDateOneDay();
		}

		while (IsWeekend(sDateFrom._Day))
		{
			sDateFrom. IncreasingDateOneDay();
		}
		return sDateFrom;
	}

	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
 	}
};

