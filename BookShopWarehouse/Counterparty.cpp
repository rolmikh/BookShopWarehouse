#include "Counterparty.h"

using namespace std;

Counterparty::Counterparty(int idCounterparty, wstring nameCounterparty, wstring phoneCounterparty, wstring emailCounterparty, wstring contactPerson, wstring termsOfCooperation, wstring country, wstring city, int typeOfCounterpartyId)
	: idCounterparty(idCounterparty), nameCounterparty(nameCounterparty), phoneCounterparty(phoneCounterparty),emailCounterparty(emailCounterparty), contactPerson(contactPerson), termsOfCooperation(termsOfCooperation), country(country), city(city), typeOfCounterpartyId(typeOfCounterpartyId){}