#include "PostWindow.h"
#include <commctrl.h>
#include "BaseTable.h"
#include <string>

using namespace std;

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

	vector<wstring> headers = { L"Код должности",L"Название" };

	wstring query = L"select ID_Post as 'Код должности', Name_Post as 'Название'  from Post";
	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"Нет данных для отображения", L"Ошибка", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"Несоответствие заголовков и данных", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	BaseTable::ClearListView(hWndListView);
	BaseTable::SetHeaders(hWndListView, headers);
	BaseTable::SetData(hWndListView, tableData);
	BaseTable::AutoResizeColumns(hWndListView, headers, tableData);

	

	

	
}




