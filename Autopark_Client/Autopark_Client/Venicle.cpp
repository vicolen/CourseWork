#include "Venicle.h"
#include"Checks.h"
#include"InvalidNumberExeption.h"
extern SOCKET Socket;
void Venicle::add()
{
	cout << "Добавление нового транспортного средства." << endl;
	cout << "Введите марку автомобиля." << endl;
	char markOfVenicle[20];
	do
	{
		cin >> markOfVenicle;
		try
		{
			if (!testLetters(markOfVenicle)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

		}
		catch (const InvalidNumberExeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!testLetters(markOfVenicle));
	
	system("cls");
	char registrNumber[20];
	cout << "Введите регистрационный номер автомобиля (1234-AB-7)." << endl;
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
	char type1[20] = "Грузовой";
	char type2[20] = "Пассажирский";
	char type3[20] = "Грузопассажирский";
	cout << "Введите тип транспортного средства по назначению." << endl;
	cout << "1. Грузовой" << endl;
	cout << "2. Пассажирский" << endl;
	cout << "3. Грузопассажирский" << endl;
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
	cout << "Просмотр транспортных средств." << endl;
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords == 0)
	{
		cout << "Записей нет." << endl;
	}
	else
	{
		char markOfVenicle[20];
		char registrNumber[20];
		char type[20];
		cout << "_______________________________________________________________________" << endl
			<< "|" << "№" << setw(3) << "|" << setw(5) << "Марка автомобиля" << setw(2) << "|" << "Регистрационный номер" << setw(3) << "|"
			<< "Тип по назначению" << setw(7) << "|" << endl
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
		cout << "Выберете номер записи для редактирования." << endl;
		int numRec = check<int>(1, numberOfRecords) - 1;
		char numRecC[5];
		_itoa_s(numRec, numRecC, 10);
		send(Socket, numRecC, 5, 0);

		system("cls");
		cout << "Выберете поле для редактирования." << endl;
		cout << "1.Марка транспортного средства." << endl;
		cout << "2.Регистрационный номер." << endl;
		cout << "3.Тип транспортного средства по назначению." << endl;
		int p = check<int>(1, 3);
		char pC[5];
		_itoa_s(p, pC, 10);
		send(Socket, pC, 5, 0);
		switch (p)
		{
		case 1:
			cout << "Введите марку автомобиля." << endl;
			char markOfVenicle[20];
			do
			{
				cin >> markOfVenicle;
				try
				{
					if (!testLetters(markOfVenicle)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

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
			cout << "Введите регистрационный номер автомобиля (1234-AB-7)." << endl;
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
			char type1[20] = "Грузовой";
			char type2[20] = "Пассажирский";
			char type3[20] = "Грузопассажирский";
			cout << "Введите тип транспортного средства по назначению." << endl;
			cout << "1. Грузовой" << endl;
			cout << "2. Пассажирский" << endl;
			cout << "3. Грузопассажирский" << endl;
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
		cout << "Записи отсутствуют." << endl;
	}

}
void  Venicle::deleteR()
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
			view();
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
void  Venicle::sort()
{
	cout << "1.Сортировать по марке транспорта." << endl;
	cout << "2.Сортировать по типу транспортного средства по назначению." << endl;
	cout << "3.Вернуться назад." << endl;
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
			cout << "Записей нет." << endl;
		}
		else
		{
			cout << "_______________________________________________________________________" << endl
				<< "|" << "№" << setw(3) << "|" << setw(5) << "Марка автомобиля" << setw(2) << "|" << "Регистрационный номер" << setw(3) << "|"
				<< "Тип по назначению" << setw(7) << "|" << endl
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
		cout << "Поиск." << endl;
		cout << "1.По марке транспортного средства." << endl;
		cout << "2.По регистрационному номеру." << endl;
		cout << "3.По типу транспортного средства по назначению." << endl;
		int p = check<int>(1, 3);
		char pC[5];
		_itoa_s(p, pC, 10);
		send(Socket, pC, 5, 0);

		switch (p)
		{
		case 1:
			cout << "Введите марку автомобиля." << endl;
			char markOfVenicle[20];
			do
			{
				cin >> markOfVenicle;
				try
				{
					if (!testLetters(markOfVenicle)) { throw InvalidNumberExeption("Данные введены некорректно. Повторите ввод."); }

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
			cout << "Введите регистрационный номер автомобиля (1234-AB-7)." << endl;
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
			char type1[20] = "Грузовой";
			char type2[20] = "Пассажирский";
			char type3[20] = "Грузопассажирский";
			cout << "Введите тип транспортного средства по назначению." << endl;
			cout << "1. Грузовой" << endl;
			cout << "2. Пассажирский" << endl;
			cout << "3. Грузопассажирский" << endl;
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
				<< "|" << "№" << setw(3) << "|" << setw(5) << "Марка автомобиля" << setw(2) << "|" << "Регистрационный номер" << setw(3) << "|"
				<< "Тип по назначению" << setw(7) << "|" << endl
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
			cout << "Запись не найдена." << endl;
		}

	}
}

void  Venicle::callMenu()
{
	int a = 0;
	do
	{
		cout << "Меню:" << endl;
		cout << "1.Добавление транспортного средства." << endl;
		cout << "2.Просмотр транспортных средств." << endl;
		cout << "3.Редактирование транспортных средств." << endl;
		cout << "4.Удаление транспортных средств." << endl;
		cout << "5.Поиск транспортных средств." << endl;
		cout << "6.Сортировка транспортных средств." << endl;
		cout << "7.Вернуться назад." << endl;
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
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);
}


