#pragma once
#include <windows.h>
#include <string>
#include <commctrl.h>
#include "BaseWindow.h"
#include "DatabaseManager.h"
#include "QueryDescriptor.h"
#include <unordered_map>



class AdminWindow : public BaseWindow
{
public:

	static const int IDC_TAB_POST = 1001;
	static const int IDC_TAB_TYPE_OF_COUNTERPARTY = 1002;
	static const int IDC_TAB_CONTRACT = 1003;
	static const int IDC_TAB_COUNTERPARTY = 1004;
	static const int IDC_TAB_DELIVERY = 1005;
	static const int IDC_TAB_DELIVERY_NOTE = 1006;
	static const int IDC_TAB_EMPLOYEE = 1007;
	static const int IDC_TAB_PRODUCT = 1008;
	static const int IDC_TAB_PRODUCT_ORDER_REQUEST = 1009;
	static const int IDC_TAB_REQUISITION_POSITION = 1010;
	static const int IDC_TAB_STATUS = 1011;
	static const int IDC_TAB_TYPE_OF_PRODUCT = 1012;
	static const int IDC_TAB_WAREHOUSE = 1013;
	static const int IDC_ADD = 1014;
	static const int IDC_EDIT = 1015;
	static const int IDC_DELETE = 1016;
	static const int IDC_FILTER = 1017;
	static const int IDC_SEARCH = 1018;
	static const int IDC_DELIVERY_POSITION = 1019;

	static const int IDC_COMBOBOX_STATUS = 1020;
	static const int IDC_COMBOBOX_WAREHOUSE = 1021;
	static const int IDC_COMBOBOX_DELIVERY_NOTE = 1022;
	static const int IDC_COMBOBOX_STATUS_DELIVERY = 1023;
	static const int IDC_COMBOBOX_CONTRACT = 1024;
	static const int IDC_COMBOBOX_REQUISITION_POSITION = 1025;
	static const int IDC_COMBOBOX_DELIVERY = 1026;
	static const int IDC_COMBOBOX_POST = 1027;
	static const int IDC_COMBOBOX_COUNTERPARTY = 1028;
	static const int IDC_COMBOBOX_TYPE_OF_COUNTERPARTY = 1028;
	static const int IDC_COMBOBOX_TYPE_OF_PRODUCT = 1029;
	static const int IDC_COMBOBOX_EMPLOYEE = 1030;
	static const int IDC_COMBOBOX_PRODUCT_ORDER_REQUEST = 1031;
	static const int IDC_COMBOBOX_PRODUCT = 1032;

	static const int IDC_DATEPICKER_STARTDATE_CONTRACT = 1033;
	static const int IDC_DATEPICKER_ENDDATE_CONTRACT = 1034;
	static const int IDC_DATEPICKER_DATE_OF_RECEIPT= 1035;
	static const int IDC_DATEPICKER_DATE_OF_FORMATION = 1036;
	static const int IDC_DATEPICKER_DELIVERY_DATE = 1037;
	static const int IDC_DATE_OF_CREATION = 1038;


	int topOffset = 150;
	int padding = 20;
	int listViewHeight = screenHeight / 2 - topOffset - 60;
	int listViewWidth = screenWidth - 2 * padding;

	int buttonHeight = 60;
	int bottomOffset = 40;
	int sideOffset = 40;
	int gap = 20;
	int buttonCount = 3;
	
	int totalGap = gap * (buttonCount - 1);
	int availableWidth = screenWidth - 2 * sideOffset - totalGap;
	int buttonWidth = availableWidth / buttonCount;

	int buttonTop = screenHeight - buttonHeight - bottomOffset;
	int buttonLeft = sideOffset;

	AdminWindow(DatabaseManager& dbManager);
	~AdminWindow();

	void CreateAdminWindow(HWND parentHWnd, LPCWSTR windowName, HINSTANCE hInstance);
	

	void DrawTable(HWND tableListView, const QueryDescriptor& descriptor);
	
	void CreateElementsView();
	void DestroyElementsView();

	void UpdateCurrentTabPage(int selected) override;

