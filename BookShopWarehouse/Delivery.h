#pragma once
#include <string>
#include <chrono>

using namespace std;

class Delivery
{
private:
	int idDelivery;
	wstring deliveryNumber;
	chrono::system_clock::time_point deliveryDate;
	int warehouseId;
	int deliveryNoteId;
	int statusId;

public:
	Delivery(int idDelivery, wstring deliveryNumber, chrono::system_clock::time_point deliveryDate, int warehouseId, int deliveryNoteId, int statusId); 

};

