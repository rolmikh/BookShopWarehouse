#include "AdminWindow.h"
#include <commctrl.h>
#include "BaseTable.h"
#include <string>

using namespace std;

AdminWindow::AdminWindow(DatabaseManager& dbManager) : dbManager(dbManager) {
	hWnd = nullptr;
	hWndListViewPost = nullptr;
	hWndListViewTypeOfCounterparty = nullptr;
	hTabCtrl = nullptr;
	
}

int tabHeight = 0;
int listViewWidth = 0;
int listViewHeight = 0;
int padding = 0;

AdminWindow::~AdminWindow() {}

void AdminWindow::CreateAdminWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	CreateBaseWindow(parentHWnd, windowName, hInstance);

	RECT rect;
	GetClientRect(hTabCtrl, &rect);
	MapWindowPoints(hTabCtrl, hWnd, (LPPOINT)&rect, 2);

	


	InitCommonControls();

	hTabCtrl = CreateBaseTabControl(hWnd, hInstance);
	this->hInstance = hInstance;

	tabHeight = 30;
	padding = 10;
	listViewWidth = rect.right - rect.left - 2 * padding;
	listViewHeight = rect.bottom - rect.top - tabHeight - 150;
	
	listViewHeight = screenHeight / 2 - tabHeight - 60;
	
	AddTabPage(hTabCtrl, L"Должность");
	hTabPagePost = CreateTabPage(hTabCtrl, 4, tabHeight + 4, listViewWidth, listViewHeight);

	AddTabPage(hTabCtrl, L"Тип контрагента");
	hTabPageTypeOfCounterparty = CreateTabPage(hTabCtrl, 4, tabHeight + 4, listViewWidth, listViewHeight);

	
	UpdateCurrentTabPage(0);

}


void AdminWindow::UpdateCurrentTabPage(int selected) {

	if (hWndListViewPost) {
		DestroyWindow(hWndListViewPost);
		hWndListViewPost = nullptr;
	}
	if (hWndListViewTypeOfCounterparty) {
		DestroyWindow(hWndListViewTypeOfCounterparty);
		hWndListViewTypeOfCounterparty = nullptr;
	}

	
	switch (selected) {
	case 0:
	{

		ShowWindow(hTabPagePost, SW_SHOW);
		ShowWindow(hTabPageTypeOfCounterparty, SW_HIDE);

		hWndListViewPost = CreateBaseListView(hTabPagePost, hInstance, padding, tabHeight + padding, listViewWidth, listViewHeight);
		

		DrawTablePost();

		hEditNamePost = CreateBaseEdit(hTabCtrl, hInstance, padding, tabHeight + padding + listViewHeight + 10, 200, 25);

		CreateBaseButton(hTabCtrl, L"Добавить", hInstance, padding, tabHeight + padding + listViewHeight + 40, 100, 30);
		CreateBaseButton(hTabCtrl, L"Изменить", hInstance, padding + 110, tabHeight + padding + listViewHeight + 40, 100, 30);
		CreateBaseButton(hTabCtrl, L"Удалить", hInstance, padding + 220, tabHeight + padding + listViewHeight + 40, 100, 30);

		hSearchButtonPost = CreateBaseButton(hTabCtrl, L"П", hInstance, screenWidth - 150, 100, 30, 30);
		hFilterButtonPost = CreateBaseButton(hTabCtrl, L"Ф", hInstance, screenWidth - 100, 100, 30, 30);

		
		break;
	}
	case 1:
	{
		ShowWindow(hTabPageTypeOfCounterparty, SW_SHOW);
		ShowWindow(hTabPagePost, SW_HIDE);
		

		hWndListViewTypeOfCounterparty = CreateBaseListView(hTabPageTypeOfCounterparty, hInstance, padding, tabHeight + padding, listViewWidth, listViewHeight);

		DrawTableTypeOfCounterparty();

		hEditNameTypeOfCounterparty = CreateBaseEdit(hTabCtrl, hInstance, padding, tabHeight + padding + listViewHeight + 10, 200, 25);

		CreateBaseButton(hTabCtrl, L"Добавить", hInstance, padding, tabHeight + padding + listViewHeight + 40, 100, 30);
		CreateBaseButton(hTabCtrl, L"Изменить", hInstance, padding + 110, tabHeight + padding + listViewHeight + 40, 100, 30);
		CreateBaseButton(hTabCtrl, L"Удалить", hInstance, padding + 220, tabHeight + padding + listViewHeight + 40, 100, 30);

		hSearchButtonTypeOfCounterparty = CreateBaseButton(hTabCtrl, L"П", hInstance, screenWidth - 150, 100, 30, 30);
		hFilterButtonTypeOfCounterparty = CreateBaseButton(hTabCtrl, L"Ф", hInstance, screenWidth - 100, 100, 30, 30);

		break;
	}
		
	}

}




void AdminWindow::DrawTablePost() {

	if (!hWndListViewPost) {
		MessageBox(NULL, L"Список еще не создан", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	vector<wstring> headers = { L"Код должности",L"Название" };
	wstring query = L"select ID_Post as 'Код должности', Name_Post as 'Название'  from Post";
	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"Нет данных для отображения", L"Ошибка", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"Несоответствие заголовков и данных", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	BaseTable::ClearListView(hWndListViewPost);
	BaseTable::SetHeaders(hWndListViewPost, headers);
	BaseTable::SetData(hWndListViewPost, tableData);
	BaseTable::AutoResizeColumns(hWndListViewPost, headers, tableData);
	BaseTable::ResizeListViewToFit(hWndListViewPost, static_cast<int>(tableData.size()));

}

void AdminWindow::DrawTableTypeOfCounterparty() {

	if (!hWndListViewTypeOfCounterparty) {
		MessageBox(NULL, L"Список еще не создан", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	vector<wstring> headers = { L"Код типа контрагента", L"Название" };
	wstring query = L"select ID_Type_Of_Counterparty as 'Код типа контрагента', Name_Type_Of_Counterparty as 'Название'  from TypeOfCounterparty";
	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"Нет данных для отображения", L"Ошибка", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"Несоответствие заголовков и данных", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	BaseTable::ClearListView(hWndListViewTypeOfCounterparty);
	BaseTable::SetHeaders(hWndListViewTypeOfCounterparty, headers);
	BaseTable::SetData(hWndListViewTypeOfCounterparty, tableData);
	BaseTable::AutoResizeColumns(hWndListViewTypeOfCounterparty, headers, tableData);
	BaseTable::ResizeListViewToFit(hWndListViewTypeOfCounterparty, static_cast<int>(tableData.size()));

}




