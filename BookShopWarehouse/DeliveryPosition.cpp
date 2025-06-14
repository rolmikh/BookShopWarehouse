#include "DeliveryPosition.h"

using namespace std;

DeliveryPosition::DeliveryPosition(int idDeliveryPosition, int requisitionPositionId, int deliveryId)
	: idDeliveryPosition(idDeliveryPosition), requisitionPositionId(requisitionPositionId), deliveryId(deliveryId){}

int DeliveryPosition::getIdDeliveryPosition() const { return idDeliveryPosition; }
int DeliveryPosition::getRequisitionPositionId() const { return requisitionPositionId; }
int DeliveryPosition::getDeliveryId() const { return deliveryId; }
