// Autopark_Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include"Libraries.h"
#include"AdminSystem.h"
#include "DriverSystem.h"
#include"ExpertSystem.h"

SOCKET Socket2[100];
int Counter = 0;
int index = 0;
void ClientHandler(int i) 
{
	index = i;
	AdminSystem admin;
	DriverSystem driver;
	ExpertSystem expert;
	char msgChoice[5];
	int t = 0;
	while (true)
	{
		do
		{
			recv(Socket2[i], msgChoice, sizeof(msgChoice), 0);
			int choice = atoi(msgChoice);

			switch (choice)
			{
			case 1: admin.authorize(); break;
			case 2: driver.authorize(); break;
			case 3: expert.authorize(); break;
			case 4:	 t = 2; break;
			}

		} while (t == 0);

	}
}

int main(int argc, char* argv[]) 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title Сервер--Автоматизированная среда управления автопарком");
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Ошибка работы сервера." << endl;
		exit(1);
	}
	else
	{
		cout << "Сервер готов к работе." << endl;
	}
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0)
		{
			cout << "Сбой работы сервера.";
		}
		else
		{
			cout << "Клиент №" << Counter+1 << " подключен.";
			SYSTEMTIME st;
			GetSystemTime(&st);
			cout << " Параметры подключения: " << st.wDay << "." << st.wMonth << "." << st.wYear << ".." << st.wHour << "-" << st.wMinute << endl;
			Socket2[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}
