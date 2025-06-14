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

	int getIdEmployee() const;
	wstring getSurname() const;
	wstring getName() const;
	wstring getPatronymic() const;
	wstring getEmail() const;
	wstring getLogin() const;
	wstring getPassword() const;
	wstring getSalt() const;
	int getPostId() const;

};

