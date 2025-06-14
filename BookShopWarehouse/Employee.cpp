#include "Employee.h"

using namespace std;

Employee::Employee(int idEmployee, wstring surname, wstring name, wstring patronymic, wstring email, wstring login, wstring password, wstring salt, int postId)
	: idEmployee(idEmployee), surname(surname), name(name), patronymic(patronymic), email(email), login(login), password(password), salt(salt), postId(postId){}

int Employee::getIdEmployee() const { return idEmployee; }
wstring Employee::getSurname() const { return surname; }
wstring Employee::getName() const { return name; }
wstring Employee::getPatronymic() const { return patronymic; }
wstring Employee::getEmail() const { return email; }
wstring Employee::getLogin() const { return login; }
wstring Employee::getPassword() const { return password; }
wstring Employee::getSalt() const { return salt; }
int Employee::getPostId() const { return postId; }
