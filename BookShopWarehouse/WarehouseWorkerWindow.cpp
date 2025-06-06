#include "WarehouseWorkerWindow.h"
#include <CommCtrl.h>
#include <AdminWindow.h>
#include "DatabaseManager.h"
#include "BaseTable.h"


using namespace std;

WarehouseWorkerWindow::WarehouseWorkerWindow(DatabaseManager& dbManager) : dbManager(dbManager) {
	hLabelWindow = nullptr;
	hLabelNumberDelivery = nullptr;
	hLabelNumberWarehouse = nullptr;
	hBtnShowAllDelivery = nullptr;
	hBtnShowRejectedDelivery = nullptr;
	hBtnShowDeliveryPosition = nullptr;
	hBtnConfirmDelivery = nullptr;
	hComboBoxNumberDelivery = nullptr;
	hComboBoxWarehouse = nullptr;
	hWndListViewDelivery = nullptr;
	hWndListViewDeliveryPosition = nullptr;
	hWndListViewWarehouse = nullptr;
	hInstance = nullptr;

}

WarehouseWorkerWindow::~WarehouseWorkerWindow(){}

const LPCWSTR WarehouseWorkerWindow::CLASS_NAME = L"WarehouseWorkerWindowClass";

void WarehouseWorkerWindow::CreateWarehouseWorkerWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	CreateBaseWindow(parentHWnd, windowName, hInstance);

	InitCommonControls();

	this->hInstance = hInstance;


	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	DestroyElementsView();

	CreateElementsView();

}

WindowTypes WarehouseWorkerWindow::GetType() const { return WindowTypes::WAREHOUSE_WORKER_WINDOW; }


void WarehouseWorkerWindow::CreateElementsView() {

	labelWindow = CreateBaseTitleLabel(hWnd, hInstance, L"Окно сотрудника склада");

	

	hBtnShowAllDelivery = CreateBaseButton(hWnd, L"Показать все поставки", hInstance, padding, screenHeight / 2 - 200, screenWidth / 3 - 30, 50, reinterpret_cast<HMENU>(IDC_BTN_SHOW_ALL_DELIVERY));
	hBtnShowRejectedDelivery = CreateBaseButton(hWnd, L"Показать непринятые поставки", hInstance, screenWidth / 3 + 20, screenHeight / 2 - 200, screenWidth / 3 - 30, 50, reinterpret_cast<HMENU>(IDC_BTN_SHOW_REJECTED_DELIVERY));

	hLabelNumberDelivery = CreateBaseLabelMin(hWnd, hInstance, padding, screenHeight / 2 - 140, L"Номер поставки");
	hComboBoxNumberDelivery = CreateBaseComboBox(hWnd, hInstance, screenWidth / 3 + 20, screenHeight / 2 - 140, screenWidth / 3 - 30, 50, reinterpret_cast<HMENU>(IDC_COMBO_BOX_DELIVERY));
	FillComboBox(hComboBoxNumberDelivery, L"select ID_Delivery, Delivery_Number from Delivery", dbManager, comboBoxIdMap);
	hBtnShowDeliveryPosition = CreateBaseButton(hWnd, L"Показать позиции поставки", hInstance, screenWidth / 2 + 240, screenHeight / 2 - 140, screenWidth / 3 - 30, 50, reinterpret_cast<HMENU>(IDC_BTN_SHOW_DELIVERY_POSITION));

	

	hBtnConfirmDelivery = CreateBaseButton(hWnd, L"Подтвердить поставку", hInstance, screenWidth / 2 + 240, screenHeight / 2 + 350, screenWidth / 3 - 30, 50, reinterpret_cast<HMENU>(IDC_BTN_CONFIRM_DELIVERY));

}

void WarehouseWorkerWindow::DrawTableAllDelivery() {
	hWndListViewDelivery = CreateBaseListView(hWnd, hInstance, padding, 70, 0, 0);
	DrawTable(hWndListViewDelivery, Queries[4]);
}

