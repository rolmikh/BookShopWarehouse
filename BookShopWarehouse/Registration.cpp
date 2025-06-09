#include "Registration.h"
#include <commctrl.h>
#include "BaseTable.h"
#include <string>
#include <iostream>

using namespace std;

Registration::Registration(DatabaseManager& dbManager) : dbManager(dbManager) {

	hEditSurnameRegistration = nullptr;
	hEditNameRegistration = nullptr;
	hEditPatronymicRegistration = nullptr;
	hEditEmailRegistration = nullptr;
	hEditLoginRegistration = nullptr;
	hEditPasswordRegistration = nullptr;
	hComboBoxPostRegistration = nullptr;
	hLabelSurnameRegistration = nullptr;
	hLabelNameRegistration = nullptr;
	hLabelPatronymicRegistration = nullptr;
	hLabelEmailRegistration = nullptr;
	hLabelLoginRegistration = nullptr;
	hLabelPasswordRegistration = nullptr;
	hLabelPostRegistration = nullptr;

}

Registration::~Registration() {}

const LPCWSTR Registration::CLASS_NAME = L"RegistrationWindowClass";

void Registration::CreateRegistrationWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE nInstance)
{
	CreateBaseWindow(parentHWnd, windowName, hInstance);

	InitCommonControls();

	this->hInstance = hInstance;

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	DestroyElementsView();

	CreateElementsView();

}

void Registration::CreateElementsView() {

	labelWindow = CreateMainTitleLabel(hWnd, hInstance, 0, screenHeight / 6, L"Регистрация");

	hLabelSurnameRegistration = CreateBaseLabel(hWnd, hInstance, 50, screenHeight / 3, L"Фамилия");
	hEditSurnameRegistration = CreateBaseEdit(hWnd, hInstance, screenWidth / 4 + 300, screenHeight / 3, screenWidth / 2, 50);

	hLabelNameRegistration = CreateBaseLabel(hWnd, hInstance, 50, screenHeight / 3 + 60, L"Имя");
	hEditNameRegistration = CreateBaseEdit(hWnd, hInstance, screenWidth / 4 + 300, screenHeight / 3 + 60, screenWidth / 2, 50);

	hLabelPatronymicRegistration = CreateBaseLabel(hWnd, hInstance, 50, screenHeight / 3 + 120, L"Отчество");
	hEditPatronymicRegistration = CreateBaseEdit(hWnd, hInstance, screenWidth / 4 + 300, screenHeight / 3 + 120, screenWidth / 2, 50);

	hLabelEmailRegistration = CreateBaseLabel(hWnd, hInstance, 50, screenHeight / 3 + 180, L"Электронная почта");
	hEditEmailRegistration = CreateBaseEdit(hWnd, hInstance, screenWidth / 4 + 300, screenHeight / 3 + 180, screenWidth / 2, 50);

	hLabelLoginRegistration = CreateBaseLabel(hWnd, hInstance, 50, screenHeight / 3 + 240, L"Логин");
	hEditLoginRegistration = CreateBaseEdit(hWnd, hInstance, screenWidth / 4 + 300, screenHeight / 3 + 240, screenWidth / 2, 50);

	hLabelPasswordRegistration = CreateBaseLabel(hWnd, hInstance, 50, screenHeight / 3 + 300, L"Пароль");
	hEditPasswordRegistration = CreateBaseEdit(hWnd, hInstance, screenWidth / 4 + 300, screenHeight / 3 + 300, screenWidth / 2, 50);

	hLabelPostRegistration = CreateBaseLabel(hWnd, hInstance, 50, screenHeight / 3 + 360, L"Должность");
	hComboBoxPostRegistration = CreateBaseComboBox(hWnd, hInstance, screenWidth / 4 + 300, screenHeight / 3 + 360, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_POST_REHISTRATION));

	FillComboBox(hComboBoxPostRegistration, L"select ID_Post, Name_Post from Post", dbManager, comboBoxIdMapPostReg);

	hBtnRegistrationP = CreateBaseButton(hWnd, L"Регистрация", hInstance, screenWidth / 4, screenHeight / 2 + 260, screenWidth / 2, 60, reinterpret_cast<HMENU>(IDC_REGISTRATION));
	hBtnAuthorizationP = CreateBaseButton(hWnd, L"Авторизация", hInstance, screenWidth / 4, screenHeight / 2 + 330, screenWidth / 2, 60, reinterpret_cast<HMENU>(IDC_REGISTRATION));


}

