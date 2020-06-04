#include "ExpertSystem.h"
#include"Checks.h"
#include "AdminSystem.h"
extern SOCKET Socket;
int ExpertSystem::authorize()
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
void ExpertSystem::callMainMenu()
{
	int a = 0;
	do
	{
		char kolC[5];
		recv(Socket, kolC, 5, 0);
		cout << "Меню:" << endl;
		cout << "1.Подбор транспортного средства методом парных сравнений(" << kolC << "+)" << endl;
		cout << "2.Просмотр результатов подбора." << endl;
		cout << "3.Вернуться назад." << endl;
		int choice = check<int>(1, 3);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);

		switch (choice)
		{
		case 1: system("cls"); runMethod(); system("pause"); system("cls"); break;
		case 2: system("cls"); viewApprovedRoutes(); system("pause"); system("cls"); break;
		case 3: a = 4; system("cls"); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);
}
int ExpertSystem::runMethod()
{

r:;
	system("cls");
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		char numberOfRoateC[5]; int  numberOfRoate;
		recv(Socket, numberOfRoateC, 5, 0);  numberOfRoate = atoi(numberOfRoateC);
		if (numberOfRoate == 0)
		{
			cout << "Отсутствуют маршруты для назначения." << endl;
		}
		else
		{
			AdminSystem admin;
			admin.view(-1);
			cout << "Выберете маршрут для назначения транспорта." << endl;
			int nR = check<int>(1, numberOfRoate);
			char nRC[5]; _itoa_s(nR, nRC, 10); send(Socket, nRC, 5, 0);
			system("cls");
			admin.view(nR - 1);
			cout << "1. Продолжить работать с данным маршрутом." << endl;
			cout << "2. Поменять маршрут." << endl;
			int choice = check<int>(1, 2);
			char msgChoice[5]; _itoa_s(choice, msgChoice, 10); send(Socket, msgChoice, 5, 0);
			if (choice == 2) goto r;
			else
			{
				double marks[18]; double a, b;
				char markC[20];   int k = 0;
				/*Ввод экспертом оценок.*/
				for (int i = 0; i < 3; i++)
				{
					system("cls");
					admin.view(nR - 1);

					cout << "Осуществлется подбор транспортного средства на маршрут методом парных сравнений." << endl;
					cout << "Внимание! При сравнении двух транспортных средств сумма оценок должна быть равна 1. " << endl << endl;
					cout << "Оценивание экспертом №" << i + 1 << ":" << endl;
					cout << " Сравнивается 1-ое и 2-ое транспортное средство." << endl;
					do
					{
						cout << " Оценка 1-го: "; a = check<double>(0.0, 1.0);
						cout << " Оценка 2-го: "; b = check<double>(0.0, 1.0);;

					} while (!compareMarks(a, b));
					marks[k] = a; k++; marks[k] = b; k++;
					sprintf(markC, "%f", a); send(Socket, markC, 20, 0);
					sprintf(markC, "%f", b); send(Socket, markC, 20, 0);
					cout << endl << " Сравнивается 1-ое и 3-е транспортное средство." << endl;
					do
					{
						cout << " Оценка 1-го: ";  a = check<double>(0.0, 1.0);;
						cout << " Оценка 3-го: ";  b = check<double>(0.0, 1.0);;

					} while (!compareMarks(a, b));
					marks[k] = a; k++; marks[k] = b; k++;
					sprintf(markC, "%f", a); send(Socket, markC, 20, 0);
					sprintf(markC, "%f", b); send(Socket, markC, 20, 0);
					cout << endl << " Сравнивается 2-ое и 3-е транспортное средство." << endl;
					do
					{
						cout << " Оценка 2-го: "; a = check<double>(0.0, 1.0);;
						cout << " Оценка 3-го: "; b = check<double>(0.0, 1.0);;

					} while (!compareMarks(a, b));
					marks[k] = a; k++; marks[k] = b; k++;
					sprintf(markC, "%f", a); send(Socket, markC, 20, 0);
					sprintf(markC, "%f", b); send(Socket, markC, 20, 0);
				}
				/*Вывод итоговой матрицы и весов.*/
				{
					char summ[20];  double sum[6];
					system("cls");
					for (int i = 0; i < 6; i++)
					{
						recv(Socket, summ, 20, 0);
						sum[i] = stod(summ);
					}
					cout << "Матрица оценок маршрутов" << endl;
					cout << "________________________________________________________________________________________" << endl
						<< "|         |Транспорт№1<->Транспорт№2|Транспорт№1<->Транспорт№3|Транспорт№2<->Транспорт№3|" << endl
						<< "|_________|_________________________|_________________________|_________________________|" << endl;
					int m = 0;
					for (int i = 0; i < 3; i++)
					{
						if (marks[0 + m] == 1 || marks[1 + m] == 1 || marks[2 + m] == 1 || marks[3 + m] == 1 || marks[4 + m] == 1 || marks[5 + m] == 1 ||
							marks[0 + m] == 0 || marks[1 + m] == 0 || marks[2 + m] == 0 || marks[3 + m] == 0 || marks[4 + m] == 0 || marks[5 + m] == 0)
						{
							cout << "|Эксперт№" << i + 1 << "|" << setw(6) << marks[0 + m] << setw(7) << "  |" << setw(6) << marks[1 + m] << setw(7) << "  |" << setw(6) << marks[2 + m] << setw(7)
								<< "  |" << setw(6) << marks[3 + m] << setw(7) << "  |" << setw(6) << marks[4 + m] << setw(7) << "  |" << setw(6) << marks[5 + m] << setw(7) << "  |" << endl
								<< "|_________|_________________________|_________________________|_________________________|" << endl;
						}
						else
						{
							cout << "|Эксперт№" << i + 1 << "|" << setw(6) << marks[0 + m] << setw(7) << " |" << setw(6) << marks[1 + m] << setw(7) << " |" << setw(6) << marks[2 + m] << setw(7)
								<< " |" << setw(6) << marks[3 + m] << setw(7) << " |" << setw(6) << marks[4 + m] << setw(7) << " |" << setw(6) << marks[5 + m] << setw(7) << " |" << endl
								<< "|_________|_________________________|_________________________|_________________________|" << endl;

						}
						m += 6;
					}
					cout << "|Сумма    |";
					for (int i = 0; i < 6; i++)
					{
						if (sum[i] == 1 || sum[i] == 2 || sum[i] == 3 || sum[i] == 0)
						{
							cout << "      " << sum[i] << "     |";
						}
						else
						{
							cout << "     " << setprecision(2) << sum[i] << "    |";
						}

					}
					cout << endl << "|_________|____________|____________|____________|____________|____________|____________|" << endl;

					char fpC[20]; double fp1, fp2, fp3;
					recv(Socket, fpC, 20, 0); fp1 = stod(fpC);
					recv(Socket, fpC, 20, 0); fp2 = stod(fpC);
					recv(Socket, fpC, 20, 0); fp3 = stod(fpC);

					char wC[20]; double w1, w2, w3;
					recv(Socket, wC, 20, 0); w1 = stod(wC);
					recv(Socket, wC, 20, 0); w2 = stod(wC);
					recv(Socket, wC, 20, 0); w3 = stod(wC);

					cout << "Оценка-предпочтение fp." << endl;
					cout << "fp1-" << fp1 << "  fp2-" << fp2 << "  fp3-" << fp3 << endl;
					cout << endl << "Вес проектов w." << endl;
					cout << "w1-" << w1 << "  w2-" << w2 << "  w3-" << w3 << endl;

				}
				/*Вывод результатов и подходящего транспорта.*/

				char resC[5]; recv(Socket, resC, 5, 0); int res = atoi(resC);

				if (res == 1)      cout << "Первое транспортное средство предпочтительнее." << endl;
				else if (res == 2) cout << "Второе транспортное средство предпочтительнее." << endl;
				else if (res == 3) cout << "Третье транспортное средство предпочтительнее." << endl;
				else if (res == 4) cout << "Первое  и второе транспортные средства предпочтительнее." << endl;
				else if (res == 5) cout << "Первое и третье транспортное средства предпочтительнее." << endl;
				else if (res == 6) cout << "Второе и третье транспортное средства предпочтительнее." << endl;
				else if (res == 0) cout << "Все транспортные средства подходят." << endl;
				cout << "_______________________________________________________________________" << endl
					<< "|" << "№" << setw(3) << "|" << setw(5) << "Марка автомобиля" << setw(2) << "|" << "Регистрационный номер" << setw(3) << "|"
					<< "Тип по назначению" << setw(7) << "|" << endl
					<< "|___|_________________|_______________________|_______________________|" << endl;
				char markOfCar[20];
				char registrNumber[20];
				char type[20];
				for (int i = 0; i < 3; i++)
				{
					recv(Socket, markOfCar, 20, 0);
					recv(Socket, registrNumber, 20, 0);
					recv(Socket, type, 20, 0);
					if (res == 1 || res == 2 || res == 3)
					{
						if (i == res - 1)
						{
							cout << "|" << i + 1 << setw(3) << "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
								<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
								<< setw(24 - strlen(type)) << "|" << endl
								<< "|___|_________________|_______________________|_______________________|" << endl;
						}

					}
					else if (res == 4)
					{
						if (i == 0 || i == 1)
						{
							cout << "|" << i + 1 << setw(3) << "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
								<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
								<< setw(24 - strlen(type)) << "|" << endl
								<< "|___|_________________|_______________________|_______________________|" << endl;
						}

					}
					else if (res == 5)
					{
						if (i == 0 || i == 2)
						{
							cout << "|" << i + 1 << setw(3) << "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
								<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
								<< setw(24 - strlen(type)) << "|" << endl
								<< "|___|_________________|_______________________|_______________________|" << endl;
						}

					}
					else if (res == 6)
					{
						if (i == 1 || i == 2)
						{
							cout << "|" << i + 1 << setw(3) << "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
								<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
								<< setw(24 - strlen(type)) << "|" << endl
								<< "|___|_________________|_______________________|_______________________|" << endl;
						}

					}
					else if (res == 0)
					{

						cout << "|" << i + 1 << setw(3) << "|" << markOfCar << setw(18 - strlen(markOfCar)) << "|"
							<< registrNumber << setw(24 - strlen(registrNumber)) << "|" << type
							<< setw(24 - strlen(type)) << "|" << endl
							<< "|___|_________________|_______________________|_______________________|" << endl;

					}
				}
				int finalRes;
				if (res > 3 || res == 0)
				{
					cout << "Выберете одно из транспротных средств. Они равнозначны." << endl;
					finalRes = check<int>(1, 3) - 1;

				}
				else
				{
					finalRes = res - 1;
				}
				char finalC[5];
				_itoa_s(finalRes, finalC, 10);
				send(Socket, finalC, 5, 0);


				char msgChoice[28];
				recv(Socket, msgChoice, 28, 0);
				cout << msgChoice << endl;
				}
		}

	}
	return 0;
}
void  ExpertSystem::viewApprovedRoutes()
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
			char surname[20];
			char name[20];
			char markOfVenicle[20];
			char registrNumber[20];
			char type[20];
			char dataTime[20];

			for (int i = 0; i < number; i++)
			{
				recv(Socket, msgGoal, 30, 0);
				recv(Socket, kmC, 30, 0);

				recv(Socket, surname, 20, 0);
				recv(Socket, name, 20, 0);
				recv(Socket, dataTime, 20, 0);
				recv(Socket, markOfVenicle, 20, 0);
				recv(Socket, registrNumber, 20, 0);
				recv(Socket, type, 20, 0);

				cout << "| " << surname << setw(15 - strlen(surname)) << "|" << name
					<< setw(15 - strlen(name)) << "|" << msgGoal << setw(34 - strlen(msgGoal)) << "|" << kmC << setw(25 - strlen(kmC))
					<< "|"<< dataTime << setw(15 - strlen(dataTime)) << "|" << markOfVenicle << setw(15 - strlen(markOfVenicle)) << "|" << registrNumber << endl;
			}
        }
	}
}