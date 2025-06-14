#pragma once
#include <string>


class Warehouse
{
private:
	int idWarehouse;
	std::wstring warehouseNumber;
	std::wstring warehouseAddress;
	std::wstring warehouseCapacity;
	std::wstring currentWarehouseLoad;

public:
	Warehouse(int idWarehouse, std::wstring warehouseNumber, std::wstring warehouseAddress, std::wstring warehouseCapacity, std::wstring currentWarehouseLoad);

	int getIdWarehouse() const;
	std::wstring getWarehouseNumber() const;
	std::wstring getWarehouseAddress() const;
	std::wstring getWarehouseCapacity() const;
	std::wstring getCurrentWarehouseLoad() const;
};

