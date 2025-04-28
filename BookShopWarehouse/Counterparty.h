#pragma once
#include <string>

using namespace std;

class Counterparty
{
private:
	int idCounterparty;
	wstring nameCounterparty;
	wstring phoneCounterparty;
	wstring emailCounterparty;
	wstring contactPerson;
	wstring termsOfCooperation;
	wstring country;
	wstring city;
	int typeOfCounterpartyId;

public:
	Counterparty(int idCounterparty, wstring nameCounterparty, wstring phoneCounterparty, wstring emailCounterparty, wstring contactPerson, wstring termsOfCooperation, wstring country, wstring city, int typeOfCounterpartyId);
};

