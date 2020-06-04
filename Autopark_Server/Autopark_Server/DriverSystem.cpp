#include "DriverSystem.h"
#include "Checks.h"
#include"Venicle.h"

extern SOCKET Socket2[100];
extern int index;

void  DriverSystem::callMainMenu()
{
	int a = 0;
	do
	{
		char msgChoice[5];
		recv(Socket2[index], msgChoice, 5, 0);
		int choice = atoi(msgChoice);
		switch (choice)
		{
		case 1: registerRoute();  break;
		case 2: viewRecordedRoutes(); break;
		case 3: viewApprovedRoutes(); break;
		case 4: a = 4; system("cls"); break;
		}

	} while (a != 4);
	
}
int DriverSystem::authorize()
{
	char  login[20];
	char password[20];
	recv(Socket2[index], login, 20, 0);
	recv(Socket2[index], password, 20, 0);
	ifstream file;
	string puth = "Drivers.txt";
	file.open(puth);
	if ((file.is_open()))
	{
		int numberOfAccount = returnNumberOfRecords(5);
		vector<DriverSystem> drivers;
		readFromFile(&drivers);
		int m = -1;
		for (int i = 0; i < numberOfAccount; i++)
		{
			if ((strcmp(drivers[i].password, password) == 0) && (strcmp(drivers[i].login, login) == 0))
			{

				send(Socket2[index], "1", 2, 0);
				send(Socket2[index], drivers[i].surname, 20, 0);
				send(Socket2[index], drivers[i].name, 20, 0);

				strcpy(surname, drivers[i].surname);
				strcpy(name, drivers[i].name);

				callMainMenu();
				return 1;
			}

		}
		if (m == -1)
		{
			send(Socket2[index], "0", 2, 0);
			char msg[54] = "Пользователь с таким логином и паролем не существует.";
			char msg1[20] = "Повторите еще раз.";
			send(Socket2[index], msg, 54, 0);
			send(Socket2[index], msg1, 20, 0);
			return 0;
		}

	}
	file.close();
	return 0;

}

