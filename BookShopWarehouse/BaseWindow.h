#pragma once
#include <windows.h>
#include <commctrl.h>

class BaseWindow
{
public:
	static const LPCWSTR CLASS_NAME;

	BaseWindow();
	virtual ~BaseWindow();

	virtual void CreateBaseWindow(HWND parentHWnd = nullptr, LPCWSTR windowName = L"", HINSTANCE hInstance = nullptr);
	HWND GetHandle() const;
	virtual void DrawTable(HWND hWnd);

	virtual HWND CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance);

	virtual HWND CreateBaseButton(HWND parentHWnd, LPCWSTR buttonName, HINSTANCE hInstance);

	//virtual void CloseWindow();


protected:
	HWND hWnd;
	int screenWidth;
	int screenHeight;
	HWND hWndListView;
};

