#include "AdminSystem.h"
#include"Venicle.h"
#include"Libraries.h"
#include"DriverSystem.h"
#include"Checks.h"
extern SOCKET Socket2[100];
extern int index;
void problemStatement();
int AdminSystem::authorize()
{
	char login[20];
	char password[20];
	recv(Socket2[index], login, 20, 0);
	recv(Socket2[index], password, 20, 0);

	ifstream file;
	string puth = "AdminAut.txt";
	file.open(puth);
	AdminSystem admin;
	if ((file.is_open()))
	{
		getline(file, admin.login);
		getline(file, admin.password);
	}
	file.close();

	for (int i = 0; i < (int)admin.login.size(); i++) admin.login[i] = admin.login[i] + 7;
	for (int i = 0; i < (int)admin.password.size(); i++) admin.password[i] = admin.password[i] + 7;

	char result[2];
	if ((admin.password == password) && (admin.login == login))
	{
		_itoa_s(1, result, sizeof(result), 10);
		send(Socket2[index], result, 2, 0);
		callMainMenu();
	}
	else {
		_itoa_s(0, result, sizeof(result), 10);
		send(Socket2[index], result, 2, 0);
	}

	return 0;
}
void AdminSystem::callMainMenu()
{
	int a = 0;
	do
	{
		char msgChoice[5];
		recv(Socket2[index], msgChoice, 5, 0);
		int choice = atoi(msgChoice);
		Venicle venicle;

		switch (choice)
		{
		case 1:venicle.callMenu(); break;
		case 2:callTaskMenu(); break;
		case 3:editExspert(); break;
		case 4:callDriverMenu(); break;
		case 5: a = 4; break;
		}

	} while (a != 4);
}

