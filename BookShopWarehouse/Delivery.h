#pragma once
#include <string>
#include <chrono>

using namespace std;

class Delivery
{
private:
	int idDelivery;
	wstring deliveryNumber;
	wstring deliveryDate;
	int warehouseId;
	int deliveryNoteId;
	int statusId;

public:
	Delivery(int idDelivery, wstring deliveryNumber, wstring deliveryDate, int warehouseId, int deliveryNoteId, int statusId); 

	int getIdDelivery() const;
	wstring getDeliveryNumber() const;
	wstring getDeliveryDate() const;
	int getWarehouseId() const;
	int getDeliveryNoteId() const;
	int getStatusId() const;


};

