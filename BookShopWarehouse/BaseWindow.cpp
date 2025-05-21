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
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | WS_BORDER | WS_HSCROLL | WS_VSCROLL,
		x, y, width, height,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr

	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 20;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(listView, WM_SETFONT, (WPARAM)hFont, TRUE);


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

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 25;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(hWndButton, WM_SETFONT, (WPARAM)hFont, TRUE);

	return hWndButton;

}

HWND BaseWindow::CreateBaseEdit(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height) {
	
	
	HWND editField = CreateWindow(
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		x, y, width, height,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr

	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 20;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(editField, WM_SETFONT, (WPARAM)hFont, TRUE);

	return editField;
}

HWND BaseWindow::CreateBaseComboBox(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id) {
	int comboBoxHeight = 500;
	HWND hComboBox = CreateWindowEx(
		0,
		WC_COMBOBOX,
		nullptr,
		CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP,
		x, y, width, comboBoxHeight,
		parentHWnd,
		id,
		hInstance,
		nullptr
	
	);

	return hComboBox;
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
			else if (controlId == AdminWindow::IDC_TAB_COUNTERPARTY) {
				adminWindow->UpdateCurrentTabPage(3); // Контрагент
			}
			else if (controlId == AdminWindow::IDC_TAB_DELIVERY) {
				adminWindow->UpdateCurrentTabPage(4); // Поставка
			}
			else if (controlId == AdminWindow::IDC_TAB_DELIVERY_NOTE) {
				adminWindow->UpdateCurrentTabPage(5); // Накладная
			}
			else if (controlId == AdminWindow::IDC_DELIVERY_POSITION) {
				adminWindow->UpdateCurrentTabPage(6); // Позиция поставки
			}
			else if (controlId == AdminWindow::IDC_TAB_EMPLOYEE) {
				adminWindow->UpdateCurrentTabPage(7); // Сотрудник
			}
			else if (controlId == AdminWindow::IDC_TAB_PRODUCT) {
				adminWindow->UpdateCurrentTabPage(8); // Товар
			}
			else if (controlId == AdminWindow::IDC_TAB_PRODUCT_ORDER_REQUEST) {
				adminWindow->UpdateCurrentTabPage(9); // Заявка на заказ товара
			}
			else if (controlId == AdminWindow::IDC_TAB_REQUISITION_POSITION) {
				adminWindow->UpdateCurrentTabPage(10); // Заявка поставки
			}
			else if (controlId == AdminWindow::IDC_TAB_STATUS) {
				adminWindow->UpdateCurrentTabPage(11); // Статус
			}
			else if (controlId == AdminWindow::IDC_TAB_TYPE_OF_PRODUCT) {
				adminWindow->UpdateCurrentTabPage(12); // Тип товара
			}
			else if (controlId == AdminWindow::IDC_TAB_WAREHOUSE) {
				adminWindow->UpdateCurrentTabPage(13); // Склад
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


