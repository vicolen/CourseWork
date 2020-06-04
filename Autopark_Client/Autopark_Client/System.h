#include"Libraries.h"
#pragma once
class System
{protected:
	char surname[20]="";
	char name[20]="";
public:
	virtual int authorize() = 0;
	virtual void callMainMenu() = 0;
};


