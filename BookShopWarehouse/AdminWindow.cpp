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
	
	int editTop = topOffset + listViewHeight + padding;

	switch (selected) {
	case 0:
	{

		hWndListViewPost = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		
		DrawTable(hWndListViewPost, Queries[0]);
		hEditIdPost = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditNamePost = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 80, screenWidth / 2, 50);

		CreateElementsView();

		ShowWindow(hWndListViewPost, SW_SHOW);

		break;
	}
	case 1:
	{

		hWndListViewTypeOfCounterparty = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewTypeOfCounterparty, Queries[1]);

		hEditIdTypeOfCounterparty = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditNameTypeOfCounterparty = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 80, screenWidth / 2, 50);

		CreateElementsView();

		ShowWindow(hWndListViewTypeOfCounterparty, SW_SHOW);

		break;
	}
	case 2:
	{

		hWndListViewContract = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		DrawTable(hWndListViewContract, Queries[2]);

		CreateElementsView();

		hEditIdContract = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);
		hEditContractNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hDPStartDateContract = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50);
		hDPEndDateContract = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 2, 50);
		hEditContractTerms = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50);
		hComboBoxStatus = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 300, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_STATUS));
		
		FillComboBox(hComboBoxStatus, L"select ID_Status, Name_Status from Status_", dbManager, comboBoxIdMap);

		ShowWindow(hWndListViewContract, SW_SHOW);


		break;
	}
	case 3:
	{

		hWndListViewCounterparty = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewCounterparty, Queries[3]);
		
		CreateElementsView();

		hEditIdContract = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 , screenWidth / 2, 50);
		hEditContractNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hDPStartDateContract = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 80, screenWidth / 2, 50);
		hDPEndDateContract = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 140, screenWidth / 2, 50);
		hEditContractTerms = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 200, screenWidth / 2, 50);
		hComboBoxStatus = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 260, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_STATUS));

		FillComboBox(hComboBoxStatus, L"select ID_Status, Name_Status from Status_", dbManager, comboBoxIdMap);

		ShowWindow(hWndListViewCounterparty, SW_SHOW);

		break;
	}
	case 4:
	{

		hWndListViewDelivery = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewDelivery, Queries[4]);

		CreateElementsView();

		hEditDeliveryNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdDelivery = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 80, screenWidth / 2, 50);
		hDPDeliveryDate = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hComboBoxWarehouse = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_WAREHOUSE));
		hComboBoxDeliveryNote = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_DELIVERY_NOTE));
		hComboBoxStatusDelivery = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_STATUS_DELIVERY));


		ShowWindow(hWndListViewDelivery, SW_SHOW);

		break;
	}
	case 5:
	{

		hWndListViewDeliveryNote = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		DrawTable(hWndListViewDeliveryNote, Queries[5]);

		CreateElementsView();

		hEditDeliveryNoteNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdDeliveryNote = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hDPDateOfFormation = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hComboBoxContract = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_CONTRACT));


		ShowWindow(hWndListViewDeliveryNote, SW_SHOW);

		break;
	}
	case 6:
	{

		hWndListViewDeliveryPosition = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewDeliveryPosition, Queries[6]);

		CreateElementsView();

		hEditIdDeliveryPosition = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50); // ID
		hComboBoxRequisitionPosition = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_REQUISITION_POSITION));
		hComboBoxDeliveryDLPosition = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_DELIVERY));


		ShowWindow(hWndListViewDeliveryPosition, SW_SHOW);

		break;
	}
	case 7:
	{

		hWndListViewEmployee = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewEmployee, Queries[7]);
		
		CreateElementsView();

		hEditSurname = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditName = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditPatronymic = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdEmployee = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditEmail = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditLogin = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditPassword = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditSalt = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hComboBoxPost = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_POST));


		ShowWindow(hWndListViewEmployee, SW_SHOW);

		break;
	}
	case 8:
	{

		hWndListViewProduct = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		DrawTable(hWndListViewProduct, Queries[8]);

		CreateElementsView();

		hEditNameProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditPurchasePrice = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditSellingPrice = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditArticle = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditQuantityOfProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hDPDateOfReceipt = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50); 
		hComboBoxCounterpartyProduct = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_COUNTERPARTY));
		hComboBoxTypeOfProduct = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_TYPE_OF_PRODUCT));


		ShowWindow(hWndListViewProduct, SW_SHOW);

		break;
	}
	case 9:
	{

		hWndListViewProductOrderRequest = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewProductOrderRequest, Queries[9]);
		
		CreateElementsView();

		hEditRequestNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdProductOrderRequest = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hDPDateOfCreation = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hComboBoxEmployee = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_EMPLOYEE));
		hEditCommentary = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hComboBoxCounterparty = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_COUNTERPARTY));


		ShowWindow(hWndListViewProductOrderRequest, SW_SHOW);

		break;
	}
	case 10:
	{

		hWndListViewRequisitionPosition = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewRequisitionPosition, Queries[10]);

		CreateElementsView();

		hEditPositionNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdRequisitionPosition = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hComboBoxProduct = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_PRODUCT));
		hComboBoxProductOrderRequest = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_PRODUCT_ORDER_REQUEST));
		hEditQuantityOfProductInRequisition = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditUnitPrice = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);


		ShowWindow(hWndListViewRequisitionPosition, SW_SHOW);

		break;
	}
	case 11:
	{

		hWndListViewStatus = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		DrawTable(hWndListViewStatus, Queries[11]);


		CreateElementsView();

		hEditStatus = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdStatus = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);


		ShowWindow(hWndListViewStatus, SW_SHOW);

		break;
	}
	case 12:
	{

		hWndListViewTypeOfProduct = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewTypeOfProduct, Queries[12]);
		
		CreateElementsView();

		hEditNameTypeOfProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdTypeOfProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);


		ShowWindow(hWndListViewTypeOfProduct, SW_SHOW);

		break;
	}
	case 13:
	{

		hWndListViewWarehouse = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);


		DrawTable(hWndListViewWarehouse, Queries[13]);


		hEditWarehouseNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditWarehouseAddress = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditIdWarehouse = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditWarehouseCapacity = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditCurrentWarehouseLoad = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);


		CreateElementsView();

		ShowWindow(hWndListViewWarehouse, SW_SHOW);

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

	hWndForDestroy(hEditIdTypeOfCounterparty);
	hWndForDestroy(hEditNameTypeOfCounterparty);

	hWndForDestroy(hEditIdTypeOfProduct);
	hWndForDestroy(hEditNameTypeOfProduct);

	hWndForDestroy(hEditIdStatus);
	hWndForDestroy(hEditStatus);

	hWndForDestroy(hEditIdWarehouse);
	hWndForDestroy(hEditWarehouseNumber);
	hWndForDestroy(hEditWarehouseAddress);
	hWndForDestroy(hEditWarehouseCapacity);
	hWndForDestroy(hEditCurrentWarehouseLoad);

	hWndForDestroy(hEditIdContract);
	hWndForDestroy(hEditContractNumber);
	hWndForDestroy(hDPStartDateContract);
	hWndForDestroy(hDPEndDateContract);
	hWndForDestroy(hEditContractTerms);
	hWndForDestroy(hComboBoxStatus);

	hWndForDestroy(hEditIdDeliveryNote);
	hWndForDestroy(hEditDeliveryNoteNumber);
	hWndForDestroy(hDPDateOfFormation);
	hWndForDestroy(hComboBoxContract);

	hWndForDestroy(hEditIdDelivery);
	hWndForDestroy(hEditDeliveryNumber);
	hWndForDestroy(hDPDeliveryDate);
	hWndForDestroy(hComboBoxWarehouse);
	hWndForDestroy(hComboBoxDeliveryNote);
	hWndForDestroy(hComboBoxStatusDelivery);

	hWndForDestroy(hEditIdEmployee);
	hWndForDestroy(hEditSurname);
	hWndForDestroy(hEditName);
	hWndForDestroy(hEditPatronymic);
	hWndForDestroy(hEditEmail);
	hWndForDestroy(hEditLogin);
	hWndForDestroy(hEditPassword);
	hWndForDestroy(hComboBoxPost);
	hWndForDestroy(hEditSalt);

	hWndForDestroy(hEditIdCounterparty);
	hWndForDestroy(hEditNameCounterparty);
	hWndForDestroy(hEditPhoneCounterparty);
	hWndForDestroy(hEditEmailCounterparty);
	hWndForDestroy(hEditContactPerson);
	hWndForDestroy(hEditTermsOfCooperation);
	hWndForDestroy(hEditCountry);
	hWndForDestroy(hEditCity);
	hWndForDestroy(hComboBoxTypeOfCounterparty);

	hWndForDestroy(hEditIdProductOrderRequest);
	hWndForDestroy(hEditRequestNumber);
	hWndForDestroy(hDPDateOfCreation);
	hWndForDestroy(hComboBoxEmployee);
	hWndForDestroy(hEditCommentary);
	hWndForDestroy(hComboBoxCounterparty);

	hWndForDestroy(hEditIdProduct);
	hWndForDestroy(hEditNameProduct);
	hWndForDestroy(hEditPurchasePrice);
	hWndForDestroy(hEditSellingPrice);
	hWndForDestroy(hEditArticle);
	hWndForDestroy(hEditQuantityOfProduct);
	hWndForDestroy(hDPDateOfReceipt);
	hWndForDestroy(hComboBoxCounterpartyProduct);
	hWndForDestroy(hComboBoxTypeOfProduct);

	hWndForDestroy(hEditIdRequisitionPosition);
	hWndForDestroy(hEditPositionNumber);
	hWndForDestroy(hComboBoxProduct);
	hWndForDestroy(hComboBoxProductOrderRequest);
	hWndForDestroy(hEditQuantityOfProductInRequisition);
	hWndForDestroy(hEditUnitPrice);

	hWndForDestroy(hEditIdDeliveryPosition);
	hWndForDestroy(hComboBoxRequisitionPosition);
	hWndForDestroy(hComboBoxDeliveryDLPosition);

}

