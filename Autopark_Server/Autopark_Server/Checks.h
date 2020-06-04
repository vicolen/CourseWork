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
bool checkString(string checker);
const bool operator > (const string& s1, const string& s2);
const bool operator == (const string& s1, const string& s2);
bool checkStringGender(string checker);
int returnNumberOfRecords(int choice);
void changeNumberOfRecords(int choice, int c);
void toChar(string s, char q[]);
#pragma once
