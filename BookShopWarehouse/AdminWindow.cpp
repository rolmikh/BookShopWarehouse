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
	
	AddTabPage(hTabCtrl, L"���������");
	hTabPagePost = CreateTabPage(hTabCtrl, 4, tabHeight + 4, listViewWidth, listViewHeight);

	AddTabPage(hTabCtrl, L"��� �����������");
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

		CreateBaseButton(hTabCtrl, L"��������", hInstance, padding, tabHeight + padding + listViewHeight + 40, 100, 30);
		CreateBaseButton(hTabCtrl, L"��������", hInstance, padding + 110, tabHeight + padding + listViewHeight + 40, 100, 30);
		CreateBaseButton(hTabCtrl, L"�������", hInstance, padding + 220, tabHeight + padding + listViewHeight + 40, 100, 30);

		hSearchButtonPost = CreateBaseButton(hTabCtrl, L"�", hInstance, screenWidth - 150, 100, 30, 30);
		hFilterButtonPost = CreateBaseButton(hTabCtrl, L"�", hInstance, screenWidth - 100, 100, 30, 30);

		
		break;
	}
	case 1:
	{
		ShowWindow(hTabPageTypeOfCounterparty, SW_SHOW);
		ShowWindow(hTabPagePost, SW_HIDE);
		

		hWndListViewTypeOfCounterparty = CreateBaseListView(hTabPageTypeOfCounterparty, hInstance, padding, tabHeight + padding, listViewWidth, listViewHeight);

		DrawTableTypeOfCounterparty();

		hEditNameTypeOfCounterparty = CreateBaseEdit(hTabCtrl, hInstance, padding, tabHeight + padding + listViewHeight + 10, 200, 25);

		CreateBaseButton(hTabCtrl, L"��������", hInstance, padding, tabHeight + padding + listViewHeight + 40, 100, 30);
		CreateBaseButton(hTabCtrl, L"��������", hInstance, padding + 110, tabHeight + padding + listViewHeight + 40, 100, 30);
		CreateBaseButton(hTabCtrl, L"�������", hInstance, padding + 220, tabHeight + padding + listViewHeight + 40, 100, 30);

		hSearchButtonTypeOfCounterparty = CreateBaseButton(hTabCtrl, L"�", hInstance, screenWidth - 150, 100, 30, 30);
		hFilterButtonTypeOfCounterparty = CreateBaseButton(hTabCtrl, L"�", hInstance, screenWidth - 100, 100, 30, 30);

		break;
	}
		
	}

}




void AdminWindow::DrawTablePost() {

	if (!hWndListViewPost) {
		MessageBox(NULL, L"������ ��� �� ������", L"������", MB_OK | MB_ICONERROR);
		return;
	}

	vector<wstring> headers = { L"��� ���������",L"��������" };
	wstring query = L"select ID_Post as '��� ���������', Name_Post as '��������'  from Post";
	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"��� ������ ��� �����������", L"������", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"�������������� ���������� � ������", L"������", MB_OK | MB_ICONERROR);
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
		MessageBox(NULL, L"������ ��� �� ������", L"������", MB_OK | MB_ICONERROR);
		return;
	}

	vector<wstring> headers = { L"��� ���� �����������", L"��������" };
	wstring query = L"select ID_Type_Of_Counterparty as '��� ���� �����������', Name_Type_Of_Counterparty as '��������'  from TypeOfCounterparty";
	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"��� ������ ��� �����������", L"������", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"�������������� ���������� � ������", L"������", MB_OK | MB_ICONERROR);
		return;
	}

	BaseTable::ClearListView(hWndListViewTypeOfCounterparty);
	BaseTable::SetHeaders(hWndListViewTypeOfCounterparty, headers);
	BaseTable::SetData(hWndListViewTypeOfCounterparty, tableData);
	BaseTable::AutoResizeColumns(hWndListViewTypeOfCounterparty, headers, tableData);
	BaseTable::ResizeListViewToFit(hWndListViewTypeOfCounterparty, static_cast<int>(tableData.size()));

}




