#pragma once
#include <windows.h>
#include <vector>
#include <string>

class BaseTable
{
public:
	static void ClearListView(HWND hWndListView);
	static void SetHeaders(HWND hWndListView, const std::vector<std::wstring>& headers);
	static void SetData(HWND hWndListView, const std::vector<std::vector<std::wstring>>& data);
	static void AutoResizeColumns(HWND hWndListView, const std::vector<std::wstring>& headers, std::vector<std::vector<std::wstring>>& data);
	static void ResizeListViewToFit(HWND hWndListView, int rowCount);


};

