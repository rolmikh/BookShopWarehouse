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
	void DrawTable();
	HWND GetHandleListView() const { return hWndListView; }

protected:
	HWND hWndListView;
	DatabaseManager& dbManager;
};

