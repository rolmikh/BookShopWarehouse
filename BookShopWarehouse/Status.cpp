#include "Status.h"

using namespace std;

Status::Status(int idStatus, wstring nameStatus)
	: idStatus(idStatus), nameStatus(nameStatus){}

int Status::getIdStatus() const { return idStatus; }
wstring Status::getNameStatus() const { return nameStatus; }
