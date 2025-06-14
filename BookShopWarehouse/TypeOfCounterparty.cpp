#include "TypeOfCounterparty.h"

using namespace std;

TypeOfCounterparty::TypeOfCounterparty(int idTypeOfCounterparty, wstring nameTypeOfCounterparty)
	: idTypeOfCounterparty(idTypeOfCounterparty), nameTypeOfCounterparty(nameTypeOfCounterparty){}


int TypeOfCounterparty::getIdTypeOfCounterparty() const { return idTypeOfCounterparty; }
wstring TypeOfCounterparty::getNameTypeOfCounterparty() const { return nameTypeOfCounterparty; }
