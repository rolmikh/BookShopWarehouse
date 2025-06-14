#include "Contract.h"

using namespace std;

Contract::Contract(int idContract, wstring contractNumber, wstring startDateContract, wstring endDateContract, wstring contractTerms, int statusId)
	: idContract(idContract), contractNumber(contractNumber), startDateContract(startDateContract), endDateContract(endDateContract), contractTerms(contractTerms), statusId(statusId){}


int Contract::getIdContract() const { return idContract; }
wstring Contract::getContractNumber() const { return contractNumber; }
wstring Contract::getStartDataContract() const { return startDateContract; }
wstring Contract::getEndDateContract() const { return endDateContract; }
wstring Contract::getContractTerms() const { return contractTerms; }
int Contract::getStatusId() const { return statusId; }