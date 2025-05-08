#pragma once
#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <string>


class BaseWindow
{
public:
	static const LPCWSTR CLASS_NAME;

	BaseWindow();
	virtual ~BaseWindow();

	virtual void CreateBaseWindow(HWND parentHWnd = nullptr, LPCWSTR windowName = L"", HINSTANCE hInstance = nullptr);
	HWND GetHandle() const;

	virtual void DrawTable(HWND hWnd);

	virtual HWND CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	virtual HWND CreateBaseTabControl(HWND parentHWnd, HINSTANCE hInstance);
	virtual HWND CreateBaseButton(HWND parentHWnd, LPCWSTR buttonName, HINSTANCE hInstance, int x, int y, int width, int height);
	virtual HWND CreateBaseEdit(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	virtual HWND CreateTabPage(HWND parentTabCtrl, int x, int y, int width, int height);
	virtual void AddTabPage(HWND hTabCtrl, LPCWSTR pageTitle);
	virtual void UpdateCurrentTabPage(int selectedTabIndex) {};


protected:
	HWND hWnd;
	int screenWidth;
	int screenHeight;
	HWND hWndListView;
	HWND hTabCtrl;
	std::vector<HWND> tabPages;

	HINSTANCE hInstance;

};

