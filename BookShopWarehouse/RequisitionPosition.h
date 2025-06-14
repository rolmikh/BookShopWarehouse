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
	wstring quantityOfProductInRequisition;
	wstring unitPrice;

public:
	RequisitionPosition(int idRequisitionPosition, wstring positionNumber, int productId, int productOrderRequestId, wstring quantityOfProductInRequisition, wstring unitPrice);


	int getIdRequisitionPosition() const;
	wstring getPositionNumber() const;
	int getProductId() const;
	int getProductOrderRequestId() const;
	wstring getQuantityOfProductInRequisition() const;
	wstring getUnitPrice() const;
};

