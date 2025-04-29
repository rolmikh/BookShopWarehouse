#pragma once
#include <windows.h>
#include <commctrl.h>

class BaseWindow
{
public:
	BaseWindow();
	virtual ~BaseWindow();

	virtual void CreateBaseWindow(HWND parentHWnd = nullptr, LPCWSTR windowName, HINSTANCE hInstance);
	HWND GetHandle() const;
	virtual void DrawTable(HWND hWnd);

	virtual void CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance);


protected:
	HWND hWnd;
	int screenWidth;
	int screenHeight;
	HWND hWndListView;
};

