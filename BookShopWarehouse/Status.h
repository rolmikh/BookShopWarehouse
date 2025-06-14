#pragma once
#include <string>

using namespace std;

class Status
{
private:
	int idStatus;
	wstring nameStatus;

public:
	Status(int idStatus, wstring nameStatus);
	int getIdStatus() const;
	wstring getNameStatus() const;

};

