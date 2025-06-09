#pragma once
#include <windows.h>
#include <string>
#include <commctrl.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"
#include "QueryDescriptor.h"
#include <unordered_map>



class Registration : public BaseWindow
{
private:
	static const int IDC_COMBOBOX_POST_REHISTRATION = 1061;

public:
	static const LPCWSTR CLASS_NAME;
	static const int IDC_REGISTRATION = 1062;
	static const int IDC_AUTHORIZATION = 1063;

	Registration(DatabaseManager& dbManager);
	~Registration();

	void CreateRegistrationWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE nInstance);

	void CreateElementsView() override;
	void DestroyElementsView() override;
	void hWndForDestroy(HWND& hWndElement);

	void FillComboBox(HWND parentHWnd, const std::wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) override;

	std::wstring GetWindowTextAsWstring(HWND hWndEdit) override;

	void DrawTable(HWND tableListView, const QueryDescriptor& descriptor) override;

	WindowTypes GetType() const override;

	std::vector<int> comboBoxIdMapPostReg;

	HWND hEditSurnameRegistration;
	HWND hEditNameRegistration;
	HWND hEditPatronymicRegistration;
	HWND hEditEmailRegistration;
	HWND hEditLoginRegistration;
	HWND hEditPasswordRegistration;
	HWND hComboBoxPostRegistration;

	HWND hLabelSurnameRegistration;
	HWND hLabelNameRegistration;
	HWND hLabelPatronymicRegistration;
	HWND hLabelEmailRegistration;
	HWND hLabelLoginRegistration;
	HWND hLabelPasswordRegistration;
	HWND hLabelPostRegistration;

	HWND hBtnRegistrationP;
	HWND hBtnAuthorizationP;

	DatabaseManager& dbManager;

	void AddEmployee(const std::wstring& tableName, const std::vector<std::wstring>& columnNames, const std::vector<std::wstring>& values);


protected:

	HINSTANCE hInstance;


	bool ExecuteSQL(LPCWSTR sql);


	HWND hBtnAdd;





};

