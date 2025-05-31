#include "AdminWindow.h"
#include <commctrl.h>
#include "BaseTable.h"
#include <string>


using namespace std;

AdminWindow::AdminWindow(DatabaseManager& dbManager) : dbManager(dbManager) {
	hWnd = nullptr;
	hWndListViewPost = nullptr;
	hWndListViewTypeOfCounterparty = nullptr;
	hWndListViewContract = nullptr;
	hWndListViewCounterparty = nullptr;
	hWndListViewDelivery = nullptr;
	hWndListViewDeliveryNote = nullptr;
	hWndListViewDeliveryPosition = nullptr;
	hWndListViewEmployee = nullptr;
	hWndListViewProduct = nullptr;
	hWndListViewProductOrderRequest = nullptr;
	hWndListViewRequisitionPosition = nullptr;
	hWndListViewStatus = nullptr;
	hWndListViewTypeOfProduct = nullptr;
	hWndListViewWarehouse = nullptr;
	hBtnTabTypeOfCounterparty = nullptr;
	hBtnTabPost = nullptr;
	hBtnAdd = nullptr;
	hBtnEdit = nullptr;
	hBtnDelete = nullptr;
	hFilterButton = nullptr;
	hSearchButton = nullptr;
	currentTab = 0;
	hEditNamePost = nullptr;
	hEditNameTypeOfCounterparty = nullptr;
	hEditIdPost = nullptr;
	hInstance = nullptr;
	hBtnTabViewContract = nullptr;
	hBtnTabViewCounterparty = nullptr;
	hBtnTabViewDelivery = nullptr;
	hBtnTabViewDeliveryNote = nullptr;
	hBtnTabViewDeliveryPosition = nullptr;
	hBtnTabViewEmployee = nullptr;
	hBtnTabPost = nullptr;
	hBtnTabViewProduct = nullptr;
	hBtnTabViewProductOrderRequest = nullptr;
	hBtnTabViewRequisitionPosition = nullptr;
	hBtnTabViewStatus = nullptr;
	hBtnTabTypeOfCounterparty = nullptr;
	hBtnTabViewTypeOfProduct = nullptr;
	hBtnTabViewWarehouse = nullptr;

	hEditIdPost = nullptr;
	hEditNamePost = nullptr;

	hEditIdTypeOfCounterparty = nullptr;
	hEditNameTypeOfCounterparty = nullptr;

	hEditIdTypeOfProduct = nullptr;
	hEditNameTypeOfProduct = nullptr;

	hEditIdStatus = nullptr;
	hEditStatus = nullptr;

	hEditIdWarehouse = nullptr;
	hEditWarehouseNumber = nullptr;
	hEditWarehouseAddress = nullptr;
	hEditWarehouseCapacity = nullptr;
	hEditCurrentWarehouseLoad = nullptr;


	hEditIdContract = nullptr;
	hEditContractNumber = nullptr;
	hDPStartDateContract = nullptr;
	hDPEndDateContract = nullptr;
	hEditContractTerms = nullptr;
	hComboBoxStatus = nullptr;

	hEditIdDeliveryNote = nullptr;
	hEditDeliveryNoteNumber = nullptr;
	hDPDateOfFormation = nullptr;
	hComboBoxContract = nullptr;

	hEditIdDelivery = nullptr;
	hEditDeliveryNumber = nullptr;
	hDPDeliveryDate = nullptr;
	hComboBoxWarehouse = nullptr;
	hComboBoxDeliveryNote = nullptr;
	hComboBoxStatusDelivery = nullptr;

	hEditIdEmployee = nullptr;
	hEditSurname = nullptr;
	hEditName = nullptr;
	hEditPatronymic = nullptr;
	hEditEmail = nullptr;
	hEditLogin = nullptr;
	hEditPassword = nullptr;
	hComboBoxPost = nullptr;

	hEditIdCounterparty = nullptr;
	hEditNameCounterparty = nullptr;
	hEditPhoneCounterparty = nullptr;
	hEditEmailCounterparty = nullptr;
	hEditContactPerson = nullptr;
	hEditTermsOfCooperation = nullptr;
	hEditCountry = nullptr;
	hEditCity = nullptr;
	hComboBoxTypeOfCounterparty = nullptr;

	hEditIdProductOrderRequest = nullptr;
	hEditRequestNumber = nullptr;
	hDPDateOfCreation = nullptr;
	hComboBoxEmployee = nullptr;
	hEditCommentary = nullptr;
	hComboBoxCounterparty = nullptr;

	hEditIdProduct = nullptr;
	hEditNameProduct = nullptr;
	hEditPurchasePrice = nullptr;
	hEditSellingPrice = nullptr;
	hEditArticle = nullptr;
	hEditQuantityOfProduct = nullptr;
	hDPDateOfReceipt = nullptr;
	hComboBoxCounterpartyProduct = nullptr;
	hComboBoxTypeOfProduct = nullptr;

	hEditIdRequisitionPosition = nullptr;
	hEditPositionNumber = nullptr;
	hComboBoxProduct = nullptr;
	hComboBoxProductOrderRequest = nullptr;
	hEditQuantityOfProductInRequisition = nullptr;
	hEditUnitPrice = nullptr;

	hEditIdDeliveryPosition = nullptr;
	hComboBoxRequisitionPosition = nullptr;
	hComboBoxDeliveryDLPosition = nullptr;

	hLabelIdPost = nullptr;
	hLabelNamePost = nullptr;

	hLabelIdTypeOfCounterparty = nullptr;
	hLabelNameTypeOfCounterparty = nullptr;

	hLabelIdTypeOfProduct = nullptr;
	hLabelNameTypeOfProduct = nullptr;

	hLabelIdStatus = nullptr;
	hLabelStatus = nullptr;

	hLabelIdWarehouse = nullptr;
	hLabelWarehouseNumber = nullptr;
	hLabelWarehouseAddress = nullptr;
	hLabelWarehouseCapacity = nullptr;
	hLabelCurrentWarehouseLoad = nullptr;


	hLabelIdContract = nullptr;
	hLabelContractNumber = nullptr;
	hLabelStartDateContract = nullptr;
	hLabelEndDateContract = nullptr;
	hLabelContractTerms = nullptr;
	hLabelStatusContract = nullptr;

	hLabelIdDeliveryNote = nullptr;
	hLabelDeliveryNoteNumber = nullptr;
	hLabelDateOfFormation = nullptr;
	hLabelContract = nullptr;

	hLabelIdDelivery = nullptr;
	hLabelDeliveryNumber = nullptr;
	hLabelDeliveryDate = nullptr;
	hLabelWarehouse = nullptr;
	hLabelDeliveryNote = nullptr;
	hLabelStatusDelivery = nullptr;

	hLabelIdSurnameEmployee = nullptr;
	hLabelNamePatronymic = nullptr;
	hLabelEmail = nullptr;
	hLabelLogin = nullptr;
	hLabelPassword = nullptr;
	hLabelPost = nullptr;

	hLabelIdCounterparty = nullptr;
	hLabelNameCounterparty = nullptr;
	hLabelPhoneEmailCounterparty = nullptr;
	hLabelContactPersonTermsOfCooperationCounterparty = nullptr;
	hLabelCountry = nullptr;
	hLabelCityTypeOfCounterparty = nullptr;

	hLabelIdProductOrderRequest = nullptr;
	hLabelRequestNumber = nullptr;
	hLabelDateOfCreation = nullptr;
	hLabelEmployee = nullptr;
	hLabelCommentary = nullptr;
	hLabelCounterparty = nullptr;

	hLabelIdProduct = nullptr;
	hLabelNameProduct = nullptr;
	hLabelPurchaseSellingPrice = nullptr;
	hLabelArticleQuantityOfProduct = nullptr;
	hLabelDateOfReceipt = nullptr;
	hLabelCounterpartyProductTypeOfProduct = nullptr;

	hLabelIdRequisitionPosition = nullptr;
	hLabelPositionNumber = nullptr;
	hLabelProduct = nullptr;
	hLabelProductOrderRequest = nullptr;
	hLabelQuantityOfProductInRequisition = nullptr;
	hLabelUnitPrice = nullptr;

	hLabelIdDeliveryPosition = nullptr;
	hLabelRequisitionPosition = nullptr;
	hLabelDeliveryDLPosition = nullptr;
	 
}





