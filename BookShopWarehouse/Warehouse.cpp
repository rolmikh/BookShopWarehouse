#include "Warehouse.h"

using namespace std;

Warehouse::Warehouse(int idWarehouse, wstring warehouseNumber, wstring warehouseAddress, int warehouseCapacity, int currentWarehouseLoad)
	: idWarehouse(idWarehouse), warehouseNumber(warehouseNumber), warehouseAddress(warehouseAddress), warehouseCapacity(warehouseCapacity), currentWarehouseLoad(currentWarehouseLoad){}
