#include "WarehouseWorkerWindow.h"
#include <CommCtrl.h>
#include <AdminWindow.h>
#include "DatabaseManager.h"


using namespace std;

WarehouseWorkerWindow::WarehouseWorkerWindow(DatabaseManager& dbManager) : dbManager(dbManager) {
	hLabelWindow = nullptr;
	hLabelNumberDelivery = nullptr;
	hLabelNumberWarehouse = nullptr;
	hBtnShowAllDelivery = nullptr;
	hBtnShowRejectedDelivery = nullptr;
	hBtnShowDeliveryPosition = nullptr;
	hBtnConfirmDelivery = nullptr;
	hEditNumberDelivery = nullptr;
	hComboBoxWarehouse = nullptr;
	hWnsListViewDelivery = nullptr;
	hWndListViewDeliveryPosition = nullptr;
	hWndListViewWarehouse = nullptr;
	hInstance = nullptr;

}

WarehouseWorkerWindow::~WarehouseWorkerWindow(){}

void WarehouseWorkerWindow::CreateWarehouseWorkerWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {



}



void WarehouseWorkerWindow::CreateElementsView() {



	hComboBoxWarehouse = CreateBaseComboBox(hWnd, hInstance, padding, screenHeight / 2 + 300, screenWidth / 3, 50, reinterpret_cast<HMENU>(IDC_COMBO_BOX_WAREHOUSE));
	FillComboBox(hComboBoxWarehouse, L"select ID_Warehouse, Warehouse_Number from Warehouse", dbManager, comboBoxIdMap);

}

void WarehouseWorkerWindow::DestroyElementsView() {

}

bool WarehouseWorkerWindow::ExecuteSQL(LPCWSTR sql) {
	try {
		dbManager.ExecuteQuery(sql);
		return true;
	}
	catch (...) {
		MessageBox(hWnd, L"Ошибка выполнения SQL", L"Ошибка", MB_OK | MB_ICONERROR);
		return false;
	}
}


