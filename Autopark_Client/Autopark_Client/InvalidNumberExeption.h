#include"Libraries.h"
#pragma once
class InvalidNumberExeption :public exception
{
public:
	string errorMessage;
	InvalidNumberExeption(string error) :errorMessage(error) {}
	const char* what() const noexcept { return errorMessage.c_str(); }
	~InvalidNumberExeption() {};
};

