#pragma once
#include <string>
#include <chrono>

using namespace std;

class Contract
{
private:
	int idContract;
	wstring contractNumber;
	wstring startDateContract;
	wstring endDateContract;
	wstring contractTerms;
	int statusId;

public:
	Contract(int idContract, wstring contractNumber, wstring startDateContract, wstring endDateContract, wstring contractTerms, int statusId);

	int getIdContract() const;
	wstring getContractNumber() const;
	wstring getStartDataContract() const;
	wstring getEndDateContract() const;
	wstring getContractTerms() const;
	int getStatusId() const;

};

