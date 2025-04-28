#include "Employee.h"

using namespace std;

Employee::Employee(int idEmployee, wstring surname, wstring name, wstring patronymic, wstring email, wstring login, wstring password, wstring salt, int postId)
	: idEmployee(idEmployee), surname(surname), name(name), patronymic(patronymic), email(email), login(login), password(password), salt(salt), postId(postId){}
