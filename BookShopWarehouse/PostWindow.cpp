#include "PostWindow.h"
#include <commctrl.h>

PostWindow::PostWindow() {
	hWnd = nullptr;
	hWndListView = nullptr;
}

PostWindow::~PostWindow() {}

void PostWindow::CreatePostWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	CreateBaseWindow(parentHWnd, windowName, hInstance);

	InitCommonControls();

	CreateBaseListView(parentHWnd, hInstance);


}



