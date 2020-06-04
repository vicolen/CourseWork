#include "Venicle.h"
#include"Checks.h"

extern SOCKET Socket2[100];
extern int index;
void Venicle::add()
{
	recv(Socket2[index], markOfCar, 20, 0);
	recv(Socket2[index], registrNumber, 20, 0);
	recv(Socket2[index], type, 20, 0);
	if (strcmp(type, "Грузовой") == 0 || strcmp(type, "Пассажирский") == 0 || strcmp(type, "Грузопассажирский") == 0)
	{
		string puth = "Venicle.txt";
		ofstream file;
		file.open(puth, ofstream::app);
		if (file.is_open())
		{
			file << markOfCar << endl;
			file << registrNumber << endl;
			file << type << endl;
			file.close();
			changeNumberOfRecords(1, 1);
			char message[30] = "Информация успешно добавлена.";
			send(Socket2[index], message, 30, 0);
		}
		else
		{
			char message[20] = "Файл не был открыт.";
			send(Socket2[index], message, 20, 0);
		}

	}
 }
void Venicle::view()
{
	vector<Venicle> cars;
	readFromFile(&cars);

	int numberOfRecords = returnNumberOfRecords(1);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		for (int i = 0; i < numberOfRecords; i++)
		{
			send(Socket2[index], cars[i].markOfCar, 20, 0);
			send(Socket2[index], cars[i].registrNumber, 20, 0);
			send(Socket2[index], cars[i].type, 20, 0);
		}
	}
}
void  Venicle::edit()
{
	int numberOfRecords = returnNumberOfRecords(1);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		view();
		vector<Venicle> cars;
		readFromFile(&cars);

		char numRecC[5]; int numRec;
		recv(Socket2[index], numRecC, 5, 0);
		numRec = atoi(numRecC);

		char pC[5]; int p;
		recv(Socket2[index], pC, 5, 0);
		p = atoi(pC);
		switch (p)
		{
		case 1: recv(Socket2[index], cars[numRec].markOfCar, 20, 0); rewriteToFile(cars); break;
		case 2: recv(Socket2[index], cars[numRec].registrNumber, 20, 0); rewriteToFile(cars); break;
		case 3: recv(Socket2[index], cars[numRec].type, 20, 0); rewriteToFile(cars); break;
		}
		char message[30] = "Информация успешно изменена.";
		send(Socket2[index], message, 30, 0);
		view();
	}

}
void  Venicle::deleteR()
{
	char pC[5]; int p;
	recv(Socket2[index], pC, 5, 0);
	p = atoi(pC);

	int numberOfRecords = returnNumberOfRecords(1);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		vector<Venicle> cars;
		readFromFile(&cars);

		if (p == 1)
		{
			view();
			char numRecC[5]; int numRec;
			recv(Socket2[index], numRecC, 5, 0);
			numRec = atoi(numRecC);
			string puth = "Venicle.txt";
			ofstream file;
			file.open(puth);
			if (file.is_open())
			{
				for (int i = 0; i < numRec - 1; i++)
				{
					file << cars[i];
				}
				for (int i = numRec; i < numberOfRecords; i++)
				{
					file << cars[i];
				}
				file.close();
				changeNumberOfRecords(2, 1);
				char message[30] = "Информация успешно удалена.";
				send(Socket2[index], message, 30, 0);
			}

		}
		if(p==2)
		{
			string puth = "Venicle.txt";
			ofstream file;
			file.open(puth);
			file.close();
			changeNumberOfRecords(3, 1);
			char message[30] = "Информация успешно удалена.";
			send(Socket2[index], message, 30, 0);
		}
		
	}
}
void  Venicle::sort()
{
	int numberOfRecords = returnNumberOfRecords(1);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		char pC[5]; int p;
		recv(Socket2[index], pC, 5, 0);
		p = atoi(pC);
		vector<Venicle> cars;
		readFromFile(&cars);
		if (p == 1)
		{
			for (int j = 0; j < numberOfRecords; j++)
			{
				for (int i = 0; i < numberOfRecords - 1; i++)
				{
					if (strcmp(cars[i].markOfCar, cars[i + 1].markOfCar) > 0) swap(cars[i], cars[i + 1]);

				}
			}

			for (int i = 0; i < numberOfRecords; i++)
			{
				send(Socket2[index], cars[i].markOfCar, 20, 0);
				send(Socket2[index], cars[i].registrNumber, 20, 0);
				send(Socket2[index], cars[i].type, 20, 0);
			}
		}
		else
		{
			for (int j = 0; j < numberOfRecords; j++)
			{
				for (int i = 0; i < numberOfRecords - 1; i++)
				{
					if (strcmp(cars[i].type, cars[i + 1].type) > 0) swap(cars[i], cars[i + 1]);

				}
			}
			for (int i = 0; i < numberOfRecords; i++)
			{
				send(Socket2[index], cars[i].markOfCar, 20, 0);
				send(Socket2[index], cars[i].registrNumber, 20, 0);
				send(Socket2[index], cars[i].type, 20, 0);
			}
		}
	}
}
void  Venicle::search()
{
	int numberOfRecords = returnNumberOfRecords(1);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2[index], numberOfRecordsC, 5, 0);
	if (numberOfRecords != 0)
	{
		vector<Venicle> cars;
		readFromFile(&cars);
		char pC[5]; int p;
		recv(Socket2[index], pC, 5, 0);
		p = atoi(pC);
		Venicle ven;
		switch (p)
		{
		case 1:
		{
			recv(Socket2[index], ven.markOfCar, 20, 0);
			int com = 0;
			for (int i = 0; i < numberOfRecords; i++)
			{
				if (strcmp(ven.markOfCar, cars[i].markOfCar) == 0)
				{
					com++;
				}

			}
			char comC[5];
			_itoa_s(com, comC, 5, 10);
			send(Socket2[index], comC, 5, 0);
			if (com != 0)
			{
				for (int i = 0; i < numberOfRecords; i++)
				{
					if (strcmp(ven.markOfCar, cars[i].markOfCar) == 0)
					{
						send(Socket2[index], cars[i].markOfCar, 20, 0);
						send(Socket2[index], cars[i].registrNumber, 20, 0);
						send(Socket2[index], cars[i].type, 20, 0);
					}

				}
			}
			break;
		}

		case 2:
		{
			recv(Socket2[index], ven.registrNumber, 20, 0);
			int com = 0;
			for (int i = 0; i < numberOfRecords; i++)
			{
				if (strcmp(ven.registrNumber, cars[i].registrNumber) == 0)
				{
					com++;
				}

			}
			char comC[5];
			_itoa_s(com, comC, 5, 10);
			send(Socket2[index], comC, 5, 0);
			if (com != 0)
			{
				for (int i = 0; i < numberOfRecords; i++)
				{
					if (strcmp(ven.registrNumber, cars[i].registrNumber) == 0)
					{
						send(Socket2[index], cars[i].markOfCar, 20, 0);
						send(Socket2[index], cars[i].registrNumber, 20, 0);
						send(Socket2[index], cars[i].type, 20, 0);
					}

				}
			}
			break;
		}
		case 3:
		{
			recv(Socket2[index], ven.type, 20, 0);
			int com = 0;
			for (int i = 0; i < numberOfRecords; i++)
			{
				if (strcmp(ven.type, cars[i].type) == 0)
				{
					com++;
				}

			}
			char comC[5];
			_itoa_s(com, comC, 5, 10);
			send(Socket2[index], comC, 5, 0);
			if (com != 0)
			{
				for (int i = 0; i < numberOfRecords; i++)
				{
					if (strcmp(ven.type, cars[i].type) == 0)
					{
						send(Socket2[index], cars[i].markOfCar, 20, 0);
						send(Socket2[index], cars[i].registrNumber, 20, 0);
						send(Socket2[index], cars[i].type, 20, 0);
					}

				}
			}
			break;
		}
		}
	}


}

