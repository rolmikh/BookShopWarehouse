#include "AdminWindow.h"
#include <commctrl.h>
#include "BaseTable.h"
#include <string>


using namespace std;

AdminWindow::AdminWindow(DatabaseManager& dbManager) : dbManager(dbManager) {
	hWnd = nullptr;
	hWndListViewPost = nullptr;
	hWndListViewTypeOfCounterparty = nullptr;
	hWndListViewContract = nullptr;
	hWndListViewCounterparty = nullptr;
	hWndListViewDelivery = nullptr;
	hWndListViewDeliveryNote = nullptr;
	hWndListViewDeliveryPosition = nullptr;
	hWndListViewEmployee = nullptr;
	hWndListViewProduct = nullptr;
	hWndListViewProductOrderRequest = nullptr;
	hWndListViewRequisitionPosition = nullptr;
	hWndListViewStatus = nullptr;
	hWndListViewTypeOfProduct = nullptr;
	hWndListViewWarehouse = nullptr;
	hBtnTabTypeOfCounterparty = nullptr;
	hBtnTabPost = nullptr;
	hBtnAdd = nullptr;
	hBtnEdit = nullptr;
	hBtnDelete = nullptr;
	hFilterButton = nullptr;
	hSearchButton = nullptr;
	currentTab = 0;
	hEditNamePost = nullptr;
	hEditNameTypeOfCounterparty = nullptr;
	hEditIdPost = nullptr;
}





AdminWindow::~AdminWindow() {}

void AdminWindow::CreateAdminWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	CreateBaseWindow(parentHWnd, windowName, hInstance);

	InitCommonControls();

	this->hInstance = hInstance;

	CreateTabButton();

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	UpdateCurrentTabPage(currentTab);

}


void AdminWindow::UpdateCurrentTabPage(int selected) {

	currentTab = selected;
	DestroyElementsView();

	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	

	HDC hdc = GetDC(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);
	FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
	ReleaseDC(hWnd, hdc);


	InvalidateRect(hWnd, nullptr, TRUE);
	UpdateWindow(hWnd);
	

	switch (selected) {
	case 0:
	{

		hWndListViewPost = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		
		DrawTable(hWndListViewPost, Queries[0]);
		hEditNamePost = CreateBaseEdit(hWnd, hInstance, padding + 100, topOffset + padding + 100, 400, 30);
		hEditIdPost = CreateBaseEdit(hWnd, hInstance, padding, topOffset + padding + 100, 80, 30);

		CreateElementsView();

		ShowWindow(hWndListViewPost, SW_SHOW);

		break;
	}
	case 1:
	{

		hWndListViewTypeOfCounterparty = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewTypeOfCounterparty, Queries[1]);
		hEditNameTypeOfCounterparty = CreateBaseEdit(hWnd, hInstance, padding, topOffset + padding + 100, 400, 30);

		CreateElementsView();

		ShowWindow(hWndListViewTypeOfCounterparty, SW_SHOW);

		break;
	}
	case 2:
	{

		hWndListViewContract = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewContract, Queries[2]);

		CreateElementsView();

		ShowWindow(hWndListViewContract, SW_SHOW);

		break;
	}
		

	}


	InvalidateRect(hWnd, nullptr, TRUE);
	UpdateWindow(hWnd);

}

void AdminWindow::DrawTable(HWND tableListView, const QueryDescriptor& descriptor) {
	HWND targetListView = tableListView;

	const auto& headers = descriptor.headers;
	wstring query = descriptor.sqlQuery;

	if (!targetListView) {
		MessageBox(NULL, L"������ ��� �� ������", L"������", MB_OK | MB_ICONERROR);
		return;
	}

	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"��� ������ ��� �����������", L"������", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"�������������� ���������� � ������", L"������", MB_OK | MB_ICONERROR);
		return;
	}

	BaseTable::ClearListView(targetListView);
	BaseTable::SetHeaders(targetListView, headers);
	BaseTable::SetData(targetListView, tableData);
	BaseTable::AutoResizeColumns(targetListView, headers, tableData);
	BaseTable::ResizeListViewToFit(targetListView, static_cast<int>(tableData.size()));

}


