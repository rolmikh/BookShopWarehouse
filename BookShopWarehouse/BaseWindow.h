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
	virtual HWND CreateBaseButton(HWND parentHWnd, LPCWSTR buttonName, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id);
	virtual HWND CreateBaseEdit(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	virtual HWND CreateBaseComboBox(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id);
	virtual HWND CreateBaseDatePicker(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id);
	virtual HWND CreateBaseLabel(HWND parentHWnd, HINSTANCE hInstance, int x, int y, LPCWSTR text);
	virtual void UpdateCurrentTabPage(int selectedTabIndex) {};

	virtual void FillComboBox(HWND parentHWnd, const std::wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) {};

	HWND labelWindow;


protected:
	HWND hWnd;
	int screenWidth;
	int screenHeight;
	HWND hWndListView;
	

	HINSTANCE hInstance;

};

