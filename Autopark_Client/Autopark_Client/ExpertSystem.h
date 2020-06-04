#pragma once
#include "Libraries.h"
#include "System.h"
class ExpertSystem :public System
{
public:
	int authorize() override;
	void callMainMenu() override;
	void viewApprovedRoutes();
	int runMethod();
};

