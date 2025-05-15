#pragma once
#include <windows.h>
#include <string>
#include <commctrl.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"
#include "QueryDescriptor.h"



class AdminWindow : public BaseWindow
{
public:

	static const int IDC_TAB_POST = 1001;
	static const int IDC_TAB_TYPE_OF_COUNTERPARTY = 1002;
	static const int IDC_TAB_CONTRACT = 1003;
	static const int IDC_TAB_COUNTERPARTY = 1004;
	static const int IDC_TAB_DELIVERY = 1005;
	static const int IDC_TAB_DELIVERY_NOTE = 1006;
	static const int IDC_TAB_EMPLOYEE = 1007;
	static const int IDC_TAB_PRODUCT = 1008;
	static const int IDC_TAB_PRODUCT_ORDER_REQUEST = 1009;
	static const int IDC_TAB_REQUISITION_POSITION = 1010;
	static const int IDC_TAB_STATUS = 1011;
	static const int IDC_TAB_TYPE_OF_PRODUCT = 1012;
	static const int IDC_TAB_WAREHOUSE = 1013;
	static const int IDC_ADD = 1014;
	static const int IDC_EDIT = 1015;
	static const int IDC_DELETE = 1016;
	static const int IDC_FILTER = 1017;
	static const int IDC_SEARCH = 1018;
	static const int IDC_DELIVERY_POSITION = 1019;

	int topOffset = 150;
	int padding = 20;
	int listViewHeight = screenHeight / 2 - topOffset - 60;
	int listViewWidth = screenWidth - 2 * padding;

	int buttonHeight = 60;
	int bottomOffset = 40;
	int sideOffset = 40;
	int gap = 20;
	int buttonCount = 3;
	
	int totalGap = gap * (buttonCount - 1);
	int availableWidth = screenWidth - 2 * sideOffset - totalGap;
	int buttonWidth = availableWidth / buttonCount;

	int buttonTop = screenHeight - buttonHeight - bottomOffset;
	int buttonLeft = sideOffset;

	AdminWindow(DatabaseManager& dbManager);
	~AdminWindow();

	void CreateAdminWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);
	

	void DrawTable(HWND tableListView, const QueryDescriptor& descriptor);
	
	void CreateElementsView();
	void DestroyElementsView();

	void UpdateCurrentTabPage(int selected) override;

	using cwstring = const std::wstring&;

	void AddRecord(cwstring tableName, const std::vector<std::wstring>& columnNames, const std::vector<std::wstring>& values);
	void UpdateRecord(cwstring tableName, const std::vector<std::wstring>& columnNames, const std::vector<std::wstring>& values, int id);
	void DeleteRecord(cwstring tableName, int id);

	void hWndForDestroy(HWND& hWndElement);


	void CreateTabButton();

	std::wstring GetWindowTextAsWstring(HWND hWndEdit);

	int selectedItemId = -1;

	HWND GetHandleListView() const { return hWndListView; }

	HWND hBtnTabViewContract;
	HWND hBtnTabViewCounterparty;
	HWND hBtnTabViewDelivery;
	HWND hBtnTabViewDeliveryNote;
	HWND hBtnTabViewDeliveryPosition;
	HWND hBtnTabViewEmployee;
	HWND hBtnTabPost;
	HWND hBtnTabViewProduct;
	HWND hBtnTabViewProductOrderRequest;
	HWND hBtnTabViewRequisitionPosition;
	HWND hBtnTabViewStatus;
	HWND hBtnTabTypeOfCounterparty;
	HWND hBtnTabViewTypeOfProduct;
	HWND hBtnTabViewWarehouse;
	int currentTab = 0;


	HWND hEditIdPost;
	HWND hEditNamePost;
	HWND hEditNameTypeOfCounterparty;




protected:
	HWND hWndListViewContract;
	HWND hWndListViewCounterparty;
	HWND hWndListViewDelivery;	
	HWND hWndListViewDeliveryNote;
	HWND hWndListViewDeliveryPosition;
	HWND hWndListViewEmployee;
	HWND hWndListViewPost;
	HWND hWndListViewProduct;
	HWND hWndListViewProductOrderRequest;
	HWND hWndListViewRequisitionPosition;
	HWND hWndListViewStatus;
	HWND hWndListViewTypeOfCounterparty;
	HWND hWndListViewTypeOfProduct;
	HWND hWndListViewWarehouse;


	HINSTANCE hInstance;

	DatabaseManager& dbManager;

	bool ExecuteSQL(LPCWSTR sql);


	HWND hBtnAdd;
	HWND hBtnEdit;
	HWND hBtnDelete;
	HWND hFilterButton;
	HWND hSearchButton;

	
};

