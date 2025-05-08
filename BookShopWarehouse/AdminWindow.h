#pragma once
#include <windows.h>
#include <string>
#include <commctrl.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"


class AdminWindow : public BaseWindow
{
public:
	AdminWindow(DatabaseManager& dbManager);
	~AdminWindow();

	void CreateAdminWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);
	void DrawTablePost();
	void DrawTableTypeOfCounterparty();


	void UpdateCurrentTabPage(int selected) override;

	HWND GetHandleListView() const { return hWndListView; }

protected:
	HWND hWndListViewPost;
	HWND hWndListViewTypeOfCounterparty;

	HWND hTabPagePost;
	HWND hTabPageTypeOfCounterparty;

	HINSTANCE hInstance;


	DatabaseManager& dbManager;
	HWND hTabCtrl;

	HWND hBtnAddPost;
	HWND hBtnEditPost;
	HWND hBtnDeletePost;
	HWND hEditNamePost;
	HWND hFilterButtonPost;
	HWND hSearchButtonPost;

	HWND hBtnAddTypeOfCounterparty;
	HWND hBtnEditTypeOfCounterparty;
	HWND hBtnDeleteTypeOfCounterparty;
	HWND hEditNameTypeOfCounterparty;
	HWND hFilterButtonTypeOfCounterparty;
	HWND hSearchButtonTypeOfCounterparty;
};

