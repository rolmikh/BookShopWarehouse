#pragma once
#include <windows.h>
#include <string>
#include <commctrl.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"


class AdminWindow : public BaseWindow
{
public:

	static const int IDC_TAB_POST = 1001;
	static const int IDC_TAB_TYPE_OF_COUNTERPARTY = 1002;
	static const int IDC_ADD = 1003;
	static const int IDC_EDIT = 1004;
	static const int IDC_DELETE = 1005;
	static const int IDC_FILTER = 1006;
	static const int IDC_SEARCH = 1007;

	AdminWindow(DatabaseManager& dbManager);
	~AdminWindow();

	void CreateAdminWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);
	void DrawTablePost();
	void DrawTableTypeOfCounterparty();


	void UpdateCurrentTabPage(int selected) override;

	HWND GetHandleListView() const { return hWndListView; }

	HWND hBtnTabPost;
	HWND hBtnTabTypeOfCounterparty;
	int currentTab = 0;

protected:
	HWND hWndListViewPost;
	HWND hWndListViewTypeOfCounterparty;

	HINSTANCE hInstance;

	DatabaseManager& dbManager;

	

	HWND hBtnAdd;
	HWND hBtnEdit;
	HWND hBtnDelete;
	HWND hEditName;
	HWND hFilterButton;
	HWND hSearchButton;

};