AdminWindow::~AdminWindow() {}

void AdminWindow::CreateAdminWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance) {

	CreateBaseWindow(parentHWnd, windowName, hInstance);

	InitCommonControls();

	this->hInstance = hInstance;


	CreateTabButton();


	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	UpdateCurrentTabPage(currentTab);

}


void AdminWindow::UpdateCurrentTabPage(int selected) {

	currentTab = selected;
	DestroyElementsView();

	labelWindow = CreateBaseLabel(hWnd, hInstance, screenWidth / 4, 5, L"Окно администратора");

	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	

	HDC hdc = GetDC(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);
	FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
	ReleaseDC(hWnd, hdc);


	InvalidateRect(hWnd, nullptr, TRUE);
	UpdateWindow(hWnd);
	
	int editTop = topOffset + listViewHeight + padding;

	switch (selected) {
	case 0:
	{

		hWndListViewPost = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);

		
		DrawTable(hWndListViewPost, Queries[0]);
		hEditIdPost = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditNamePost = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 80, screenWidth / 2, 50);
		hLabelIdPost = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 20, L"Код должности");
		hLabelNamePost = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 80, L"Название должности");

		
		CreateElementsView();

		ShowWindow(hWndListViewPost, SW_SHOW);

		break;
	}
	case 1:
	{

		hWndListViewTypeOfCounterparty = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewTypeOfCounterparty, Queries[1]);

		hEditIdTypeOfCounterparty = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 20, screenWidth / 2, 50);
		hEditNameTypeOfCounterparty = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 80, screenWidth / 2, 50);
		hLabelIdTypeOfCounterparty = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 20, L"Код типа контрагента");
		hLabelNameTypeOfCounterparty = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 80, L"Название типа контрагента");

		CreateElementsView();

		ShowWindow(hWndListViewTypeOfCounterparty, SW_SHOW);

		break;
	}
	case 2:
	{

		hWndListViewContract = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);

		DrawTable(hWndListViewContract, Queries[2]);

		CreateElementsView();

		hEditIdContract = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);
		hEditContractNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hDPStartDateContract = CreateBaseDatePicker(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_DATEPICKER_STARTDATE_CONTRACT));
		hDPEndDateContract = CreateBaseDatePicker(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_DATEPICKER_ENDDATE_CONTRACT));
		hEditContractTerms = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50);
		hComboBoxStatus = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 300, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_STATUS));
		
		FillComboBox(hComboBoxStatus, L"select ID_Status, Name_Status from Status_", dbManager, comboBoxIdMap);

		hLabelIdContract = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код контракта");
		hLabelContractNumber = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Номер контракта");
		hLabelStartDateContract = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Дата заключения контракта");
		hLabelEndDateContract = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Дата окончания контракта");
		hLabelContractTerms = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 240, L"Условия сотрудничества");
		hLabelStatusContract = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 300, L"Статус контракта");


		ShowWindow(hWndListViewContract, SW_SHOW);


		break;
	}
	case 3:
	{

		hWndListViewCounterparty = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewCounterparty, Queries[3]);
		
		CreateElementsView();

		hEditIdCounterparty = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);
		hEditNameCounterparty = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hEditPhoneCounterparty = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 4 - 5, 50);
		hEditEmailCounterparty = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50 + (screenWidth / 4), screenHeight / 2 + 120, screenWidth / 4, 50);
		hEditContactPerson = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 4 - 5, 50);
		hEditTermsOfCooperation = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50 + (screenWidth / 4), screenHeight / 2 + 180, screenWidth / 4, 50);
		hEditCountry = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50);
		hEditCity = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 300, screenWidth / 4, 50);
		hComboBoxTypeOfCounterparty = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50 + (screenWidth / 4), screenHeight / 2 + 300, screenWidth / 4, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_TYPE_OF_COUNTERPARTY));


		FillComboBox(hComboBoxTypeOfCounterparty, L"select ID_Type_Of_Counterparty, Name_Type_Of_Counterparty from TypeOfCounterparty", dbManager, comboBoxIdMap);
		
		hLabelIdCounterparty = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код контрагента");
		hLabelNameCounterparty = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Название контрагента");
		hLabelPhoneEmailCounterparty = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Телефон контрагента / Электронная почта контрагента");
		hLabelContactPersonTermsOfCooperationCounterparty = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Контактное лицо / Условия сотрудничества");
		hLabelCountry = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 240, L"Страна");
		hLabelCityTypeOfCounterparty = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 300, L"Город / Тип контрагента");

		ShowWindow(hWndListViewCounterparty, SW_SHOW);

		break;
	}
	case 4:
	{

		hWndListViewDelivery = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewDelivery, Queries[4]);

		CreateElementsView();

		hEditIdDelivery = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);
		hEditDeliveryNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hDPDeliveryDate = CreateBaseDatePicker(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_DATEPICKER_DELIVERY_DATE));
		hComboBoxDeliveryNote = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_DELIVERY_NOTE));
		hComboBoxStatusDelivery = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_STATUS_DELIVERY));

		hLabelIdDelivery = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код поставки");
		hLabelDeliveryNumber = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Номер поставки");
		hLabelDeliveryDate = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Дата поставки");
		hLabelDeliveryNote = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Накладная");
		hLabelStatusDelivery = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 240, L"Статус поставки");


		FillComboBox(hComboBoxWarehouse, L"select ID_Warehouse, Warehouse_Number from Warehouse", dbManager, comboBoxIdMap);
		FillComboBox(hComboBoxDeliveryNote, L"select ID_DeliveryNote, DeliveryNote_Number from DeliveryNote", dbManager, comboBoxIdMap);
		FillComboBox(hComboBoxStatusDelivery, L"select ID_Status, Name_Status from Status_", dbManager, comboBoxIdMap);

		ShowWindow(hWndListViewDelivery, SW_SHOW);

		break;
	}
	case 5:
	{

		hWndListViewDeliveryNote = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);

		DrawTable(hWndListViewDeliveryNote, Queries[5]);

		CreateElementsView();
		hEditIdDeliveryNote = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);

		hEditDeliveryNoteNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hDPDateOfFormation = CreateBaseDatePicker(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_DATEPICKER_DATE_OF_FORMATION));
		hComboBoxContract = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_CONTRACT));

		hLabelIdDeliveryNote = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код накладной");
		hLabelDeliveryNoteNumber = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Номер накладной");
		hLabelDateOfFormation = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Дата составления");
		hLabelContract = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Договор");


		FillComboBox(hComboBoxContract, L"select ID_Contract, Contract_Number from Contract_", dbManager, comboBoxIdMap);


		ShowWindow(hWndListViewDeliveryNote, SW_SHOW);

		break;
	}
	case 6:
	{

		hWndListViewDeliveryPosition = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewDeliveryPosition, Queries[6]);

		CreateElementsView();

		hEditIdDeliveryPosition = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50); // ID
		hComboBoxRequisitionPosition = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_REQUISITION_POSITION));
		hComboBoxDeliveryDLPosition = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_DELIVERY));

		hLabelIdDeliveryPosition = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код позиции поставки");
		hLabelRequisitionPosition = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Код позиции заявки");
		hLabelDeliveryDLPosition = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Код поставки");


		FillComboBox(hComboBoxRequisitionPosition, L"select ID_RequisitionPosition, Position_Number from RequisitionPosition", dbManager, comboBoxIdMap);
		FillComboBox(hComboBoxDeliveryDLPosition, L"select ID_Delivery, Delivery_Number from Delivery", dbManager, comboBoxIdMap);


		ShowWindow(hWndListViewDeliveryPosition, SW_SHOW);

		break;
	}
	case 7:
	{

		hWndListViewEmployee = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewEmployee, Queries[7]);
		
		CreateElementsView();

		hEditIdEmployee = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 4 - 5, 50);
		hEditSurname = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50 + (screenWidth / 4), screenHeight / 2, screenWidth / 4, 50);
		hEditName = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 4 - 5, 50);
		hEditPatronymic = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50 + (screenWidth / 4), screenHeight / 2 + 60, screenWidth / 4, 50);
		hEditEmail = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50);
		hEditLogin = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 2, 50);
		hEditPassword = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50);
		hComboBoxPost = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 300, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_POST));

		hLabelIdSurnameEmployee = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код сотрудника / Фамилия сотрудника");
		hLabelNamePatronymic = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Имя сотрудника / Отчество сотрудника");
		hLabelEmail = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Электронная почта");
		hLabelLogin = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Логин");
		hLabelPassword = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 240, L"Пароль");
		hLabelPost = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 300, L"Должность");


		FillComboBox(hComboBoxPost, L"select ID_Post, Name_Post from Post", dbManager, comboBoxIdMap);

		ShowWindow(hWndListViewEmployee, SW_SHOW);

		break;
	}
	case 8:
	{

		hWndListViewProduct = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);

		DrawTable(hWndListViewProduct, Queries[8]);

		CreateElementsView();

		hEditIdProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);
		hEditNameProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hEditPurchasePrice = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 4 - 5, 50);
		hEditSellingPrice = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50 + (screenWidth / 4), screenHeight / 2 + 120, screenWidth / 4, 50);
		hEditArticle = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 4 - 5, 50);
		hEditQuantityOfProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50 + (screenWidth / 4), screenHeight / 2 + 180, screenWidth / 4, 50);
		hDPDateOfReceipt = CreateBaseDatePicker(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_DATEPICKER_DATE_OF_RECEIPT));
		hComboBoxCounterpartyProduct = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 300, screenWidth / 4, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_COUNTERPARTY));
		hComboBoxTypeOfProduct = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50 + (screenWidth / 4), screenHeight / 2 + 300, screenWidth / 4, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_TYPE_OF_PRODUCT));
		
		hLabelIdProduct = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код товара");
		hLabelNameProduct = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Название товара");
		hLabelPurchaseSellingPrice = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Цена закупки / Цена продажи");
		hLabelArticleQuantityOfProduct = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Артикул / Количество товара");
		hLabelDateOfReceipt = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 240, L"Дата поступления");
		hLabelCounterpartyProductTypeOfProduct = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 300, L"Контрагент / Тип товара");


		FillComboBox(hComboBoxCounterpartyProduct, L"select ID_Counterparty, Name_Counterparty from Counterparty", dbManager, comboBoxIdMap);
		FillComboBox(hComboBoxTypeOfProduct, L"select ID_Type_Of_Product, Name_Type_Of_Product from TypeOfProduct", dbManager, comboBoxIdMap);


		ShowWindow(hWndListViewProduct, SW_SHOW);

		break;
	}
	case 9:
	{

		hWndListViewProductOrderRequest = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewProductOrderRequest, Queries[9]);
		
		CreateElementsView();

		hEditIdProductOrderRequest = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);		
		hEditRequestNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hDPDateOfCreation = CreateBaseDatePicker(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_DATE_OF_CREATION));
		hComboBoxEmployee = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_EMPLOYEE));
		hEditCommentary = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50);
		hComboBoxCounterparty = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 300, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_COUNTERPARTY));

		hLabelIdProductOrderRequest = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код заявки на заказ товара");
		hLabelRequestNumber = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Номер заявки");
		hLabelDateOfCreation = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Дата создания");
		hLabelEmployee = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Сотрудник");
		hLabelCommentary = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 240, L"Комментарий");
		hLabelCounterparty = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 300, L"Контрагент");


		FillComboBox(hComboBoxEmployee, L"select ID_Employee, Email from Employee", dbManager, comboBoxIdMap);
		FillComboBox(hComboBoxCounterparty, L"select ID_Counterparty, Name_Counterparty from Counterparty", dbManager, comboBoxIdMap);

		ShowWindow(hWndListViewProductOrderRequest, SW_SHOW);

		break;
	}
	case 10:
	{

		hWndListViewRequisitionPosition = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewRequisitionPosition, Queries[10]);

		CreateElementsView();

		hEditIdRequisitionPosition = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);
		hEditPositionNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hComboBoxProduct = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_PRODUCT));
		hComboBoxProductOrderRequest = CreateBaseComboBox(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 2, 50, reinterpret_cast<HMENU>(IDC_COMBOBOX_PRODUCT_ORDER_REQUEST));
		hEditQuantityOfProductInRequisition = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50);
		hEditUnitPrice = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 300, screenWidth / 2, 50);

		hLabelIdRequisitionPosition = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код позиции заявки");
		hLabelPositionNumber = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Номер позиции");
		hLabelProduct = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Товар");
		hLabelProductOrderRequest = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Заявка на заказ товара");
		hLabelQuantityOfProductInRequisition = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 240, L"Количество товара в заявке");
		hLabelUnitPrice = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 300, L"Цена за единицу");


		FillComboBox(hComboBoxProductOrderRequest, L"select ID_ProductOrderRequest, Request_Number from ProductOrderRequest", dbManager, comboBoxIdMap);
		FillComboBox(hComboBoxProduct, L"select ID_Product, concat(Name_Product, ' ', Article) from Product", dbManager, comboBoxIdMap);

		ShowWindow(hWndListViewRequisitionPosition, SW_SHOW);

		break;
	}
	case 11:
	{

		hWndListViewStatus = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);

		DrawTable(hWndListViewStatus, Queries[11]);


		CreateElementsView();

		hEditIdStatus = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hEditStatus = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50);

		hLabelIdStatus = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Код статуса");
		hLabelStatus = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Статус");


		ShowWindow(hWndListViewStatus, SW_SHOW);

		break;
	}
	case 12:
	{

		hWndListViewTypeOfProduct = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewTypeOfProduct, Queries[12]);
		
		CreateElementsView();

		hEditIdTypeOfProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hEditNameTypeOfProduct = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50);

		hLabelIdTypeOfProduct = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Код типа продукта");
		hLabelNameTypeOfProduct = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Название типа продукта");


		ShowWindow(hWndListViewTypeOfProduct, SW_SHOW);

		break;
	}
	case 13:
	{

		hWndListViewWarehouse = CreateBaseListView(hWnd, hInstance, padding, topOffset + 50, 0, 0);


		DrawTable(hWndListViewWarehouse, Queries[13]);

		hEditIdWarehouse = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2, screenWidth / 2, 50);
		hEditWarehouseNumber = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 60, screenWidth / 2, 50);
		hEditWarehouseAddress = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 120, screenWidth / 2, 50);
		hEditWarehouseCapacity = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 180, screenWidth / 2, 50);
		hEditCurrentWarehouseLoad = CreateBaseEdit(hWnd, hInstance, (padding + screenWidth / 2) - 50, screenHeight / 2 + 240, screenWidth / 2, 50);


		hLabelIdWarehouse = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2, L"Код склада");
		hLabelWarehouseNumber = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 60, L"Номер склада");
		hLabelWarehouseAddress = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 120, L"Адрес склада");
		hLabelWarehouseCapacity = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 180, L"Вместимость склада");
		hLabelCurrentWarehouseLoad = CreateBaseLabel(hWnd, hInstance, padding, screenHeight / 2 + 240, L"Текущая загрузка склада");

		CreateElementsView();

		ShowWindow(hWndListViewWarehouse, SW_SHOW);

		break;
	}
	
		

	}


	InvalidateRect(hWnd, nullptr, TRUE);
	UpdateWindow(hWnd);

}

