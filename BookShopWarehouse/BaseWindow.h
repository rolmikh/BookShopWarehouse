#pragma once
#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <string>
#include "HashAndSalt.h"
#include "WindowTypes.h"

class DatabaseManager;

class QueryDescriptor;

class BaseWindow
{
public:
	static const LPCWSTR CLASS_NAME;

	BaseWindow();
	virtual ~BaseWindow();

	virtual void CreateBaseWindow(HWND parentHWnd = nullptr, LPCWSTR windowName = L"", HINSTANCE hInstance = nullptr);
	HWND GetHandle() const;

	//virtual LPCWSTR GetClassName() const = 0;

	virtual void DrawTable(HWND hWnd);

	virtual HWND CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	virtual HWND CreateBaseButton(HWND parentHWnd, LPCWSTR buttonName, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id);
	virtual HWND CreateBaseEdit(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	virtual HWND CreateBaseComboBox(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id);
	virtual HWND CreateBaseDatePicker(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id);
	virtual HWND CreateBaseLabel(HWND parentHWnd, HINSTANCE hInstance, int x, int y, LPCWSTR text);
	virtual HWND CreateBaseLabelMin(HWND parentHWnd, HINSTANCE hInstance, int x, int y, LPCWSTR text);
	virtual HWND CreateMainTitleLabel(HWND parentHWnd, HINSTANCE hInstance, int x, int y, LPCWSTR text);

	virtual HWND CreateBaseTitleLabel(HWND parentHWnd, HINSTANCE hInstance, LPCWSTR text);

	virtual void UpdateCurrentTabPage(int selectedTabIndex) {};

	virtual void FillComboBox(HWND parentHWnd, const std::wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) = 0;

	virtual void DrawTable(HWND tableListView, const QueryDescriptor& descriptor) = 0;

	virtual void CreateElementsView() = 0;
	virtual void DestroyElementsView() = 0;

	HWND labelWindow;

	std::string WstrToStr(const std::wstring& wstr);
	std::wstring StrToWstr(const std::string& str);

	virtual WindowTypes GetType() const;

protected:
	HWND hWnd;
	int screenWidth;
	int screenHeight;
	HWND hWndListView;
	

	HINSTANCE hInstance;

};

