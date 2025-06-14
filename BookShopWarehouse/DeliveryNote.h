#pragma once
#include <string>
#include <chrono>

using namespace std;

class DeliveryNote
{
private:
	int idDeliveryNote;
	wstring deliveryNoteNumber;
	wstring dateOfFormation;
	int contractId;

public:
	DeliveryNote(int idDeliveryNote, wstring deliveryNoteNumber, wstring dateOfFormation, int contractId);


	int getIdDeliveryNote() const;
	wstring getDeliveryNoteNumber() const;
	wstring getDateOfFormation() const;
	int getContractId() const;

};

