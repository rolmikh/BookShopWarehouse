#pragma once
#include <windows.h>
#include <CommCtrl.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"
#include "QueryDescriptor.h"

class AdminWindow;
class WarehouseWorkerWindow;

class Authorization : public BaseWindow
{

private:

	
	AdminWindow* adminWindow = nullptr;
	WarehouseWorkerWindow* warehouseWorkerWindow = nullptr;

public:
	static const LPCWSTR CLASS_NAME;

	BaseWindow* nextWindow = nullptr;
	
	static const int IDC_BTN_AUTHORIZATION = 1111;

	Authorization(DatabaseManager& dbManager);
	~Authorization();

	void CreateAuthorizationWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);

	void CreateElementsView() override;
	void DestroyElementsView() override;

	void ToAuthorization(std::wstring login, std::wstring password);
	void SwitchingToWindow(std::wstring namePost);

	void hWndForDestroy(HWND& hWndElement);

	std::wstring GetWindowTextAsWstring(HWND hWndEdit) override;

	void DrawTable(HWND tableListView, const QueryDescriptor& descriptor) override;

	void FillComboBox(HWND parentHWnd, const std::wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) override;

	WindowTypes GetType() const override;
	HWND hEditLogin;
	HWND hPBPassword;

protected:
	HWND labelLogin;
	HWND labelPassword;
	
	HINSTANCE hInstance;
	HWND hBtnAuthorization;

	DatabaseManager& dbManager;



};

