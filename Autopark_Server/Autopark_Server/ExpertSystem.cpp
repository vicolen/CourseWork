#include "ExpertSystem.h"
#include "Checks.h"
#include"DriverSystem.h"
#include"AdminSystem.h"
#include"Venicle.h"
extern SOCKET Socket2[100];
extern int index;
void runMethod();
int ExpertSystem::authorize()
{
	char login[20];
	char password[20];
	recv(Socket2[index], login, 20, 0);
	recv(Socket2[index], password, 20, 0);

	ifstream file;
	string puth = "Exspert.txt";
	file.open(puth);
	ExpertSystem expert;
	if ((file.is_open()))
	{
		getline(file, expert.login);
		getline(file, expert.password);
	}
    file.close();

	for (int i = 0; i < (int)expert.login.size(); i++) expert.login[i] = expert.login[i] + 7;
	for (int i = 0; i < (int)expert.password.size(); i++) expert.password[i] = expert.password[i] + 7;

	char result[2];
	if ((expert.password == password) && (expert.login == login))
	{
		_itoa_s(1, result, 2, 10);
		send(Socket2[index], result, 2, 0);
		callMainMenu();
	}
	else {
		_itoa_s(0, result, 2, 10);
		send(Socket2[index], result, 2, 0);
	}
	return 0;
}
void  ExpertSystem::callMainMenu()
{
	int a = 0;
	do
	{
		int kol = returnNumberOfRecords(3);
		char kolC[5];
		_itoa_s(kol, kolC, 10);
		send(Socket2[index], kolC, 5, 0);

		char msgChoice[5];
		recv(Socket2[index], msgChoice, 5, 0);
		int choice = atoi(msgChoice);
		switch (choice)
		{
		case 1: runMethod(); break;
		case 2: viewApprovedRoutes(); break;
		case 3: a = 4; system("cls"); break;
		}

	} while (a != 4);
}
void runMethod()
{
    r:;
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

			char number[5];
			_itoa_s(data.size(), number, 10);
			send(Socket2[index], number, 5, 0);
			if (data.size() != 0)
			{
				AdminSystem admin;
				admin.view(-1);
			
				vector<pair>::iterator mapPtr;
				char numberRoateC[5]; int numberRoate;
				recv(Socket2[index], numberRoateC, 5, 0);  numberRoate = atoi(numberRoateC) - 1;
			
				admin.view(numberRoate);
				char msgChoice[5];
				recv(Socket2[index], msgChoice, 5, 0);
				int choice = atoi(msgChoice);
				if (choice == 1)
				{
					double marks[3][6];
					char markC[20];
					for (int i = 0; i < 3; i++)
					{
						admin.view(numberRoate); 
						for (int j = 0; j < 6; j++)
						{
							recv(Socket2[index], markC, 20, 0);
							marks[i][j] = stod(markC);
						}
					}
					double sum[6];
					int m = 0; char summ[20];
					for (int i = 0; i < 6; i++)
					{
						sum[m] = marks[0][i] + marks[1][i] + marks[2][i];
						sprintf(summ, "%f", sum[m]); send(Socket2[index], summ, 20, 0);
						m++;
					}
					double fp1, fp2, fp3;
					char fpC[20];
					fp1 = sum[0] + sum[2];  sprintf(fpC, "%f", fp1); send(Socket2[index], fpC, 20, 0);
					fp2 = sum[1] + sum[4];  sprintf(fpC, "%f", fp2); send(Socket2[index], fpC, 20, 0);
					fp3 = sum[3] + sum[5];  sprintf(fpC, "%f", fp3); send(Socket2[index], fpC, 20, 0);
					double w1, w2, w3;
					double k = fp1+ fp2+ fp3; char wC[20];
					w1 = fp1 / k;  sprintf(wC, "%f", w1); send(Socket2[index], wC, 20, 0);
					w2 = fp2 / k;  sprintf(wC, "%f", w2); send(Socket2[index], wC, 20, 0);
					w3 = fp3 / k;  sprintf(wC, "%f", w3); send(Socket2[index], wC, 20, 0);
					int res = -1;
					if (w1 > w2&& w1 > w3) res = 1;
					else if (w2 > w3&& w2 > w1) res = 2;
					else if (w3 > w1&& w3 > w2) res = 3;
					else if (w1 == w2 && w1== w3 && w2==w3) res = 0;
					else if (w1 == w2) res = 4;
					else if (w1 == w3) res = 5;
					else if (w2 == w3) res = 6;

					char resC[5];
					_itoa_s(res, resC, 10);
					send(Socket2[index], resC, 5, 0);

					mapPtr = data.begin();
					advance(mapPtr, numberRoate);
					for (int i = 0; i < 3; i++)
					{
						send(Socket2[index], mapPtr->second[i].markOfCar, 20, 0);
						send(Socket2[index] ,mapPtr->second[i].registrNumber, 20, 0);
						send(Socket2[index], mapPtr->second[i].type, 20, 0);
					}

					char finalC[5]; int finalRes;
					recv(Socket2[index], finalC, 5, 0);  finalRes = atoi(finalC);
					cout << finalRes << endl;
					mapPtr = data.begin();
					advance(mapPtr, numberRoate);
					ofstream filef;
					string puth1 = "RoateFinal.txt";
					filef.open(puth1, ofstream::app);
					if (file.is_open())
					{
						filef << mapPtr->first;
						filef << mapPtr->first.dataTime << endl;
						filef << mapPtr->second[finalRes];
						filef << mapPtr->first.dataAdm << endl;
						changeNumberOfRecords(1, 4);
					}
					filef.close();

					ofstream file1;
					string puth3 = "RoutToExpert.txt";
					file1.open(puth3);
					if (file1.is_open())
					{
						for (int i = 0; i < numberRoate; i++)
						{
							file1 << data[i].first;
							file1 << data[i].first.dataTime << endl;
							file1 << data[i].second[0];
							file1 << data[i].second[1];
							file1 << data[i].second[2];
							file1<< data[i].first.dataAdm << endl;
						}
						for (int i = numberRoate; i < (int)data.size(); i++)
						{
							file1 << data[i].first;
							file1 << data[i].first.dataTime << endl;
							file1 << data[i].second[0];
							file1 << data[i].second[1];
							file1 << data[i].second[2];
							file1 << data[i].first.dataAdm << endl;
						}
					}
					changeNumberOfRecords(2, 3);
					file1.close();
					send(Socket2[index], "Маршрут успешно обработан.", 27, 0);
				}
				else
				{
					goto r;
				}
			}
        }
		file.close();
	}
}
void  ExpertSystem::viewApprovedRoutes()
{
	ifstream file;
	string puth = "RoateFinal.txt";
	file.open(puth);
	int number = 0;
	if (file.is_open())
	{
		int numberOfRecords = returnNumberOfRecords(4);
		char numberOfRecordsC[5];
		_itoa_s(numberOfRecords, numberOfRecordsC, 10);
		send(Socket2[index], numberOfRecordsC, 5, 0);
		if (numberOfRecords != 0)
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
				data.push_back(pair(driver, venicle));
			}
			char number[5];
			if (data.size() != 0)
			{
				_itoa_s(data.size(), number, 10);
				send(Socket2[index], number, 5, 0);
				vector<pair>::iterator n;
				for (n = data.begin(); n != data.end(); ++n)
				{
					n->first.sendV();
					n->second.sendV();
					
				}

			}
		}
		
	}

}