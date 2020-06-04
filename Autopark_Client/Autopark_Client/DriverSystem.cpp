#include "DriverSystem.h"
#include"Venicle.h"
#include"InvalidNumberExeption.h"
extern SOCKET Socket;
int DriverSystem::authorize()
{
	char  login[20];
	char password[20];

	cout << "������� �����" << endl;
	cin >> login;
	cout << "������� ������" << endl;
	int j = 0;
	while (j != 21)
	{
		password[j] = _getch();
		if (password[j] == '\r')
			break;
		if (password[j] == '\b')
		{
			printf("\b \b");
			j--;
		}
		else if (password[j] != '\0')
		{
			printf("*");
			j++;
		}
	}
	password[j] = '\0';
	send(Socket, login, 20, 0);
	send(Socket, password, 20, 0);

	char choiceC[2];
	int choice;
	recv(Socket, choiceC, 2, 0);
	choice = atoi(choiceC);
	if (choice == 1)
	{
		recv(Socket, surname, 20, 0);
		recv(Socket, name, 20, 0);
		system("cls");
		cout << "������������ " << surname << " " << name << " �����������." << endl;
		callMainMenu();
	}
	if (choice == 0)
	{
		char msg[54];
		char msg1[20];
		recv(Socket, msg, 54, 0);
		recv(Socket, msg1, 20, 0);
		system("cls");
		cout << msg << endl;
		cout << msg1 << endl;
	}
	return 0;
}

void  DriverSystem::callMainMenu()
{
	int a = 0;
	do
	{
		cout << "����:" << endl;
		cout << "1.����������� ��������." << endl;
		cout << "2.�������� ������������������ ���������." << endl;
		cout << "3.�������� ���������� ���������." << endl;
		cout << "4.��������� �����." << endl;
		int choice = check<int>(1, 4);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);

		switch (choice)
		{
		case 1: system("cls"); registerRoute(); system("cls");  break;
		case 2: system("cls"); viewRecordedRoutes(); break;
		case 3: system("cls"); viewApprovedRoutes(); break;
		case 4: a = 4; system("cls"); break;
		default:system("cls"); cout << "������ ������� �����������." << endl;
		}

	} while (a != 4);

}

