#include "Delivery.h"

using namespace std;

Delivery::Delivery(int idDelivery, wstring deliveryNumber, chrono::system_clock::time_point deliveryDate, int warehouseId, int deliveryNoteId, int statusId)
	: idDelivery(idDelivery), deliveryNumber(deliveryNumber), deliveryDate(deliveryDate), warehouseId(warehouseId), deliveryNoteId(deliveryNoteId), statusId(statusId) {}
