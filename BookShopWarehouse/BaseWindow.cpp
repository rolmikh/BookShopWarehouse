#include "BaseWindow.h"
#pragma comment(lib, "comctl32.lib")


BaseWindow::BaseWindow() {
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	hWnd = nullptr;
	hWndListView = nullptr;
}

BaseWindow::~BaseWindow() {}

void BaseWindow::CreateBaseWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

		hWnd = CreateWindowEx(
			0,
			L"STATIC",
			windowName,
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			screenWidth,
			screenHeight,
			parentHWnd,
			nullptr,
			hInstance,
			nullptr

		);

		if (hWnd) {
			ShowWindow(hWnd, SW_SHOW);
			UpdateWindow(hWnd);
		}

	
}

HWND BaseWindow::CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance) {
	
	INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_LISTVIEW_CLASSES };
	InitCommonControlsEx(&icex);
	
	HWND listView = CreateWindowEx(
		0,
		WC_LISTVIEW,
		L"",
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | WS_BORDER,
		10, 10, screenWidth - 20, screenHeight - 20,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr

	);

	return listView;
}

HWND BaseWindow::GetHandle() const {
	return hWnd;
}

void BaseWindow::DrawTable(HWND hWnd) {

}
