#include "RequisitionPosition.h"

using namespace std;

RequisitionPosition::RequisitionPosition(int idRequisitionPosition, wstring positionNumber, int productId, int productOrderRequestId, int quantityOfProductInRequisition, float unitPrice)
	: idRequisitionPosition(idRequisitionPosition), positionNumber(positionNumber), productId(productId), productOrderRequestId(productOrderRequestId), quantityOfProductInRequisition(quantityOfProductInRequisition), unitPrice(unitPrice) {}
