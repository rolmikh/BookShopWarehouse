#include "DeliveryNote.h"

using namespace std;

DeliveryNote::DeliveryNote(int idDeliveryNote, wstring deliveryNoteNumber, chrono::system_clock::time_point dateOfFormation, int contractId)
	: idDeliveryNote(idDeliveryNote), deliveryNoteNumber(deliveryNoteNumber), dateOfFormation(dateOfFormation), contractId(contractId){}