void AdminWindow::CreateElementsView() {

	if (!hBtnAdd) hBtnAdd = CreateBaseButton(hWnd, L"��������", hInstance, buttonLeft, buttonTop - 20, buttonWidth, buttonHeight, reinterpret_cast<HMENU>(IDC_ADD));
	buttonLeft += buttonWidth + gap;
	if(!hBtnEdit) hBtnEdit = CreateBaseButton(hWnd, L"��������", hInstance, buttonLeft, buttonTop - 20, buttonWidth, buttonHeight, reinterpret_cast<HMENU>(IDC_EDIT));
	buttonLeft += buttonWidth + gap;
	if(!hBtnDelete)	hBtnDelete = CreateBaseButton(hWnd, L"�������", hInstance, buttonLeft, buttonTop - 20, buttonWidth, buttonHeight, reinterpret_cast<HMENU>(IDC_DELETE));
	if(!hSearchButton)	hSearchButton = CreateBaseButton(hWnd, L"�", hInstance, screenWidth - 150, 100, 30, 30, reinterpret_cast<HMENU>(IDC_SEARCH));
	if(!hFilterButton)	hFilterButton = CreateBaseButton(hWnd, L"�", hInstance, screenWidth - 100, 100, 30, 30, reinterpret_cast<HMENU>(IDC_FILTER));


	buttonLeft = sideOffset;
}



bool AdminWindow::ExecuteSQL(LPCWSTR sql) {
	try {
		dbManager.ExecuteQuery(sql);
		return true;
	}
	catch (...) {
		MessageBox(hWnd, L"������ ���������� SQL",L"������", MB_OK | MB_ICONERROR);
		return false;
	}
}

void AdminWindow::AddRecord(cwstring tableName, const vector<wstring>& columnNames, const vector<wstring>& values) {

	if (columnNames.size() != values.size()) {
		MessageBox(hWnd, L"���������� ����� �� ���������", L"������", MB_OK | MB_ICONERROR);
		return;
	}

	wstring sql = L"insert into " + tableName + L" (";
	for (size_t i = 0; i < columnNames.size(); ++i) {
		sql += columnNames[i];
		if (i != columnNames.size() - 1) sql += L", ";
	}

	sql += L") values (";

	for (size_t i = 0; i < values.size(); ++i) {
		sql += L"N'" + values[i] + L"'";
		if (i != values.size() - 1) sql += L", ";
	}

	sql += L")";

	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"������ ������� ���������", L"�����", MB_OK);
		
		UpdateCurrentTabPage(currentTab);
	}

}

void AdminWindow::UpdateRecord(cwstring tableName, const vector<wstring>& columnNames, const vector<wstring>& values, int id) {

	if (columnNames.size() != values.size()) {
		MessageBox(hWnd, L"���������� ����� �� ���������", L"������", MB_OK | MB_ICONERROR);
		return;
	}

	wstring sql = L"update " + tableName + L" set ";
	for (size_t i = 0; i < columnNames.size(); ++i) {
		sql += columnNames[i] + L" = N'" + values[i] + L"'";
		if (i != columnNames.size() - 1) sql += L", ";
	}

	sql += L" where ID_" + tableName + L" = " + to_wstring(id);


	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"������ ������� ���������", L"�����", MB_OK);
		
		UpdateCurrentTabPage(currentTab);
	}

}

//������� ���������� �������� ���� ���
void AdminWindow::DeleteRecord(cwstring tableName, int id) {

	
	wstring sql = L"delete from " + tableName + L" Where ID_" + tableName + L" = " + to_wstring(id);
	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"������ ������� �������", L"�����", MB_OK);
		
		UpdateCurrentTabPage(currentTab);
		
	}
}


void AdminWindow::hWndForDestroy(HWND& hWndElement) {
	if (hWndElement) {
		DestroyWindow(hWndElement);
		SetWindowLongPtr(hWndElement, GWLP_USERDATA, NULL);
		hWndElement = nullptr;
	}
}