	using cwstring = const std::wstring&;

	void AddRecord(cwstring tableName, const std::vector<std::wstring>& columnNames, const std::vector<std::wstring>& values);
	void UpdateRecord(cwstring tableName, const std::vector<std::wstring>& columnNames, const std::vector<std::wstring>& values, int id);
	void DeleteRecord(cwstring tableName, int id);

	void hWndForDestroy(HWND& hWndElement);

	std::vector<int> comboBoxIdMap;

	void FillComboBox(HWND parentHWnd, const std::wstring& query, DatabaseManager& dbManager, std::vector<int>& idMap) override;

	void CreateTabButton();

	std::wstring GetWindowTextAsWstring(HWND hWndEdit);
	std::wstring GetDateFromDatePicker(HWND hDatePicker);

	std::unordered_map<int, std::wstring> comboBoxIndexToIdMap;

	int selectedItemId = -1;

	HWND GetHandleListView() const { return hWndListView; }


	HWND hBtnTabViewContract;
	HWND hBtnTabViewCounterparty;
	HWND hBtnTabViewDelivery;
	HWND hBtnTabViewDeliveryNote;
	HWND hBtnTabViewDeliveryPosition;
	HWND hBtnTabViewEmployee;
	HWND hBtnTabPost;
	HWND hBtnTabViewProduct;
	HWND hBtnTabViewProductOrderRequest;
	HWND hBtnTabViewRequisitionPosition;
	HWND hBtnTabViewStatus;
	HWND hBtnTabTypeOfCounterparty;
	HWND hBtnTabViewTypeOfProduct;
	HWND hBtnTabViewWarehouse;
	int currentTab = 0;


	HWND hEditIdPost;
	HWND hEditNamePost;

	HWND hEditIdTypeOfCounterparty;
	HWND hEditNameTypeOfCounterparty;

	HWND hEditIdTypeOfProduct;
	HWND hEditNameTypeOfProduct;

	HWND hEditIdStatus;
	HWND hEditStatus;

	HWND hEditIdWarehouse;
	HWND hEditWarehouseNumber;
	HWND hEditWarehouseAddress;
	HWND hEditWarehouseCapacity;
	HWND hEditCurrentWarehouseLoad;


	HWND hEditIdContract;
	HWND hEditContractNumber;
	HWND hDPStartDateContract;
	HWND hDPEndDateContract;
	HWND hEditContractTerms;
	HWND hComboBoxStatus;

	HWND hEditIdDeliveryNote;
	HWND hEditDeliveryNoteNumber;
	HWND hDPDateOfFormation;
	HWND hComboBoxContract;

	HWND hEditIdDelivery;
	HWND hEditDeliveryNumber;
	HWND hDPDeliveryDate;
	HWND hComboBoxWarehouse;
	HWND hComboBoxDeliveryNote;
	HWND hComboBoxStatusDelivery;

	HWND hEditIdEmployee;
	HWND hEditSurname;
	HWND hEditName;
	HWND hEditPatronymic;
	HWND hEditEmail;
	HWND hEditLogin;
	HWND hEditPassword;
	HWND hComboBoxPost;

	HWND hEditIdCounterparty;
	HWND hEditNameCounterparty;
	HWND hEditPhoneCounterparty;
	HWND hEditEmailCounterparty;
	HWND hEditContactPerson;
	HWND hEditTermsOfCooperation;
	HWND hEditCountry;
	HWND hEditCity;
	HWND hComboBoxTypeOfCounterparty;

	HWND hEditIdProductOrderRequest;
	HWND hEditRequestNumber;
	HWND hDPDateOfCreation;
	HWND hComboBoxEmployee;
	HWND hEditCommentary;
	HWND hComboBoxCounterparty;

	HWND hEditIdProduct;
	HWND hEditNameProduct;
	HWND hEditPurchasePrice;
	HWND hEditSellingPrice;
	HWND hEditArticle;
	HWND hEditQuantityOfProduct;
	HWND hDPDateOfReceipt;
	HWND hComboBoxCounterpartyProduct;
	HWND hComboBoxTypeOfProduct;

