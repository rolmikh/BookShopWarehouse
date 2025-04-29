#include "BaseWindow.h"

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

	
}

void BaseWindow::CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance) {
	hWndListView = CreateWindowEx(
		0,
		WC_LISTVIEW,
		L"",
		WS_CHILD | WS_VISIBLE | LVS_REPORT,
		10, 10, screenWidth - 20, screenHeight - 20,
		hWnd,
		nullptr,
		hInstance,
		nullptr

	);
}

HWND BaseWindow::GetHandle() const {
	return hWnd;
}

void BaseWindow::DrawTable(HWND hWnd) {

}
