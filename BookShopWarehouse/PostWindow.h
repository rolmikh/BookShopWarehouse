#pragma once
#include <windows.h>
#include <string>
#include <commctrl.h>
#include "BaseWindow.h"

using namespace std;

class PostWindow : public BaseWindow
{
public:
	PostWindow();
	~PostWindow();

	void CreatePostWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);
	void DrawTable(HWND hWndListView);

protected:
	HWND hWndListView;


	
};

