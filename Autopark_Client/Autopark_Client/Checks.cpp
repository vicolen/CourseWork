#include "Checks.h"
#include "Libraries.h"
bool testLetters(char s[])
{
	for (int i = 0; i <(int)strlen(s); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			return false;
		}
	}
	return true;
}
bool testRegisrNumber(char s[])
{
	int res = 0;
	for (int i = 0; i <4; i++)
	{
		if (s[i] >= '0' && s[i] <= '9') res++;
	}
	for (int i = 5; i < 7; i++)
	{
		if (s[i] >= '0' && s[i] <= '9') res--;
	}
	if (s[8] >= '0' && s[8] <= '9') res++;
	if (res == 5) return true;
	else
	{
		cout << "Данные введены некорректно. Повторите ввод." << endl;
		return false;
	}

}
bool compareMarks(double a, double b)
{
	if (a + b == 1) return true;
	else
	{
		cout << "Данные введены некорректно." << endl;
		return false;
	}
}
bool checkDriverLicense(char s[])
{
	int a = 0;
	if (strlen(s) != 9) return false;
	else return true;
	for (int i = 0; i < (int)strlen(s); i++)
	{
		if (s[i] <= '0' && s[i] >= '9')
		{
			return false;
		}
		else a++;
	}
	if (a == (int)strlen(s)) return true;
	else return false;
}