void  Venicle::callMenu()
{
	int a = 0;
	do
	{
		char msgChoice[5];
		recv(Socket2[index], msgChoice, sizeof(msgChoice), 0);
		int choice = atoi(msgChoice);

		switch (choice)
		{
		case 1: add();  break;
		case 2: view(); break;
		case 3: edit();  break;
		case 4: deleteR(); break;
		case 5: search();  break;
		case 6: sort();  break;
		case 7: a = 4;  break;
		}

	} while (a != 4);
}

void Venicle::readFromFile(vector<Venicle>* venicles)
{
	string puth = "Venicle.txt";
	ifstream file;
	file.open(puth);
	if (!file.is_open())
	{
		cout << "Файл не был открыт." << endl;
	}
	else
	{
		int numberOfDoctors = returnNumberOfRecords(1);
		Venicle car;
		for (int i = 0; i < numberOfDoctors; i++)
		{
			file >> car;
			venicles->push_back(car);
		}

	}
	file.close();
}
void Venicle::rewriteToFile(vector<Venicle> venicles)
{
	string puth = "Venicle.txt";
	ofstream file;
	file.open(puth);
	if (file.is_open())
	{
		for (int i = 0; i < returnNumberOfRecords(1); i++)
		{
			file << venicles[i];
		}
		file.close();
	}
}

void Venicle::sendV()
{
	send(Socket2[index], markOfCar, 20, 0);
	send(Socket2[index], registrNumber, 20, 0);
	send(Socket2[index], type, 20, 0);
}
Venicle Venicle::returnCar(int num)
{
	vector<Venicle> cars;
	readFromFile(&cars);
	return cars[num - 1];
}

ofstream& operator <<(ofstream& file, const Venicle& ob)
{
	file << ob.markOfCar << endl;
	file << ob.registrNumber << endl;
	file << ob.type << endl;
	return file;
}
ifstream& operator >>(ifstream& file, Venicle& ob)
{
	file >> ob.markOfCar;
	file >> ob.registrNumber;
	file >> ob.type;
	return file;
}



