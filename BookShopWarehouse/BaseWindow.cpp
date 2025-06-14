#include "BaseWindow.h"
#include "AdminWindow.h"
#include "Authorization.h"
#include "WarehouseWorkerWindow.h"
#include "DatabaseManager.h"
#include "Registration.h"
#pragma comment(lib, "comctl32.lib")
#include <cctype>
#include <algorithm>
#include "Post.h"
#include "Contract.h"
#include "Counterparty.h"
#include "Delivery.h"
#include "DeliveryNote.h"
#include "DeliveryPosition.h"
#include "Employee.h"
#include "Product.h"
#include "ProductOrderRequest.h"
#include "TypeOfProduct.h"
#include "RequisitionPosition.h"
#include "Status.h"
#include "TypeOfCounterparty.h"
#include "Warehouse.h"

LRESULT CALLBACK BaseWindowWnd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const LPCWSTR BaseWindow::CLASS_NAME = L"MyBaseWindowClass";

ATOM RegisterBaseWindowClass(HINSTANCE hInstance) {
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = BaseWindowWnd;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = BaseWindow::CLASS_NAME;

	return RegisterClass(&wc);
}


BaseWindow::BaseWindow() {
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	hWnd = nullptr;
	hWndListView = nullptr;
	hInstance = nullptr;
	labelWindow = nullptr;
}

BaseWindow::~BaseWindow() {}

void BaseWindow::CreateBaseWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	this->hInstance = hInstance;

	RegisterBaseWindowClass(hInstance);

	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		windowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		0,
		0,
		screenWidth,
		screenHeight,
		parentHWnd,
		nullptr,
		hInstance,
		this

	);

	if (hWnd) {
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}


}

HWND BaseWindow::CreateBaseListView(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height) {

	INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_LISTVIEW_CLASSES };
	InitCommonControlsEx(&icex);

	HWND listView = CreateWindowEx(
		0,
		WC_LISTVIEW,
		L"",
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | WS_BORDER | WS_HSCROLL | WS_VSCROLL,
		x, y, width, height,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr

	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 20;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(listView, WM_SETFONT, (WPARAM)hFont, TRUE);


	return listView;
}

