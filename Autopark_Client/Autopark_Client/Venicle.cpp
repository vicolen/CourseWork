#include "Venicle.h"
#include"Checks.h"
#include"InvalidNumberExeption.h"
extern SOCKET Socket;
void Venicle::add()
{
	cout << "���������� ������ ������������� ��������." << endl;
	cout << "������� ����� ����������." << endl;
	char markOfVenicle[20];
	do
	{
		cin >> markOfVenicle;
		try
		{
			if (!testLetters(markOfVenicle)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

		}
		catch (const InvalidNumberExeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!testLetters(markOfVenicle));
	
	system("cls");
	char registrNumber[20];
	cout << "������� ��������������� ����� ���������� (1234-AB-7)." << endl;
	do
	{
		int j = 0;
		while (j != 11)
		{
			if (j == 4)
			{
				registrNumber[j] = '-';
				cout << registrNumber[j];
				j++;
			}
			if (j == 7)
			{
				registrNumber[j] = '-';
				cout << registrNumber[j];
				j++;
			}

			registrNumber[j] = _getch();
			if (registrNumber[j] == '\r')
				break;
			if (registrNumber[j] == '\b')
			{
				printf("\b \b");
				j--;
			}

			else if (registrNumber[j] != '\0')
			{
				cout << registrNumber[j];
				j++;
			}
		}
		registrNumber[j] = '\0';
		cout << endl;
	} while (!testRegisrNumber(registrNumber));
	
	system("cls");
	send(Socket, markOfVenicle, 20, 0);
	send(Socket, registrNumber, 20, 0);
	char type1[20] = "��������";
	char type2[20] = "������������";
	char type3[20] = "�����������������";
	cout << "������� ��� ������������� �������� �� ����������." << endl;
	cout << "1. ��������" << endl;
	cout << "2. ������������" << endl;
	cout << "3. �����������������" << endl;
	int choice = check<int>(1, 3);
	if (choice == 1) send(Socket, type1, 20, 0);
	if (choice == 2) send(Socket, type2, 20, 0);
	if (choice == 3) send(Socket, type3, 20, 0);

	system("cls");
	char fileIsOpen[30];
	recv(Socket, fileIsOpen, 30, 0);
	cout << fileIsOpen << endl;

}
int  Venicle::view()
{
	cout << "�������� ������������ �������." << endl;
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords == 0)
	{
		cout << "������� ���." << endl;
	}
	else
	{
		char markOfVenicle[20];
		char registrNumber[20];
		char type[20];
		cout << "_______________________________________________________________________" << endl
			<< "|" << "�" << setw(3) << "|" << setw(5) << "����� ����������" << setw(2) << "|" << "��������������� �����" << setw(3) << "|"
			<< "��� �� ����������" << setw(7) << "|" << endl
			<< "|___|_________________|_______________________|_______________________|" << endl;
		for (int i = 0; i < numberOfRecords; i++)
		{
			recv(Socket, markOfVenicle, 20, 0);
			recv(Socket, registrNumber, 20, 0);
			recv(Socket, type, 20, 0);
			cout << "|" << i + 1 << setw(3) << "|" << markOfVenicle << setw(18 - strlen(markOfVenicle)) << "|"
				<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
				<< setw(24 - strlen(type)) << "|" << endl
				<< "|___|_________________|_______________________|_______________________|" << endl;

		}
	}
	return numberOfRecords;
}
void  Venicle::edit()
{
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		int numberOfRecords = view();
		cout << "�������� ����� ������ ��� ��������������." << endl;
		int numRec = check<int>(1, numberOfRecords) - 1;
		char numRecC[5];
		_itoa_s(numRec, numRecC, 10);
		send(Socket, numRecC, 5, 0);

		system("cls");
		cout << "�������� ���� ��� ��������������." << endl;
		cout << "1.����� ������������� ��������." << endl;
		cout << "2.��������������� �����." << endl;
		cout << "3.��� ������������� �������� �� ����������." << endl;
		int p = check<int>(1, 3);
		char pC[5];
		_itoa_s(p, pC, 10);
		send(Socket, pC, 5, 0);
		switch (p)
		{
		case 1:
			cout << "������� ����� ����������." << endl;
			char markOfVenicle[20];
			do
			{
				cin >> markOfVenicle;
				try
				{
					if (!testLetters(markOfVenicle)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

				}
				catch (const InvalidNumberExeption e)
				{

					cout << e.errorMessage << endl;

				}

			} while (!testLetters(markOfVenicle));
			send(Socket, markOfVenicle, 20, 0); break;
		case 2:
			system("cls");
			char registrNumber[10];
			cout << "������� ��������������� ����� ���������� (1234-AB-7)." << endl;
			do
			{
				int j = 0;
				while (j != 11)
				{
					if (j == 4)
					{
						registrNumber[j] = '-';
						cout << registrNumber[j];
						j++;
					}
					if (j == 7)
					{
						registrNumber[j] = '-';
						cout << registrNumber[j];
						j++;
					}

					registrNumber[j] = _getch();
					if (registrNumber[j] == '\r')
						break;
					if (registrNumber[j] == '\b')
					{
						printf("\b \b");
						j--;
					}

					else if (registrNumber[j] != '\0')
					{
						cout << registrNumber[j];
						j++;
					}
				}
				registrNumber[j] = '\0';
			} while (!testRegisrNumber(registrNumber));
			send(Socket, registrNumber, 8, 0); break;
		case 3:
			char type1[20] = "��������";
			char type2[20] = "������������";
			char type3[20] = "�����������������";
			cout << "������� ��� ������������� �������� �� ����������." << endl;
			cout << "1. ��������" << endl;
			cout << "2. ������������" << endl;
			cout << "3. �����������������" << endl;
			int choice = check<int>(1, 3);
			if (choice == 1) send(Socket, type1, 20, 0);
			if (choice == 2) send(Socket, type2, 20, 0);
			if (choice == 3) send(Socket, type3, 20, 0); break;
		}

		system("cls");
		char fileIsOpen[30];
		recv(Socket, fileIsOpen, 30, 0);
		cout << fileIsOpen << endl;
		view();
	}
	else
	{
		cout << "������ �����������." << endl;
	}

}
void  Venicle::deleteR()
{
	cout << "1.������� ������������ ������." << endl;
	cout << "2.������� ���." << endl;
	cout << "3.��������� �����." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (p == 1)
	{
		if (numberOfRecords != 0)
		{
			view();
			cout << "�������� ������ ��� ��������." << endl;
			int numRec = check<int>(1, numberOfRecords);
			char numRecC[5];
			_itoa_s(numRec, numRecC, 10);
			send(Socket, numRecC, 5, 0);
		}
		else cout << "������ �����������." << endl;
	}
	if (p == 1 || p == 2)
	{
		char fileIsOpen[30];
		recv(Socket, fileIsOpen, sizeof(fileIsOpen), 0);
		cout << fileIsOpen << endl;
    }
}
void  Venicle::sort()
{
	cout << "1.����������� �� ����� ����������." << endl;
	cout << "2.����������� �� ���� ������������� �������� �� ����������." << endl;
	cout << "3.��������� �����." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	if (p != 3)
	{
		char markOfVenicle[20];
		char registrNumber[20];
		char type[20];
		char numberOfRecordsC[5];
		recv(Socket, numberOfRecordsC, 5, 0);
		int numberOfRecords = atoi(numberOfRecordsC);
		if (numberOfRecords == 0)
		{
			cout << "������� ���." << endl;
		}
		else
		{
			cout << "_______________________________________________________________________" << endl
				<< "|" << "�" << setw(3) << "|" << setw(5) << "����� ����������" << setw(2) << "|" << "��������������� �����" << setw(3) << "|"
				<< "��� �� ����������" << setw(7) << "|" << endl
				<< "|___|_________________|_______________________|_______________________|" << endl;
			for (int i = 0; i < numberOfRecords; i++)
			{
				recv(Socket, markOfVenicle, 20, 0);
				recv(Socket, registrNumber, 20, 0);
				recv(Socket, type, 20, 0);
				cout << "|" << i + 1 << setw(3) << "|" << markOfVenicle << setw(18 - strlen(markOfVenicle)) << "|"
					<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
					<< setw(24 - strlen(type)) << "|" << endl
					<< "|___|_________________|_______________________|_______________________|" << endl;

			}

		}
	}
}
void  Venicle::search()
{
	char  numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	if (atoi(numberOfRecordsC) != 0)
	{
		cout << "�����." << endl;
		cout << "1.�� ����� ������������� ��������." << endl;
		cout << "2.�� ���������������� ������." << endl;
		cout << "3.�� ���� ������������� �������� �� ����������." << endl;
		int p = check<int>(1, 3);
		char pC[5];
		_itoa_s(p, pC, 10);
		send(Socket, pC, 5, 0);

		switch (p)
		{
		case 1:
			cout << "������� ����� ����������." << endl;
			char markOfVenicle[20];
			do
			{
				cin >> markOfVenicle;
				try
				{
					if (!testLetters(markOfVenicle)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

				}
				catch (const InvalidNumberExeption e)
				{

					cout << e.errorMessage << endl;

				}

			} while (!testLetters(markOfVenicle));
			send(Socket, markOfVenicle, 20, 0);
			break;
		case 2:
			system("cls");
			char registrNumber[10];
			cout << "������� ��������������� ����� ���������� (1234-AB-7)." << endl;
			do
			{
				int j = 0;
				while (j != 11)
				{
					if (j == 4)
					{
						registrNumber[j] = '-';
						cout << registrNumber[j];
						j++;
					}
					if (j == 7)
					{
						registrNumber[j] = '-';
						cout << registrNumber[j];
						j++;
					}

					registrNumber[j] = _getch();
					if (registrNumber[j] == '\r')
						break;
					if (registrNumber[j] == '\b')
					{
						printf("\b \b");
						j--;
					}

					else if (registrNumber[j] != '\0')
					{
						cout << registrNumber[j];
						j++;
					}
				}
				registrNumber[j] = '\0';
			} while (!testRegisrNumber(registrNumber));
			send(Socket, registrNumber, 8, 0); break;
		case 3:
			char type1[20] = "��������";
			char type2[20] = "������������";
			char type3[20] = "�����������������";
			cout << "������� ��� ������������� �������� �� ����������." << endl;
			cout << "1. ��������" << endl;
			cout << "2. ������������" << endl;
			cout << "3. �����������������" << endl;
			int choice = check<int>(1, 3);
			if (choice == 1) send(Socket, type1, 20, 0);
			if (choice == 2) send(Socket, type2, 20, 0);
			if (choice == 3) send(Socket, type3, 20, 0); break;
		}
		char comC[5]; int com;
		recv(Socket, comC, 5, 0);
		com = atoi(comC);
		if (com != 0)
		{
			cout << "_______________________________________________________________________" << endl
				<< "|" << "�" << setw(3) << "|" << setw(5) << "����� ����������" << setw(2) << "|" << "��������������� �����" << setw(3) << "|"
				<< "��� �� ����������" << setw(7) << "|" << endl
				<< "|___|_________________|_______________________|_______________________|" << endl;
			char markOfVenicle[20];
			char registrNumber[20];
			char type[20];
			for (int i = 0; i < com; i++)
			{
				recv(Socket, markOfVenicle, 20, 0);
				recv(Socket, registrNumber, 20, 0);
				recv(Socket, type, 20, 0);
				cout << "|" << i + 1 << setw(3) << "|" << markOfVenicle << setw(18 - strlen(markOfVenicle)) << "|"
					<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
					<< setw(24 - strlen(type)) << "|" << endl
					<< "|___|_________________|_______________________|_______________________|" << endl;

			}
		}
		else
		{
			cout << "������ �� �������." << endl;
		}

	}
}

void  Venicle::callMenu()
{
	int a = 0;
	do
	{
		cout << "����:" << endl;
		cout << "1.���������� ������������� ��������." << endl;
		cout << "2.�������� ������������ �������." << endl;
		cout << "3.�������������� ������������ �������." << endl;
		cout << "4.�������� ������������ �������." << endl;
		cout << "5.����� ������������ �������." << endl;
		cout << "6.���������� ������������ �������." << endl;
		cout << "7.��������� �����." << endl;
		int choice = check<int>(1, 7);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);
		switch (choice)
		{
		case 1:system("cls"); add();  break;
		case 2:system("cls"); view();  break;
		case 3:system("cls"); edit();  break;
		case 4:system("cls"); deleteR();  break;
		case 5:system("cls"); search();  break;
		case 6:system("cls"); sort();  break;
		case 7: a = 4; system("cls"); break;
		default:system("cls"); cout << "������ ������� �����������." << endl;
		}

	} while (a != 4);
}


