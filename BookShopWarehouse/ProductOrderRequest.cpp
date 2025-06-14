#include "ProductOrderRequest.h"

using namespace std;

ProductOrderRequest::ProductOrderRequest(int idProductOrderRequest, wstring requestNumber, wstring dateOfCreation, int employeeId, wstring commentary, int counterpartyId) 
	: idProductOrderRequest(idProductOrderRequest), requestNumber(requestNumber), dateOfCreation(dateOfCreation), employeeId(employeeId), commentary(commentary), counterpartyId(counterpartyId){}

int ProductOrderRequest::getIdProductOrderRequest() const { return idProductOrderRequest; }
wstring ProductOrderRequest::getRequestNumber() const { return requestNumber; }
wstring ProductOrderRequest::getDateOfCreation() const { return dateOfCreation; }
int ProductOrderRequest::getEmployeeId() const { return employeeId; }
wstring ProductOrderRequest::getCommentary() const { return commentary; }
int ProductOrderRequest::getCounterpartyId() const { return counterpartyId; }
