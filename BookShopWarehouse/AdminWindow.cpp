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

	hBtnTabPost = CreateBaseButton(hWnd, L"Должность", hInstance, 10, 10, 120, 30, reinterpret_cast<HMENU>(IDC_TAB_POST));
	hBtnTabTypeOfCounterparty = CreateBaseButton(hWnd, L"Тип контрагента", hInstance, 140, 10, 150, 30, reinterpret_cast<HMENU>(IDC_TAB_TYPE_OF_COUNTERPARTY));
	hBtnTabViewContract = CreateBaseButton(hWnd, L"Контракт", hInstance, 300, 10, 150, 30, reinterpret_cast<HMENU>(IDC_TAB_CONTRACT));


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
		hWndListViewPost = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		vector<wstring> headers = { L"Код должности",L"Название" };
		wstring query = L"select ID_Post as 'Код должности', Name_Post as 'Название'  from Post";

		DrawTable(hWndListViewPost, headers, query);

		hEditName = CreateBaseEdit(hWnd, hInstance, padding, topOffset + padding + listViewHeight - 20, 400, 30);

		CreateElementsView();

		ShowWindow(hWndListViewPost, SW_SHOW);

		break;
	}
	case 1:
	{

		hWndListViewTypeOfCounterparty = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		vector<wstring> headers = { L"Код типа контрагента", L"Название" };
		wstring query = L"select ID_Type_Of_Counterparty as 'Код типа контрагента', Name_Type_Of_Counterparty as 'Название'  from TypeOfCounterparty";

		DrawTable(hWndListViewTypeOfCounterparty, headers, query);

		hEditName = CreateBaseEdit(hWnd, hInstance, padding, topOffset + padding + listViewHeight - 20, 200, 25);

		CreateElementsView();

		ShowWindow(hWndListViewTypeOfCounterparty, SW_SHOW);

		break;
	}
	case 2:
	{
		hWndListViewContract = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);
		vector<wstring> headers = { L"Код договора", L"Номер договора", L"Дата заключения", L"Дата окончания", L"Условия договора", L"Статус договора" };
		wstring query = L"select ID_Contract as 'Код договора', Contract_Number as 'Номер договора', Start_Date_Contract as 'Дата заключения',";
		query += L"End_Date_Contract as 'Дата окончания', Contract_Terms as 'Условия договора', Name_Status as 'Статус договора'  from Contract_ ";
		query += L"inner join Status_ on Status_ID = Status_.ID_Status";


		DrawTable(hWndListViewContract, headers, query);

		hEditName = CreateBaseEdit(hWnd, hInstance, padding, topOffset + padding + listViewHeight - 20, 200, 25);


		CreateElementsView();

		ShowWindow(hWndListViewContract, SW_SHOW);
	}
		

	}


	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);

}

void AdminWindow::DrawTable(HWND tableListView, vector<wstring> headers, wstring query) {
	HWND targetListView = tableListView;


	if (!targetListView) {
		MessageBox(NULL, L"Список еще не создан", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"Нет данных для отображения", L"Ошибка", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"Несоответствие заголовков и данных", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	BaseTable::ClearListView(targetListView);
	BaseTable::SetHeaders(targetListView, headers);
	BaseTable::SetData(targetListView, tableData);
	BaseTable::AutoResizeColumns(targetListView, headers, tableData);
	BaseTable::ResizeListViewToFit(targetListView, static_cast<int>(tableData.size()));

}


void AdminWindow::CreateElementsView() {
	hBtnAdd = CreateBaseButton(hWnd, L"Добавить", hInstance, padding, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_ADD));
	hBtnEdit = CreateBaseButton(hWnd, L"Изменить", hInstance, padding + 110, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_EDIT));
	hBtnDelete = CreateBaseButton(hWnd, L"Удалить", hInstance, padding + 220, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_DELETE));

	hSearchButton = CreateBaseButton(hWnd, L"П", hInstance, screenWidth - 150, 100, 30, 30, reinterpret_cast<HMENU>(IDC_SEARCH));
	hFilterButton = CreateBaseButton(hWnd, L"Ф", hInstance, screenWidth - 100, 100, 30, 30, reinterpret_cast<HMENU>(IDC_FILTER));
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

bool AdminWindow::ExecuteSQL(LPCWSTR sql) {
	try {
		dbManager.ExecuteQuery(sql);
		return true;
	}
	catch (...) {
		MessageBox(hWnd, L"Ошибка выполнения SQL",L"Ошибка", MB_OK | MB_ICONERROR);
		return false;
	}
}

void AdminWindow::AddRecord(cwstring tableName, const vector<wstring>& columnNames, const vector<wstring>& values) {

	if (columnNames.size() != values.size()) {
		MessageBox(hWnd, L"Количество полей не совпадает", L"Ошибка", MB_OK | MB_ICONERROR);
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
		MessageBox(hWnd, L"Запись успешно добавлена", L"Успех", MB_OK | MB_ICONERROR);
		UpdateCurrentTabPage(currentTab);
		//обновить таблицу
	}

}

void AdminWindow::UpdateRecord(cwstring tableName, const vector<wstring>& columnNames, const vector<wstring>& values, int id) {

	if (columnNames.size() != values.size()) {
		MessageBox(hWnd, L"Количество полей не совпадает", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	wstring sql = L"update " + tableName + L" set";
	for (size_t i = 0; i < columnNames.size(); ++i) {
		sql += columnNames[i] + L" = N'" + values[i] + L"'";
		if (i != columnNames.size() - 1) sql += L", ";
	}

	sql += L" where ID_" + tableName + L" = " + to_wstring(id);


	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"Запись успешно обновлена", L"Успех", MB_OK | MB_ICONERROR);
		UpdateCurrentTabPage(currentTab);
		//обновить таблицу
	}

}

//Добавлю логическое удаление пока так
void AdminWindow::DeleteRecord(cwstring tableName, int id) {
	wstring sql = L"delete from " + tableName + L"Where ID_" + tableName + L" = " + to_wstring(id);
	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"Запись успешно удалена", L"Успех", MB_OK | MB_ICONERROR);
		UpdateCurrentTabPage(currentTab);
		//перерисовку метода добавь если что;
	}
}

void AdminWindow::DestroyElementsView() {
	if (hWndListViewPost) {
		DestroyWindow(hWndListViewPost);
		hWndListViewPost = nullptr;
	}
	if (hWndListViewTypeOfCounterparty) {
		DestroyWindow(hWndListViewTypeOfCounterparty);
		hWndListViewTypeOfCounterparty = nullptr;
	}
	if (hBtnAdd) {
		DestroyWindow(hBtnAdd);
		hBtnAdd = nullptr;
	}
	if (hBtnDelete) {
		DestroyWindow(hBtnDelete);
		hBtnDelete = nullptr;
	}
	if (hEditName) {
		DestroyWindow(hEditName);
		hEditName = nullptr;
	}
	if (hFilterButton) {
		DestroyWindow(hFilterButton);
		hFilterButton = nullptr;
	}
	if (hSearchButton) {
		DestroyWindow(hSearchButton);
		hSearchButton = nullptr;
	}
	if (hBtnEdit) {
		DestroyWindow(hBtnEdit);
		hBtnEdit = nullptr;
	}
}