void DriverSystem::registerRoute()
{
	char pC[5]; int p;
	recv(Socket2[index], pC, 5, 0);
	p = atoi(pC);
	if (p == 1)
	{
		recv(Socket2[index], msgGoal, 30, 0);
		recv(Socket2[index], kmC, 30, 0);
		recv(Socket2[index], surname, 20, 0);
		recv(Socket2[index], name, 20, 0);
		SYSTEMTIME st;
		GetSystemTime(&st);
		ofstream file;
		string puth = "Roate.txt";
		file.open(puth, ofstream::app);
		if (file.is_open())
		{
			file << msgGoal << endl;
			file << kmC << endl;
			file << surname << endl;
			file << name << endl;
			file << st.wDay + 1 << "." << st.wMonth << "." << st.wYear << endl;
			changeNumberOfRecords(1, 2);
			file.close();
			char msg[37] = "Маршрут успешно зарегистрирован";
			send(Socket2[index], msg, 37, 0);
		}
		else
		{
			char msg[37] = "Сбой регистрации. Повторите снова.";
			send(Socket2[index], msg, 37, 0);
		}
	}


}
int  DriverSystem::viewRecordedRoutes()
{
	ifstream file;
	string puth = "Roate.txt";
	file.open(puth);
	vector<DriverSystem> drivers;
	int numberOfRecords = returnNumberOfRecords(2);

	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);

	if (numberOfRecords != 0)
	{
		if (file.is_open())
		{
			DriverSystem driver;
			string m;
			for (int i = 0; i < numberOfRecords; i++)
			{
				file >> driver;
				
				if ((strcmp(driver.surname, surname) == 0) && (strcmp(driver.name, name) == 0))
				{
					drivers.push_back(driver);
				}
			}
			char number[5];
			_itoa_s(drivers.size(), number, 10);
			send(Socket2[index], number, 5, 0);
			if (drivers.size() != 0)
			{
				for (int i = 0; i < (int)drivers.size(); i++)
				{
					send(Socket2[index], drivers[i].msgGoal, 30, 0);
					send(Socket2[index], drivers[i].kmC, 30, 0);
					send(Socket2[index], drivers[i].dataTime, 20, 0);
				}

			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
	return 0;
}
int  DriverSystem::viewApprovedRoutes()
{
	ifstream file;
	string puth = "RoateFinal.txt";
	file.open(puth);

	int numberOfRecords = returnNumberOfRecords(4);

	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);

	if (numberOfRecords != 0)
	{
		if (file.is_open())
		{
			typedef pair<DriverSystem, Venicle> pair;
			vector<pair> data;

			DriverSystem driver;
			Venicle venicle;
			string m;

			for (int i = 0; i < numberOfRecords; i++)
			{
				file >> driver;
				file >> venicle;
				file >> driver.dataAdm;
				if ((strcmp(driver.surname, surname) == 0) && (strcmp(driver.name, name) == 0))
				{
					data.push_back(pair(driver, venicle));
				}
			}
			char number[5];
			_itoa_s(data.size(), number, 10);
			send(Socket2[index], number, 5, 0);
			if (data.size() != 0)
			{
				vector<pair>::iterator n;
				for (n = data.begin(); n != data.end(); ++n)
				{
					send(Socket2[index], n->first.msgGoal, 30, 0);
					send(Socket2[index], n->first.kmC, 30, 0);
					send(Socket2[index], n->first.dataTime, 20, 0);
					n->second.sendV();

				}

			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
	return 0;

}
void DriverSystem::sendV()
{
	send(Socket2[index], msgGoal, 30, 0);
	send(Socket2[index], kmC, 30, 0);
	send(Socket2[index], surname, 20, 0);
	send(Socket2[index], name, 20, 0);
	send(Socket2[index], dataTime, 20, 0);
}
ifstream& operator >>(ifstream& file, DriverSystem& ob)
{
	string m;
	getline(file >> ws, m);
	strcpy(ob.msgGoal, m.c_str());
	string n;
	getline(file, n);
	strcpy(ob.kmC, n.c_str());
	string b;
	getline(file, b);
	strcpy(ob.surname, b.c_str());
	string v;
	getline(file, v);
	strcpy(ob.name, v.c_str());

	string z;
	getline(file, z);
	strcpy(ob.dataTime, z.c_str());

	/*file >> ob.msgGoal;
	file >> ob.kmC;
	file >> ob.surname;
	file >> ob.name;*/
	return file;
}
ofstream& operator <<(ofstream& file, DriverSystem& ob)
{
	file << ob.msgGoal << endl;
	file << ob.kmC << endl;
	file << ob.surname << endl;
	file << ob.name << endl;
	return file;
}

void DriverSystem::deleteRecordedRoutes()
{
	int numberOfRecords = returnNumberOfRecords(2);
	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		viewRecordedRoutes();
		char numRecC[5]; int numRec;
		recv(Socket2[index], numRecC, 5, 0);
		numRec = atoi(numRecC);
		ifstream file;
		string puth = "Roate.txt";
		file.open(puth);
		vector<DriverSystem> drivers;
		if (file.is_open())
		{
			DriverSystem driver;
			string m;
			for (int i = 0; i < numberOfRecords; i++)
			{
				file >> driver;
				if ((strcmp(driver.surname, surname) == 0) && (strcmp(driver.name, name) == 0))
				{
					drivers.push_back(driver);
				}
			}
		}
		file.close();
		ofstream filef;

		filef.open(puth);

		if (filef.is_open())
		{
			DriverSystem driver;
			string m;
			for (int i = 0; i < numRec - 1; i++)
			{
				filef << drivers[i];
			}
			for (int i = numRec; i < numberOfRecords; i++)
			{
				filef << drivers[i];
			}
		}
		file.close();
		viewRecordedRoutes();
	}

}

void DriverSystem::addDriver()
{

	recv(Socket2[index], surname, 20, 0);
	recv(Socket2[index], name, 20, 0);
	recv(Socket2[index], driveLicense, 20, 0);
	recv(Socket2[index], login, 20, 0);
	recv(Socket2[index], password, 20, 0);
	for (int i = 0; i < (int)strlen(login); i++) login[i] = login[i] - 7;
	for (int i = 0; i <(int) strlen(password); i++) password[i] = password[i] - 7;

	string puth = "Drivers.txt";
	ofstream file;
	file.open(puth, ofstream::app);
	if (file.is_open())
	{
		file << surname << endl;
		file << name << endl;
		file << driveLicense << endl;
		file << login << endl;
		file << password << endl;
		file.close();
		changeNumberOfRecords(1, 5);
		char message[30] = "Информация успешно добавлена.";
		send(Socket2[index], message, 30, 0);
	}
	else
	{
		char message[20] = "Файл не был открыт.";
		send(Socket2[index], message, 20, 0);
	}
}
void DriverSystem::editDriver()
{
	int numberOfRecords = returnNumberOfRecords(5);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		viewDriver();
		vector<DriverSystem> drivers;
		readFromFile(&drivers);

		char numRecC[5]; int numRec;
		recv(Socket2[index], numRecC, 5, 0);
		numRec = atoi(numRecC);

		char pC[5]; int p;
		recv(Socket2[index], pC, 5, 0);
		p = atoi(pC);
		switch (p)
		{
		case 1: recv(Socket2[index], drivers[numRec].surname, 20, 0); rewriteToFile(drivers); break;
		case 2: recv(Socket2[index], drivers[numRec].name, 20, 0);    rewriteToFile(drivers); break;
		case 3: recv(Socket2[index], drivers[numRec].driveLicense, 20, 0); rewriteToFile(drivers); break;
		case 4: recv(Socket2[index], drivers[numRec].login, 20, 0); rewriteToFile(drivers); break;
		case 5: recv(Socket2[index], drivers[numRec].password, 20, 0); rewriteToFile(drivers); break;
		}
		char message[30] = "Информация успешно изменена.";
		send(Socket2[index], message, 30, 0);
		viewDriver();
	}
}
void DriverSystem::deleteDriver()
{
	char pC[5]; int p;
	recv(Socket2[index], pC, 5, 0);
	p = atoi(pC);

	int numberOfRecords = returnNumberOfRecords(5);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		vector<DriverSystem> drivers;
		readFromFile(&drivers);

		if (p == 1)
		{
			viewDriver();
			char numRecC[5]; int numRec;
			recv(Socket2[index], numRecC, 5, 0);
			numRec = atoi(numRecC);
			string puth = "Drivers.txt";
			ofstream file;
			file.open(puth);
			if (file.is_open())
			{
				for (int i = 0; i < numRec - 1; i++)
				{
					file << drivers[i].surname << endl;
					file << drivers[i].name << endl;
					file << drivers[i].driveLicense << endl;
					for (int m = 0; m < (int)strlen(drivers[i].login); m++) drivers[i].login[m] = drivers[i].login[m] - 7;
					for (int m = 0; m <(int) strlen(drivers[i].password); m++) drivers[i].password[m] = drivers[i].password[m] - 7;
					file << drivers[i].login << endl;
					file << drivers[i].password << endl;
				}
				for (int i = numRec; i < numberOfRecords; i++)
				{
					file << drivers[i].surname << endl;
					file << drivers[i].name << endl;
					file << drivers[i].driveLicense << endl;
					for (int m = 0; m < (int)strlen(drivers[i].login); m++) drivers[i].login[m] = drivers[i].login[m] - 7;
					for (int m = 0; m < (int)strlen(drivers[i].password); m++) drivers[i].password[m] = drivers[i].password[m] - 7;
					file << drivers[i].login << endl;
					file << drivers[i].password << endl;
				}
				file.close();
				changeNumberOfRecords(2, 5);
				char message[30] = "Информация успешно удалена.";
				send(Socket2[index], message, 30, 0);
			}

		}
		if (p == 2)
		{
			string puth = "Drivers.txt";
			ofstream file;
			file.open(puth);
			file.close();
			changeNumberOfRecords(3, 5);
			char message[30] = "Информация успешно удалена.";
			send(Socket2[index], message, 30, 0);
		}

	}
}
void DriverSystem::viewDriver()
{
	vector<DriverSystem> drivers;
	readFromFile(&drivers);

	int numberOfRecords = returnNumberOfRecords(5);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		for (int i = 0; i < numberOfRecords; i++)
		{
			drivers[i].sendDriver();
		}
	}
}
void DriverSystem::readFromFile(vector<DriverSystem>* drivers)
{
	string puth = "Drivers.txt";
	ifstream file;
	file.open(puth);
	if (file.is_open())
	{
		int numberOfDoctors = returnNumberOfRecords(5);
		DriverSystem driver;
		for (int m = 0; m < numberOfDoctors; m++)
		{
			file >> driver.surname;
			file >> driver.name;
			file >> driver.driveLicense;
			file >> driver.login;
			file >> driver.password;
			for (int i = 0; i < (int)strlen(driver.login); i++) driver.login[i] = driver.login[i] + 7;
			for (int i = 0; i < (int)strlen(driver.password); i++) driver.password[i] = driver.password[i] + 7;
			drivers->push_back(driver);
		}

	}
	file.close();
}
void DriverSystem::sendDriver()
{
	send(Socket2[index], surname, 20, 0);
	send(Socket2[index], name, 20, 0);
	send(Socket2[index], driveLicense, 20, 0);
	send(Socket2[index], login, 20, 0);
	send(Socket2[index], password, 20, 0);
}
void DriverSystem::rewriteToFile(vector<DriverSystem> drivers)
{
	string puth = "Drivers.txt";
	ofstream file;
	file.open(puth);
	if (file.is_open())
	{
		for (int i = 0; i < returnNumberOfRecords(5); i++)
		{
			file << drivers[i].surname << endl;
			file << drivers[i].name << endl;
			file << drivers[i].driveLicense << endl;
			for (int m = 0; m < (int)strlen(drivers[i].login); m++) drivers[i].login[m] = drivers[i].login[m] - 7;
			for (int m = 0; m < (int)strlen(drivers[i].password); m++) drivers[i].password[m] = drivers[i].password[m] - 7;

			file << drivers[i].login << endl;
			file << drivers[i].password << endl;
		}
		file.close();
	}
}
