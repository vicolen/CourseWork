#include "DriverSystem.h"
#include"Venicle.h"
#include"InvalidNumberExeption.h"
extern SOCKET Socket;
int DriverSystem::authorize()
{
	char  login[20];
	char password[20];

	cout << "Введите логин" << endl;
	cin >> login;
	cout << "Введите пароль" << endl;
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
		cout << "Пользователь " << surname << " " << name << " авторизован." << endl;
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
		cout << "Меню:" << endl;
		cout << "1.Регистрация маршрута." << endl;
		cout << "2.Просмотр зарегистрированных маршрутов." << endl;
		cout << "3.Просмотр одобренных маршрутов." << endl;
		cout << "4.Вернуться назад." << endl;
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
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);

}

int  DriverSystem::registerRoute()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	cout << "Внимание! Маршрут регистрируется за 1 день до поездки." << endl;
	cout << "Текущая дата: " << st.wDay << "." << st.wMonth << "." << st.wYear << endl;
	cout << "Дата поездки: " << st.wDay + 1 << "." << st.wMonth << "." << st.wYear << endl;
	cout << "Для подтверждения своих намерений введите 1." << endl;
	cout << "Для отказа от регистрации введите 2." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	if (p == 1)
	{
		cout << "Введите данные о маршруте." << endl << endl;
		char goal1[30] = "Перевозка легковесного груза";    char km1[30] = "Меньше 100 км";
		char goal2[30] = "Перевозка тяжеловесного груза";   char km2[30] = "Больше 100 км, меньше 1000 км";
		char goal3[30] = "Перевозка пассажиров";            char km3[30] = "Больше 1000 км";
		char goal4[30] = "Деловая поездка";
		cout << "Выберете цель поездки." << endl;
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
		cout << "Выберете киллометраж поездки ." << endl;
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
	else cout << "Регистрация отменена" << endl;
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
			cout << "Зарегистрированные маршруты отсутствуют." << endl;
		}
		else
		{
			cout << "________________________________________________________________________________________________________________" << endl
				<< "|" << "№" << setw(3) << "|" << setw(5) << "Фамилия" << setw(9) << "|" << "Имя" << setw(13) << "|"
				<< "Цель маршрута" << "                |" << "Километраж маршрута" << setw(11) << "|" << "Дата маршрута" << "  |" << endl
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
		cout << "У вас отстутсвуют одобренные маршруты." << endl;
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
			cout << "У вас отстутсвуют одобренные маршруты." << endl;
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
		cout << "У вас отстутсвуют одобренные маршруты." << endl;
	}
}


void DriverSystem::addDriver()
{
	cout << "Добавление нового водителя в штат." << endl;
	cout << "Введите фамилию соотрудника." << endl;
	char surname[20];
	do
	{
		cin >> surname;
		try
		{
			if (!testLetters(surname)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

		}
		catch (const InvalidNumberExeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!testLetters(surname));
	send(Socket, surname, 20, 0);
	system("cls");
	cout << "Введите имя соотрудника." << endl;
	char name[20];
	do
	{
		cin >> name;
		try
		{
			if (!testLetters(name)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

		}
		catch (const InvalidNumberExeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!testLetters(name));
	send(Socket, name, 20, 0);
	system("cls");

	char driveLicense[20];
	cout << "Введите идентификационный номер водительских прав (123456789)." << endl;
	do
	{
		cin >> driveLicense;
		try
		{
			if (!checkDriverLicense(driveLicense)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

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
	cout << "Введите логин водителя для авторизации в системе." << endl;
	cin >> login;
	send(Socket, login, 20, 0);
	cout << "Введите пароль водителя для авторизации в системе." << endl;
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
		cout << "Выберете номер записи для редактирования." << endl;
		int numRec = check<int>(1, numberOfRecords) - 1;
		char numRecC[5];
		_itoa_s(numRec, numRecC, 10);
		send(Socket, numRecC, 5, 0);

		system("cls");
		cout << "Выберете поле для редактирования." << endl;
		cout << "1.Фамилия водителя." << endl;
		cout << "2.Имя водителя." << endl;
		cout << "3.Номер водительских прав." << endl;
		cout << "4.Логин водителя для авторизации в системе." << endl;
		cout << "5.Пароль водителя для авторизации в системе." << endl;
		int p = check<int>(1, 5);
		char pC[5];
		_itoa_s(p, pC, 10);
		send(Socket, pC, 5, 0);
		switch (p)
		{
		case 1:
			system("cls");
			cout << "Введите фамилию соотрудника." << endl;
			char surname[20];
			do
			{
				cin >> surname;
				try
				{
					if (!testLetters(surname)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

				}
				catch (const InvalidNumberExeption e)
				{

					cout << e.errorMessage << endl;

				}

			} while (!testLetters(surname));
			send(Socket, surname, 20, 0); break;
		case 2:
			system("cls");
			cout << "Введите имя соотрудника." << endl;
			char name[20];
			do
			{
				cin >> name;
				try
				{
					if (!testLetters(name)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

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
			cout << "Введите идентификационный номер водительских прав (1234567890)." << endl;
			do
			{
				cin >> driveLicense;
				try
				{
					if (!checkDriverLicense(driveLicense)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

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
			cout << "Введите логин водителя для авторизации в системе." << endl;
			cin >> login;

			send(Socket, login, 20, 0); break;
		case 5:
			system("cls");
			char password[20];
			cout << "Введите пароль водителя для авторизации в системе." << endl;
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
		cout << "Записи отсутствуют." << endl;
	}

}
void DriverSystem::deleteDriver()
{
	cout << "1.Удалить определенную запись." << endl;
	cout << "2.Удалить все." << endl;
	cout << "3.Вернуться назад." << endl;
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
			cout << "Выберете запись для удаления." << endl;
			int numRec = check<int>(1, numberOfRecords);
			char numRecC[5];
			_itoa_s(numRec, numRecC, 10);
			send(Socket, numRecC, 5, 0);
		}
		else cout << "Записи отсутствуют." << endl;
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
	cout << "Просмотр штата водителей." << endl;
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords == 0)
	{
		cout << "Записей нет." << endl;
	}
	else
	{
		char surname[20];      char login[20];
		char name[20];         char password[20];
		char driveLisence[20];
		cout << "_______________________________________________________________________________________________" << endl
			<< "|" << "№" << setw(3) << "|" << setw(5) << "Фамилия" << setw(9) << "|" << "Имя" << setw(13) << "|"
			<< "Номер водительских прав" << "|" << "Логин" << setw(12) << "|" << "Пароль" << "           |" << endl
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