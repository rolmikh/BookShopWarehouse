#include "Counterparty.h"

using namespace std;

Counterparty::Counterparty(int idCounterparty, wstring nameCounterparty, wstring phoneCounterparty, wstring emailCounterparty, wstring contactPerson, wstring termsOfCooperation, wstring country, wstring city, int typeOfCounterpartyId)
	: idCounterparty(idCounterparty), nameCounterparty(nameCounterparty), phoneCounterparty(phoneCounterparty),emailCounterparty(emailCounterparty), contactPerson(contactPerson), termsOfCooperation(termsOfCooperation), country(country), city(city), typeOfCounterpartyId(typeOfCounterpartyId){}

int Counterparty::getIdCounterparty() const { return idCounterparty; }
wstring Counterparty::getNameCounterparty() const { return nameCounterparty; }
wstring Counterparty::getPhoneCounterparty() const { return phoneCounterparty; }
wstring Counterparty::getEmailCounterparty() const { return emailCounterparty; }
wstring Counterparty::getContractPerson() const { return contactPerson; }
wstring Counterparty::getTermsOfCooperation() const { return termsOfCooperation; }
wstring Counterparty::getCountry() const { return country; }
wstring Counterparty::getCity() const { return city; }
int Counterparty::getTypeOfCounterpartyId() const { return typeOfCounterpartyId; }