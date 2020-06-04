#include "AdminSystem.h"
#include"Libraries.h"
#include "Checks.h"
#include"Venicle.h"
#include"DriverSystem.h"
extern SOCKET Socket;
int AdminSystem::authorize()
{
	char login[20];
	char password[20];
	cout << "Введите логин" << endl;
	cin >> login;
	send(Socket, login, 20, 0);
	cout << "Введите пароль" << endl;
	int j = 1;
	while (j != 21)
	{
		password[j-1] = _getch();
		if (password[j-1] == '\r')
			break;
		if (password[j-1] == '\b' && j!=0)
		{
			printf("\b \b");
			j--;
		}
		else if (password[j]-1 != '\0')
		{
			printf("*");
			j++;
		}
	}
	password[j-1] = '\0';

	send(Socket, password, 20, 0);
	char result[2];
	recv(Socket, result, 2, 0);
	if (atoi(result) == 1)
	{
		system("cls");
		cout << "Вход выполнен успешно." << endl;
		system("pause");
		system("cls");
		callMainMenu();
		return 1;
	}
	else
	{
		system("cls");
		cout << "Логин или пароль введены неверно." << endl;
		system("pause");
		system("cls");
		return 0;
	}

}
void AdminSystem::callMainMenu()
{
	int a = 0;
	do
	{
		cout << "Меню администратора:" << endl;
		cout << "1.Управление флотом автопарка." << endl;
		cout << "2.Управление задачами." << endl;
		cout << "3.Управление экспертом." << endl;
		cout << "4.Управление штатом водителей." << endl;
		cout << "5.Вернуться назад." << endl;
		int choice = check<int>(1, 5);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);
		Venicle venicle;
		switch (choice)
		{
		case 1:system("cls"); venicle.callMenu(); system("pause"); system("cls"); break;
		case 2: system("cls"); callTaskMenu(); system("pause"); system("cls"); break;
		case 3: system("cls"); editExspert(); system("pause"); system("cls"); break;
		case 4: system("cls"); callDriverMenu(); system("pause"); system("cls"); break;
		case 5: a = 4; system("cls"); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);
}

