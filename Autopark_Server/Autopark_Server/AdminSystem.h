#include"Libraries.h"
#include"System.h"
#pragma once
class AdminSystem :public System
{
	string login;
	string password;
public:
	int  authorize() override;
	void callMainMenu() override;
	void view(int num);
	void edit();
	void editExspert();
	void callDriverMenu();
	void callTaskMenu();
};

