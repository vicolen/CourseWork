#pragma once
#include "System.h"
class DriverSystem :public System
{
	char msgGoal[30]="";
	char kmC[30] = "";

	char surname[20] = "";
	char name[20] = "";

	char driveLicense[20] = "";
	
public:
	char dataTime[20] = "";
	char dataAdm[20] = "";
	int authorize() override;
	void callMainMenu() override;
	
	void registerRoute();
	int viewRecordedRoutes();
	int viewApprovedRoutes();
	void deleteRecordedRoutes();
	
	void sendV();
	friend ifstream& operator >>(ifstream& file, DriverSystem& ob);
	friend ofstream& operator <<(ofstream& file, DriverSystem& ob);
	friend void problemStatement();
	friend void runMethod();

	void addDriver();
	void viewDriver();
	void deleteDriver();
	void editDriver();

	void readFromFile(vector<DriverSystem>* drivers);
	void rewriteToFile(vector<DriverSystem> drivers);
	VOID sendDriver();
};

