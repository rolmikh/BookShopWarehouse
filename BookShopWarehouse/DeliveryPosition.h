#pragma once

using namespace std;

class DeliveryPosition
{
private:
	int idDeliveryPosition;
	int requisitionPositionId;
	int deliveryId;

public:
	DeliveryPosition(int idDeliveryPosition, int requisitionPositionId, int deliveryId);
};

