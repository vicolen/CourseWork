#include"Libraries.h"
#include"ExpertSystem.h"
#pragma once
class Venicle
{
	char markOfCar[20];
	char registrNumber[20];
	char type[20];
public:
	void sendV();
	void add();
	void view();
	void callMenu();
	Venicle returnCar(int num);
	void readFromFile(vector<Venicle> *venicles);
	void rewriteToFile(vector<Venicle> venicles);
	void  edit();
	void deleteR();
	void search();
	void sort();
	friend ofstream& operator <<(ofstream& file, const Venicle& ob);
	friend ifstream& operator >>(ifstream& file, Venicle& ob);
	friend void runMethod();
};