void WarehouseWorkerWindow::DrawTableDeliveryPosition(wstring number) {

	wstring query = L"select ID_DeliveryPosition, Position_Number, Quantity_Of_Product_In_Requisition, Unit_Price , Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as 'ФИО', Email, Name_Product, Purchase_Price, Article, Quantity_Of_Product, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty, Delivery_Number, Delivery_Date, Warehouse_Number, DeliveryNote_Number , Date_Of_Formation , Contract_Number from DeliveryPosition  inner join RequisitionPosition on RequisitionPosition_ID = RequisitionPosition.ID_RequisitionPosition inner join Product on Product_ID = Product.ID_Product inner join ProductOrderRequest on ProductOrderRequest_ID = ProductOrderRequest.ID_ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on ProductOrderRequest.Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty inner join Delivery on Delivery_ID = Delivery.ID_Delivery inner join DeliveryNote on DeliveryNote_ID = DeliveryNote.ID_DeliveryNote inner join Warehouse on Warehouse_ID = Warehouse.ID_Warehouse inner join Contract_ on Contract_ID = Contract_.ID_Contract where Delivery_ID= '" + number;
	query += L"'";
	hWndListViewDeliveryPosition = CreateBaseListView(hWnd, hInstance, padding, screenHeight / 2 - 80, 0, 0);

	HWND targetListView = hWndListViewDeliveryPosition;

	
	const vector<wstring>& headers = { L"Код позиции поставки", L"Номер позиции заявки", L"Количество товара в заявке", L"Стоимость товара в заявке", L"Номер заявки",  L"Дата создания", L"ФИО сотрудника", L"Электронная почта", L"Название продукта", L"Цена закупки", L"Артикул", L"Количество товара", L"Название типа продукта", L"Название контрагента", L"Телефон контрагента", L"Электронная почта контрагента", L"Страна", L"Город", L"Название типа контрагента", L"Номер поставки", L"Дата поставки", L"Номер склада", L"Номер накладной", L"Дата формирования", L"Номер договора" };


	if (!targetListView) {
		MessageBox(NULL, L"Список еще не создан", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"Нет данных для отображения", L"Ошибка", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"Несоответствие заголовков и данных", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	BaseTable::ClearListView(targetListView);
	BaseTable::SetHeaders(targetListView, headers);
	BaseTable::SetData(targetListView, tableData);
	BaseTable::AutoResizeColumns(targetListView, headers, tableData);
	BaseTable::ResizeListViewToFit(targetListView, static_cast<int>(tableData.size()));

}


bool WarehouseWorkerWindow::ExecuteSQL(LPCWSTR sql) {
	try {
		dbManager.ExecuteQuery(sql);
		return true;
	}
	catch (...) {
		MessageBox(hWnd, L"Ошибка выполнения SQL", L"Ошибка", MB_OK | MB_ICONERROR);
		return false;
	}
}


void WarehouseWorkerWindow::FillComboBox(HWND hComboBox, const wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) {
	SendMessage(hComboBox, CB_RESETCONTENT, 0, 0);

	idMap.clear();

	auto data = dbManager.ExecuteQuery(query);

	wprintf(L"Получено строк: %zu\n", data.size());

	for (const auto& row : data) {
		if (row.size() >= 2) {
			int id = stoi(row[0]);
			const wstring& name = row[1];

			SendMessage(hComboBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(name.c_str()));

			idMap.push_back(id);
		}
	}

	if (!data.empty()) {
		SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
	}
}


void WarehouseWorkerWindow::DrawTable(HWND tableListView, const QueryDescriptor& descriptor) {
	HWND targetListView = tableListView;

	const auto& headers = descriptor.headers;
	wstring query = descriptor.sqlQuery;

	if (!targetListView) {
		MessageBox(NULL, L"Список еще не создан", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}



	vector<vector<wstring>> tableData = dbManager.ExecuteQuery(query);

	if (tableData.empty()) {
		MessageBox(NULL, L"Нет данных для отображения", L"Ошибка", MB_OK | MB_ICONWARNING);
		return;
	}

	if (headers.size() != tableData[0].size()) {
		MessageBox(NULL, L"Несоответствие заголовков и данных", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	BaseTable::ClearListView(targetListView);
	BaseTable::SetHeaders(targetListView, headers);
	BaseTable::SetData(targetListView, tableData);
	BaseTable::AutoResizeColumns(targetListView, headers, tableData);
	BaseTable::ResizeListViewToFit(targetListView, static_cast<int>(tableData.size()));

}


void WarehouseWorkerWindow::hWndForDestroy(HWND& hWndElement) {
	if (hWndElement) {
		DestroyWindow(hWndElement);
		SetWindowLongPtr(hWndElement, GWLP_USERDATA, NULL);
		hWndElement = nullptr;
	}
}


void WarehouseWorkerWindow::DestroyElementsView() {
	hWndForDestroy(hBtnShowAllDelivery);
	hWndForDestroy(hBtnShowRejectedDelivery);
	hWndForDestroy(hBtnShowDeliveryPosition);
	hWndForDestroy(hBtnConfirmDelivery);
	hWndForDestroy(hComboBoxNumberDelivery);
	hWndForDestroy(hComboBoxWarehouse);
	hWndForDestroy(hWndListViewDelivery);
	hWndForDestroy(hWndListViewDeliveryPosition);
	hWndForDestroy(hWndListViewWarehouse);
	hWndForDestroy(hLabelWindow);
	hWndForDestroy(hLabelNumberDelivery);
	hWndForDestroy(hLabelNumberWarehouse);

}

wstring WarehouseWorkerWindow::GetWindowTextAsWstring(HWND hWndEdit) {
	int length = GetWindowTextLength(hWndEdit);
	std::vector<wchar_t> buffer(length + 1);  // +1 для учета нулевого символа
	GetWindowText(hWndEdit, &buffer[0], length + 1);

	return std::wstring(&buffer[0]);
}