int  DriverSystem::registerRoute()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	cout << "��������! ������� �������������� �� 1 ���� �� �������." << endl;
	cout << "������� ����: " << st.wDay << "." << st.wMonth << "." << st.wYear << endl;
	cout << "���� �������: " << st.wDay + 1 << "." << st.wMonth << "." << st.wYear << endl;
	cout << "��� ������������� ����� ��������� ������� 1." << endl;
	cout << "��� ������ �� ����������� ������� 2." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	if (p == 1)
	{
		cout << "������� ������ � ��������." << endl << endl;
		char goal1[30] = "��������� ������������ �����";    char km1[30] = "������ 100 ��";
		char goal2[30] = "��������� ������������� �����";   char km2[30] = "������ 100 ��, ������ 1000 ��";
		char goal3[30] = "��������� ����������";            char km3[30] = "������ 1000 ��";
		char goal4[30] = "������� �������";
		cout << "�������� ���� �������." << endl;
		cout << "1. " << goal1 << endl;
		cout << "2. " << goal2 << endl;
		cout << "3. " << goal3 << endl;
		cout << "4. " << goal4 << endl;
		int goal = check<int>(1, 4);
		switch (goal)
		{
		case 1: send(Socket, goal1, 30, 0); break;
		case 2: send(Socket, goal2, 30, 0); break;
		case 3: send(Socket, goal3, 30, 0); break;
		case 4: send(Socket, goal4, 30, 0); break;
		}
		cout << "�������� ����������� ������� ." << endl;
		cout << "1." << km1 << endl;
		cout << "2." << km2 << endl;
		cout << "3." << km3 << endl;
		int  km = check<int>(1, 3);
		switch (km)
		{
		case 1: send(Socket, km1, 30, 0); break;
		case 2: send(Socket, km2, 30, 0); break;
		case 3: send(Socket, km3, 30, 0); break;

		}

		send(Socket, surname, 20, 0);
		send(Socket, name, 20, 0);
		char msg[37];
		recv(Socket, msg, 37, 0);
		system("cls");
		cout << msg << endl;
		system("pause");

	}
	else cout << "����������� ��������" << endl;
	return 0;
}
void  DriverSystem::viewRecordedRoutes()
{
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		char numberC[5];
		recv(Socket, numberC, 5, 0);
		int number = atoi(numberC);
		char kmC[30];
		char msgGoal[30];
		char data[20];
		if (number == 0)
		{
			cout << "������������������ �������� �����������." << endl;
		}
		else
		{
			cout << "________________________________________________________________________________________________________________" << endl
				<< "|" << "�" << setw(3) << "|" << setw(5) << "�������" << setw(9) << "|" << "���" << setw(13) << "|"
				<< "���� ��������" << "                |" << "���������� ��������" << setw(11) << "|" << "���� ��������" << "  |" << endl
				<< "|___|_______________|_______________|_____________________________|_____________________________|_______________|" << endl;
			for (int i = 0; i < number; i++)
			{
				recv(Socket, msgGoal, 30, 0);
				recv(Socket, kmC, 30, 0);
				recv(Socket, data, 20, 0);
				cout <<"|"<< i + 1 << "  | " << surname << setw(15 - strlen(surname)) << "|" << name
					<< setw(16 - strlen(name)) << "|" << msgGoal << setw(30 - strlen(msgGoal)) << "|" << kmC
					<< setw(30 - strlen(kmC)) << "|" << data <<setw(16-strlen(data))<<"|" <<endl;

				cout<< "|___|_______________|_______________|_____________________________|_____________________________|_______________|" << endl;
			}

		}
	}
	else
	{
		cout << "� ��� ����������� ���������� ��������." << endl;
	}

}
void  DriverSystem::viewApprovedRoutes()
{
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		char numberC[5];
		recv(Socket, numberC, 5, 0);
		int number = atoi(numberC);

		if (number == 0)
		{
			cout << "� ��� ����������� ���������� ��������." << endl;
		}
		else
		{
			char kmC[30];
			char msgGoal[30];

			char markOfVenicle[20];
			char registrNumber[20];
			char type[20];   char dataTime[20];

			for (int i = 0; i < number; i++)
			{
				recv(Socket, msgGoal, 30, 0);
				recv(Socket, kmC, 30, 0);
				recv(Socket, dataTime, 20, 0);
				recv(Socket, markOfVenicle, 20, 0);
				recv(Socket, registrNumber, 20, 0);
				recv(Socket, type, 20, 0);
				cout << "| " << surname << setw(15 - strlen(surname)) << "|" << name
					<< setw(15 - strlen(name)) << "|" << msgGoal << setw(34 - strlen(msgGoal)) << "|" << kmC << setw(25 - strlen(kmC))
					<< "|" << dataTime << setw(15 - strlen(dataTime)) << "|" << markOfVenicle << setw(15 - strlen(markOfVenicle)) << "|" << registrNumber << endl;
			}

		}
	}
	else
	{
		cout << "� ��� ����������� ���������� ��������." << endl;
	}
}


