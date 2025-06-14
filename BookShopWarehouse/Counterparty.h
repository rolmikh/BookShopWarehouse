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

	int getIdCounterparty() const;
	wstring getNameCounterparty() const;
	wstring getPhoneCounterparty() const;
	wstring getEmailCounterparty() const;
	wstring getContractPerson() const;
	wstring getTermsOfCooperation() const;
	wstring getCountry() const;
	wstring getCity() const;
	int getTypeOfCounterpartyId() const;



};