void AdminSystem::problemStatement()
{
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		char surname[20];
		char name[20];

		char numberC[5];
		recv(Socket, numberC, 5, 0);
		int number = atoi(numberC);

		char kmC[30];
		char msgGoal[30];
		char data[20];
		cout << "________________________________________________________________________________________________________________" << endl
			<< "|" << "№" << setw(3) << "|" << setw(5) << "Фамилия" << setw(9) << "|" << "Имя" << setw(13) << "|"
			<< "Цель маршрута" << "                |" << "Километраж маршрута" << setw(11) << "|" << "Дата маршрута" << "  |" << endl
			<< "|___|_______________|_______________|_____________________________|_____________________________|_______________|" << endl;
		for (int i = 0; i < number; i++)
		{
			recv(Socket, msgGoal, 30, 0);
			recv(Socket, kmC, 30, 0);
			recv(Socket, surname, 20, 0);
			recv(Socket, name, 20, 0);
			recv(Socket, data, 20, 0);
			cout << "|" << i + 1 << "  | " << surname << setw(15 - strlen(surname)) << "|" << name
				<< setw(16 - strlen(name)) << "|" << msgGoal << setw(30 - strlen(msgGoal)) << "|" << kmC
				<< setw(30 - strlen(kmC)) << "|" << data << setw(16 - strlen(data)) << "|" << endl
				<< "|___|_______________|_______________|_____________________________|_____________________________|_______________|" << endl;
		}

		cout << "Выберете маршрут для назначения транспорта." << endl;
		int nR = check<int>(1, number) - 1;
		char nRC[5];
		_itoa_s(nR, nRC, 10);
		send(Socket, nRC, 5, 0);
	r:;
		Venicle venicle;
		int numCars = venicle.view();
		cout << "Выберете три наиболее подходящих для этого маршрута машины." << endl;
		int car1 = check<int>(1, numCars);
		int car2 = check<int>(1, numCars);
		int car3 = check<int>(1, numCars);

		system("cls");
		venicle.view();
		cout << "Ваш выбор:" << endl;
		cout << "Транспортное средство №" << car1 << endl;
		cout << "Транспортное средство №" << car2 << endl;
		cout << "Транспортное средство №" << car3 << endl;

		cout << " 1. Подтвердить выбор" << endl;
		cout << " 2. Повторить выбор" << endl;
		int choice = check<int>(1, 2);
		char repeat[5];
		_itoa_s(choice, repeat, 10);
		send(Socket, repeat, 5, 0);
		if (choice == 1)
		{
			char car1C[5];
			char car2C[5];
			char car3C[5];
			_itoa_s(car1, car1C, 10);
			_itoa_s(car2, car2C, 10);
			_itoa_s(car3, car3C, 10);

			send(Socket, car1C, 5, 0);
			send(Socket, car2C, 5, 0);
			send(Socket, car3C, 5, 0);
		}
		else
		{
			system("cls");
			goto r;
		}
		system("cls");
		char fileIsOpen[30];
		recv(Socket, fileIsOpen, 30, 0);
		cout << fileIsOpen << endl;
	}
}
void AdminSystem::view(int num)
{
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		if (num == -1)
		{
			cout << "_____________________________________________________________________________________________________________________________" << endl
				<< "|" << "№" << setw(3) << "|" << "	Данные клиента" << setw(3) << "|"
				<< "Данные маршрута маршрута" << setw(11) << "|"
				<< setw(10) << "Данные транспортного средства" << setw(37) << "|" << endl
				<< "|___|___________________|__________________________________|_________________________________________________________________|" << endl;
			char msgGoal[30]; 	char kmC[30];
			char surname[20];   char name[20];
			char markOfCar[20]; char registrNumber[20]; char type[20];
			char dataTime[20];  char dataAdm[20];
			for (int m = 0; m < numberOfRecords; m++)
			{
				recv(Socket, msgGoal, 30, 0);
				recv(Socket, kmC, 30, 0);
				recv(Socket, surname, 20, 0);
				recv(Socket, name, 20, 0);
				recv(Socket, dataTime, 20, 0);

				for (int i = 0; i < 3; i++)
				{
					recv(Socket, markOfCar, 20, 0);
					recv(Socket, registrNumber, 20, 0);
					recv(Socket, type, 20, 0);
					if (i == 0)
					{
						cout << "|" << m + 1 << setw(3) << "|" << surname << setw(20 - strlen(surname))
							<< "|" << msgGoal << setw(35 - strlen(msgGoal))
							<< "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
							<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
							<< setw(24 - strlen(type)) << "|" << endl
							<< "|   |                   |                                  |_________________|_______________________|_______________________|" << endl;
					}
					if (i == 1)
					{
						cout << "|" << setw(4) << "|" << name << setw(20 - strlen(name))
							<< "|" << kmC << setw(35 - strlen(kmC))
							<< "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
							<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
							<< setw(24 - strlen(type)) << "|" << endl
							<< "|   |                   |                                  |_________________|_______________________|_______________________|" << endl;

					}
					if (i == 2)
					{
						recv(Socket, dataAdm, 20, 0);
						cout << "|" << setw(4) << "|" << dataAdm << setw(20 - strlen(dataAdm))
							<< "|" << dataTime << setw(35 - strlen(dataTime))
							<< "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
							<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
							<< setw(24 - strlen(type)) << "|" << endl
							<< "|___|___________________|__________________________________|_________________|_______________________|_______________________|" << endl;

					}

				}
			}
		}
		else
		{
			cout << "_____________________________________________________________________________________________________________________________" << endl
				<< "|" << "№" << setw(3) << "|" << "	Данные клиента" << setw(3) << "|"
				<< "Данные маршрута маршрута" << setw(11) << "|"
				<< setw(10) << "Данные транспортного средства" << setw(37) << "|" << endl
				<< "|___|___________________|__________________________________|_________________________________________________________________|" << endl;
			char msgGoal[30]; 	char kmC[30];
			char surname[20];   char name[20];
			char markOfCar[20]; char registrNumber[20]; char type[20];
			char dataTime[20];  char dataAdm[20];

			recv(Socket, msgGoal, 30, 0);
			recv(Socket, kmC, 30, 0);
			recv(Socket, surname, 20, 0);
			recv(Socket, name, 20, 0);
			recv(Socket, dataTime, 20, 0);

			for (int i = 0; i < 3; i++)
			{
				recv(Socket, markOfCar, 20, 0);
				recv(Socket, registrNumber, 20, 0);
				recv(Socket, type, 20, 0);
				if (i == 0)
				{
					cout << "|" << num + 1 << setw(3) << "|" << surname << setw(20 - strlen(surname))
						<< "|" << msgGoal << setw(35 - strlen(msgGoal))
						<< "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
						<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
						<< setw(24 - strlen(type)) << "|" << endl
						<< "|   |                   |                                  |_________________|_______________________|_______________________|" << endl;
				}
				if (i == 1)
				{
					cout << "|" << setw(4) << "|" << name << setw(20 - strlen(name))
						<< "|" << kmC << setw(35 - strlen(kmC))
						<< "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
						<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
						<< setw(24 - strlen(type)) << "|" << endl
						<< "|   |                   |                                  |_________________|_______________________|_______________________|" << endl;

				}
				if (i == 2)
				{
					recv(Socket, dataAdm, 20, 0);
					cout << "|" << setw(4) << "|" << dataAdm << setw(20 - strlen(dataAdm))
						<< "|" << dataTime << setw(35 - strlen(dataTime))
						<< "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
						<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
						<< setw(24 - strlen(type)) << "|" << endl
						<< "|___|___________________|__________________________________|_________________|_______________________|_______________________|" << endl;

				}

			}
		}
	}
	else cout << "Отсутствуют поставленные задачи." << endl;
}
void AdminSystem::edit()
{
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		view(-1);
		cout << "Выберете запись для редактирования." << endl;
		int nR = check<int>(1, numberOfRecords) - 1;
		char nRC[5];
		_itoa_s(nR, nRC, 10);
		send(Socket, nRC, 5, 0);
	r:;
		Venicle venicle;
		int numCars = venicle.view();
		cout << "Выберете три наиболее подходящих для этого маршрута машины." << endl;
		int car1 = check<int>(1, numCars);
		int car2 = check<int>(1, numCars);
		int car3 = check<int>(1, numCars);

		system("cls");
		venicle.view();
		cout << "Ваш выбор:" << endl;
		cout << "Транспортное средство №" << car1 << endl;
		cout << "Транспортное средство №" << car2 << endl;
		cout << "Транспортное средство №" << car3 << endl;

		cout << " 1. Подтвердить выбор" << endl;
		cout << " 2. Повторить выбор" << endl;
		int choice = check<int>(1, 2);
		char repeat[5];
		_itoa_s(choice, repeat, 10);
		send(Socket, repeat, 5, 0);
		if (choice == 1)
		{
			char car1C[5];
			char car2C[5];
			char car3C[5];
			_itoa_s(car1, car1C, 10);
			_itoa_s(car2, car2C, 10);
			_itoa_s(car3, car3C, 10);

			send(Socket, car1C, 5, 0);
			send(Socket, car2C, 5, 0);
			send(Socket, car3C, 5, 0);
		}
		else
		{
			system("cls");
			goto r;
		}
	}

}

