#include "Warehouse.h"

using namespace std;

Warehouse::Warehouse(int idWarehouse, wstring warehouseNumber, wstring warehouseAddress, wstring warehouseCapacity, wstring currentWarehouseLoad)
	: idWarehouse(idWarehouse), warehouseNumber(warehouseNumber), warehouseAddress(warehouseAddress), warehouseCapacity(warehouseCapacity), currentWarehouseLoad(currentWarehouseLoad){}


int Warehouse::getIdWarehouse() const { return idWarehouse; }
wstring Warehouse::getWarehouseNumber() const { return warehouseNumber; }
wstring Warehouse::getWarehouseAddress() const { return warehouseAddress; }
wstring Warehouse::getWarehouseCapacity() const { return warehouseCapacity; }
wstring Warehouse::getCurrentWarehouseLoad() const { return currentWarehouseLoad; }