void AdminWindow::DrawTable(HWND tableListView, const QueryDescriptor& descriptor) {
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


void AdminWindow::CreateElementsView() {

	if (!hBtnAdd) hBtnAdd = CreateBaseButton(hWnd, L"Добавить", hInstance, buttonLeft, buttonTop - 20, buttonWidth, buttonHeight, reinterpret_cast<HMENU>(IDC_ADD));
	buttonLeft += buttonWidth + gap;
	if(!hBtnEdit) hBtnEdit = CreateBaseButton(hWnd, L"Изменить", hInstance, buttonLeft, buttonTop - 20, buttonWidth, buttonHeight, reinterpret_cast<HMENU>(IDC_EDIT));
	buttonLeft += buttonWidth + gap;
	if(!hBtnDelete)	hBtnDelete = CreateBaseButton(hWnd, L"Удалить", hInstance, buttonLeft, buttonTop - 20, buttonWidth, buttonHeight, reinterpret_cast<HMENU>(IDC_DELETE));
	/*if(!hSearchButton)	hSearchButton = CreateBaseButton(hWnd, L"П", hInstance, screenWidth - 150, 100, 30, 30, reinterpret_cast<HMENU>(IDC_SEARCH));
	if(!hFilterButton)	hFilterButton = CreateBaseButton(hWnd, L"Ф", hInstance, screenWidth - 100, 100, 30, 30, reinterpret_cast<HMENU>(IDC_FILTER));*/


	buttonLeft = sideOffset;
}



bool AdminWindow::ExecuteSQL(LPCWSTR sql) {
	try {
		dbManager.ExecuteQuery(sql);
		return true;
	}
	catch (...) {
		MessageBox(hWnd, L"Ошибка выполнения SQL",L"Ошибка", MB_OK | MB_ICONERROR);
		return false;
	}
}

void AdminWindow::AddRecord(cwstring tableName, const vector<wstring>& columnNames, const vector<wstring>& values) {

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
		MessageBox(hWnd, L"Запись успешно добавлена", L"Успех", MB_OK);
		
		UpdateCurrentTabPage(currentTab);
	}

}

