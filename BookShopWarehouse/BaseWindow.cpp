#include "BaseWindow.h"
#pragma comment(lib, "comctl32.lib")

const LPCWSTR BaseWindow::CLASS_NAME = L"MyBaseWindowClass";

ATOM RegisterBaseWindowClass(HINSTANCE hInstance) {
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = BaseWindow::CLASS_NAME;

	return RegisterClass(&wc);
}


BaseWindow::BaseWindow() {
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	hWnd = nullptr;
	hWndListView = nullptr;
}

BaseWindow::~BaseWindow() {}

void BaseWindow::CreateBaseWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {
	RegisterBaseWindowClass(hInstance);

		hWnd = CreateWindowEx(
			0,
			CLASS_NAME,
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
		50, 50, screenWidth - 100, screenHeight - 100,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr

	);

	return listView;
}

HWND BaseWindow::CreateBaseButton(HWND parentHWnd, LPCWSTR buttonName, HINSTANCE hInstance) {
	HWND hWndButton = CreateWindow(
		L"BUTTON",
		buttonName,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		screenWidth - 20, screenHeight - 20, 100, 100,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr
	
	);

	return hWndButton;
}

HWND BaseWindow::GetHandle() const {
	return hWnd;
}

void BaseWindow::DrawTable(HWND hWnd) {

}

LRESULT CALLBACK BaseWindowWnd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
}
