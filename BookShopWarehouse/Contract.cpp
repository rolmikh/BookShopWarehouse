#include "Contract.h"

using namespace std;

Contract::Contract(int idContract, wstring contractNumber, chrono::system_clock::time_point startDateContract, chrono::system_clock::time_point endDateContract, wstring contractTerms, int statusId)
	: idContract(idContract), contractNumber(contractNumber), startDateContract(startDateContract), endDateContract(endDateContract), contractTerms(contractTerms), statusId(statusId){}
