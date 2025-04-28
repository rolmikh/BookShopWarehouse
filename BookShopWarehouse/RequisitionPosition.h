#pragma once
#include <string>

using namespace std;

class RequisitionPosition
{

private: 
	int idRequisitionPosition;
	wstring positionNumber;
	int productId;
	int productOrderRequestId;
	int quantityOfProductInRequisition;
	float unitPrice;

public:
	RequisitionPosition(int idRequisitionPosition, wstring positionNumber, int productId, int productOrderRequestId, int quantityOfProductInRequisition, float unitPrice);
};

