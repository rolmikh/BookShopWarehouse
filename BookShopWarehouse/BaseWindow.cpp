#include "BaseWindow.h"
#include "AdminWindow.h"
#pragma comment(lib, "comctl32.lib")


LRESULT CALLBACK BaseWindowWnd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const LPCWSTR BaseWindow::CLASS_NAME = L"MyBaseWindowClass";

ATOM RegisterBaseWindowClass(HINSTANCE hInstance) {
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = BaseWindowWnd;
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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
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
		parentHWnd,
		nullptr,
		hInstance,
		nullptr

	);

	return listView;
}

HWND BaseWindow::CreateBaseButton(HWND parentHWnd, LPCWSTR buttonName, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id) {
	HWND hWndButton = CreateWindow(
		L"BUTTON",
		buttonName,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		x, y, width, height,
		parentHWnd,
		id,
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



HWND BaseWindow::GetHandle() const {
	return hWnd;
}

void BaseWindow::DrawTable(HWND hWnd) {

}

LRESULT CALLBACK BaseWindowWnd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BaseWindow* window = reinterpret_cast<BaseWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (uMsg == WM_CREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<BaseWindow*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		return 0;
	}

	if (!window) {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	switch (uMsg) {

	case WM_NOTIFY:
		//LPNMHDR nmhdr = (LPNMHDR)lParam;
		//if(nmhdr->hwndFrom == window->GetListViewHandle())
	case WM_COMMAND:
	{
		// Проверяем тип окна
		wchar_t className[256];
		GetClassName(hwnd, className, 256);

		if (wcscmp(className, AdminWindow::CLASS_NAME) == 0) {
			AdminWindow* adminWindow = static_cast<AdminWindow*>(window);
			int controlId = LOWORD(wParam);
			int tab = adminWindow->currentTab;
			// Обработка кнопок-вкладок
			if (controlId == AdminWindow::IDC_TAB_POST) {
				adminWindow->UpdateCurrentTabPage(0); // Должность
			}
			else if (controlId == AdminWindow::IDC_TAB_TYPE_OF_COUNTERPARTY) {
				adminWindow->UpdateCurrentTabPage(1); // Тип контрагента
			}
			else if (controlId == AdminWindow::IDC_TAB_CONTRACT) {
				adminWindow->UpdateCurrentTabPage(2); // Контракт
			}

			// Обработка других кнопок
			else if (controlId == AdminWindow::IDC_ADD) {
				
				switch (tab)
				{
				case 0: {
					std::wstring namePost = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNamePost);
					std::vector<std::wstring> columnNames = { L"Name_Post" };
					std::vector<std::wstring> values = { namePost };

					adminWindow->AddRecord(L"Post", columnNames, values);

					
					break;
				}

				default:
					break;
				}

			}
			else if (controlId == AdminWindow::IDC_EDIT) {
				switch (tab)
				{
				case 0: {
					std::wstring namePost = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNamePost);
					std::vector<std::wstring> columnNames = { L"Name_Post" };
					std::wstring idPostStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdPost);
					int idPost = _wtoi(idPostStr.c_str());
					std::vector<std::wstring> values = { namePost };
					
					adminWindow->UpdateRecord(L"Post", columnNames, values, idPost);


					break;//кнопки не кликабельны
				}

				default:
					break;
				}
			}
			else if (controlId == AdminWindow::IDC_DELETE) {
				switch (tab) {
				case 0:
					std::wstring idPostStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdPost);

					int idPost = _wtoi(idPostStr.c_str());

					adminWindow->DeleteRecord(L"Post", idPost);

					break;
				}

			}
			else if (controlId == AdminWindow::IDC_SEARCH) {
				MessageBox(hwnd, L"Поиск", L"Debug", MB_OK);
			}
			else if (controlId == AdminWindow::IDC_FILTER) {
				MessageBox(hwnd, L"Фильтр", L"Debug", MB_OK);
			}
		}
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}