void problemStatement()
{
	int numberOfRecords = returnNumberOfRecords(2);
	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);

	if (numberOfRecords != 0)
	{
		ifstream file;
		string puth = "Roate.txt";
		file.open(puth);
		int number = 0;
		if (file.is_open())
		{
			vector<DriverSystem> drivers;
			DriverSystem driver;
			for (int i = 0; i < numberOfRecords; i++)
			{
				file >> driver;
				drivers.push_back(driver);

			}
			char number[5];
			_itoa_s(drivers.size(), number, 10);
			send(Socket2[index], number, 5, 0);
			if (drivers.size() != 0)
			{
				for (int i = 0; i < (int)drivers.size(); i++)
				{
					drivers[i].sendV();
				}

				char nRC[5]; int nR;
				recv(Socket2[index], nRC, 5, 0);   nR = atoi(nRC);
			r:;
				Venicle venicle;
				venicle.view();
				venicle.view();

				char repeatC[5]; int repeat;
				recv(Socket2[index], repeatC, 5, 0); repeat = atoi(repeatC);
				if (repeat == 1)
				{
					char car1C[5]; int car1;
					char car2C[5]; int car2;
					char car3C[5]; int car3;

					recv(Socket2[index], car1C, 5, 0); car1 = atoi(car1C);
					recv(Socket2[index], car2C, 5, 0); car2 = atoi(car2C);
					recv(Socket2[index], car3C, 5, 0); car3 = atoi(car3C);

					vector<Venicle> cars;
					cars.push_back(venicle.returnCar(car1));
					cars.push_back(venicle.returnCar(car2));
					cars.push_back(venicle.returnCar(car3));

					string puth = "RoutToExpert.txt";
					ofstream file;
					file.open(puth, ofstream::app);
					if (file.is_open())
					{
						SYSTEMTIME st;
						GetSystemTime(&st);
						file << drivers[nR];
						file << drivers[nR].dataTime << endl;
						file << cars[0];
						file << cars[1];
						file << cars[2];
						file << st.wDay << "." << st.wMonth << "." << st.wYear << ".." << st.wHour << "-" << st.wMinute << endl;
						file.close();

						changeNumberOfRecords(1, 3);

						string puth1 = "Roate.txt";
						ofstream file;
						file.open(puth1);
						if (file.is_open())
						{
							for (int i = 0; i < nR; i++)
							{
								file << drivers[i];
								file << drivers[i].dataTime << endl;

							}
							for (int i = nR; i < numberOfRecords; i++)
							{
								file << drivers[i];
								file << drivers[i].dataTime << endl;
							}
						}
						file.close();
						changeNumberOfRecords(2, 2);
						char message[30] = "Информация успешно добавлена.";
						send(Socket2[index], message, 30, 0);
					}
					else
					{
						char message[30] = "Файл не был открыт.";
						send(Socket2[index], message, 30, 0);
					}

				}
				else
				{
					goto r;
				}
			}
		}
	}
}
void AdminSystem::view(int num)
{
	int numberOfRecords = returnNumberOfRecords(3);
	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		ifstream file;
		string puth = "RoutToExpert.txt";
		file.open(puth);
		if (file.is_open())
		{
			typedef pair<DriverSystem, vector<Venicle>> pair;
			vector<pair> data;
			DriverSystem driver;
			vector<Venicle> venicle;
			Venicle ven;
			for (int i = 0; i < numberOfRecords; i++)
			{
				file >> driver;
				file >> ven; venicle.push_back(ven);
				file >> ven; venicle.push_back(ven);
				file >> ven; venicle.push_back(ven);
				file >> driver.dataAdm;
				pair p(driver, venicle);
				data.push_back(p);
				venicle.clear();
			}
			if (num == -1)
			{
				for (int ptr = 0; ptr < numberOfRecords; ptr++)
				{
					data[ptr].first.sendV();

					for (int i = 0; i < 3; i++)
					{
						data[ptr].second[i].sendV();
					}
					send(Socket2[index], data[ptr].first.dataAdm, 20, 0);
				}

			}
			else
			{
				data[num].first.sendV();

				for (int i = 0; i < 3; i++)
				{
					data[num].second[i].sendV();
				}
				send(Socket2[index], data[num].first.dataAdm, 20, 0);
			}
		}
	}
}
void AdminSystem::edit()
{
	int numberOfRecords = returnNumberOfRecords(3);
	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		view(-1);
		char pC[5]; int p;
		recv(Socket2[index], pC, 5, 0);
		p = atoi(pC);
	r:;
		Venicle venicle;
		venicle.view();
		venicle.view();

		char repeatC[5]; int repeat;
		recv(Socket2[index], repeatC, 5, 0); repeat = atoi(repeatC);
		if (repeat == 1)
		{
			ifstream file;
			string puth = "RoutToExpert.txt";
			file.open(puth);
			if (file.is_open())
			{
				typedef pair<DriverSystem, vector<Venicle>> pair;
				vector<pair> data;
				DriverSystem driver;
				vector<Venicle> venicle;
				Venicle ven;
				for (int i = 0; i < numberOfRecords; i++)
				{
					file >> driver;
					file >> ven; venicle.push_back(ven);
					file >> ven; venicle.push_back(ven);
					file >> ven; venicle.push_back(ven);
					file >> driver.dataAdm;
					pair p(driver, venicle);
					data.push_back(p);
					venicle.clear();
				}

				char car1C[5]; int car1;
				char car2C[5]; int car2;
				char car3C[5]; int car3;

				recv(Socket2[index], car1C, 5, 0); car1 = atoi(car1C);
				recv(Socket2[index], car2C, 5, 0); car2 = atoi(car2C);
				recv(Socket2[index], car3C, 5, 0); car3 = atoi(car3C);

				data[p].second[0] = ven.returnCar(car1);
				data[p].second[1] = ven.returnCar(car2);
				data[p].second[2] = ven.returnCar(car3);

				vector<pair>::iterator i;
				string puth = "RoutToExpert.txt";
				ofstream filef;
				filef.open(puth);
				if (filef.is_open())
				{
					for (i = data.begin(); i != data.end(); ++i)
					{
						filef << i->first;
						filef << i->first.dataTime << endl;
						filef << i->second[0];
						filef << i->second[1];
						filef << i->second[2];
						filef << i->first.dataAdm << endl;
					}
					file.close();
				}
			}
			file.close();
		}
		else
		{
			goto r;
		}
	}

}
void AdminSystem::editExspert()
{
	char pC[5]; int p;
	recv(Socket2[index], pC, 5, 0);
	p = atoi(pC);
	if (p == 1)
	{
		char login[20];
		char password[20];
		recv(Socket2[index], login, 20, 0);
		recv(Socket2[index], password, 20, 0);
		for (int i = 0; i < (int)strlen(login); i++) login[i] = login[i] - 7;
		for (int i = 0; i <(int)strlen(password); i++) password[i] = password[i] - 7;
		ofstream file;
		string puth = "Exspert.txt";
		file.open(puth);
		AdminSystem admin;
		if ((file.is_open()))
		{
			file << login << endl;
			file << password << endl;
		}
		file.close();
		for (int i = 0; i < (int)strlen(login); i++) login[i] = login[i] + 7;
		for (int i = 0; i < (int)strlen(password); i++) password[i] = password[i] + 7;
		send(Socket2[index], login, 20, 0);
		send(Socket2[index], password, 20, 0);
	}
	if (p == 2)
	{
		char login[20]=" ";
		char password[20]=" ";
		ifstream file;
		string puth = "Exspert.txt";
		file.open(puth);
		AdminSystem admin;
		if ((file.is_open()))
		{
			file >> login;
			file >> password;
		}
		file.close();
		for (int i = 0; i < (int)strlen(login); i++) login[i] = login[i] + 7;
		for (int i = 0; i < (int)strlen(password); i++) password[i] = password[i] + 7;
		send(Socket2[index], login, 20, 0);
		send(Socket2[index], password, 20, 0);
	}
}
void AdminSystem::callTaskMenu()
{
	int a = 0;
	do
	{
		int kol = returnNumberOfRecords(2);
		char kolC[5];
		_itoa_s(kol, kolC, 10);
		send(Socket2[index], kolC, 5, 0);

		char msgChoice[5];
		recv(Socket2[index], msgChoice, 5, 0);
		int choice = atoi(msgChoice);

		switch (choice)
		{
		case 1:problemStatement(); break;
		case 2:view(-1); break;
		case 3:edit(); break;
		case 4: a = 4; break;
		}

	} while (a != 4);

}
void AdminSystem::callDriverMenu()
{
	int a = 0;
	do
	{
		char msgChoice[5];
		recv(Socket2[index], msgChoice, 5, 0);
		int choice = atoi(msgChoice);
		DriverSystem driver;
		switch (choice)
		{
		case 1: driver.addDriver(); break;
		case 2: driver.viewDriver(); break;
		case 3: driver.editDriver(); break;
		case 4: driver.deleteDriver(); break;
		case 5: a = 4; break;
		}

	} while (a != 4);

}