void DriverSystem::addDriver()
{
	cout << "���������� ������ �������� � ����." << endl;
	cout << "������� ������� �����������." << endl;
	char surname[20];
	do
	{
		cin >> surname;
		try
		{
			if (!testLetters(surname)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

		}
		catch (const InvalidNumberExeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!testLetters(surname));
	send(Socket, surname, 20, 0);
	system("cls");
	cout << "������� ��� �����������." << endl;
	char name[20];
	do
	{
		cin >> name;
		try
		{
			if (!testLetters(name)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

		}
		catch (const InvalidNumberExeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!testLetters(name));
	send(Socket, name, 20, 0);
	system("cls");

	char driveLicense[20];
	cout << "������� ����������������� ����� ������������ ���� (123456789)." << endl;
	do
	{
		cin >> driveLicense;
		try
		{
			if (!checkDriverLicense(driveLicense)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

		}
		catch (const InvalidNumberExeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!checkDriverLicense(driveLicense));
	send(Socket, driveLicense, 20, 0);
	system("cls");

	char login[20];
	char password[20];
	cout << "������� ����� �������� ��� ����������� � �������." << endl;
	cin >> login;
	send(Socket, login, 20, 0);
	cout << "������� ������ �������� ��� ����������� � �������." << endl;
	cin >> password;
	send(Socket, password, 20, 0);

	system("cls");
	char fileIsOpen[30];
	recv(Socket, fileIsOpen, 30, 0);
	cout << fileIsOpen << endl;

}
void DriverSystem::editDriver()
{
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		int numberOfRecords = viewDriver();
		cout << "�������� ����� ������ ��� ��������������." << endl;
		int numRec = check<int>(1, numberOfRecords) - 1;
		char numRecC[5];
		_itoa_s(numRec, numRecC, 10);
		send(Socket, numRecC, 5, 0);

		system("cls");
		cout << "�������� ���� ��� ��������������." << endl;
		cout << "1.������� ��������." << endl;
		cout << "2.��� ��������." << endl;
		cout << "3.����� ������������ ����." << endl;
		cout << "4.����� �������� ��� ����������� � �������." << endl;
		cout << "5.������ �������� ��� ����������� � �������." << endl;
		int p = check<int>(1, 5);
		char pC[5];
		_itoa_s(p, pC, 10);
		send(Socket, pC, 5, 0);
		switch (p)
		{
		case 1:
			system("cls");
			cout << "������� ������� �����������." << endl;
			char surname[20];
			do
			{
				cin >> surname;
				try
				{
					if (!testLetters(surname)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

				}
				catch (const InvalidNumberExeption e)
				{

					cout << e.errorMessage << endl;

				}

			} while (!testLetters(surname));
			send(Socket, surname, 20, 0); break;
		case 2:
			system("cls");
			cout << "������� ��� �����������." << endl;
			char name[20];
			do
			{
				cin >> name;
				try
				{
					if (!testLetters(name)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

				}
				catch (const InvalidNumberExeption e)
				{

					cout << e.errorMessage << endl;

				}

			} while (!testLetters(name));
			send(Socket, name, 20, 0); break;
		case 3:
			system("cls");
			char driveLicense[20];
			cout << "������� ����������������� ����� ������������ ���� (1234567890)." << endl;
			do
			{
				cin >> driveLicense;
				try
				{
					if (!checkDriverLicense(driveLicense)) { throw InvalidNumberExeption("������ ������� �����������. ��������� ����."); }

				}
				catch (const InvalidNumberExeption e)
				{

					cout << e.errorMessage << endl;

				}

			} while (!checkDriverLicense(driveLicense));
			send(Socket, driveLicense, 20, 0); break;

		case 4:
			system("cls");
			char login[20];
			cout << "������� ����� �������� ��� ����������� � �������." << endl;
			cin >> login;

			send(Socket, login, 20, 0); break;
		case 5:
			system("cls");
			char password[20];
			cout << "������� ������ �������� ��� ����������� � �������." << endl;
			cin >> password;

			send(Socket, password, 20, 0); break;
		}

		system("cls");
		char fileIsOpen[30];
		recv(Socket, fileIsOpen, 30, 0);
		cout << fileIsOpen << endl;
		viewDriver();
	}
	else
	{
		cout << "������ �����������." << endl;
	}

}
void DriverSystem::deleteDriver()
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
			viewDriver();
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
int DriverSystem::viewDriver()
{
	cout << "�������� ����� ���������." << endl;
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords == 0)
	{
		cout << "������� ���." << endl;
	}
	else
	{
		char surname[20];      char login[20];
		char name[20];         char password[20];
		char driveLisence[20];
		cout << "_______________________________________________________________________________________________" << endl
			<< "|" << "�" << setw(3) << "|" << setw(5) << "�������" << setw(9) << "|" << "���" << setw(13) << "|"
			<< "����� ������������ ����" << "|" << "�����" << setw(12) << "|" << "������" << "           |" << endl
			<< "|___|_______________|_______________|_______________________|________________|_________________|" << endl;

		for (int i = 0; i < numberOfRecords; i++)
		{
			recv(Socket, surname, 20, 0);
			recv(Socket, name, 20, 0);
			recv(Socket, driveLisence, 20, 0);
			recv(Socket, login, 20, 0);
			recv(Socket, password, 20, 0);
			cout << "|" << i + 1 << setw(3) << "|" << surname << setw(16 - strlen(surname)) << "|"
				<< name << setw(16 - strlen(name)) << "|" << driveLisence
				<< setw(24 - strlen(driveLisence)) << "|" << login << setw(17 - strlen(login)) << "|"
				<< password << setw(18 - strlen(password)) << "|" << endl
				<< "|___|_______________|_______________|_______________________|________________|_________________|" << endl;
		}
	}
	return numberOfRecords;
}