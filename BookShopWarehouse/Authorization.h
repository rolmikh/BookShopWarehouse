#pragma once
#include <windows.h>
#include <CommCtrl.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"

class Authorization : public BaseWindow
{

public:

	Authorization(DatabaseManager& dbManager);
	~Authorization();

	void CreateAuthorizationWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);

	void CreateElementsView() override;
	void DestroyElementsView() override;

};

