#include "Delivery.h"

using namespace std;

Delivery::Delivery(int idDelivery, wstring deliveryNumber, wstring deliveryDate, int warehouseId, int deliveryNoteId, int statusId)
	: idDelivery(idDelivery), deliveryNumber(deliveryNumber), deliveryDate(deliveryDate), warehouseId(warehouseId), deliveryNoteId(deliveryNoteId), statusId(statusId) {}


int Delivery::getIdDelivery() const { return idDelivery; }
wstring Delivery::getDeliveryNumber() const { return deliveryNumber; }
wstring Delivery::getDeliveryDate() const { return deliveryDate; }
int Delivery::getWarehouseId() const { return warehouseId; }
int Delivery::getDeliveryNoteId() const { return deliveryNoteId; }
int Delivery::getStatusId() const { return statusId; }
