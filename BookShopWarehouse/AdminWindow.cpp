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

	hBtnTabPost = CreateBaseButton(hWnd, L"���������", hInstance, 10, 10, 120, 30, reinterpret_cast<HMENU>(IDC_TAB_POST));

	hBtnTabTypeOfCounterparty = CreateBaseButton(hWnd, L"��� �����������", hInstance, 140, 10, 150, 30, reinterpret_cast<HMENU>(IDC_TAB_TYPE_OF_COUNTERPARTY));

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	UpdateCurrentTabPage(currentTab);

}


void AdminWindow::UpdateCurrentTabPage(int selected) {

	currentTab = selected;

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

	RECT rect;
	GetClientRect(hWnd, &rect);
	int topOffset = 50;
	int padding = 10;
	int listViewHeight = screenHeight / 2 - topOffset - 60;
	int listViewWidth = screenWidth - 2 * padding;

	switch (selected) {
	case 0:
	{
		hWndListViewPost = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		DrawTablePost();
		hEditName = CreateBaseEdit(hWnd, hInstance, padding, topOffset + padding + listViewHeight + 10, 200, 25);

		hBtnAdd = CreateBaseButton(hWnd, L"��������", hInstance, padding, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_ADD));
		hBtnEdit = CreateBaseButton(hWnd, L"��������", hInstance, padding + 110, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_EDIT));
		hBtnDelete = CreateBaseButton(hWnd, L"�������", hInstance, padding + 220, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_DELETE));
		hSearchButton = CreateBaseButton(hWnd, L"�", hInstance, screenWidth - 150, 100, 30, 30, reinterpret_cast<HMENU>(IDC_SEARCH));
		hFilterButton = CreateBaseButton(hWnd, L"�", hInstance, screenWidth - 100, 100, 30, 30, reinterpret_cast<HMENU>(IDC_FILTER));

		ShowWindow(hWndListViewPost, SW_SHOW);

		break;
	}
	case 1:
	{

		hWndListViewTypeOfCounterparty = CreateBaseListView(hWnd, hInstance, padding, topOffset, 0, 0);

		DrawTableTypeOfCounterparty();

		hEditName = CreateBaseEdit(hWnd, hInstance, padding, topOffset + padding + listViewHeight + 10, 200, 25);

		hBtnAdd = CreateBaseButton(hWnd, L"��������", hInstance, padding, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_ADD));
		hBtnEdit = CreateBaseButton(hWnd, L"��������", hInstance, padding + 110, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_EDIT));
		hBtnDelete = CreateBaseButton(hWnd, L"�������", hInstance, padding + 220, topOffset + listViewHeight + 40, 100, 30, reinterpret_cast<HMENU>(IDC_DELETE));

		hSearchButton = CreateBaseButton(hWnd, L"�", hInstance, screenWidth - 150, 100, 30, 30, reinterpret_cast<HMENU>(IDC_SEARCH));
		hFilterButton = CreateBaseButton(hWnd, L"�", hInstance, screenWidth - 100, 100, 30, 30, reinterpret_cast<HMENU>(IDC_FILTER));

		ShowWindow(hWndListViewTypeOfCounterparty, SW_SHOW);

		break;
	}

	}


	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);

}




void AdminWindow::DrawTablePost() {

	HWND targetListView = hWndListViewPost;

	if (!targetListView) {
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

	BaseTable::ClearListView(targetListView);
	BaseTable::SetHeaders(targetListView, headers);
	BaseTable::SetData(targetListView, tableData);
	BaseTable::AutoResizeColumns(targetListView, headers, tableData);
	BaseTable::ResizeListViewToFit(targetListView, static_cast<int>(tableData.size()));

}

void AdminWindow::DrawTableTypeOfCounterparty() {

	HWND targetListView = hWndListViewTypeOfCounterparty;


	if (!targetListView) {
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

	BaseTable::ClearListView(targetListView);
	BaseTable::SetHeaders(targetListView, headers);
	BaseTable::SetData(targetListView, tableData);
	BaseTable::AutoResizeColumns(targetListView, headers, tableData);
	BaseTable::ResizeListViewToFit(targetListView, static_cast<int>(tableData.size()));

}