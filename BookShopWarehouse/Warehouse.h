#pragma once
#include <string>

using namespace std;

class Warehouse
{
private:
	int idWarehouse;
	wstring warehouseNumber;
	wstring warehouseAddress;
	int warehouseCapacity;
	int currentWarehouseLoad;

public:
	Warehouse(int idWarehouse, wstring warehouseNumber, wstring warehouseAddress, int warehouseCapacity, int currentWarehouseLoad);


};