void Registration::hWndForDestroy(HWND& hWndElement) {
	if (hWndElement) {
		DestroyWindow(hWndElement);
		SetWindowLongPtr(hWndElement, GWLP_USERDATA, NULL);
		hWndElement = nullptr;
	}
}



void Registration::DestroyElementsView() {
	hWndForDestroy(hEditSurnameRegistration);
	hWndForDestroy(hEditNameRegistration);
	hWndForDestroy(hEditPatronymicRegistration);
	hWndForDestroy(hEditEmailRegistration);
	hWndForDestroy(hEditLoginRegistration);
	hWndForDestroy(hEditPasswordRegistration);
	hWndForDestroy(hComboBoxPostRegistration);
	hWndForDestroy(hLabelSurnameRegistration);
	hWndForDestroy(hLabelNameRegistration);
	hWndForDestroy(hLabelPatronymicRegistration);
	hWndForDestroy(hLabelEmailRegistration);
	hWndForDestroy(hLabelLoginRegistration);
	hWndForDestroy(hLabelPasswordRegistration);
	hWndForDestroy(hLabelPostRegistration);
	hWndForDestroy(hBtnRegistrationP);
	hWndForDestroy(hBtnAuthorizationP);

}

void Registration::FillComboBox(HWND parentHWnd, const wstring& query, DatabaseManager& dbManager, vector<int>& idMap) {
	SendMessage(parentHWnd, CB_RESETCONTENT, 0, 0);

	idMap.clear();

	auto data = dbManager.ExecuteQuery(query);

	wprintf(L"Получено строк: %zu\n", data.size());

	for (const auto& row : data) {
		if (row.size() >= 2) {
			int id = stoi(row[0].c_str());
			const wstring& name = row[1];

			SendMessage(parentHWnd, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(name.c_str()));

			idMap.push_back(id);
		}
	}

	if (!data.empty()) {
		SendMessage(parentHWnd, CB_SETCURSEL, 0, 0);
	}
}

wstring Registration::GetWindowTextAsWstring(HWND hWndEdit) {
	int length = GetWindowTextLength(hWndEdit);
	std::vector<wchar_t> buffer(length + 1);  // +1 для учета нулевого символа
	GetWindowText(hWndEdit, &buffer[0], length + 1);

	return std::wstring(&buffer[0]);
}

bool Registration::ExecuteSQL(LPCWSTR sql) {
	try {
		dbManager.ExecuteQuery(sql);
		return true;
	}
	catch (...) {
		MessageBox(hWnd, L"Ошибка выполнения SQL", L"Ошибка", MB_OK | MB_ICONERROR);
		return false;
	}
}


void Registration::DrawTable(HWND tableListView, const QueryDescriptor& descriptor) {

}

WindowTypes Registration::GetType() const { return WindowTypes::REGISTRATION_WINDOW; }

void Registration::AddEmployee(const wstring& tableName, const vector<wstring>& columnNames, const vector<wstring>& values) {

	if (columnNames.size() != values.size()) {
		MessageBox(hWnd, L"Количество полей не совпадает", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	wstring sql = L"insert into " + tableName + L" (";
	for (size_t i = 0; i < columnNames.size(); ++i) {
		sql += columnNames[i];
		if (i != columnNames.size() - 1) sql += L", ";
	}

	sql += L") values (";

	for (size_t i = 0; i < values.size(); ++i) {
		sql += L"N'" + values[i] + L"'";
		if (i != values.size() - 1) sql += L", ";
	}

	sql += L")";

	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"Поздравляем вы успешно зарегистрированы", L"Успех", MB_OK);
	}

}
