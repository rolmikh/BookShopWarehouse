#pragma once
#include <string>
#include <chrono>


using namespace std;

class ProductOrderRequest
{
private:
	int idProductOrderRequest;
	wstring requestNumber;
	chrono::system_clock::time_point dateOfCreation;
	int employeeId;
	wstring commentary;
	int counterpartyId;

public:
	ProductOrderRequest(int idProductOrderRequest, wstring requestNumber, chrono::system_clock::time_point dateOfCreation, int employeeId, wstring commentary, int counterpartyId);
};

