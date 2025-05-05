#pragma once
#include <windows.h>
#include <string>
#include <commctrl.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"

using namespace std;

class PostWindow : public BaseWindow
{
public:
	PostWindow(DatabaseManager& dbManager);
	~PostWindow();

	void CreatePostWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);
	void DrawTable();
	HWND GetHandleListView() const { return hWndListView; }

protected:
	HWND hWndListView;
	DatabaseManager& dbManager;
};