void AdminWindow::UpdateRecord(cwstring tableName, const vector<wstring>& columnNames, const vector<wstring>& values, int id) {

	if (columnNames.size() != values.size()) {
		MessageBox(hWnd, L"Количество полей не совпадает", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}

	wstring sql = L"update " + tableName + L" set ";
	for (size_t i = 0; i < columnNames.size(); ++i) {
		sql += columnNames[i] + L" = N'" + values[i] + L"'";
		if (i != columnNames.size() - 1) sql += L", ";
	}

	sql += L" where ID_" + tableName + L" = " + to_wstring(id);


	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"Запись успешно обновлена", L"Успех", MB_OK);
		
		UpdateCurrentTabPage(currentTab);
	}

}

//Добавлю логическое удаление пока так
void AdminWindow::DeleteRecord(cwstring tableName, int id) {

	
	wstring sql = L"delete from " + tableName + L" Where ID_" + tableName + L" = " + to_wstring(id);
	if (ExecuteSQL(sql.c_str())) {
		MessageBox(hWnd, L"Запись успешно удалена", L"Успех", MB_OK);
		
		UpdateCurrentTabPage(currentTab);
		
	}
}


void AdminWindow::hWndForDestroy(HWND& hWndElement) {
	if (hWndElement) {
		DestroyWindow(hWndElement);
		SetWindowLongPtr(hWndElement, GWLP_USERDATA, NULL);
		hWndElement = nullptr;
	}
}