	HWND hEditIdRequisitionPosition;
	HWND hEditPositionNumber;
	HWND hComboBoxProduct;
	HWND hComboBoxProductOrderRequest;
	HWND hEditQuantityOfProductInRequisition;
	HWND hEditUnitPrice;

	HWND hEditIdDeliveryPosition;
	HWND hComboBoxRequisitionPosition;
	HWND hComboBoxDeliveryDLPosition;


	HWND hLabelIdPost;
	HWND hLabelNamePost;

	HWND hLabelIdTypeOfCounterparty;
	HWND hLabelNameTypeOfCounterparty;

	HWND hLabelIdTypeOfProduct;
	HWND hLabelNameTypeOfProduct;

	HWND hLabelIdStatus;
	HWND hLabelStatus;

	HWND hLabelIdWarehouse;
	HWND hLabelWarehouseNumber;
	HWND hLabelWarehouseAddress;
	HWND hLabelWarehouseCapacity;
	HWND hLabelCurrentWarehouseLoad;


	HWND hLabelIdContract;
	HWND hLabelContractNumber;
	HWND hLabelStartDateContract;
	HWND hLabelEndDateContract;
	HWND hLabelContractTerms;
	HWND hLabelStatusContract;

	HWND hLabelIdDeliveryNote;
	HWND hLabelDeliveryNoteNumber;
	HWND hLabelDateOfFormation;
	HWND hLabelContract;

	HWND hLabelIdDelivery;
	HWND hLabelDeliveryNumber;
	HWND hLabelDeliveryDate;
	HWND hLabelWarehouse;
	HWND hLabelDeliveryNote;
	HWND hLabelStatusDelivery;

	HWND hLabelIdSurnameEmployee;
	HWND hLabelNamePatronymic;
	HWND hLabelEmail;
	HWND hLabelLogin;
	HWND hLabelPassword;
	HWND hLabelPost;

	HWND hLabelIdCounterparty;
	HWND hLabelNameCounterparty;
	HWND hLabelPhoneEmailCounterparty;
	HWND hLabelContactPersonTermsOfCooperationCounterparty;
	HWND hLabelCountry;
	HWND hLabelCityTypeOfCounterparty;

	HWND hLabelIdProductOrderRequest;
	HWND hLabelRequestNumber;
	HWND hLabelDateOfCreation;
	HWND hLabelEmployee;
	HWND hLabelCommentary;
	HWND hLabelCounterparty;

	HWND hLabelIdProduct;
	HWND hLabelNameProduct;
	HWND hLabelPurchaseSellingPrice;
	HWND hLabelArticleQuantityOfProduct;
	HWND hLabelDateOfReceipt;
	HWND hLabelCounterpartyProductTypeOfProduct;

	HWND hLabelIdRequisitionPosition;
	HWND hLabelPositionNumber;
	HWND hLabelProduct;
	HWND hLabelProductOrderRequest;
	HWND hLabelQuantityOfProductInRequisition;
	HWND hLabelUnitPrice;

	HWND hLabelIdDeliveryPosition;
	HWND hLabelRequisitionPosition;
	HWND hLabelDeliveryDLPosition;



protected:
	HWND hWndListViewContract;
	HWND hWndListViewCounterparty;
	HWND hWndListViewDelivery;	
	HWND hWndListViewDeliveryNote;
	HWND hWndListViewDeliveryPosition;
	HWND hWndListViewEmployee;
	HWND hWndListViewPost;
	HWND hWndListViewProduct;
	HWND hWndListViewProductOrderRequest;
	HWND hWndListViewRequisitionPosition;
	HWND hWndListViewStatus;
	HWND hWndListViewTypeOfCounterparty;
	HWND hWndListViewTypeOfProduct;
	HWND hWndListViewWarehouse;


	HINSTANCE hInstance;

	DatabaseManager& dbManager;

	bool ExecuteSQL(LPCWSTR sql);


	HWND hBtnAdd;
	HWND hBtnEdit;
	HWND hBtnDelete;
	HWND hFilterButton;
	HWND hSearchButton;

	
};

