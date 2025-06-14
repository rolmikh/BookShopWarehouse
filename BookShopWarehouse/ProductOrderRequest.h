#pragma once
#include <string>
#include <chrono>


using namespace std;

class ProductOrderRequest
{
private:
	int idProductOrderRequest;
	wstring requestNumber;
	wstring dateOfCreation;
	int employeeId;
	wstring commentary;
	int counterpartyId;

public:
	ProductOrderRequest(int idProductOrderRequest, wstring requestNumber, wstring dateOfCreation, int employeeId, wstring commentary, int counterpartyId);


	int getIdProductOrderRequest() const;
	wstring getRequestNumber() const;
	wstring getDateOfCreation() const;
	int getEmployeeId() const;
	wstring getCommentary() const;
	int getCounterpartyId() const;

};

