#pragma once
#include <string>


class Warehouse
{
private:
	int idWarehouse;
	std::wstring warehouseNumber;
	std::wstring warehouseAddress;
	int warehouseCapacity;
	int currentWarehouseLoad;

public:
	Warehouse(int idWarehouse, std::wstring warehouseNumber, std::wstring warehouseAddress, int warehouseCapacity, int currentWarehouseLoad);


};