void AdminSystem::editExspert()
{
	cout << "1.Изменить логин/пароль эксперта." << endl;
	cout << "2.Просмотреть текущий логин/пароль эксперта." << endl;
	cout << "3.Вернуться назад." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	if (p == 1)
	{
		char login[20];
		char password[20];
		cout << "Введите логин" << endl;
		cin >> login;
		send(Socket, login, 20, 0);
		cout << "Введите пароль" << endl;
		int j = 1;
		while (j != 20)
		{
			password[j-1] = _getch();
			if (password[j-1] == '\r')
				break;
			if (password[j-1] == '\b')
			{
				printf("\b \b");
				j--;
			}
			else if (password[j-1] != '\0')
			{
				printf("*");
				j++;
			}
		}
		password[j-1] = '\0';

		send(Socket, password, 20, 0);
		recv(Socket, login, 20, 0);
		recv(Socket, password, 20, 0);
		cout <<endl<< "Логин: " << login << endl;
		cout << "Пароль: " << password << endl;

	}
	if (p == 2)
	{
		char login[20];
		char password[20];
		recv(Socket, login, 20, 0);
		recv(Socket, password, 20, 0);
		cout << "Логин: " << login << endl;
		cout << "Пароль: " << password << endl;
	}

}
void AdminSystem::callTaskMenu()
{
	int a = 0;
	do
	{
		char kolC[5];
		recv(Socket, kolC, 5, 0);
		cout << "Меню управления задачами:" << endl;
		cout << "1.Постановка задачи(" << atoi(kolC) << "+)." << endl;
		cout << "2.Просмотр поставленных задач." << endl;
		cout << "3.Редактирование поставленных задач." << endl;
		cout << "4.Вернуться назад." << endl;
		int choice = check<int>(1, 4);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);
		switch (choice)
		{
		case 1: system("cls"); problemStatement(); system("pause"); system("cls"); break;
		case 2: system("cls"); view(-1); system("pause"); system("cls"); break;
		case 3: system("cls"); edit(); system("pause"); system("cls"); break;
		case 4: a = 4; system("cls"); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);
}
void AdminSystem::callDriverMenu()
{
	int a = 0;
	do
	{
		cout << "Меню управления штатом водителей:" << endl;
		cout << "1.Добавить сведения о водителе." << endl;
		cout << "2.Просмотреть штат водителей." << endl;
		cout << "3.Редактировать сведения о водителях." << endl;
		cout << "4.Удалить сведения о водителях." << endl;
		cout << "5.Вернуться назад." << endl;
		int choice = check<int>(1, 5);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);
		DriverSystem driver;
		switch (choice)
		{
		case 1: system("cls"); driver.addDriver(); system("pause"); system("cls"); break;
		case 2: system("cls"); driver.viewDriver(); system("pause"); system("cls"); break;
		case 3: system("cls"); driver.editDriver(); system("pause"); system("cls"); break;
		case 4: system("cls"); driver.deleteDriver(); system("pause"); system("cls"); break;
		case 5: a = 4; system("cls"); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);
}