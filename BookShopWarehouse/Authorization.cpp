#include "Authorization.h"
#include <CommCtrl.h>
#include "AdminWindow.h"
#include "WarehouseWorkerWindow.h"


using namespace std;

Authorization::Authorization(DatabaseManager& dbManager) : dbManager(dbManager) {

	labelLogin = nullptr;
	labelPassword = nullptr;
	hEditLogin = nullptr;
	hPBPassword = nullptr;
	hBtnAuthorization = nullptr;
	labelWindow = nullptr;
	hInstance = nullptr;
}

Authorization::~Authorization() {}

const LPCWSTR Authorization::CLASS_NAME = L"AuthorizationWindowClass";

void Authorization::CreateAuthorizationWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	CreateBaseWindow(parentHWnd, windowName, hInstance);

	InitCommonControls();

	this->hInstance = hInstance;

	CreateElementsView();

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

}

void Authorization::ToAuthorization(wstring login, wstring password) {

	wstring query = L"select Login_Employee, Password_Employee, Salt, Name_Post from Employee inner join Post on Post_ID = Post.ID_Post where Login_Employee = '" + login;
	query += L"'";
	bool salt = false;
	HashAndSalt hashAndSalt;

	vector<vector<wstring>> result = dbManager.ExecuteQuery(query);

	if (!result.empty()) {
		wstring loginEmployee = result[0][0];
		wstring passwordEmployee = result[0][1];
		wstring saltEmployee = result[0][2];
		wstring namePost = result[0][3];

		

		if (login == loginEmployee) {
			salt = hashAndSalt.AreEqual(WstrToStr(password), WstrToStr(passwordEmployee), WstrToStr(saltEmployee));
		
			if (salt == true) {
				MessageBox(hWnd, L"Авторизация прошла успешно", L"Успех", MB_OK);
				SwitchingToWindow(namePost);
			}
			else {
				MessageBox(hWnd, L"Ошибка авторизации", L"Ошибка", MB_OK | MB_ICONERROR);

			}
		
		}
	}

}

WindowTypes Authorization::GetType() const { return WindowTypes::AUTHORIZATION_WINDOW; }

void Authorization::SwitchingToWindow(wstring namePost) {

	
	if (namePost == L"Администратор баз данных")
	{
		adminWindow = new AdminWindow(dbManager);
		adminWindow->CreateAdminWindow(hWnd, L"Окно администратора", GetModuleHandle(NULL));	
		ShowWindow(hWnd, SW_HIDE);
	}
	else if (namePost == L"Сотрудник склада") {
		warehouseWorkerWindow = new WarehouseWorkerWindow(dbManager);
		warehouseWorkerWindow->CreateWarehouseWorkerWindow(hWnd, L"Окно сотрудника склада", GetModuleHandle(NULL));
		ShowWindow(hWnd, SW_HIDE);
	}

	

}


void Authorization::CreateElementsView() {

	DestroyElementsView();

	labelWindow = CreateMainTitleLabel(hWnd, hInstance, 0, screenHeight / 2 - 100, L"Книжная страна");


	hEditLogin = CreateBaseEdit(hWnd, hInstance, screenWidth / 4, screenHeight / 2, screenWidth / 2,  60);
	hPBPassword = CreateBaseEditPassword(hWnd, hInstance, screenWidth / 4, screenHeight / 2 + 100, screenWidth / 2, 60);

	hBtnAuthorization = CreateBaseButton(hWnd,L"Авторизация", hInstance, screenWidth / 4, screenHeight / 2 + 200, screenWidth / 2, 60, reinterpret_cast<HMENU>(IDC_BTN_AUTHORIZATION));
	hBtnRegistration = CreateBaseButton(hWnd, L"Регистрация", hInstance, screenWidth / 4, screenHeight / 2 + 300, screenWidth / 2, 60, reinterpret_cast<HMENU>(IDC_BTN_REGISTRATION));


}


void Authorization::DestroyElementsView() {

	hWndForDestroy(labelLogin);
	hWndForDestroy(labelPassword);
	hWndForDestroy(hEditLogin);
	hWndForDestroy(hPBPassword);
	hWndForDestroy(hBtnAuthorization);
	hWndForDestroy(labelWindow);

}

void Authorization::hWndForDestroy(HWND& hWndElement) {
	if (hWndElement) {
		DestroyWindow(hWndElement);
		SetWindowLongPtr(hWndElement, GWLP_USERDATA, NULL);
		hWndElement = nullptr;
	}
}


wstring Authorization::GetWindowTextAsWstring(HWND hWndEdit) {
	int length = GetWindowTextLength(hWndEdit);
	std::vector<wchar_t> buffer(length + 1);  // +1 для учета нулевого символа
	GetWindowText(hWndEdit, &buffer[0], length + 1);

	return std::wstring(&buffer[0]);
}


void Authorization::DrawTable(HWND tableListView, const QueryDescriptor& descriptor) {
}


void Authorization::FillComboBox(HWND hComboBox, const wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) {
	
}
