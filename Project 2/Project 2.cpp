#include <iostream>
#include"clsDate.h"

using namespace std;

int main()
{
	clsDate Date1;
	Date1.Print();

	clsDate Date2("31/1/2023");
	Date2.Print();
	
	clsDate Date3(20, 12, 2022);
	Date3.Print();

	cout << Date2.IsLeapYear() << endl;
	Date2.StringToDate("12/10/2022");
	Date2.Print();
	cout << Date2.IsLeapYear() << endl;

	//Date2.IsLastDayInMonth();
	//clsDate::IsLastDayInMonth(Date1);
	\
	Date2 .IncreasingDateOneDay();
	Date2.Print();

	Date2.IncreasingDateByXDays(10);
	Date2.Print();
	
	cout << Date2.CalculatingActualVicationDays(Date1, 5) << endl;
	return 0;
}