#pragma once
#include <string>
#include <chrono>

using namespace std;

class DeliveryNote
{
private:
	int idDeliveryNote;
	wstring deliveryNoteNumber;
	chrono::system_clock::time_point dateOfFormation;
	int contractId;

public:
	DeliveryNote(int idDeliveryNote, wstring deliveryNoteNumber, chrono::system_clock::time_point dateOfFormation, int contractId);
};

