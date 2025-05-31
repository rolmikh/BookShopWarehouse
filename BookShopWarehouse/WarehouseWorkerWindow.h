#pragma once
#include <windows.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"
#include "QueryDescriptor.h"
#include "AdminWindow.h"

class WarehouseWorkerWindow : public BaseWindow
{
public:

	static const int IDC_COMBO_BOX_WAREHOUSE = 1050;

	int padding = 20;


	WarehouseWorkerWindow(DatabaseManager& dbManager);
	~WarehouseWorkerWindow();

	void CreateWarehouseWorkerWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);

	void CreateElementsView();
	void DestroyElementsView();

	HWND hLabelWindow;
	HWND hLabelNumberDelivery;
	HWND hLabelNumberWarehouse;

	HWND hBtnShowAllDelivery;
	HWND hBtnShowRejectedDelivery;
	HWND hBtnShowDeliveryPosition;
	HWND hBtnConfirmDelivery;

	HWND hEditNumberDelivery;

	HWND hComboBoxWarehouse;

	void FillComboBox(HWND parentHWnd, const std::wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) override;

	std::vector<int> comboBoxIdMap;



protected:

	HWND hWnsListViewDelivery;
	HWND hWndListViewDeliveryPosition;
	HWND hWndListViewWarehouse;

	DatabaseManager& dbManager;
	HINSTANCE hInstance;

	bool ExecuteSQL(LPCWSTR sql);


};

