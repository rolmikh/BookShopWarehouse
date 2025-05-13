#include "AdminWindow.h"
#include <commctrl.h>
#include "BaseTable.h"
#include <string>


using namespace std;

AdminWindow::AdminWindow(DatabaseManager& dbManager) : dbManager(dbManager) {
	hWnd = nullptr;
	hWndListViewPost = nullptr;
	hWndListViewTypeOfCounterparty = nullptr;
	hBtnTabTypeOfCounterparty = nullptr;
	hBtnTabPost = nullptr;
	hBtnAdd = nullptr;
	hBtnEdit = nullptr;
	hBtnDelete = nullptr;
	hEditName = nullptr;
	hFilterButton = nullptr;
	hSearchButton = nullptr;
	currentTab = 0;
}



AdminWindow::~AdminWindow() {}

void AdminWindow::CreateAdminWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	CreateBaseWindow(parentHWnd, windowName, hInstance);

	InitCommonControls();



	this->hInstance = hInstance;



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

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	UpdateCurrentTabPage(currentTab);

}


void AdminWindow::UpdateCurrentTabPage(int selected) {

	currentTab = selected;
	DestroyElementsView();
	

	RECT rect;
	GetClientRect(hWnd, &rect);
	

	switch (selected) {
	case 0:
	{
		DestroyElementsView();

		hWndListViewPost = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		vector<wstring> headers = { L"��� ���������",L"��������" };
		wstring query = L"select ID_Post as '��� ���������', Name_Post as '��������'  from Post";

		DrawTable(hWndListViewPost, headers, query);
		CreateInputFields(hWnd, headers);


		CreateElementsView();

		ShowWindow(hWndListViewPost, SW_SHOW);

		break;
	}
	case 1:
	{

		hWndListViewTypeOfCounterparty = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		vector<wstring> headers = { L"��� ���� �����������", L"��������" };
		wstring query = L"select ID_Type_Of_Counterparty as '��� ���� �����������', Name_Type_Of_Counterparty as '��������'  from TypeOfCounterparty";

		DrawTable(hWndListViewTypeOfCounterparty, headers, query);

		CreateInputFields(hWnd, headers);

		CreateElementsView();

		ShowWindow(hWndListViewTypeOfCounterparty, SW_SHOW);

		break;
	}
	case 2:
	{

		hWndListViewContract = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		vector<wstring> headers = { L"��� ��������", L"����� ��������", L"���� ����������", L"���� ���������", L"������� ��������", L"������ ��������" };
		wstring query = L"select ID_Contract as '��� ��������', Contract_Number as '����� ��������', Start_Date_Contract as '���� ����������',";
		query += L"End_Date_Contract as '���� ���������', Contract_Terms as '������� ��������', Name_Status as '������ ��������'  from Contract_ ";
		query += L"inner join Status_ on Status_ID = Status_.ID_Status";


		DrawTable(hWndListViewContract, headers, query);

		CreateInputFields(hWnd, headers);


		CreateElementsView();

		ShowWindow(hWndListViewContract, SW_SHOW);

		break;
	}
		

	}


	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);

}

void AdminWindow::DrawTable(HWND tableListView, vector<wstring> headers, wstring query) {
	HWND targetListView = tableListView;


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

	if (!hBtnAdd) hBtnAdd = CreateBaseButton(hWnd, L"��������", hInstance, padding, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_ADD));
	if(!hBtnEdit) hBtnEdit = CreateBaseButton(hWnd, L"��������", hInstance, padding + 110, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_EDIT));
	if(!hBtnDelete)	hBtnDelete = CreateBaseButton(hWnd, L"�������", hInstance, padding + 220, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_DELETE));
	if(!hSearchButton)	hSearchButton = CreateBaseButton(hWnd, L"�", hInstance, screenWidth - 150, 100, 30, 30, reinterpret_cast<HMENU>(IDC_SEARCH));
	if(!hFilterButton)	hFilterButton = CreateBaseButton(hWnd, L"�", hInstance, screenWidth - 100, 100, 30, 30, reinterpret_cast<HMENU>(IDC_FILTER));

}



int AdminWindow::GetSelectedRowID(HWND hListView) {
	if (!hListView) return -1;

	int selectedItem = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);

	if (selectedItem == -1) return -1;

	LVITEM item = {};

	item.iItem = selectedItem;
	item.iSubItem = 0;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.pszText = new wchar_t[256];
	item.cchTextMax = 256;

	ListView_GetItem(hListView, &item);

	delete[] item.pszText;

	int id = _wtoi(item.pszText);
	return id;
}

vector<wstring> GetInputValues(HWND* editFields, size_t count) {
	vector<wstring> values;
	for (size_t i = 0; i < count; ++i) {
		int len = GetWindowTextLength(editFields[i]);
		wstring value(len, L'\0');
		GetWindowText(editFields[i], value.data(), len + 1);
		values.push_back(value);
	}
	return values;
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
		MessageBox(hWnd, L"������ ������� ���������", L"�����", MB_OK | MB_ICONERROR);
		UpdateCurrentTabPage(currentTab);
		//�������� �������
	}

}

void AdminWindow::CreateInputFields(HWND parent, const vector<wstring>& headers) {
	DestroyInputFields();
	int x = padding;
	int y = topOffset + padding + listViewHeight - 20;
	int fieldWidth = 200;
	int fieldHeight = 30;
	int spacing = 40;

	editFields.resize(headers.size());

	for (size_t i = 0; i < headers.size(); ++i) {
		editFields[i] = CreateBaseEdit(parent, hInstance, x, y + i * spacing, fieldWidth, fieldHeight);
	}
}

void AdminWindow::DestroyInputFields() {
	for (HWND hWnd : editFields) {
		if (hWnd) DestroyWindow(hWnd);
	}
	editFields.clear();
}

void AdminWindow::UpdateRecord(cwstring tableName, const vector<wstring>& columnNames, const vector<wstring>& values, int id) {

	if (columnNames.size() != values.size()) {
		MessageBox(hWnd, L"���������� ����� �� ���������", L"������", MB_OK | MB_ICONERROR);
		return;
	}

	wstring sql = L"update " + tableName + L" set";
	for (size_t i = 0; i < columnNames.size(); ++i) {
		sql += columnNames[i] + L" = N'" + values[i] + L"'";
		if (i != columnNames.size() - 1) sql += L", ";
	}

	sql += L" where ID_" + tableName + L" = " + to_wstring(id);


	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"������ ������� ���������", L"�����", MB_OK | MB_ICONERROR);
		UpdateCurrentTabPage(currentTab);
		//�������� �������
	}

}

//������� ���������� �������� ���� ���
void AdminWindow::DeleteRecord(cwstring tableName, int id) {
	wstring sql = L"delete from " + tableName + L" Where ID_" + tableName + L" = " + to_wstring(id);
	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"������ ������� �������", L"�����", MB_OK | MB_ICONERROR);
		UpdateCurrentTabPage(currentTab);
		//����������� ������ ������ ���� ���;
	}
}


void AdminWindow::hWndForDestroy(HWND hWndElement) {
	if (hWndElement) {
		DestroyWindow(hWndElement);
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
	hWndForDestroy(hEditName);
	hWndForDestroy(hFilterButton);
	hWndForDestroy(hSearchButton);
}

