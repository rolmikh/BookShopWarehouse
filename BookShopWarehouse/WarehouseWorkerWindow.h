#pragma once
#include <windows.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"
#include "QueryDescriptor.h"

class WarehouseWorkerWindow : public BaseWindow
{

private:
	static const int IDC_COMBO_BOX_WAREHOUSE = 1050;
	static const int IDC_COMBO_BOX_DELIVERY = 1055;
	int padding = 20;


public:
	static const LPCWSTR CLASS_NAME;


	static const int IDC_BTN_SHOW_ALL_DELIVERY = 1051;
	static const int IDC_BTN_SHOW_REJECTED_DELIVERY = 1052;
	static const int IDC_BTN_SHOW_DELIVERY_POSITION = 1053;
	static const int IDC_BTN_CONFIRM_DELIVERY = 1054;
	static const int IDC_EXIT_WORKER = 1018;


	WindowTypes GetType() const override;



	WarehouseWorkerWindow(DatabaseManager& dbManager);
	~WarehouseWorkerWindow();

	void CreateWarehouseWorkerWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);

	void CreateElementsView() override;
	void DestroyElementsView() override;

	HWND hLabelWindow;
	HWND hLabelNumberDelivery;
	HWND hLabelNumberWarehouse;

	HWND hBtnShowAllDelivery;
	HWND hBtnShowRejectedDelivery;
	HWND hBtnShowDeliveryPosition;
	HWND hBtnConfirmDelivery;

	HWND hComboBoxNumberDelivery;

	HWND hComboBoxWarehouse;

	HWND hBtnExit;

	std::vector<int> comboBoxIdMap;


	void FillComboBox(HWND parentHWnd, const std::wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) override;

	void DrawTable(HWND tableListView, const QueryDescriptor& descriptor) override;

	void hWndForDestroy(HWND& hWndElement);

	std::wstring GetWindowTextAsWstring(HWND hWndEdit) override;


	void DrawTableAllDelivery();
	void DrawTableDeliveryPosition(std::wstring number);

	HWND hWndListViewDeliveryPosition;

	std::wstring currentDeliveryNumberFilter;

	void ConfirmDelivery(std::wstring id);

	void DrawRejectedDelivery();
	DatabaseManager& dbManager;



protected:

	HWND hWndListViewDelivery;
	HWND hWndListViewWarehouse;

	HINSTANCE hInstance;

	bool ExecuteSQL(LPCWSTR sql);


};

