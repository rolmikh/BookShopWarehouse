#include "BaseWindow.h"
#include "AdminWindow.h"
#include "Authorization.h"
#pragma comment(lib, "comctl32.lib")


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
	SendMessage(hComboBox, CB_SETITEMHEIGHT, static_cast<WPARAM>(-1), MAKELPARAM(40, 0));

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

	SendMessage(hDatePicker, WM_SETFONT, (WPARAM)hFont, TRUE);

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

			break;
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


			else if (controlId == AdminWindow::IDC_ADD) {

				switch (tab)
				{
				case 0: {
					std::wstring namePost = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNamePost);
					std::vector<std::wstring> columnNames = { L"Name_Post" };
					std::vector<std::wstring> values = { namePost };

					adminWindow->AddRecord(L"Post", columnNames, values);

					break;
				}
				case 1: {
					std::wstring nameTypeOfCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameTypeOfCounterparty);
					std::vector<std::wstring> columnNames = { L"Name_Type_Of_Counterparty" };
					std::vector<std::wstring> values = { nameTypeOfCounterparty };

					adminWindow->AddRecord(L"TypeOfCounterparty", columnNames, values);

					break;
				}
				case 2: {

					std::wstring contractNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContractNumber);
					std::wstring startDateContract = adminWindow->GetDateFromDatePicker(adminWindow->hDPStartDateContract);
					std::wstring endDateContract = adminWindow->GetDateFromDatePicker(adminWindow->hDPEndDateContract);
					std::wstring contractTerms = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContractTerms);

					int index = SendMessage(adminWindow->hComboBoxStatus, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedStatusContractId = adminWindow->comboBoxIdMap[index];

					std::vector<std::wstring> columnNames = { L"Contract_Number", L"Start_Date_Contract", L"End_Date_Contract", L"Contract_Terms", L"Status_ID" };

					std::vector<std::wstring> values = { contractNumber, startDateContract, endDateContract, contractTerms, std::to_wstring(selectedStatusContractId) };

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

					int index = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedTypeOfCounterpartyId = adminWindow->comboBoxIdMap[index];

					std::vector<std::wstring> columnNames = { L"Name_Counterparty", L"Phone_Counterparty", L"Email_Counterparty", L"Contact_Person", L"Terms_Of_Cooperation", L"Country", L"City", L"TypeOfCounterparty_ID" };

					std::vector<std::wstring> values = { nameCounterparty, phoneCounterparty, emailCounterparty, contactPerson, termsOfCooperation, country, city, std::to_wstring(selectedTypeOfCounterpartyId) };

					adminWindow->AddRecord(L"Counterparty", columnNames, values);

					break;

				}
				case 4: {
					std::wstring deliveryNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameCounterparty);
					std::wstring deliveryDate = adminWindow->GetDateFromDatePicker(adminWindow->hDPStartDateContract);

					int indexWarehouse = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (indexWarehouse == CB_ERR) break;

					int indexDeliveryNote = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (indexDeliveryNote == CB_ERR) break;

					int indexStatus = SendMessage(adminWindow->hComboBoxTypeOfCounterparty, CB_GETCURSEL, 0, 0);
					if (indexStatus == CB_ERR) break;

					int selectedWarehouseId = adminWindow->comboBoxIdMap[indexWarehouse];
					int selectedDeliveryNoteId = adminWindow->comboBoxIdMap[indexDeliveryNote];
					int selectedStatusId = adminWindow->comboBoxIdMap[indexStatus];

					std::vector<std::wstring> columnNames = { L"Delivery_Number", L"Delivery_Date", L"Warehouse_ID", L"DeliveryNote_ID", L"Status_ID" };

					std::vector<std::wstring> values = { deliveryNumber, deliveryDate, std::to_wstring(selectedWarehouseId), std::to_wstring(selectedDeliveryNoteId), std::to_wstring(selectedStatusId) };

					adminWindow->AddRecord(L"Delivery", columnNames, values);

					break;

				}
				case 5: {

					std::wstring deliveryNoteNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditDeliveryNoteNumber);
					std::wstring dateOfFormation = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfFormation);

					int index = SendMessage(adminWindow->hComboBoxContract, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedContractId = adminWindow->comboBoxIdMap[index];

					std::vector<std::wstring> columnNames = { L"DeliveryNote_Number", L"Date_Of_Formation", L"Contract_ID" };

					std::vector<std::wstring> values = { deliveryNoteNumber, dateOfFormation, std::to_wstring(selectedContractId) };

					adminWindow->AddRecord(L"DeliveryNote", columnNames, values);

					break;

				}
				case 6: {

					int indexRequisition = SendMessage(adminWindow->hComboBoxRequisitionPosition, CB_GETCURSEL, 0, 0);
					if (indexRequisition == CB_ERR) break;

					int indexDelivery = SendMessage(adminWindow->hComboBoxDeliveryDLPosition, CB_GETCURSEL, 0, 0);
					if (indexDelivery == CB_ERR) break;

					int selectedRequisitionId = adminWindow->comboBoxIdMap[indexRequisition];
					int selectedDeliveryId = adminWindow->comboBoxIdMap[indexDelivery];

					std::vector<std::wstring> columnNames = { L"RequisitionPosition_ID", L"Delivery_ID" };

					std::vector<std::wstring> values = { std::to_wstring(selectedRequisitionId), std::to_wstring(selectedDeliveryId) };

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

					HashAndSalt hasher;

					std::string salt = hasher.CreateSalt(16);
					std::string hash = hasher.GenerateHash(window->WstrToStr(password), salt);

					int index = SendMessage(adminWindow->hComboBoxPost, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedPostId = adminWindow->comboBoxIdMap[index];

					std::vector<std::wstring> columnNames = { L"Surname", L"Name", L"Patronymic", L"Email", L"Login_Employee", L"Password_Employee", L"Post_ID", L"Salt" };

					std::vector<std::wstring> values = { surname, name, patronymic, email, login, window->StrToWstr(hash), std::to_wstring(selectedPostId), window->StrToWstr(salt) };

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

					int indexCounterparty = SendMessage(adminWindow->hComboBoxCounterpartyProduct, CB_GETCURSEL, 0, 0);
					if (indexCounterparty == CB_ERR) break;

					int indexTypeProduct = SendMessage(adminWindow->hComboBoxTypeOfProduct, CB_GETCURSEL, 0, 0);
					if (indexTypeProduct == CB_ERR) break;

					int selectedCounterpartyId = adminWindow->comboBoxIdMap[indexCounterparty];
					int selectedTypeProductId = adminWindow->comboBoxIdMap[indexTypeProduct];


					std::vector<std::wstring> columnNames = { L"Name_Product", L"Purchase_Price", L"Selling_Price", L"Article", L"Quantity_Of_Product", L"Date_Of_Receipt", L"Counterparty_ID", L"TypeOfProduct_ID" };

					std::vector<std::wstring> values = { nameProduct, purchasePrice, sellingPrice, article, quantityOfProduct, dateOfReceipt, std::to_wstring(selectedCounterpartyId), std::to_wstring(selectedTypeProductId) };

					adminWindow->AddRecord(L"Product", columnNames, values);

					break;


				}
				case 9: {
					std::wstring requestNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditRequestNumber);
					std::wstring dateOfCreation = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfCreation);
					std::wstring editCommentary = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCommentary);

					int indexEmployee = SendMessage(adminWindow->hComboBoxEmployee, CB_GETCURSEL, 0, 0);
					if (indexEmployee == CB_ERR) break;

					int indexCounterparty = SendMessage(adminWindow->hComboBoxCounterparty, CB_GETCURSEL, 0, 0);
					if (indexCounterparty == CB_ERR) break;

					int selectedEmployeeId = adminWindow->comboBoxIdMap[indexEmployee];
					int selectedCounterpartyId = adminWindow->comboBoxIdMap[indexCounterparty];



					std::vector<std::wstring> columnNames = { L"Request_Number", L"Date_Of_Creation", L"Employee_ID", L"Commentary", L"Counterparty_ID" };

					std::vector<std::wstring> values = { requestNumber, dateOfCreation, std::to_wstring(selectedEmployeeId), editCommentary, std::to_wstring(selectedCounterpartyId) };

					adminWindow->AddRecord(L"ProductOrderRequest", columnNames, values);

					break;


				}
				case 10: {
					std::wstring positionNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditPositionNumber);
					std::wstring quantityOfProductInRequisition = adminWindow->GetWindowTextAsWstring(adminWindow->hEditQuantityOfProductInRequisition);
					std::wstring unitPrice = adminWindow->GetWindowTextAsWstring(adminWindow->hEditUnitPrice);

					int indexProduct = SendMessage(adminWindow->hComboBoxProduct, CB_GETCURSEL, 0, 0);
					if (indexProduct == CB_ERR) break;

					int indexOrderRequest = SendMessage(adminWindow->hComboBoxProductOrderRequest, CB_GETCURSEL, 0, 0);
					if (indexOrderRequest == CB_ERR) break;

					int selectedProductId = adminWindow->comboBoxIdMap[indexProduct];
					int selectedOrderRequestId = adminWindow->comboBoxIdMap[indexOrderRequest];



					std::vector<std::wstring> columnNames = { L"Position_Number", L"Product_ID", L"ProductOrderRequest_ID", L"Quantity_Of_Product_In_Requisition", L"Unit_Price" };

					std::vector<std::wstring> values = { positionNumber, std::to_wstring(selectedProductId), std::to_wstring(selectedOrderRequestId), quantityOfProductInRequisition, unitPrice };

					adminWindow->AddRecord(L"RequisitionPosition", columnNames, values);

					break;


				}
				case 11: {
					std::wstring status = adminWindow->GetWindowTextAsWstring(adminWindow->hEditStatus);
					std::vector<std::wstring> columnNames = { L"Name_Status" };
					std::vector<std::wstring> values = { status };

					adminWindow->AddRecord(L"Status_", columnNames, values);

					break;
				}
				case 12: {
					std::wstring nameTypeOfProduct = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameTypeOfProduct);
					std::vector<std::wstring> columnNames = { L"Name_Type_Of_Product" };
					std::vector<std::wstring> values = { nameTypeOfProduct };

					adminWindow->AddRecord(L"TypeOfProduct", columnNames, values);

					break;
				}
				case 13: {

					std::wstring warehouseNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditWarehouseNumber);
					std::wstring warehouseAddress = adminWindow->GetWindowTextAsWstring(adminWindow->hEditWarehouseAddress);
					std::wstring warehouseCapacity = adminWindow->GetWindowTextAsWstring(adminWindow->hEditWarehouseCapacity);
					std::wstring currentWarehouseLoad = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCurrentWarehouseLoad);


					std::vector<std::wstring> columnNames = { L"Warehouse_Number", L"Warehouse_Address", L"Warehouse_Capacity", L"Current_Warehouse_Load" };

					std::vector<std::wstring> values = { warehouseNumber, warehouseAddress, warehouseCapacity, currentWarehouseLoad };

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
					std::vector<std::wstring> columnNames = { L"Name_Post" };
					std::wstring idPostStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdPost);
					int idPost = _wtoi(idPostStr.c_str());
					std::vector<std::wstring> values = { namePost };

					adminWindow->UpdateRecord(L"Post", columnNames, values, idPost);


					break;
				}

				case 1: {
					std::wstring nameTypeOfCounterparty = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameTypeOfCounterparty);
					std::vector<std::wstring> columnNames = { L"Name_Type_Of_Counterparty" };
					std::vector<std::wstring> values = { nameTypeOfCounterparty };

					std::wstring idTypeCounterpartyStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdTypeOfCounterparty);
					int id = _wtoi(idTypeCounterpartyStr.c_str());

					adminWindow->UpdateRecord(L"TypeOfCounterparty", columnNames, values, id);

					break;
				}
				case 2: {

					std::wstring contractNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContractNumber);
					std::wstring startDateContract = adminWindow->GetDateFromDatePicker(adminWindow->hDPStartDateContract);
					std::wstring endDateContract = adminWindow->GetDateFromDatePicker(adminWindow->hDPEndDateContract);
					std::wstring contractTerms = adminWindow->GetWindowTextAsWstring(adminWindow->hEditContractTerms);

					std::wstring idContractStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdContract);
					int id = _wtoi(idContractStr.c_str());

					int index = SendMessage(adminWindow->hComboBoxStatus, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedStatusContractId = adminWindow->comboBoxIdMap[index];

					std::vector<std::wstring> columnNames = { L"Contract_Number", L"Start_Date_Contract", L"End_Date_Contract", L"Contract_Terms", L"Status_ID" };

					std::vector<std::wstring> values = { contractNumber, startDateContract, endDateContract, contractTerms, std::to_wstring(selectedStatusContractId) };

					adminWindow->UpdateRecord(L"Contract_", columnNames, values, id);

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

					int selectedTypeOfCounterpartyId = adminWindow->comboBoxIdMap[index];

					std::vector<std::wstring> columnNames = { L"Name_Counterparty", L"Phone_Counterparty", L"Email_Counterparty", L"Contact_Person", L"Terms_Of_Cooperation", L"Country", L"City", L"TypeOfCounterparty_ID" };

					std::vector<std::wstring> values = { nameCounterparty, phoneCounterparty, emailCounterparty, contactPerson, termsOfCooperation, country, city, std::to_wstring(selectedTypeOfCounterpartyId) };

					adminWindow->UpdateRecord(L"Counterparty", columnNames, values, id);

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

					int selectedWarehouseId = adminWindow->comboBoxIdMap[indexWarehouse];
					int selectedDeliveryNoteId = adminWindow->comboBoxIdMap[indexDeliveryNote];
					int selectedStatusId = adminWindow->comboBoxIdMap[indexStatus];

					std::vector<std::wstring> columnNames = { L"Delivery_Number", L"Delivery_Date", L"Warehouse_ID", L"DeliveryNote_ID", L"Status_ID" };

					std::vector<std::wstring> values = { deliveryNumber, deliveryDate, std::to_wstring(selectedWarehouseId), std::to_wstring(selectedDeliveryNoteId), std::to_wstring(selectedStatusId) };

					adminWindow->UpdateRecord(L"Delivery", columnNames, values, id);

					break;

				}
				case 5: {

					std::wstring deliveryNoteNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditDeliveryNoteNumber);
					std::wstring dateOfFormation = adminWindow->GetDateFromDatePicker(adminWindow->hDPDateOfFormation);

					std::wstring idDeliveryNoteStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDeliveryNote);
					int id = _wtoi(idDeliveryNoteStr.c_str());

					int index = SendMessage(adminWindow->hComboBoxContract, CB_GETCURSEL, 0, 0);
					if (index == CB_ERR) break;

					int selectedContractId = adminWindow->comboBoxIdMap[index];

					std::vector<std::wstring> columnNames = { L"DeliveryNote_Number", L"Date_Of_Formation", L"Contract_ID" };

					std::vector<std::wstring> values = { deliveryNoteNumber, dateOfFormation, std::to_wstring(selectedContractId) };

					adminWindow->UpdateRecord(L"DeliveryNote", columnNames, values, id);
					break;

				}
				case 6: {

					std::wstring idDeliveryPositionStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDeliveryPosition);
					int id = _wtoi(idDeliveryPositionStr.c_str());

					int indexRequisition = SendMessage(adminWindow->hComboBoxRequisitionPosition, CB_GETCURSEL, 0, 0);
					if (indexRequisition == CB_ERR) break;

					int indexDelivery = SendMessage(adminWindow->hComboBoxDeliveryDLPosition, CB_GETCURSEL, 0, 0);
					if (indexDelivery == CB_ERR) break;

					int selectedRequisitionId = adminWindow->comboBoxIdMap[indexRequisition];
					int selectedDeliveryId = adminWindow->comboBoxIdMap[indexDelivery];

					std::vector<std::wstring> columnNames = { L"RequisitionPosition_ID", L"Delivery_ID" };

					std::vector<std::wstring> values = { std::to_wstring(selectedRequisitionId), std::to_wstring(selectedDeliveryId) };

					adminWindow->UpdateRecord(L"DeliveryPosition", columnNames, values, id);

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

					int selectedPostId = adminWindow->comboBoxIdMap[index];

					std::vector<std::wstring> columnNames = { L"Surname", L"Name", L"Patronymic", L"Email", L"Login_Employee", L"Password_Employee", L"Post_ID" };

					std::vector<std::wstring> values = { surname, name, patronymic, email, login, password, std::to_wstring(selectedPostId) };

					adminWindow->UpdateRecord(L"Employee", columnNames, values, id);

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

					int selectedCounterpartyId = adminWindow->comboBoxIdMap[indexCounterparty];
					int selectedTypeProductId = adminWindow->comboBoxIdMap[indexTypeProduct];


					std::vector<std::wstring> columnNames = { L"Name_Product", L"Purchase_Price", L"Selling_Price", L"Article", L"Quantity_Of_Product", L"Date_Of_Receipt", L"Counterparty_ID", L"TypeOfProduct_ID" };

					std::vector<std::wstring> values = { nameProduct, purchasePrice, sellingPrice, article, quantityOfProduct, dateOfReceipt, std::to_wstring(selectedCounterpartyId), std::to_wstring(selectedTypeProductId) };

					adminWindow->UpdateRecord(L"Product", columnNames, values, id);

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

					int selectedEmployeeId = adminWindow->comboBoxIdMap[indexEmployee];
					int selectedCounterpartyId = adminWindow->comboBoxIdMap[indexCounterparty];



					std::vector<std::wstring> columnNames = { L"Request_Number", L"Date_Of_Creation", L"Employee_ID", L"Commentary", L"Counterparty_ID" };

					std::vector<std::wstring> values = { requestNumber, dateOfCreation, std::to_wstring(selectedEmployeeId), editCommentary, std::to_wstring(selectedCounterpartyId) };

					adminWindow->UpdateRecord(L"ProductOrderRequest", columnNames, values, id);

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

					int selectedProductId = adminWindow->comboBoxIdMap[indexProduct];
					int selectedOrderRequestId = adminWindow->comboBoxIdMap[indexOrderRequest];



					std::vector<std::wstring> columnNames = { L"Position_Number", L"Product_ID", L"ProductOrderRequest_ID", L"Quantity_Of_Product_In_Requisition", L"Unit_Price" };

					std::vector<std::wstring> values = { positionNumber, std::to_wstring(selectedProductId), std::to_wstring(selectedOrderRequestId), quantityOfProductInRequisition, unitPrice };

					adminWindow->UpdateRecord(L"RequisitionPosition", columnNames, values, id);

					break;


				}
				case 11: {
					std::wstring status = adminWindow->GetWindowTextAsWstring(adminWindow->hEditStatus);
					std::vector<std::wstring> columnNames = { L"Name_Status" };
					std::vector<std::wstring> values = { status };

					std::wstring idStatusStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdStatus);
					int id = _wtoi(idStatusStr.c_str());

					adminWindow->UpdateRecord(L"Status_", columnNames, values, id);

					break;
				}
				case 12: {
					std::wstring nameTypeOfProduct = adminWindow->GetWindowTextAsWstring(adminWindow->hEditNameTypeOfProduct);
					std::vector<std::wstring> columnNames = { L"Name_Type_Of_Product" };
					std::vector<std::wstring> values = { nameTypeOfProduct };

					std::wstring idTypeOfProductStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdTypeOfProduct);
					int id = _wtoi(idTypeOfProductStr.c_str());

					adminWindow->UpdateRecord(L"TypeOfProduct", columnNames, values, id);

					break;
				}
				case 13: {

					std::wstring warehouseNumber = adminWindow->GetWindowTextAsWstring(adminWindow->hEditWarehouseNumber);
					std::wstring warehouseAddress = adminWindow->GetDateFromDatePicker(adminWindow->hEditWarehouseAddress);
					std::wstring warehouseCapacity = adminWindow->GetDateFromDatePicker(adminWindow->hEditWarehouseCapacity);
					std::wstring currentWarehouseLoad = adminWindow->GetWindowTextAsWstring(adminWindow->hEditCurrentWarehouseLoad);

					std::wstring idWarehouseStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdWarehouse);
					int id = _wtoi(idWarehouseStr.c_str());

					std::vector<std::wstring> columnNames = { L"Warehouse_Number", L"Warehouse_Address", L"Warehouse_Capacity", L"Current_Warehouse_Load" };

					std::vector<std::wstring> values = { warehouseNumber, warehouseAddress, warehouseCapacity, currentWarehouseLoad };

					adminWindow->UpdateRecord(L"Warehouse", columnNames, values, id);
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

					adminWindow->DeleteRecord(L"Post", idPost);

					break;
				}

				case 1: {

					std::wstring idTypeCounterpartyStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdTypeOfCounterparty);
					int id = _wtoi(idTypeCounterpartyStr.c_str());

					adminWindow->DeleteRecord(L"TypeOfCounterparty", id);

					break;
				}case 2: {


					std::wstring idContractStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdContract);
					int id = _wtoi(idContractStr.c_str());


					adminWindow->DeleteRecord(L"Contract_", id);

					break;

				}
				case 3: {

					std::wstring idCounterpartyStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdCounterparty);
					int id = _wtoi(idCounterpartyStr.c_str());

					adminWindow->DeleteRecord(L"Counterparty", id);

					break;

				}
				case 4: {

					std::wstring idDeliveryStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDelivery);
					int id = _wtoi(idDeliveryStr.c_str());

					adminWindow->DeleteRecord(L"Delivery", id);

					break;

				}
				case 5: {

					std::wstring idDeliveryNoteStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDeliveryNote);
					int id = _wtoi(idDeliveryNoteStr.c_str());

					adminWindow->DeleteRecord(L"DeliveryNote", id);

					break;

				}
				case 6: {

					std::wstring idDeliveryPositionStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdDeliveryPosition);
					int id = _wtoi(idDeliveryPositionStr.c_str());

					adminWindow->DeleteRecord(L"DeliveryPosition", id);

					break;

				}
				case 7: {

					std::wstring idEmployeeStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdEmployee);
					int id = _wtoi(idEmployeeStr.c_str());

					adminWindow->DeleteRecord(L"Employee", id);

					break;


				}
				case 8: {

					std::wstring idProductStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdProduct);
					int id = _wtoi(idProductStr.c_str());

					adminWindow->DeleteRecord(L"Product", id);

					break;


				}
				case 9: {

					std::wstring idProductOrderRequestStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdProductOrderRequest);
					int id = _wtoi(idProductOrderRequestStr.c_str());


					adminWindow->DeleteRecord(L"ProductOrderRequest", id);

					break;


				}
				case 10: {

					std::wstring idRequisitionPosStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdRequisitionPosition);
					int id = _wtoi(idRequisitionPosStr.c_str());

					adminWindow->DeleteRecord(L"RequisitionPosition", id);

					break;


				}
				case 11: {

					std::wstring idStatusStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdStatus);
					int id = _wtoi(idStatusStr.c_str());

					adminWindow->DeleteRecord(L"Status_", id);



					break;
				}
				case 12: {

					std::wstring idTypeOfProductStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdTypeOfProduct);
					int id = _wtoi(idTypeOfProductStr.c_str());

					adminWindow->DeleteRecord(L"TypeOfProduct", id);

					break;
				}
				case 13: {


					std::wstring idWarehouseStr = adminWindow->GetWindowTextAsWstring(adminWindow->hEditIdWarehouse);
					int id = _wtoi(idWarehouseStr.c_str());

					adminWindow->DeleteRecord(L"Warehouse", id);

					break;
				}

				}
			}

			else if (controlId == AdminWindow::IDC_SEARCH) {
				MessageBox(hwnd, L"Поиск", L"Debug", MB_OK);
			}
			else if (controlId == AdminWindow::IDC_FILTER) {
				MessageBox(hwnd, L"Фильтр", L"Debug", MB_OK);
			}

			break;

		}
		case WindowTypes::WAREHOUSE_WORKER_WINDOW: {
			//WarehouseWorkerWindow* warehouseWorker = static_cast<WarehouseWorkerWindow*>(window);
			int controlId = LOWORD(wParam);
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


