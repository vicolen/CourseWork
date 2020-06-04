#include "Checks.h"
#include "Libraries.h"
int returnNumberOfRecords(int choice)
{
	int const SIZE =5;
	int numberOfRecords[SIZE];
	int m=-1;
	string puth = "NumberOfRecords.txt";
	ifstream file;
	file.open(puth);
	if (!file.is_open())
	{
		cout << "Файл не был открыт." << endl;
	}
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			string num;
			file >> num;
			numberOfRecords[i] = atoi(num.c_str());

		}
		m = numberOfRecords[choice - 1];
	}
	file.close();
	return m;

}
void changeNumberOfRecords(int c, int choice)
{
	int const SIZE = 5;
	int numberOfRecords[SIZE]{0,0,0,0,0};
	int m = -1;
	string puth = "NumberOfRecords.txt";
	ifstream file;
	file.open(puth);
	if (!file.is_open())
	{
		cout << "Файл не был открыт." << endl;
	}
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			string num;
			file >> num;
			numberOfRecords[i] = atoi(num.c_str());
		
		}
		m = numberOfRecords[choice - 1];
	}
	if (c == 1)
	{
	   m++;
	}
	if (c == 2)
	{
		m--;
	}
	if (c == 3)
	{
		m= 0;
	}
	numberOfRecords[choice - 1] = m;
	file.close();

	ofstream file1;
	file1.open(puth);
	if (!file1.is_open())
	{
		cout << "Файл не был открыт." << endl;
	}
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			file1 << numberOfRecords[i] << endl;
		}

	}
	file1.close();
}

