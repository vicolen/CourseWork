#include "Libraries.h"
template <typename T>
T check(int maxNumb)
{
	T x;
	while (!(cin >> x) || (cin.peek() != '\n') || (x < 0) || (x > maxNumb))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "¬ведите данные корректно.\n";
	}
	return x;
}
template <typename T>
T check()
{
	T x;
	while (!(cin >> x) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "¬ведите данные корректно.\n";
	}
	return x;

}
template <typename T>
T check(int minNumb, int maxNumb)
{
	T x;
	while (!(cin >> x) || (cin.peek() != '\n') || (x < minNumb) || (x > maxNumb))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "¬ведите данные корректно.\n";
	}
	return x;
}
template <typename T>
T check(double minNumb, double maxNumb)
{
	T x;
	while (!(cin >> x) || (cin.peek() != '\n') || (x < minNumb) || (x > maxNumb))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "¬ведите данные корректно.\n";
	}
	return x;
}

bool testLetters(char s[]);
bool testRegisrNumber(char s[]);
bool compareMarks(double a, double b);
bool checkDriverLicense(char s[]);
#pragma once