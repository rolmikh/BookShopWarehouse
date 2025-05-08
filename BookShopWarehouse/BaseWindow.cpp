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
	hTabCtrl = nullptr;
	//tabPages = nullptr;
	hInstance = nullptr;
}

BaseWindow::~BaseWindow() {}

void BaseWindow::CreateBaseWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {
	
	this->hInstance = hInstance;
	
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

HWND BaseWindow::CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height) {
	
	INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_LISTVIEW_CLASSES };
	InitCommonControlsEx(&icex);
	
	HWND listView = CreateWindowEx(
		0,
		WC_LISTVIEW,
		L"",
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | WS_BORDER,
		x, y, width, height,
		hTabCtrl,
		nullptr,
		hInstance,
		nullptr

	);

	return listView;
}

HWND BaseWindow::CreateBaseButton(HWND parentHWnd, LPCWSTR buttonName, HINSTANCE hInstance, int x, int y, int width, int height) {
	HWND hWndButton = CreateWindow(
		L"BUTTON",
		buttonName,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		x, y, width, height,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr
	
	);

	return hWndButton;
}

HWND BaseWindow::CreateBaseEdit(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height) {
	return CreateWindow(
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		x, y, width, height,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr
	
	);

}

HWND BaseWindow::CreateBaseTabControl(HWND parentHWnd, HINSTANCE hInstance) {
	INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_TAB_CLASSES };
	InitCommonControlsEx(&icex);

	return CreateWindow(
		WC_TABCONTROL,
		L"",
		WS_CHILD | WS_VISIBLE,
		50, 50,
		screenWidth - 100,
		screenHeight - 500,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr
	
	);
}

void BaseWindow::AddTabPage(HWND hTabCtrl, LPCWSTR pageTitle) {
	TCITEM tie = {};
	tie.mask = TCIF_TEXT;
	tie.pszText = const_cast<LPWSTR>(pageTitle);
	SendMessage(hTabCtrl, TCM_INSERTITEM, TabCtrl_GetItemCount(hTabCtrl), (LPARAM)&tie);



}

HWND BaseWindow::CreateTabPage(HWND parentTabCtrl, int x, int y, int width, int height) {
	HWND hTabPage = CreateWindowEx(
		0,
		WC_DIALOG,
		L"",
		WS_CHILD | WS_VISIBLE,
		x, y, width, height,
		parentTabCtrl,
		nullptr,
		hInstance,
		nullptr
	);

	tabPages.push_back(hTabPage);

	ShowWindow(hTabPage, SW_SHOW);
	UpdateWindow(hTabPage);

	return hTabPage;
}

HWND BaseWindow::GetHandle() const {
	return hWnd;
}

void BaseWindow::DrawTable(HWND hWnd) {

}

LRESULT CALLBACK BaseWindowWnd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BaseWindow* window = reinterpret_cast<BaseWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (window && uMsg == WM_CREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<BaseWindow*>(cs->lpCreateParams);
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	}

	/*if (window && uMsg == WM_COMMAND) {
		switch (LOWORD(wParam))
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_NOTIFY:
			if (((LPNMHDR)lParam)->code == TCN_SELCHANGE) {
				HWND hTab = ((LPNMHDR)lParam)->hwndFrom;
				int selected = TabCtrl_GetCurSel(hTab);
				if (window) {
					window->UpdateCurrentTabPage(selected);
				}
			}
			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}
	}*/

	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->code == TCN_SELCHANGE) {
			HWND hTab = ((LPNMHDR)lParam)->hwndFrom;
			int selected = TabCtrl_GetCurSel(hTab);
			if (window) {
				window->UpdateCurrentTabPage(selected);
			}
		}
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
	
}
