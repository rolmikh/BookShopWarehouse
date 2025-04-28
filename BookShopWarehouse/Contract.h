#pragma once
#include <string>
#include <chrono>

using namespace std;

class Contract
{
private:
	int idContract;
	wstring contractNumber;
	chrono::system_clock::time_point startDateContract;
	chrono::system_clock::time_point endDateContract;
	wstring contractTerms;
	int statusId;

public:
	Contract(int idContract, wstring contractNumber, chrono::system_clock::time_point startDateContract, chrono::system_clock::time_point endDateContract, wstring contractTerms, int statusId);

};

