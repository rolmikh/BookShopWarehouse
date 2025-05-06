#include "BaseTable.h"
#include <commctrl.h>
#include <windows.h>
#include <vector>

void BaseTable::ClearListView(HWND hWndListView) {
	if (!hWndListView) return;

	ListView_DeleteAllItems(hWndListView);
	int colCount = Header_GetItemCount(ListView_GetHeader(hWndListView));
	for (int i = colCount - 1; i >= 0; --i) {
		ListView_DeleteColumn(hWndListView, i);
	}

}

void BaseTable::SetHeaders(HWND hWndListView, const std::vector<std::wstring>& headers) {
	if (!hWndListView || headers.empty()) return;
	

	for (size_t i = 0; i < headers.size(); i++) {
		LVCOLUMN lvc = {};
		lvc.mask = LVCF_TEXT | LVCF_SUBITEM;
		lvc.pszText = const_cast<LPWSTR>(headers[i].c_str());
		lvc.iSubItem = static_cast<int>(i);
		ListView_InsertColumn(hWndListView, static_cast<int>(i), &lvc);
	}
}

void BaseTable::SetData(HWND hWndListView, const std::vector<std::vector<std::wstring>>& data) {
	if (!hWndListView || data.empty()) return;

	for (const auto& row : data) {
		if (row.empty()) continue;

		LVITEM lvi = {};
		lvi.mask = LVIF_TEXT;
		lvi.iItem = ListView_GetItemCount(hWndListView);
		lvi.iSubItem = 0;
		lvi.pszText = const_cast<LPWSTR>(row[0].c_str());
		int itemIndex = ListView_InsertItem(hWndListView, &lvi);
		

		for (size_t col = 1; col < row.size(); ++col) {
			ListView_SetItemText(hWndListView, itemIndex, static_cast<int>(col), const_cast<LPWSTR>(row[col].c_str()));
		}

	}
}

//точки выводятся можно исправить позже
void BaseTable::AutoResizeColumns(HWND hWndListView, const std::vector<std::wstring>& headers, std::vector<std::vector<std::wstring>>& data) {
	if (!hWndListView || headers.empty()) return;

	HDC hdc = GetDC(hWndListView);
	SIZE size;
	int columnCount = static_cast<int>(headers.size());
	std::vector<int> columnWidths(columnCount, 0);

	for (int i = 0; i < columnCount; ++i) {
		GetTextExtentPoint32(hdc, headers[i].c_str(), static_cast<int>(headers[i].length()), &size);
		columnWidths[i] = size.cx + 30;
	}

	for (const auto& row : data) {
		for (size_t col = 0; col < row.size() && col < columnCount; ++col) {
			GetTextExtentPoint32(hdc, row[col].c_str(), static_cast<int>(row[col].length()), &size);
			if (size.cx + 30 > columnWidths[col]) {
				columnWidths[col] = size.cx + 30;
			}
		}
	}

	ReleaseDC(hWndListView, hdc);

	for (int i = 0; i < columnCount; ++i) {
		ListView_SetColumnWidth(hWndListView, i, columnWidths[i]);
	}

}