#include"Libraries.h"
#include"Checks.h"
#include"System.h"
#include"AdminSystem.h"
#include"DriverSystem.h"
#include "ExpertSystem.h"
SOCKET Socket;

int main(int argc, char* argv[])
{
	system("title Клиент--Автоматизированная среда управления автопарком");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Ошибка соединения." << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Socket = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Socket, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Ошибка подключения к серверу" << endl;
		return 1;
	}

	AdminSystem admin;
	while (1)
	{
		int choice;
		cout << "1.Вход под администратором." << endl;
		cout << "2.Вход в качестве водителя." << endl;
		cout << "3.Вход в качестве эксперта." << endl;
		cout << "4.Выход из программы." << endl;
		cout << " Ваш выбор? " << endl;
		choice = check<int>(1, 4);
		System* systemW;

		DriverSystem driver;
		ExpertSystem expert;
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);

		switch (choice)
		{
		case 1: system("cls"); systemW = &admin;  systemW->authorize();  break;
		case 2: system("cls"); systemW = &driver; systemW->authorize(); break;
		case 3: system("cls"); systemW = &expert; systemW->authorize();  break;
		case 4:system("cls");  exit(0); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}
	}
	system("pause");
	return 0;
}