#include "DeliveryNote.h"

using namespace std;

DeliveryNote::DeliveryNote(int idDeliveryNote, wstring deliveryNoteNumber, wstring dateOfFormation, int contractId)
	: idDeliveryNote(idDeliveryNote), deliveryNoteNumber(deliveryNoteNumber), dateOfFormation(dateOfFormation), contractId(contractId){}

int DeliveryNote::getIdDeliveryNote() const { return idDeliveryNote; }
wstring DeliveryNote::getDeliveryNoteNumber() const { return deliveryNoteNumber; }
wstring DeliveryNote::getDateOfFormation() const { return dateOfFormation; }
int DeliveryNote::getContractId() const { return contractId; }
