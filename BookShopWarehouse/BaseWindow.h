#pragma once
#include <windows.h>
#include <commctrl.h>

class BaseWindow
{
public:
	BaseWindow();
	virtual ~BaseWindow();

	virtual void CreateBaseWindow(HWND parentHWnd = nullptr, LPCWSTR windowName = L"", HINSTANCE hInstance = nullptr);
	HWND GetHandle() const;
	virtual void DrawTable(HWND hWnd);

	virtual HWND CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance);


protected:
	HWND hWnd;
	int screenWidth;
	int screenHeight;
	HWND hWndListView;
};

