#include"Libraries.h"
#include"Checks.h"
#include "System.h"
#pragma once
class DriverSystem :public System
{
public:
	int authorize() override;
	void callMainMenu() override;
	
	int registerRoute();
	void viewRecordedRoutes();
	void viewApprovedRoutes();
	void addDriver();
	int viewDriver();
	void deleteDriver();
	void editDriver();
};