wstring AdminWindow::GetWindowTextAsWstring(HWND hWndEdit) {
	int length = GetWindowTextLength(hWndEdit);
	std::vector<wchar_t> buffer(length + 1);  // +1 ��� ����� �������� �������
	GetWindowText(hWndEdit, &buffer[0], length + 1);

	return std::wstring(&buffer[0]);
}


void AdminWindow::CreateTabButton() {

	RECT rc;
	GetClientRect(hWnd, &rc);
	int totalWidth = rc.right - rc.left;

	const int buttonsPerRow = 7;
	int buttonWidth = totalWidth / buttonsPerRow;

	int topOffset1 = 10;
	int topOffset2 = 70;

	hBtnTabPost = CreateBaseButton(hWnd, L"���������", hInstance, buttonWidth * 0, topOffset1, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_POST));
	hBtnTabTypeOfCounterparty = CreateBaseButton(hWnd, L"��� �����������", hInstance, buttonWidth * 1, topOffset1, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_TYPE_OF_COUNTERPARTY));
	hBtnTabViewContract = CreateBaseButton(hWnd, L"��������", hInstance, buttonWidth * 2, topOffset1, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_CONTRACT));
	hBtnTabViewCounterparty = CreateBaseButton(hWnd, L"����������", hInstance, buttonWidth * 3, topOffset1, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_COUNTERPARTY));
	hBtnTabViewDelivery = CreateBaseButton(hWnd, L"��������", hInstance, buttonWidth * 4, topOffset1, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_DELIVERY));
	hBtnTabViewDeliveryNote = CreateBaseButton(hWnd, L"���������", hInstance, buttonWidth * 5, topOffset1, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_DELIVERY_NOTE));
	hBtnTabViewDeliveryPosition = CreateBaseButton(hWnd, L"������� ��������", hInstance, buttonWidth * 6, topOffset1, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_DELIVERY_POSITION));
	hBtnTabViewEmployee = CreateBaseButton(hWnd, L"���������", hInstance, buttonWidth * 0, topOffset2, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_EMPLOYEE));
	hBtnTabViewProduct = CreateBaseButton(hWnd, L"�����", hInstance, buttonWidth * 1, topOffset2, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_PRODUCT));
	hBtnTabViewProductOrderRequest = CreateBaseButton(hWnd, L"������ �� �����", hInstance, buttonWidth * 2, topOffset2, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_PRODUCT_ORDER_REQUEST));
	hBtnTabViewRequisitionPosition = CreateBaseButton(hWnd, L"������� ������", hInstance, buttonWidth * 3, topOffset2, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_REQUISITION_POSITION));
	hBtnTabViewStatus = CreateBaseButton(hWnd, L"������", hInstance, buttonWidth * 4, topOffset2, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_STATUS));
	hBtnTabViewTypeOfProduct = CreateBaseButton(hWnd, L"��� ������", hInstance, buttonWidth * 5, topOffset2, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_TYPE_OF_PRODUCT));
	hBtnTabViewWarehouse = CreateBaseButton(hWnd, L"�����", hInstance, buttonWidth * 6, topOffset2, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_WAREHOUSE));

}

void AdminWindow::FillComboBox(HWND hComboBox, const wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) {
	SendMessage(hComboBox, CB_RESETCONTENT, 0, 0);

	idMap.clear();

	auto data = dbManager.ExecuteQuery(query);

	wprintf(L"�������� �����: %zu\n", data.size());

	for (const auto& row : data) {
		if (row.size() >= 2) {
			int id = stoi(row[0]);
			const wstring& name = row[1];

			SendMessage(hComboBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(name.c_str()));

			idMap.push_back(id);
		}
	}

	if (!data.empty()) {
		SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
	}
}

