#include"Libraries.h"
#pragma once
class System
{
protected:
   
	char  login[20]="";
	char password[20]="";
public:
	virtual int authorize() = 0;
	virtual void callMainMenu() = 0;
};