void AdminWindow::DestroyElementsView() {

	
	hWndForDestroy(hWndListViewContract);
	hWndForDestroy(hWndListViewCounterparty);
	hWndForDestroy(hWndListViewDelivery);
	hWndForDestroy(hWndListViewDeliveryNote);
	hWndForDestroy(hWndListViewDeliveryPosition);
	hWndForDestroy(hWndListViewEmployee);
	hWndForDestroy(hWndListViewPost);
	hWndForDestroy(hWndListViewProduct);
	hWndForDestroy(hWndListViewProductOrderRequest);
	hWndForDestroy(hWndListViewRequisitionPosition);
	hWndForDestroy(hWndListViewStatus);
	hWndForDestroy(hWndListViewTypeOfCounterparty);
	hWndForDestroy(hWndListViewTypeOfProduct);
	hWndForDestroy(hWndListViewWarehouse);

	hWndForDestroy(hBtnAdd);
	hWndForDestroy(hBtnEdit);
	hWndForDestroy(hBtnDelete);
	hWndForDestroy(hFilterButton);
	hWndForDestroy(hSearchButton);

	hWndForDestroy(hEditIdPost);
	hWndForDestroy(hEditNamePost);
	hWndForDestroy(hEditNameTypeOfCounterparty);

}

wstring AdminWindow::GetWindowTextAsWstring(HWND hWndEdit) {
	int length = GetWindowTextLength(hWndEdit);
	std::vector<wchar_t> buffer(length + 1);  // +1 ��� ����� �������� �������
	GetWindowText(hWndEdit, &buffer[0], length + 1);

	return std::wstring(&buffer[0]);
}


void AdminWindow::CreateTabButton() {
	hBtnTabPost = CreateBaseButton(hWnd, L"���������", hInstance, 10, 10, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_POST));
	hBtnTabTypeOfCounterparty = CreateBaseButton(hWnd, L"��� �����������", hInstance, 190, 10, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_TYPE_OF_COUNTERPARTY));
	hBtnTabViewContract = CreateBaseButton(hWnd, L"��������", hInstance, 370, 10, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_CONTRACT));
	hBtnTabViewCounterparty = CreateBaseButton(hWnd, L"����������", hInstance, 550, 10, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_COUNTERPARTY));
	hBtnTabViewDelivery = CreateBaseButton(hWnd, L"��������", hInstance, 730, 10, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_DELIVERY));
	hBtnTabViewDeliveryNote = CreateBaseButton(hWnd, L"���������", hInstance, 910, 10, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_DELIVERY_NOTE));
	hBtnTabViewDeliveryPosition = CreateBaseButton(hWnd, L"������� ��������", hInstance, 1090, 10, 170, 50, reinterpret_cast<HMENU>(IDC_DELIVERY_POSITION));
	hBtnTabViewEmployee = CreateBaseButton(hWnd, L"���������", hInstance, 1270, 10, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_EMPLOYEE));
	hBtnTabViewProduct = CreateBaseButton(hWnd, L"�����", hInstance, 10, 70, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_PRODUCT));
	hBtnTabViewProductOrderRequest = CreateBaseButton(hWnd, L"������ �� �����", hInstance, 190, 70, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_PRODUCT_ORDER_REQUEST));
	hBtnTabViewRequisitionPosition = CreateBaseButton(hWnd, L"������� ������", hInstance, 370, 70, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_REQUISITION_POSITION));
	hBtnTabViewStatus = CreateBaseButton(hWnd, L"������", hInstance, 550, 70, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_STATUS));
	hBtnTabViewTypeOfProduct = CreateBaseButton(hWnd, L"��� ������", hInstance, 730, 70, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_TYPE_OF_PRODUCT));
	hBtnTabViewWarehouse = CreateBaseButton(hWnd, L"�����", hInstance, 910, 70, 170, 50, reinterpret_cast<HMENU>(IDC_TAB_WAREHOUSE));

}

