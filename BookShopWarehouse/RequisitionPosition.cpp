#include "RequisitionPosition.h"

using namespace std;

RequisitionPosition::RequisitionPosition(int idRequisitionPosition, wstring positionNumber, int productId, int productOrderRequestId, wstring quantityOfProductInRequisition, wstring unitPrice)
	: idRequisitionPosition(idRequisitionPosition), positionNumber(positionNumber), productId(productId), productOrderRequestId(productOrderRequestId), quantityOfProductInRequisition(quantityOfProductInRequisition), unitPrice(unitPrice) {}


int RequisitionPosition::getIdRequisitionPosition() const { return idRequisitionPosition; }
wstring RequisitionPosition::getPositionNumber() const { return positionNumber; }
int RequisitionPosition::getProductId() const { return productId; }
int RequisitionPosition::getProductOrderRequestId() const { return productOrderRequestId; }
wstring RequisitionPosition::getQuantityOfProductInRequisition() const { return quantityOfProductInRequisition; }
wstring RequisitionPosition::getUnitPrice() const { return unitPrice; }