void AdminWindow::DestroyElementsView() {

	
	hWndForDestroy(hWndListViewContract);
	hWndForDestroy(hWndListViewCounterparty);
	hWndForDestroy(hWndListViewDelivery);
	hWndForDestroy(hWndListViewDeliveryNote);
	hWndForDestroy(hWndListViewDeliveryPosition);
	hWndForDestroy(hWndListViewEmployee);
	hWndForDestroy(hWndListViewPost);
	hWndForDestroy(hWndListViewProduct);
	hWndForDestroy(hWndListViewProductOrderRequest);
	hWndForDestroy(hWndListViewRequisitionPosition);
	hWndForDestroy(hWndListViewStatus);
	hWndForDestroy(hWndListViewTypeOfCounterparty);
	hWndForDestroy(hWndListViewTypeOfProduct);
	hWndForDestroy(hWndListViewWarehouse);

	hWndForDestroy(hBtnAdd);
	hWndForDestroy(hBtnEdit);
	hWndForDestroy(hBtnDelete);
	hWndForDestroy(hFilterButton);
	hWndForDestroy(hSearchButton);

	hWndForDestroy(hEditIdPost);
	hWndForDestroy(hEditNamePost);

	hWndForDestroy(hEditIdTypeOfCounterparty);
	hWndForDestroy(hEditNameTypeOfCounterparty);

	hWndForDestroy(hEditIdTypeOfProduct);
	hWndForDestroy(hEditNameTypeOfProduct);

	hWndForDestroy(hEditIdStatus);
	hWndForDestroy(hEditStatus);

	hWndForDestroy(hEditIdWarehouse);
	hWndForDestroy(hEditWarehouseNumber);
	hWndForDestroy(hEditWarehouseAddress);
	hWndForDestroy(hEditWarehouseCapacity);
	hWndForDestroy(hEditCurrentWarehouseLoad);

	hWndForDestroy(hEditIdContract);
	hWndForDestroy(hEditContractNumber);
	hWndForDestroy(hDPStartDateContract);
	hWndForDestroy(hDPEndDateContract);
	hWndForDestroy(hEditContractTerms);
	hWndForDestroy(hComboBoxStatus);

	hWndForDestroy(hEditIdDeliveryNote);
	hWndForDestroy(hEditDeliveryNoteNumber);
	hWndForDestroy(hDPDateOfFormation);
	hWndForDestroy(hComboBoxContract);

	hWndForDestroy(hEditIdDelivery);
	hWndForDestroy(hEditDeliveryNumber);
	hWndForDestroy(hDPDeliveryDate);
	hWndForDestroy(hComboBoxWarehouse);
	hWndForDestroy(hComboBoxDeliveryNote);
	hWndForDestroy(hComboBoxStatusDelivery);

	hWndForDestroy(hEditIdEmployee);
	hWndForDestroy(hEditSurname);
	hWndForDestroy(hEditName);
	hWndForDestroy(hEditPatronymic);
	hWndForDestroy(hEditEmail);
	hWndForDestroy(hEditLogin);
	hWndForDestroy(hEditPassword);
	hWndForDestroy(hComboBoxPost);

	hWndForDestroy(hEditIdCounterparty);
	hWndForDestroy(hEditNameCounterparty);
	hWndForDestroy(hEditPhoneCounterparty);
	hWndForDestroy(hEditEmailCounterparty);
	hWndForDestroy(hEditContactPerson);
	hWndForDestroy(hEditTermsOfCooperation);
	hWndForDestroy(hEditCountry);
	hWndForDestroy(hEditCity);
	hWndForDestroy(hComboBoxTypeOfCounterparty);

	hWndForDestroy(hEditIdProductOrderRequest);
	hWndForDestroy(hEditRequestNumber);
	hWndForDestroy(hDPDateOfCreation);
	hWndForDestroy(hComboBoxEmployee);
	hWndForDestroy(hEditCommentary);
	hWndForDestroy(hComboBoxCounterparty);

	hWndForDestroy(hEditIdProduct);
	hWndForDestroy(hEditNameProduct);
	hWndForDestroy(hEditPurchasePrice);
	hWndForDestroy(hEditSellingPrice);
	hWndForDestroy(hEditArticle);
	hWndForDestroy(hEditQuantityOfProduct);
	hWndForDestroy(hDPDateOfReceipt);
	hWndForDestroy(hComboBoxCounterpartyProduct);
	hWndForDestroy(hComboBoxTypeOfProduct);

	hWndForDestroy(hEditIdRequisitionPosition);
	hWndForDestroy(hEditPositionNumber);
	hWndForDestroy(hComboBoxProduct);
	hWndForDestroy(hComboBoxProductOrderRequest);
	hWndForDestroy(hEditQuantityOfProductInRequisition);
	hWndForDestroy(hEditUnitPrice);

	hWndForDestroy(hEditIdDeliveryPosition);
	hWndForDestroy(hComboBoxRequisitionPosition);
	hWndForDestroy(hComboBoxDeliveryDLPosition);

	hWndForDestroy(hLabelIdPost);
	hWndForDestroy(hLabelNamePost);

	hWndForDestroy(hLabelIdTypeOfCounterparty);
	hWndForDestroy(hLabelNameTypeOfCounterparty);

	hWndForDestroy(hLabelIdTypeOfProduct);
	hWndForDestroy(hLabelNameTypeOfProduct);

	hWndForDestroy(hLabelIdStatus);
	hWndForDestroy(hLabelStatus);

	hWndForDestroy(hLabelIdWarehouse);
	hWndForDestroy(hLabelWarehouseNumber);
	hWndForDestroy(hLabelWarehouseAddress);
	hWndForDestroy(hLabelWarehouseCapacity);
	hWndForDestroy(hLabelCurrentWarehouseLoad);

	hWndForDestroy(hLabelIdContract);
	hWndForDestroy(hLabelContractNumber);
	hWndForDestroy(hLabelStartDateContract);
	hWndForDestroy(hLabelEndDateContract);
	hWndForDestroy(hLabelContractTerms);
	hWndForDestroy(hLabelStatusContract);

	hWndForDestroy(hLabelIdDeliveryNote);
	hWndForDestroy(hLabelDeliveryNoteNumber);
	hWndForDestroy(hLabelDateOfFormation);
	hWndForDestroy(hLabelContract);

	hWndForDestroy(hLabelIdDelivery);
	hWndForDestroy(hLabelDeliveryNumber);
	hWndForDestroy(hLabelDeliveryDate);
	hWndForDestroy(hLabelWarehouse);
	hWndForDestroy(hLabelDeliveryNote);
	hWndForDestroy(hLabelStatusDelivery);

	hWndForDestroy(hLabelNamePatronymic);
	hWndForDestroy(hLabelIdSurnameEmployee);
	hWndForDestroy(hLabelEmail);
	hWndForDestroy(hLabelLogin);
	hWndForDestroy(hLabelPassword);
	hWndForDestroy(hLabelPost);

	hWndForDestroy(hLabelIdCounterparty);
	hWndForDestroy(hLabelNameCounterparty);
	hWndForDestroy(hLabelPhoneEmailCounterparty);
	hWndForDestroy(hLabelCountry);
	hWndForDestroy(hLabelCityTypeOfCounterparty);
	hWndForDestroy(hLabelContactPersonTermsOfCooperationCounterparty);

	hWndForDestroy(hLabelIdProductOrderRequest);
	hWndForDestroy(hLabelRequestNumber);
	hWndForDestroy(hLabelDateOfCreation);
	hWndForDestroy(hLabelEmployee);
	hWndForDestroy(hLabelCommentary);
	hWndForDestroy(hLabelCounterparty);

	hWndForDestroy(hLabelIdProduct);
	hWndForDestroy(hLabelNameProduct);
	hWndForDestroy(hLabelPurchaseSellingPrice);
	hWndForDestroy(hLabelArticleQuantityOfProduct);
	hWndForDestroy(hLabelDateOfReceipt);
	hWndForDestroy(hLabelCounterpartyProductTypeOfProduct);

	hWndForDestroy(hLabelIdRequisitionPosition);
	hWndForDestroy(hLabelPositionNumber);
	hWndForDestroy(hLabelProduct);
	hWndForDestroy(hLabelProductOrderRequest);
	hWndForDestroy(hLabelQuantityOfProductInRequisition);
	hWndForDestroy(hLabelUnitPrice);

	hWndForDestroy(hLabelIdDeliveryPosition);
	hWndForDestroy(hLabelRequisitionPosition);
	hWndForDestroy(hLabelDeliveryDLPosition);
	

}

