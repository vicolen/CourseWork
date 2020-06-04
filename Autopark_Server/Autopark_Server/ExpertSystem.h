#include "System.h"
#include"Libraries.h"
#pragma once
class ExpertSystem:public System
{
	string login;
	string password;
public:
	int authorize() override;
	void callMainMenu() override;
	void viewApprovedRoutes();
};

