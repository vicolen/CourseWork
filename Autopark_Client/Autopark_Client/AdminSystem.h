#include"Libraries.h"
#include"System.h"
#pragma once
class AdminSystem:public System
{public:
	int  authorize() override;
	void callMainMenu() override;
	void problemStatement();
	void view(int num);
	void edit();
	void editExspert();
	void callTaskMenu();
	void callDriverMenu();

};