wstring AdminWindow::GetWindowTextAsWstring(HWND hWndEdit) {
	int length = GetWindowTextLength(hWndEdit);
	std::vector<wchar_t> buffer(length + 1);  // +1 для учета нулевого символа
	GetWindowText(hWndEdit, &buffer[0], length + 1);

	return std::wstring(&buffer[0]);
}

wstring AdminWindow::GetDateFromDatePicker(HWND hDatePicker) {
	SYSTEMTIME st;
	if (DateTime_GetSystemtime(hDatePicker, &st) == GDT_VALID) {
		wchar_t buffer[256];
		swprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), L"%04d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
		return wstring(buffer);
	}

	return L"";
}


void AdminWindow::CreateTabButton() {

	RECT rc;
	GetClientRect(hWnd, &rc);
	int totalWidth = rc.right - rc.left;

	const int buttonsPerRow = 7;
	int buttonWidth = totalWidth / buttonsPerRow;

	int topOffset1 = 10;
	int topOffset2 = 70;

	hBtnTabPost = CreateBaseButton(hWnd, L"Должность", hInstance, buttonWidth * 0, topOffset1 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_POST));
	hBtnTabTypeOfCounterparty = CreateBaseButton(hWnd, L"Тип контрагента", hInstance, buttonWidth * 1, topOffset1 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_TYPE_OF_COUNTERPARTY));
	hBtnTabViewContract = CreateBaseButton(hWnd, L"Контракт", hInstance, buttonWidth * 2, topOffset1 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_CONTRACT));
	hBtnTabViewCounterparty = CreateBaseButton(hWnd, L"Контрагент", hInstance, buttonWidth * 3, topOffset1 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_COUNTERPARTY));
	hBtnTabViewDelivery = CreateBaseButton(hWnd, L"Поставка", hInstance, buttonWidth * 4, topOffset1 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_DELIVERY));
	hBtnTabViewDeliveryNote = CreateBaseButton(hWnd, L"Накладная", hInstance, buttonWidth * 5, topOffset1 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_DELIVERY_NOTE));
	hBtnTabViewDeliveryPosition = CreateBaseButton(hWnd, L"Позиция поставки", hInstance, buttonWidth * 6, topOffset1 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_DELIVERY_POSITION));
	hBtnTabViewEmployee = CreateBaseButton(hWnd, L"Сотрудник", hInstance, buttonWidth * 0, topOffset2 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_EMPLOYEE));
	hBtnTabViewProduct = CreateBaseButton(hWnd, L"Товар", hInstance, buttonWidth * 1, topOffset2 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_PRODUCT));
	hBtnTabViewProductOrderRequest = CreateBaseButton(hWnd, L"Заявка на заказ", hInstance, buttonWidth * 2, topOffset2 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_PRODUCT_ORDER_REQUEST));
	hBtnTabViewRequisitionPosition = CreateBaseButton(hWnd, L"Позиция заявки", hInstance, buttonWidth * 3, topOffset2 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_REQUISITION_POSITION));
	hBtnTabViewStatus = CreateBaseButton(hWnd, L"Статус", hInstance, buttonWidth * 4, topOffset2 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_STATUS));
	hBtnTabViewTypeOfProduct = CreateBaseButton(hWnd, L"Тип товара", hInstance, buttonWidth * 5, topOffset2 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_TYPE_OF_PRODUCT));
	hBtnTabViewWarehouse = CreateBaseButton(hWnd, L"Склад", hInstance, buttonWidth * 6, topOffset2 + 50, buttonWidth, 50, reinterpret_cast<HMENU>(IDC_TAB_WAREHOUSE));

}

void AdminWindow::FillComboBox(HWND hComboBox, const wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) {
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




