#pragma once
#include <string>

using namespace std;

class Employee
{
private: 
	int idEmployee;
	wstring surname;
	wstring name;
	wstring patronymic;
	wstring email;
	wstring login;
	wstring password;
	wstring salt;
	int postId;
	
public:
	Employee(int idEmployee, wstring surname, wstring name, wstring patronymic, wstring email, wstring login, wstring password, wstring salt, int postId);
};