HWND BaseWindow::CreateBaseButton(HWND parentHWnd, LPCWSTR buttonName, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id) {
	HWND hWndButton = CreateWindow(
		L"BUTTON",
		buttonName,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		x, y, width, height,
		parentHWnd,
		id,
		hInstance,
		nullptr

	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 25;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(hWndButton, WM_SETFONT, (WPARAM)hFont, TRUE);

	return hWndButton;

}

HWND BaseWindow::CreateBaseEdit(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height) {


	HWND editField = CreateWindow(
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		x, y, width, height,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr

	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 25;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(editField, WM_SETFONT, (WPARAM)hFont, TRUE);

	return editField;
}

HWND BaseWindow::CreateBaseEditPassword(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height) {


	HWND editField = CreateWindow(
		L"EDIT",
		L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
		x, y, width, height,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr

	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 25;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(editField, WM_SETFONT, (WPARAM)hFont, TRUE);

	return editField;
}

HWND BaseWindow::CreateBaseComboBox(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id) {
	int comboBoxHeight = 500;
	HWND hComboBox = CreateWindowEx(
		0,
		WC_COMBOBOX,
		nullptr,
		CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP,
		x, y, width, comboBoxHeight,
		parentHWnd,
		id,
		hInstance,
		nullptr

	);
	SendMessage(hComboBox, CB_SETCURSEL, -1, 0);

	return hComboBox;
}

HWND BaseWindow::CreateBaseDatePicker(HWND parentHWnd, HINSTANCE hInstance, int x, int y, int width, int height, HMENU id) {
	HWND hDatePicker = CreateWindow(

		DATETIMEPICK_CLASS,
		NULL,
		WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT | DTS_UPDOWN,
		x, y, width, height,
		hWnd,
		id,
		hInstance,
		NULL

	);
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 25;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(hDatePicker, DTM_SETSYSTEMTIME, GDT_NONE, 0);

	return hDatePicker;
}

HWND BaseWindow::CreateBaseLabel(HWND parentHWnd, HINSTANCE hInstance, int x, int y, LPCWSTR text) {
	HWND hLabel = CreateWindow(
		L"STATIC",
		text,
		WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
		x, y, screenWidth / 2 - 100, 50,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr
	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 25;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

	return hLabel;

}

HWND BaseWindow::CreateBaseLabelMin(HWND parentHWnd, HINSTANCE hInstance, int x, int y, LPCWSTR text) {
	HWND hLabel = CreateWindow(
		L"STATIC",
		text,
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		x, y, screenWidth / 3 - 30, 50,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr
	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 25;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

	return hLabel;

}

HWND BaseWindow::CreateBaseTitleLabel(HWND parentHWnd, HINSTANCE hInstance, LPCWSTR text) {
	HWND hLabel = CreateWindow(
		L"STATIC",
		text,
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		0, 5, screenWidth, 50,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr
	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 30;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

	return hLabel;

}

HWND BaseWindow::CreateMainTitleLabel(HWND parentHWnd, HINSTANCE hInstance, int x, int y, LPCWSTR text) {
	HWND hLabel = CreateWindow(
		L"STATIC",
		text,
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		x, y, screenWidth, 60,
		parentHWnd,
		nullptr,
		hInstance,
		nullptr
	);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	lf.lfHeight = 30;
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

	return hLabel;

}

std::string BaseWindow::WstrToStr(const std::wstring& wstr) {
	if (wstr.empty()) return "";
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, nullptr, nullptr);
	return str;
}

std::wstring BaseWindow::StrToWstr(const std::string& str) {
	if (str.empty()) return {};
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), nullptr, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
	return wstr;
}



HWND BaseWindow::GetHandle() const {
	return hWnd;
}

void BaseWindow::DrawTable(HWND hWnd) {

}

WindowTypes BaseWindow::GetType() const { return WindowTypes::BASE_WINDOW; }

bool BaseWindow::IsSpaceOrEmpty(const std::wstring& value) {
	return std::all_of(value.begin(), value.end(), iswspace);
}



LRESULT CALLBACK BaseWindowWnd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BaseWindow* window = reinterpret_cast<BaseWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (uMsg == WM_CREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<BaseWindow*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		return 0;
	}

	if (!window) {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	switch (uMsg) {

	case WM_NOTIFY:
	{


	}
	case WM_COMMAND:
	{
		switch (window->GetType()) {
		case WindowTypes::AUTHORIZATION_WINDOW:
		{
			Authorization* authorization = static_cast<Authorization*>(window);
			int controlId = LOWORD(wParam);

			if (controlId == Authorization::IDC_BTN_AUTHORIZATION) {
				std::wstring login = authorization->GetWindowTextAsWstring(authorization->hEditLogin);
				std::wstring password = authorization->GetWindowTextAsWstring(authorization->hPBPassword);

				authorization->ToAuthorization(login, password);

			}
			else if (controlId == Authorization::IDC_BTN_REGISTRATION) {

				Registration* registration = new Registration(authorization->dbManager);
				authorization->DestroyElementsView();
				window = registration;
				registration->CreateRegistrationWindow(hwnd, L"Окно регистрации", GetModuleHandle(NULL));
			}

			break;
		}
		case WindowTypes::REGISTRATION_WINDOW:
		{
			Registration* registration = static_cast<Registration*>(window);

			int controlId = LOWORD(wParam);

			if (controlId == Registration::IDC_AUTHORIZATION) {
				Authorization* authorization = new Authorization(registration->dbManager);
				registration->DestroyElementsView();
				window = authorization;
				authorization->CreateAuthorizationWindow(hwnd, L"Окно авторизации", GetModuleHandle(NULL));
			}
			else if (controlId == Registration::IDC_REGISTRATION) {
				std::wstring surname = registration->GetWindowTextAsWstring(registration->hEditSurnameRegistration);
				std::wstring name = registration->GetWindowTextAsWstring(registration->hEditNameRegistration);
				std::wstring patronymic = registration->GetWindowTextAsWstring(registration->hEditPatronymicRegistration);
				std::wstring email = registration->GetWindowTextAsWstring(registration->hEditEmailRegistration);
				std::wstring login = registration->GetWindowTextAsWstring(registration->hEditLoginRegistration);
				std::wstring password = registration->GetWindowTextAsWstring(registration->hEditPasswordRegistration);

				if (window->IsSpaceOrEmpty(surname) ||
					window->IsSpaceOrEmpty(name) ||
					window->IsSpaceOrEmpty(patronymic) ||
					window->IsSpaceOrEmpty(email) ||
					window->IsSpaceOrEmpty(login) ||
					window->IsSpaceOrEmpty(password))
				{
					MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
					break;
				}
				HashAndSalt hasher;

				std::string salt = hasher.CreateSalt(16);
				std::string hash = hasher.GenerateHash(window->WstrToStr(password), salt);

				int index = SendMessage(registration->hComboBoxPostRegistration, CB_GETCURSEL, 0, 0);
				if (index == CB_ERR) break;

				int selectedPostId = registration->comboBoxIdMapPostReg[index];

				std::vector<std::wstring> columnNames = { L"Surname", L"Name", L"Patronymic", L"Email", L"Login_Employee", L"Password_Employee", L"Post_ID", L"Salt" };

				std::vector<std::wstring> values = { surname, name, patronymic, email, login, window->StrToWstr(hash), std::to_wstring(selectedPostId), window->StrToWstr(salt) };

				registration->AddEmployee(L"Employee", columnNames, values);

			}


		}
		case WindowTypes::ADMIN_WINDOW: {
			AdminWindow* adminWindow = static_cast<AdminWindow*>(window);
			int controlId = LOWORD(wParam);
			int tab = adminWindow->currentTab;
			// Обработка кнопок-вкладок
			if (controlId == AdminWindow::IDC_TAB_POST) {
				adminWindow->UpdateCurrentTabPage(0); // Должность
			}
			else if (controlId == AdminWindow::IDC_TAB_TYPE_OF_COUNTERPARTY) {
				adminWindow->UpdateCurrentTabPage(1); // Тип контрагента
			}
			else if (controlId == AdminWindow::IDC_TAB_CONTRACT) {
				adminWindow->UpdateCurrentTabPage(2); // Контракт
			}
			else if (controlId == AdminWindow::IDC_TAB_COUNTERPARTY) {
				adminWindow->UpdateCurrentTabPage(3); // Контрагент
			}
			else if (controlId == AdminWindow::IDC_TAB_DELIVERY) {
				adminWindow->UpdateCurrentTabPage(4); // Поставка
			}
			else if (controlId == AdminWindow::IDC_TAB_DELIVERY_NOTE) {
				adminWindow->UpdateCurrentTabPage(5); // Накладная
			}
			else if (controlId == AdminWindow::IDC_DELIVERY_POSITION) {
				adminWindow->UpdateCurrentTabPage(6); // Позиция поставки
			}
			else if (controlId == AdminWindow::IDC_TAB_EMPLOYEE) {
				adminWindow->UpdateCurrentTabPage(7); // Сотрудник
			}
			else if (controlId == AdminWindow::IDC_TAB_PRODUCT) {
				adminWindow->UpdateCurrentTabPage(8); // Товар
			}
			else if (controlId == AdminWindow::IDC_TAB_PRODUCT_ORDER_REQUEST) {
				adminWindow->UpdateCurrentTabPage(9);
			}
			else if (controlId == AdminWindow::IDC_TAB_REQUISITION_POSITION) {
				adminWindow->UpdateCurrentTabPage(10);
			}
			else if (controlId == AdminWindow::IDC_TAB_STATUS) {
				adminWindow->UpdateCurrentTabPage(11);
			}
			else if (controlId == AdminWindow::IDC_TAB_TYPE_OF_PRODUCT) {
				adminWindow->UpdateCurrentTabPage(12);
			}
			else if (controlId == AdminWindow::IDC_TAB_WAREHOUSE) {
				adminWindow->UpdateCurrentTabPage(13);
			}
			else if (controlId == AdminWindow::IDC_EXIT_ADMIN) {
				Authorization* authorization = new Authorization(adminWindow->dbManager);
				adminWindow->DestroyElementsView();
				window = authorization;
				authorization->CreateAuthorizationWindow(hwnd, L"Окно авторизации", GetModuleHandle(NULL));
			}


			else if (controlId == AdminWindow::IDC_ADD) {

				switch (tab)
				{
				case 0: {

					
					
					std::wstring namePost = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNamePost);
					if (window->IsSpaceOrEmpty(namePost))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					Post post(0, namePost);

					std::vector<std::wstring> columnNames = { L"Name_Post" };
					std::vector<std::wstring> values = { post.getNamePost()};

					adminWindow->AddRecord(L"Post", columnNames, values);

					break;
				}
				case 1: {
					std::wstring nameTypeOfCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameTypeOfCounterparty);

					if (window->IsSpaceOrEmpty(nameTypeOfCounterparty))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					TypeOfCounterparty typeOfCounterparty(0, nameTypeOfCounterparty);

					std::vector<std::wstring> columnNames = { L"Name_Type_Of_Counterparty" };
					std::vector<std::wstring> values = { typeOfCounterparty.getNameTypeOfCounterparty()};

					adminWindow->AddRecord(L"TypeOfCounterparty", columnNames, values);



					break;
				}
				case 2: {
					
					

					std::wstring contractNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContractNumber);
					std::wstring startDateContract = adminWindow->GetDateFromDatePicker(adminWindow->hDPStartDateContract);
					std::wstring endDateContract = adminWindow->GetDateFromDatePicker(adminWindow->hDPEndDateContract);
					std::wstring contractTerms = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContractTerms);

					if (window->IsSpaceOrEmpty(contractNumber) ||
						window->IsSpaceOrEmpty(startDateContract) ||
						window->IsSpaceOrEmpty(endDateContract) ||
						window->IsSpaceOrEmpty(contractTerms))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					int index = SendMessage(adminWindow->hComboBoxStatus, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedStatusContractId = adminWindow->comboBoxIdMapStatusContract[index];

					Contract contract(0, contractNumber, startDateContract, endDateContract, contractTerms, selectedStatusContractId);


					std::vector<std::wstring> columnNames = { L"Contract_Number", L"Start_Date_Contract", L"End_Date_Contract", L"Contract_Terms", L"Status_ID" };

					std::vector<std::wstring> values = { contract.getContractNumber(), contract.getStartDataContract(), contract.getEndDateContract(), contract.getContractTerms(), std::to_wstring(contract.getStatusId())};

					adminWindow->AddRecord(L"Contract_", columnNames, values);


					break;

				}
				case 3: {
					std::wstring nameCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameCounterparty);
					std::wstring phoneCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPhoneCounterparty);
					std::wstring emailCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditEmailCounterparty);
					std::wstring contactPerson = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContactPerson);
					std::wstring termsOfCooperation = adminWindow->GetWindowTextAsWstring(adminWindow->hEditTermsOfCooperation);
					std::wstring country = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCountry);
					std::wstring city = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCity);

					if (window->IsSpaceOrEmpty(nameCounterparty) ||
						window->IsSpaceOrEmpty(phoneCounterparty) ||
						window->IsSpaceOrEmpty(emailCounterparty) ||
						window->IsSpaceOrEmpty(contactPerson) ||
						window->IsSpaceOrEmpty(termsOfCooperation) ||
						window->IsSpaceOrEmpty(country) ||
						window->IsSpaceOrEmpty(city))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}


					int index = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedTypeOfCounterpartyId = adminWindow->comboBoxIdMapTypeCounterparty[index];

					Counterparty counterparty(0, nameCounterparty, phoneCounterparty, emailCounterparty, contactPerson, termsOfCooperation, country, city, selectedTypeOfCounterpartyId);

					std::vector<std::wstring> columnNames = { L"Name_Counterparty", L"Phone_Counterparty", L"Email_Counterparty", L"Contact_Person", L"Terms_Of_Cooperation", L"Country", L"City", L"TypeOfCounterparty_ID" };

					std::vector<std::wstring> values = { counterparty.getNameCounterparty(), counterparty.getPhoneCounterparty(), counterparty.getEmailCounterparty(), counterparty.getContractPerson(), counterparty.getTermsOfCooperation(), counterparty.getCountry(), counterparty.getCity(), std::to_wstring(counterparty.getTypeOfCounterpartyId())};

					adminWindow->AddRecord(L"Counterparty", columnNames, values);


					break;

				}
				case 4: {
					std::wstring deliveryNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditDeliveryNumber);
					std::wstring deliveryDate = adminWindow->GetDateFromDatePicker(adminWindow->hDPDeliveryDate);

					if (window->IsSpaceOrEmpty(deliveryNumber) ||
						window->IsSpaceOrEmpty(deliveryDate))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					int indexWarehouse = SendMessage(adminWindow->hComboBoxWarehouse, CB_GETCURSEL, 0, 0);
					if (indexWarehouse == CB_ERR) break;

					int indexDeliveryNote = SendMessage(adminWindow->hComboBoxDeliveryNote, CB_GETCURSEL, 0, 0);
					if (indexDeliveryNote == CB_ERR) break;

					int indexStatus = SendMessage(adminWindow->hComboBoxStatusDelivery, CB_GETCURSEL, 0, 0);
					if (indexStatus == CB_ERR) break;

					int selectedWarehouseId = adminWindow->comboBoxIdMapDeliveryWarehouse[indexWarehouse];
					int selectedDeliveryNoteId = adminWindow->comboBoxIdMapDeliveryNoteDelivery[indexDeliveryNote];
					int selectedStatusId = adminWindow->comboBoxIdMapStatusDelivery[indexStatus];

					Delivery delivery(0, deliveryNumber, deliveryDate, selectedWarehouseId, selectedDeliveryNoteId, selectedStatusId);

					std::vector<std::wstring> columnNames = { L"Delivery_Number", L"Delivery_Date", L"Warehouse_ID", L"DeliveryNote_ID", L"Status_ID" };

					std::vector<std::wstring> values = { delivery.getDeliveryNumber(), delivery.getDeliveryDate(), std::to_wstring(delivery.getWarehouseId()), std::to_wstring(delivery.getDeliveryNoteId()), std::to_wstring(delivery.getStatusId())};

					adminWindow->AddRecord(L"Delivery", columnNames, values);


					break;

				}
				case 5: {

					std::wstring deliveryNoteNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditDeliveryNoteNumber);
					std::wstring dateOfFormation = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfFormation);

					if (window->IsSpaceOrEmpty(deliveryNoteNumber) ||
						window->IsSpaceOrEmpty(dateOfFormation))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					int index = SendMessage(adminWindow->hComboBoxContract, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedContractId = adminWindow->comboBoxIdMapContractDeliveryNote[index];

					DeliveryNote deliveryNote(0, deliveryNoteNumber, dateOfFormation, selectedContractId);

					std::vector<std::wstring> columnNames = { L"DeliveryNote_Number", L"Date_Of_Formation", L"Contract_ID" };

					std::vector<std::wstring> values = { deliveryNote.getDeliveryNoteNumber(), deliveryNote.getDateOfFormation(), std::to_wstring(deliveryNote.getContractId())};

					adminWindow->AddRecord(L"DeliveryNote", columnNames, values);


					break;

				}
				case 6: {

					int indexRequisition = SendMessage(adminWindow->hComboBoxRequisitionPosition, CB_GETCURSEL, 0, 0);
					if (indexRequisition == CB_ERR) break;

					int indexDelivery = SendMessage(adminWindow->hComboBoxDeliveryDLPosition, CB_GETCURSEL, 0, 0);
					if (indexDelivery == CB_ERR) break;

					int selectedRequisitionId = adminWindow->comboBoxIdMapRequisitionPosition[indexRequisition];
					int selectedDeliveryId = adminWindow->comboBoxIdMapDeliveryPosition[indexDelivery];

					DeliveryPosition deliveryPosition(0, selectedRequisitionId, selectedDeliveryId);

					std::vector<std::wstring> columnNames = { L"RequisitionPosition_ID", L"Delivery_ID" };

					std::vector<std::wstring> values = { std::to_wstring(deliveryPosition.getRequisitionPositionId()), std::to_wstring(deliveryPosition.getDeliveryId()) };

					adminWindow->AddRecord(L"DeliveryPosition", columnNames, values);

					break;

				}
				case 7: {
					std::wstring surname = adminWindow->GetWindowTextAsWstring(adminWindow->hEditSurname);
					std::wstring name = adminWindow->GetWindowTextAsWstring(adminWindow->hEditName);
					std::wstring patronymic = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPatronymic);
					std::wstring email = adminWindow->GetWindowTextAsWstring(adminWindow->hEditEmail);
					std::wstring login = adminWindow->GetWindowTextAsWstring(adminWindow->hEditLogin);
					std::wstring password = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPassword);

					if (window->IsSpaceOrEmpty(surname) ||
						window->IsSpaceOrEmpty(name) ||
						window->IsSpaceOrEmpty(patronymic) ||
						window->IsSpaceOrEmpty(email) ||
						window->IsSpaceOrEmpty(login) ||
						window->IsSpaceOrEmpty(password))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					HashAndSalt hasher;

					std::string salt = hasher.CreateSalt(16);
					std::string hash = hasher.GenerateHash(window->WstrToStr(password), salt);

					int index = SendMessage(adminWindow->hComboBoxPost, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedPostId = adminWindow->comboBoxIdMapPost[index];

					Employee employee(0, surname, name, patronymic, email, login, window->StrToWstr(hash), window->StrToWstr(salt), selectedPostId);

					std::vector<std::wstring> columnNames = { L"Surname", L"Name", L"Patronymic", L"Email", L"Login_Employee", L"Password_Employee", L"Post_ID", L"Salt" };

					std::vector<std::wstring> values = { employee.getSurname(), employee.getName(), employee.getPatronymic(), employee.getEmail(), employee.getLogin(), employee.getPassword(), std::to_wstring(employee.getPostId()), employee.getSalt()};

					adminWindow->AddRecord(L"Employee", columnNames, values);



					break;


				}
				case 8: {
					std::wstring nameProduct = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameProduct);
					std::wstring purchasePrice = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPurchasePrice);
					std::wstring sellingPrice = adminWindow->GetWindowTextAsWstring(adminWindow->hEditSellingPrice);
					std::wstring article = adminWindow->GetWindowTextAsWstring(adminWindow->hEditArticle);
					std::wstring quantityOfProduct = adminWindow->GetWindowTextAsWstring(adminWindow->hEditQuantityOfProduct);
					std::wstring dateOfReceipt = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfReceipt);

					if (window->IsSpaceOrEmpty(nameProduct) ||
						window->IsSpaceOrEmpty(purchasePrice) ||
						window->IsSpaceOrEmpty(sellingPrice) ||
						window->IsSpaceOrEmpty(article) ||
						window->IsSpaceOrEmpty(quantityOfProduct) ||
						window->IsSpaceOrEmpty(dateOfReceipt))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}


					int indexCounterparty = SendMessage(adminWindow->hComboBoxCounterpartyProduct, CB_GETCURSEL, 0, 0);
					if (indexCounterparty == CB_ERR) break;

					int indexTypeProduct = SendMessage(adminWindow->hComboBoxTypeOfProduct, CB_GETCURSEL, 0, 0);
					if (indexTypeProduct == CB_ERR) break;

					int selectedCounterpartyId = adminWindow->comboBoxIdMapProductCounterparty[indexCounterparty];
					int selectedTypeProductId = adminWindow->comboBoxIdMapTypeProduct[indexTypeProduct];

					Product product(0, nameProduct, purchasePrice, sellingPrice, article, quantityOfProduct, dateOfReceipt, selectedCounterpartyId, selectedTypeProductId);

					std::vector<std::wstring> columnNames = { L"Name_Product", L"Purchase_Price", L"Selling_Price", L"Article", L"Quantity_Of_Product", L"Date_Of_Receipt", L"Counterparty_ID", L"TypeOfProduct_ID" };

					std::vector<std::wstring> values = { product.getNameProduct(), product.getPurchasePrice(), product.getSellingPrice(), product.getArticle(), product.getQuantityOfProduct(), product.getDateOfReceipt(), std::to_wstring(product.getCounterpartyId()), std::to_wstring(product.getTypeOfProduct())};

					adminWindow->AddRecord(L"Product", columnNames, values);


					break;


				}
				case 9: {
					std::wstring requestNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditRequestNumber);
					std::wstring dateOfCreation = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfCreation);
					std::wstring editCommentary = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCommentary);

					if (window->IsSpaceOrEmpty(requestNumber) ||
						window->IsSpaceOrEmpty(dateOfCreation) ||
						window->IsSpaceOrEmpty(editCommentary))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					int indexEmployee = SendMessage(adminWindow->hComboBoxEmployee, CB_GETCURSEL, 0, 0);
					if (indexEmployee == CB_ERR) break;

					int indexCounterparty = SendMessage(adminWindow->hComboBoxCounterparty, CB_GETCURSEL, 0, 0);
					if (indexCounterparty == CB_ERR) break;

					int selectedEmployeeId = adminWindow->comboBoxIdMapOrderRequestEmployee[indexEmployee];
					int selectedCounterpartyId = adminWindow->comboBoxIdMapOrderRequestCounterparty[indexCounterparty];

					ProductOrderRequest productOrderRequest(0, requestNumber, dateOfCreation, selectedEmployeeId, editCommentary, selectedCounterpartyId);

					std::vector<std::wstring> columnNames = { L"Request_Number", L"Date_Of_Creation", L"Employee_ID", L"Commentary", L"Counterparty_ID" };

					std::vector<std::wstring> values = { productOrderRequest.getRequestNumber(), productOrderRequest.getDateOfCreation(), std::to_wstring(productOrderRequest.getEmployeeId()), productOrderRequest.getCommentary(), std::to_wstring(productOrderRequest.getCounterpartyId())};

					adminWindow->AddRecord(L"ProductOrderRequest", columnNames, values);


					break;


				}
				case 10: {
					std::wstring positionNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPositionNumber);
					std::wstring quantityOfProductInRequisition = adminWindow->GetWindowTextAsWstring(adminWindow->hEditQuantityOfProductInRequisition);
					std::wstring unitPrice = adminWindow->GetWindowTextAsWstring(adminWindow->hEditUnitPrice);


					if (window->IsSpaceOrEmpty(positionNumber) ||
						window->IsSpaceOrEmpty(quantityOfProductInRequisition) ||
						window->IsSpaceOrEmpty(unitPrice))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					int indexProduct = SendMessage(adminWindow->hComboBoxProduct, CB_GETCURSEL, 0, 0);
					if (indexProduct == CB_ERR) break;

					int indexOrderRequest = SendMessage(adminWindow->hComboBoxProductOrderRequest, CB_GETCURSEL, 0, 0);
					if (indexOrderRequest == CB_ERR) break;

					int selectedProductId = adminWindow->comboBoxIdMapProduct[indexProduct];
					int selectedOrderRequestId = adminWindow->comboBoxIdMapProductOrderRequest[indexOrderRequest];

					RequisitionPosition requisitionPosition(0, positionNumber, selectedProductId, selectedOrderRequestId, quantityOfProductInRequisition, unitPrice);

					std::vector<std::wstring> columnNames = { L"Position_Number", L"Product_ID", L"ProductOrderRequest_ID", L"Quantity_Of_Product_In_Requisition", L"Unit_Price" };

					std::vector<std::wstring> values = { requisitionPosition.getPositionNumber(), std::to_wstring(requisitionPosition.getProductId()), std::to_wstring(requisitionPosition.getProductOrderRequestId()), requisitionPosition.getQuantityOfProductInRequisition(), requisitionPosition.getUnitPrice()};

					adminWindow->AddRecord(L"RequisitionPosition", columnNames, values);


					break;


				}
				case 11: {
					std::wstring nameStatus = adminWindow->GetWindowTextAsWstring(adminWindow->hEditStatus);
					if (window->IsSpaceOrEmpty(nameStatus))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					Status status(0, nameStatus);
					std::vector<std::wstring> columnNames = { L"Name_Status" };
					std::vector<std::wstring> values = { status.getNameStatus()};

					

					adminWindow->AddRecord(L"Status_", columnNames, values);

					break;
				}
				case 12: {
					std::wstring nameTypeOfProduct = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameTypeOfProduct);

					if (window->IsSpaceOrEmpty(nameTypeOfProduct))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					TypeOfProduct typeOfProduct(0, nameTypeOfProduct);
					std::vector<std::wstring> columnNames = { L"Name_Type_Of_Product" };
					std::vector<std::wstring> values = { typeOfProduct.getNameTypeOfProduct()};

					

					adminWindow->AddRecord(L"TypeOfProduct", columnNames, values);

					break;
				}
				case 13: {

					std::wstring warehouseNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditWarehouseNumber);
					std::wstring warehouseAddress = adminWindow->GetWindowTextAsWstring(adminWindow->hEditWarehouseAddress);
					std::wstring warehouseCapacity = adminWindow->GetWindowTextAsWstring(adminWindow->hEditWarehouseCapacity);
					std::wstring currentWarehouseLoad = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCurrentWarehouseLoad);

					if (window->IsSpaceOrEmpty(warehouseNumber) ||
						window->IsSpaceOrEmpty(warehouseAddress) ||
						window->IsSpaceOrEmpty(warehouseCapacity) ||
						window->IsSpaceOrEmpty(currentWarehouseLoad))
					{
						MessageBox(hwnd, L"Все поля должны быть заполнены и не содержать только пробелы!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					Warehouse warehouse(0, warehouseNumber, warehouseAddress, warehouseCapacity, currentWarehouseLoad);

					std::vector<std::wstring> columnNames = { L"Warehouse_Number", L"Warehouse_Address", L"Warehouse_Capacity", L"Current_Warehouse_Load" };

					std::vector<std::wstring> values = { warehouse.getWarehouseNumber(), warehouse.getWarehouseAddress(), warehouse.getWarehouseCapacity(), warehouse.getCurrentWarehouseLoad()};

					adminWindow->AddRecord(L"Warehouse", columnNames, values);

					break;

				}
				default:
					break;
				}

			}
			else if (controlId == AdminWindow::IDC_EDIT) {

				switch (tab)
				{
				case 0: {
					std::wstring namePost = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNamePost);
					std::wstring idPostStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdPost);
					int idPost = _wtoi(idPostStr.c_str());

					Post post(idPost, namePost);

					std::vector<std::wstring> columnNames = { L"Name_Post" };
					std::vector<std::wstring> values = { post.getNamePost() };


					if (window->IsSpaceOrEmpty(idPostStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {
						
						std::wstring query = L"select Name_Post from Post where ID_Post = '" + idPostStr;
						query += L"'";

						if (window->IsSpaceOrEmpty(namePost)) {

							std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);
							namePost = result[0][0];
							values = { namePost };

						}

						adminWindow->UpdateRecord(L"Post", columnNames, values, post.getIdPost());
					}

					break;
				}

				case 1: {
					std::wstring nameTypeOfCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameTypeOfCounterparty);
					std::wstring idTypeCounterpartyStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdTypeOfCounterparty);
					int id = _wtoi(idTypeCounterpartyStr.c_str());


					TypeOfCounterparty typeOfCounterparty(id, nameTypeOfCounterparty);

					std::vector<std::wstring> columnNames = { L"Name_Type_Of_Counterparty" };
					std::vector<std::wstring> values = { typeOfCounterparty.getNameTypeOfCounterparty() };


					if (window->IsSpaceOrEmpty(idTypeCounterpartyStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {
						std::wstring query = L"select Name_Type_Of_Counterparty from TypeOfCounterparty where ID_Type_Of_Counterparty = '" + idTypeCounterpartyStr;
						query += L"'";

						if (window->IsSpaceOrEmpty(nameTypeOfCounterparty)) {

							std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);
							nameTypeOfCounterparty = result[0][0];
							values = { nameTypeOfCounterparty };

						}
						adminWindow->UpdateRecord(L"TypeOfCounterparty", columnNames, values, typeOfCounterparty.getIdTypeOfCounterparty());

					}

					break;
				}
				case 2: {

					std::wstring contractNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContractNumber);
					std::wstring startDateContract = adminWindow->GetDateFromDatePicker(adminWindow->hDPStartDateContract);
					std::wstring endDateContract = adminWindow->GetDateFromDatePicker(adminWindow->hDPEndDateContract);
					std::wstring contractTerms = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContractTerms);

					std::wstring idContractStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdContract);

					int index = SendMessage(adminWindow->hComboBoxStatus, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedStatusContractId = adminWindow->comboBoxIdMapStatusContract[index];

					
					int id = _wtoi(idContractStr.c_str());

					Contract contract(id, contractNumber, startDateContract, endDateContract, contractTerms, selectedStatusContractId);


					std::vector<std::wstring> columnNames = { L"Contract_Number", L"Start_Date_Contract", L"End_Date_Contract", L"Contract_Terms", L"Status_ID" };

					std::vector<std::wstring> values = { contract.getContractNumber(), contract.getStartDataContract(), contract.getEndDateContract(), contract.getContractTerms(), std::to_wstring(contract.getStatusId()) };

					
					if (window->IsSpaceOrEmpty(idContractStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {


						std::wstring query = L"select Contract_Number, Start_Date_Contract, End_Date_Contract, Contract_Terms from Contract_ where ID_Contract = '" + idContractStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);


						if (window->IsSpaceOrEmpty(contractNumber)) contractNumber = result[0][0];
						if(window->IsSpaceOrEmpty(contractTerms)) contractTerms = result[0][3];
						startDateContract = result[0][1];
						endDateContract = result[0][2];
						values = { contractNumber, startDateContract, endDateContract, contractTerms, std::to_wstring(selectedStatusContractId) };
						adminWindow->UpdateRecord(L"Contract_", columnNames, values, contract.getIdContract());

					}

					break;

				}
				case 3: {
					std::wstring nameCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameCounterparty);
					std::wstring phoneCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPhoneCounterparty);
					std::wstring emailCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditEmailCounterparty);
					std::wstring contactPerson = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContactPerson);
					std::wstring termsOfCooperation = adminWindow->GetWindowTextAsWstring(adminWindow->hEditTermsOfCooperation);
					std::wstring country = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCountry);
					std::wstring city = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCity);

					std::wstring idCounterpartyStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdCounterparty);

					int id = _wtoi(idCounterpartyStr.c_str());

					int index = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedTypeOfCounterpartyId = adminWindow->comboBoxIdMapStatusContract[index];

					Counterparty counterparty(id, nameCounterparty, phoneCounterparty, emailCounterparty, contactPerson, termsOfCooperation, country, city, selectedTypeOfCounterpartyId);

					std::vector<std::wstring> columnNames = { L"Name_Counterparty", L"Phone_Counterparty", L"Email_Counterparty", L"Contact_Person", L"Terms_Of_Cooperation", L"Country", L"City", L"TypeOfCounterparty_ID" };

					std::vector<std::wstring> values = { counterparty.getNameCounterparty(), counterparty.getPhoneCounterparty(), counterparty.getEmailCounterparty(), counterparty.getContractPerson(), counterparty.getTermsOfCooperation(), counterparty.getCountry(), counterparty.getCity(), std::to_wstring(counterparty.getTypeOfCounterpartyId()) };


					if (window->IsSpaceOrEmpty(idCounterpartyStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {
						

						std::wstring query = L"select Name_Counterparty, Phone_Counterparty, Email_Counterparty, Contact_Person, Terms_Of_Cooperation, Country, City from Counterparty where ID_Counterparty = '" + idCounterpartyStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);


						if (window->IsSpaceOrEmpty(nameCounterparty)) nameCounterparty = result[0][0];
						if (window->IsSpaceOrEmpty(phoneCounterparty)) phoneCounterparty = result[0][1];
						if (window->IsSpaceOrEmpty(emailCounterparty)) emailCounterparty = result[0][2];
						if (window->IsSpaceOrEmpty(contactPerson)) contactPerson = result[0][3];
						if (window->IsSpaceOrEmpty(termsOfCooperation)) phoneCounterparty = result[0][4];
						if (window->IsSpaceOrEmpty(country)) country = result[0][5];						
						if (window->IsSpaceOrEmpty(city)) city = result[0][6];



						
						adminWindow->UpdateRecord(L"Counterparty", columnNames, values, counterparty.getIdCounterparty());

					}

					break;

				}
				case 4: {
					std::wstring deliveryNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameCounterparty);
					std::wstring deliveryDate = adminWindow->GetDateFromDatePicker(adminWindow->hDPStartDateContract);

					std::wstring idDeliveryStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDelivery);
					int id = _wtoi(idDeliveryStr.c_str());

					int indexWarehouse = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (indexWarehouse == CB_ERR) break;

					int indexDeliveryNote = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (indexDeliveryNote == CB_ERR) break;

					int indexStatus = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (indexStatus == CB_ERR) break;

					int selectedWarehouseId = adminWindow->comboBoxIdMapDeliveryWarehouse[indexWarehouse];
					int selectedDeliveryNoteId = adminWindow->comboBoxIdMapDeliveryNoteDelivery[indexDeliveryNote];
					int selectedStatusId = adminWindow->comboBoxIdMapStatusDelivery[indexStatus];

					Delivery delivery(id, deliveryNumber, deliveryDate, selectedWarehouseId, selectedDeliveryNoteId, selectedStatusId);

					std::vector<std::wstring> columnNames = { L"Delivery_Number", L"Delivery_Date", L"Warehouse_ID", L"DeliveryNote_ID", L"Status_ID" };

					std::vector<std::wstring> values = { delivery.getDeliveryNumber(), delivery.getDeliveryDate(), std::to_wstring(delivery.getWarehouseId()), std::to_wstring(delivery.getDeliveryNoteId()), std::to_wstring(delivery.getStatusId()) };

					
					if (window->IsSpaceOrEmpty(idDeliveryStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					else {


						std::wstring query = L"select Delivery_Number, Delivery_Date from Delivery where ID_Delivery = '" + idDeliveryStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);
						
						if (window->IsSpaceOrEmpty(deliveryNumber)) deliveryNumber = result[0][0];
						deliveryDate = result[0][1];
						
						adminWindow->UpdateRecord(L"Delivery", columnNames, values, delivery.getIdDelivery());
					}


					break;

				}
				case 5: {

					std::wstring deliveryNoteNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditDeliveryNoteNumber);
					std::wstring dateOfFormation = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfFormation);

					std::wstring idDeliveryNoteStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDeliveryNote);
					int id = _wtoi(idDeliveryNoteStr.c_str());

					int index = SendMessage(adminWindow->hComboBoxContract, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedContractId = adminWindow->comboBoxIdMapContractDeliveryNote[index];

					DeliveryNote deliveryNote(id, deliveryNoteNumber, dateOfFormation, selectedContractId);

					std::vector<std::wstring> columnNames = { L"DeliveryNote_Number", L"Date_Of_Formation", L"Contract_ID" };

					std::vector<std::wstring> values = { deliveryNote.getDeliveryNoteNumber(), deliveryNote.getDateOfFormation(), std::to_wstring(deliveryNote.getContractId()) };


					
					if (window->IsSpaceOrEmpty(idDeliveryNoteStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {
						
						std::wstring query = L"select DeliveryNote_Number, Date_Of_Formation from DeliveryNote where ID_DeliveryNote = '" + idDeliveryNoteStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);

						
						if (window->IsSpaceOrEmpty(deliveryNoteNumber)) deliveryNoteNumber = result[0][0];
						dateOfFormation = result[0][1];

						
						adminWindow->UpdateRecord(L"DeliveryNote", columnNames, values, deliveryNote.getIdDeliveryNote());
					}

					break;

				}
				case 6: {

					std::wstring idDeliveryPositionStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDeliveryPosition);

					int id = _wtoi(idDeliveryPositionStr.c_str());

					int indexRequisition = SendMessage(adminWindow->hComboBoxRequisitionPosition, CB_GETCURSEL, 0, 0);
					if (indexRequisition == CB_ERR) break;

					int indexDelivery = SendMessage(adminWindow->hComboBoxDeliveryDLPosition, CB_GETCURSEL, 0, 0);
					if (indexDelivery == CB_ERR) break;

					int selectedRequisitionId = adminWindow->comboBoxIdMapRequisitionPosition[indexRequisition];
					int selectedDeliveryId = adminWindow->comboBoxIdMapDeliveryPosition[indexDelivery];

					DeliveryPosition deliveryPosition(id, selectedRequisitionId, selectedDeliveryId);

					std::vector<std::wstring> columnNames = { L"RequisitionPosition_ID", L"Delivery_ID" };

					std::vector<std::wstring> values = { std::to_wstring(deliveryPosition.getRequisitionPositionId()), std::to_wstring(deliveryPosition.getDeliveryId()) };


					if (window->IsSpaceOrEmpty(idDeliveryPositionStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {
						
						adminWindow->UpdateRecord(L"DeliveryPosition", columnNames, values, deliveryPosition.getIdDeliveryPosition());

					}

					break;

				}
				case 7: {
					std::wstring surname = adminWindow->GetWindowTextAsWstring(adminWindow->hEditSurname);
					std::wstring name = adminWindow->GetWindowTextAsWstring(adminWindow->hEditName);
					std::wstring patronymic = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPatronymic);
					std::wstring email = adminWindow->GetWindowTextAsWstring(adminWindow->hEditEmail);
					std::wstring login = adminWindow->GetWindowTextAsWstring(adminWindow->hEditLogin);
					std::wstring password = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPassword);

					std::wstring idEmployeeStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdEmployee);

					int id = _wtoi(idEmployeeStr.c_str());

					int index = SendMessage(adminWindow->hComboBoxPost, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedPostId = adminWindow->comboBoxIdMapPost[index];



					if (window->IsSpaceOrEmpty(idEmployeeStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {
						
						std::wstring query = L"select Surname, Name, Patronymic, Email, Login_Employee, Password_Employee from Employee where ID_Employee = '" + idEmployeeStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);


						if (window->IsSpaceOrEmpty(surname)) surname = result[0][0];
						if (window->IsSpaceOrEmpty(name)) name = result[0][1];
						if (window->IsSpaceOrEmpty(patronymic)) patronymic = result[0][2];
						if (window->IsSpaceOrEmpty(email)) email = result[0][3];
						if (window->IsSpaceOrEmpty(login)) login = result[0][4];
						if (window->IsSpaceOrEmpty(password)) password = result[0][5];



						std::vector<std::wstring> columnNames = { L"Surname", L"Name", L"Patronymic", L"Email", L"Login_Employee", L"Password_Employee", L"Post_ID" };

						std::vector<std::wstring> values = { surname, name, patronymic, email, login, password, std::to_wstring(selectedPostId) };

						adminWindow->UpdateRecord(L"Employee", columnNames, values, id);
					}


					break;


				}
				case 8: {
					std::wstring nameProduct = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameProduct);
					std::wstring purchasePrice = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPurchasePrice);
					std::wstring sellingPrice = adminWindow->GetWindowTextAsWstring(adminWindow->hEditSellingPrice);
					std::wstring article = adminWindow->GetWindowTextAsWstring(adminWindow->hEditArticle);
					std::wstring quantityOfProduct = adminWindow->GetWindowTextAsWstring(adminWindow->hEditQuantityOfProduct);
					std::wstring dateOfReceipt = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfReceipt);
					std::wstring idProductStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdProduct);
					int id = _wtoi(idProductStr.c_str());

					int indexCounterparty = SendMessage(adminWindow->hComboBoxCounterpartyProduct, CB_GETCURSEL, 0, 0);
					if (indexCounterparty == CB_ERR) break;

					int indexTypeProduct = SendMessage(adminWindow->hComboBoxTypeOfProduct, CB_GETCURSEL, 0, 0);
					if (indexTypeProduct == CB_ERR) break;

					int selectedCounterpartyId = adminWindow->comboBoxIdMapProductCounterparty[indexCounterparty];
					int selectedTypeProductId = adminWindow->comboBoxIdMapTypeProduct[indexTypeProduct];

					Product product(id, nameProduct, purchasePrice, sellingPrice, article, quantityOfProduct, dateOfReceipt, selectedCounterpartyId, selectedTypeProductId);

					std::vector<std::wstring> columnNames = { L"Name_Product", L"Purchase_Price", L"Selling_Price", L"Article", L"Quantity_Of_Product", L"Date_Of_Receipt", L"Counterparty_ID", L"TypeOfProduct_ID" };

					std::vector<std::wstring> values = { product.getNameProduct(), product.getPurchasePrice(), product.getSellingPrice(), product.getArticle(), product.getQuantityOfProduct(), product.getDateOfReceipt(), std::to_wstring(product.getCounterpartyId()), std::to_wstring(product.getTypeOfProduct()) };


					if (window->IsSpaceOrEmpty(idProductStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {

						std::wstring query = L"select Name_Product, Purchase_Price, Selling_Price, Article, Quantity_Of_Product, Date_Of_Receipt from Product where ID_Product = '" + idProductStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);

						

						if (window->IsSpaceOrEmpty(nameProduct)) nameProduct = result[0][0];
						if (window->IsSpaceOrEmpty(purchasePrice)) purchasePrice = result[0][1];
						if (window->IsSpaceOrEmpty(sellingPrice)) sellingPrice = result[0][2];
						if (window->IsSpaceOrEmpty(article)) article = result[0][3];
						if (window->IsSpaceOrEmpty(quantityOfProduct)) quantityOfProduct = result[0][4];
						dateOfReceipt = result[0][5];

						adminWindow->UpdateRecord(L"Product", columnNames, values, product.getIdProduct());

					}

					break;


				}
				case 9: {
					std::wstring requestNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditRequestNumber);
					std::wstring dateOfCreation = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfCreation);
					std::wstring editCommentary = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCommentary);

					std::wstring idProductOrderRequestStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdProductOrderRequest);

					int id = _wtoi(idProductOrderRequestStr.c_str());


					int indexEmployee = SendMessage(adminWindow->hComboBoxEmployee, CB_GETCURSEL, 0, 0);
					if (indexEmployee == CB_ERR) break;

					int indexCounterparty = SendMessage(adminWindow->hComboBoxCounterparty, CB_GETCURSEL, 0, 0);
					if (indexCounterparty == CB_ERR) break;

					int selectedEmployeeId = adminWindow->comboBoxIdMapOrderRequestEmployee[indexEmployee];
					int selectedCounterpartyId = adminWindow->comboBoxIdMapOrderRequestCounterparty[indexCounterparty];


					ProductOrderRequest productOrderRequest(id, requestNumber, dateOfCreation, selectedEmployeeId, editCommentary, selectedCounterpartyId);

					std::vector<std::wstring> columnNames = { L"Request_Number", L"Date_Of_Creation", L"Employee_ID", L"Commentary", L"Counterparty_ID" };

					std::vector<std::wstring> values = { productOrderRequest.getRequestNumber(), productOrderRequest.getDateOfCreation(), std::to_wstring(productOrderRequest.getEmployeeId()), productOrderRequest.getCommentary(), std::to_wstring(productOrderRequest.getCounterpartyId()) };



					if (window->IsSpaceOrEmpty(idProductOrderRequestStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {
						std::wstring query = L"select Request_Number, Date_Of_Creation, Commentary from ProductOrderRequest where ID_ProductOrderRequest = '" + idProductOrderRequestStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);



						if (window->IsSpaceOrEmpty(requestNumber)) requestNumber = result[0][0];
						if (window->IsSpaceOrEmpty(editCommentary)) editCommentary = result[0][2];
						dateOfCreation = result[0][1];

						
						adminWindow->UpdateRecord(L"ProductOrderRequest", columnNames, values, productOrderRequest.getIdProductOrderRequest());

					}

					break;


				}
				case 10: {
					std::wstring positionNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPositionNumber);
					std::wstring quantityOfProductInRequisition = adminWindow->GetDateFromDatePicker(adminWindow->hEditQuantityOfProductInRequisition);
					std::wstring unitPrice = adminWindow->GetWindowTextAsWstring(adminWindow->hEditUnitPrice);

					std::wstring idRequisitionPosStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdRequisitionPosition);

					int id = _wtoi(idRequisitionPosStr.c_str());

					int indexProduct = SendMessage(adminWindow->hComboBoxProduct, CB_GETCURSEL, 0, 0);
					if (indexProduct == CB_ERR) break;

					int indexOrderRequest = SendMessage(adminWindow->hComboBoxProductOrderRequest, CB_GETCURSEL, 0, 0);
					if (indexOrderRequest == CB_ERR) break;

					int selectedProductId = adminWindow->comboBoxIdMapProduct[indexProduct];
					int selectedOrderRequestId = adminWindow->comboBoxIdMapProductOrderRequest[indexOrderRequest];

					RequisitionPosition requisitionPosition(id, positionNumber, selectedProductId, selectedOrderRequestId, quantityOfProductInRequisition, unitPrice);

					std::vector<std::wstring> columnNames = { L"Position_Number", L"Product_ID", L"ProductOrderRequest_ID", L"Quantity_Of_Product_In_Requisition", L"Unit_Price" };

					std::vector<std::wstring> values = { requisitionPosition.getPositionNumber(), std::to_wstring(requisitionPosition.getProductId()), std::to_wstring(requisitionPosition.getProductOrderRequestId()), requisitionPosition.getQuantityOfProductInRequisition(), requisitionPosition.getUnitPrice() };


					if (window->IsSpaceOrEmpty(idRequisitionPosStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {
						

						std::wstring query = L"select Position_Number, Quantity_Of_Product_In_Requisition, Unit_Price from RequisitionPosition where ID_RequisitionPosition = '" + idRequisitionPosStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);


						if (window->IsSpaceOrEmpty(positionNumber)) positionNumber = result[0][0];
						if (window->IsSpaceOrEmpty(quantityOfProductInRequisition)) quantityOfProductInRequisition = result[0][1];
						if (window->IsSpaceOrEmpty(unitPrice)) unitPrice = result[0][2];

						adminWindow->UpdateRecord(L"RequisitionPosition", columnNames, values, requisitionPosition.getIdRequisitionPosition());

					}

					break;


				}
				case 11: {
					std::wstring nameStatus = adminWindow->GetWindowTextAsWstring(adminWindow->hEditStatus);
					

					std::wstring idStatusStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdStatus);
					int id = _wtoi(idStatusStr.c_str());

					Status status(id, nameStatus);
					std::vector<std::wstring> columnNames = { L"Name_Status" };
					std::vector<std::wstring> values = { status.getNameStatus() };


					if (window->IsSpaceOrEmpty(idStatusStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {

						std::wstring query = L"select Name_Status from Status_ where ID_Status = '" + idStatusStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);


						if (window->IsSpaceOrEmpty(nameStatus)) nameStatus = result[0][0];
					
						adminWindow->UpdateRecord(L"Status_", columnNames, values, status.getIdStatus());

					}

					break;
				}
				case 12: {
					std::wstring nameTypeOfProduct = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameTypeOfProduct);
					
					std::wstring idTypeOfProductStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdTypeOfProduct);

					int id = _wtoi(idTypeOfProductStr.c_str());

					TypeOfProduct typeOfProduct(id, nameTypeOfProduct);
					std::vector<std::wstring> columnNames = { L"Name_Type_Of_Product" };
					std::vector<std::wstring> values = { typeOfProduct.getNameTypeOfProduct() };


					if (window->IsSpaceOrEmpty(idTypeOfProductStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {

						std::wstring query = L"select Name_Type_Of_Product from TypeOfProduct where ID_Type_Of_Product = '" + idTypeOfProductStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);


						if (window->IsSpaceOrEmpty(nameTypeOfProduct)) nameTypeOfProduct = result[0][0];
						
						adminWindow->UpdateRecord(L"TypeOfProduct", columnNames, values, typeOfProduct.getIdTypeOfProduct());

					}

					break;
				}
				case 13: {

					std::wstring warehouseNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditWarehouseNumber);
					std::wstring warehouseAddress = adminWindow->GetDateFromDatePicker(adminWindow->hEditWarehouseAddress);
					std::wstring warehouseCapacity = adminWindow->GetDateFromDatePicker(adminWindow->hEditWarehouseCapacity);
					std::wstring currentWarehouseLoad = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCurrentWarehouseLoad);

					std::wstring idWarehouseStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdWarehouse);

					int id = _wtoi(idWarehouseStr.c_str());


					Warehouse warehouse(id, warehouseNumber, warehouseAddress, warehouseCapacity, currentWarehouseLoad);

					std::vector<std::wstring> columnNames = { L"Warehouse_Number", L"Warehouse_Address", L"Warehouse_Capacity", L"Current_Warehouse_Load" };

					std::vector<std::wstring> values = { warehouse.getWarehouseNumber(), warehouse.getWarehouseAddress(), warehouse.getWarehouseCapacity(), warehouse.getCurrentWarehouseLoad() };


					if (window->IsSpaceOrEmpty(idWarehouseStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					else {

						std::wstring query = L"select Warehouse_Number, Warehouse_Address, Warehouse_Capacity, Current_Warehouse_Load from Warehouse where ID_Warehouse = '" + idWarehouseStr;
						query += L"'";
						std::vector<std::vector<std::wstring>> result = adminWindow->dbManager.ExecuteQuery(query);


						if (window->IsSpaceOrEmpty(warehouseNumber)) warehouseNumber = result[0][0];
						if (window->IsSpaceOrEmpty(warehouseAddress)) warehouseAddress = result[0][1];
						if (window->IsSpaceOrEmpty(warehouseCapacity)) warehouseCapacity = result[0][2];
						if (window->IsSpaceOrEmpty(currentWarehouseLoad)) currentWarehouseLoad = result[0][3];


						adminWindow->UpdateRecord(L"Warehouse", columnNames, values, warehouse.getIdWarehouse());
					}

					break;

				}

				default:
					break;
				}
			}
			else if (controlId == AdminWindow::IDC_DELETE) {
				switch (tab) {
				case 0: {
					std::wstring idPostStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdPost);

					int idPost = _wtoi(idPostStr.c_str());
					if (window->IsSpaceOrEmpty(idPostStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					adminWindow->DeleteRecord(L"Post", idPost);

					break;
				}

				case 1: {

					std::wstring idTypeCounterpartyStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdTypeOfCounterparty);
					int id = _wtoi(idTypeCounterpartyStr.c_str());
					if (window->IsSpaceOrEmpty(idTypeCounterpartyStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"TypeOfCounterparty", id);

					break;
				}case 2: {


					std::wstring idContractStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdContract);
					int id = _wtoi(idContractStr.c_str());
					if (window->IsSpaceOrEmpty(idContractStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					adminWindow->DeleteRecord(L"Contract_", id);

					break;

				}
				case 3: {

					std::wstring idCounterpartyStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdCounterparty);
					int id = _wtoi(idCounterpartyStr.c_str());
					if (window->IsSpaceOrEmpty(idCounterpartyStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"Counterparty", id);

					break;

				}
				case 4: {

					std::wstring idDeliveryStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDelivery);
					int id = _wtoi(idDeliveryStr.c_str());
					if (window->IsSpaceOrEmpty(idDeliveryStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"Delivery", id);

					break;

				}
				case 5: {

					std::wstring idDeliveryNoteStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDeliveryNote);
					int id = _wtoi(idDeliveryNoteStr.c_str());
					if (window->IsSpaceOrEmpty(idDeliveryNoteStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"DeliveryNote", id);

					break;

				}
				case 6: {

					std::wstring idDeliveryPositionStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDeliveryPosition);
					int id = _wtoi(idDeliveryPositionStr.c_str());
					if (window->IsSpaceOrEmpty(idDeliveryPositionStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"DeliveryPosition", id);

					break;

				}
				case 7: {

					std::wstring idEmployeeStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdEmployee);
					int id = _wtoi(idEmployeeStr.c_str());
					if (window->IsSpaceOrEmpty(idEmployeeStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"Employee", id);

					break;


				}
				case 8: {

					std::wstring idProductStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdProduct);
					int id = _wtoi(idProductStr.c_str());
					if (window->IsSpaceOrEmpty(idProductStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"Product", id);

					break;


				}
				case 9: {

					std::wstring idProductOrderRequestStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdProductOrderRequest);
					int id = _wtoi(idProductOrderRequestStr.c_str());
					if (window->IsSpaceOrEmpty(idProductOrderRequestStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}

					adminWindow->DeleteRecord(L"ProductOrderRequest", id);

					break;


				}
				case 10: {

					std::wstring idRequisitionPosStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdRequisitionPosition);
					int id = _wtoi(idRequisitionPosStr.c_str());
					if (window->IsSpaceOrEmpty(idRequisitionPosStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"RequisitionPosition", id);

					break;


				}
				case 11: {

					std::wstring idStatusStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdStatus);
					int id = _wtoi(idStatusStr.c_str());
					if (window->IsSpaceOrEmpty(idStatusStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"Status_", id);



					break;
				}
				case 12: {

					std::wstring idTypeOfProductStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdTypeOfProduct);
					int id = _wtoi(idTypeOfProductStr.c_str());
					if (window->IsSpaceOrEmpty(idTypeOfProductStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"TypeOfProduct", id);

					break;
				}
				case 13: {


					std::wstring idWarehouseStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdWarehouse);
					int id = _wtoi(idWarehouseStr.c_str());
					if (window->IsSpaceOrEmpty(idWarehouseStr)) {
						MessageBox(hwnd, L"Поле не должно быть пустым или состоять из пробелов!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					adminWindow->DeleteRecord(L"Warehouse", id);

					break;
				}

				}
			}

			break;


		}
		case WindowTypes::WAREHOUSE_WORKER_WINDOW: {
			WarehouseWorkerWindow* warehouseWorker = static_cast<WarehouseWorkerWindow*>(window);
			int controlId = LOWORD(wParam);

			if (controlId == WarehouseWorkerWindow::IDC_BTN_SHOW_ALL_DELIVERY) {
				warehouseWorker->DrawTableAllDelivery();
			}
			else if (controlId == WarehouseWorkerWindow::IDC_BTN_SHOW_DELIVERY_POSITION) {

				int index = SendMessage(warehouseWorker->hComboBoxNumberDelivery, CB_GETCURSEL, 0, 0);
				if (index == CB_ERR) break;

				int selectedDeliveryId = warehouseWorker->comboBoxIdMap[index];

				std::wstring deliveryId = std::to_wstring(selectedDeliveryId);

				warehouseWorker->DrawTableDeliveryPosition(deliveryId);
			}
			else if (controlId == WarehouseWorkerWindow::IDC_BTN_CONFIRM_DELIVERY) {


				warehouseWorker->ConfirmDelivery(warehouseWorker->currentDeliveryNumberFilter);
			}

			else if (controlId == WarehouseWorkerWindow::IDC_EXIT_WORKER) {
				Authorization* authorization = new Authorization(warehouseWorker->dbManager);
				warehouseWorker->DestroyElementsView();
				window = authorization;
				authorization->CreateAuthorizationWindow(hwnd, L"Окно авторизации", GetModuleHandle(NULL));
			}
		}
			
			break;

		}


		break;


	}
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;

	}
	return 0;
}


