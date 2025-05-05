#include "PostWindow.h"
#include <commctrl.h>

PostWindow::PostWindow(DatabaseManager& dbManager) : dbManager(dbManager) {
	hWnd = nullptr;
	hWndListView = nullptr;
}


PostWindow::~PostWindow() {}

void PostWindow::CreatePostWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	CreateBaseWindow(parentHWnd, windowName, hInstance);

	InitCommonControls();

	hWndListView = CreateBaseListView(hWnd, hInstance);

	


}



void PostWindow::DrawTable() {

	if (!hWndListView) {
		MessageBox(NULL, L"Список еще не создан", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	vector<wstring> headers = { L"id",L"name" };

	wstring query = L"select * from Post";
	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"Нет данных для отображения", L"Ошибка", MB_OK | MB_ICONWARNING);
		return;
	}

	ListView_DeleteAllItems(hWndListView);
	int colCount = Header_GetItemCount(ListView_GetHeader(hWndListView));
	for (int i = colCount - 1; i >= 0; --i) {
		ListView_DeleteColumn(hWndListView, i);
	}

	for (int i = 0; i < headers.size(); i++) {
		LVCOLUMN lvc = {};
		lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.cx = 100;
		lvc.pszText = (LPWSTR)headers[i].c_str();
		lvc.iSubItem = i;
		ListView_InsertColumn(hWndListView, i, &lvc);
	}

	for (size_t row = 0; row < tableData.size(); row++) {
		LVITEM lvi = {};
		lvi.mask = LVIF_TEXT;
		lvi.iItem = static_cast<int>(row);
		lvi.iSubItem = 0;
		lvi.pszText = (LPWSTR)tableData[row][0].c_str();
		ListView_InsertItem(hWndListView, &lvi);

		for (int col = 1; col < tableData[row].size(); col++) {
			ListView_SetItemText(hWndListView, static_cast<int>(row), col, (LPWSTR)tableData[row][col].c_str());
		}

	}
}



