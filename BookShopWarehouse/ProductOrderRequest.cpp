#include "ProductOrderRequest.h"

using namespace std;

ProductOrderRequest::ProductOrderRequest(int idProductOrderRequest, wstring requestNumber, chrono::system_clock::time_point dateOfCreation, int employeeId, wstring commentary, int counterpartyId) 
	: idProductOrderRequest(idProductOrderRequest), requestNumber(requestNumber), dateOfCreation(dateOfCreation), employeeId(employeeId), commentary(commentary), counterpartyId(counterpartyId){}