#include "QueryDescriptor.h"

const std::vector<QueryDescriptor> Queries = {
	{
		{ L"��� ���������",L"��������" },
		L"select ID_Post, Name_Post from Post",
		L"Post"
	},
	{
		{ L"��� ���� �����������", L"��������" },
		L"select ID_Type_Of_Counterparty, Name_Type_Of_Counterparty  from TypeOfCounterparty",
		L"TypeOfCounterparty"
	},
	{
		{ L"��� ��������", L"����� ��������", L"���� ����������", L"���� ���������", L"������� ��������", L"������ ��������" },
		L"select ID_Contract, Contract_Number, Start_Date_Contract, End_Date_Contract, Contract_Terms, Name_Status from Contract_ inner join Status_ on Status_ID = Status_.ID_Status",
		L"Contract_"
	},
	{
		{L"��� �����������", L"�������� �����������", L"�������", L"����������� �����", L"���������� ����", L"������� ��������������", L"������", L"�����", L"�������� ���� �����������", },
		L"select ID_Counterparty, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Contact_Person, Terms_Of_Cooperation, Country, City, Name_Type_Of_Counterparty from Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty",
		L"Counterparty"
	},
	{
		{L"��� ��������", L"����� ��������", L"���� ��������", L"������", L"����� ������", L"����� ���������", L"���� ������������", L"����� ��������"},
		L"select ID_Delivery, Delivery_Number, Delivery_Date, Name_Status, Warehouse_Number, DeliveryNote_Number , Date_Of_Formation , Contract_Number from Delivery inner join DeliveryNote on DeliveryNote_ID = DeliveryNote.ID_DeliveryNote inner join Warehouse on Warehouse_ID = Warehouse.ID_Warehouse inner join Contract_ on Contract_ID = Contract_.ID_Contract inner join Status_ on Delivery.Status_ID = Status_.ID_Status ",
		L"Delivery"
	} ,
	{
		{L"��� ���������", L"����� ���������", L"���� ������������", L"����� ��������", L"���� ���������� ��������", L"���� ��������� ��������", L"������� ��������", L"������ ��������" },
		L"select ID_DeliveryNote, DeliveryNote_Number, Date_Of_Formation, Contract_Number, Start_Date_Contract, End_Date_Contract, Contract_Terms, Name_Status from DeliveryNote inner join Contract_ on Contract_ID = Contract_.ID_Contract inner join Status_ on Status_ID = Status_.ID_Status ",
		L"DeliveryNote"
	},
	{
		{L"��� ������� ��������", L"����� ������� ������", L"���������� ������ � ������", L"��������� ������ � ������", L"����� ������",  L"���� ��������", L"��� ����������", L"����������� �����", L"�������� ��������", L"���� �������", L"�������", L"���������� ������", L"�������� ���� ��������", L"�������� �����������", L"������� �����������", L"����������� ����� �����������", L"������", L"�����", L"�������� ���� �����������", L"����� ��������", L"���� ��������", L"����� ������", L"����� ���������", L"���� ������������", L"����� ��������"},
		L"select ID_DeliveryPosition, Position_Number, Quantity_Of_Product_In_Requisition, Unit_Price , Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as '���', Email, Name_Product, Purchase_Price, Article, Quantity_Of_Product, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty, Delivery_Number, Delivery_Date, Warehouse_Number, DeliveryNote_Number , Date_Of_Formation , Contract_Number from DeliveryPosition  inner join RequisitionPosition on RequisitionPosition_ID = RequisitionPosition.ID_RequisitionPosition inner join Product on Product_ID = Product.ID_Product inner join ProductOrderRequest on ProductOrderRequest_ID = ProductOrderRequest.ID_ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on ProductOrderRequest.Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty inner join Delivery on Delivery_ID = Delivery.ID_Delivery inner join DeliveryNote on DeliveryNote_ID = DeliveryNote.ID_DeliveryNote inner join Warehouse on Warehouse_ID = Warehouse.ID_Warehouse inner join Contract_ on Contract_ID = Contract_.ID_Contract",
		L"DeliveryPosition"
	},
	{
		{L"��� ����������", L"�������", L"���", L"��������", L"����������� �����", L"�����", L"���������"},
		L"select ID_Employee, Surname, Name, Patronymic, Email, Login_Employee, Name_Post from Employee inner join Post on Post_ID = Post.ID_Post ",
		L"Employee"
	},
	{
		{L"��� ������", L"�������� ������", L"���� �������", L"���� �������", L"�������", L"���������� ������", L"���� �����������", L"�������� ���� ������", L"�������� �����������",L"������� �����������", L"����������� �����", L"������", L"�����", L"�������� ���� �����������"},
		L"select ID_Product, Name_Product, Purchase_Price, Selling_Price, Article, Quantity_Of_Product, Date_Of_Receipt, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty from Product inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty",
		L"Product"
	},
	{
		{L"��� ������ �� ����� ������", L"����� ������", L"���� ��������", L"��� ����������", L"����������� ����� ����������", L"�����������", L"�������� �����������", L"������� �����������", L"����������� ����� �����������",L"���������� ����", L"������� ��������������", L"������", L"�����", L"�������� ���� �����������"},
		L"select ID_ProductOrderRequest, Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as '���', Email , Commentary, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Contact_Person, Terms_Of_Cooperation, Country, City, Name_Type_Of_Counterparty from ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join Counterparty on Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty",
		L"ProductOrderRequest"
	},
	{
		{L"��� ������� ������", L"����� ������� ������", L"���������� ������� � ������", L"���� �� �������", L"����� ������", L"���� ��������", L"��� ����������", L"����������� ����� ����������", L"�������� ������", L"���� �������", L"�������", L"���������� ������", L"�������� ���� ��������", L"�������� �����������", L"������� �����������", L"����������� ����� �����������", L"������", L"�����", L"�������� ���� �����������"},
		L"select ID_RequisitionPosition, Position_Number, Quantity_Of_Product_In_Requisition, Unit_Price , Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as '���', Email, Name_Product, Purchase_Price, Article, Quantity_Of_Product, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty from RequisitionPosition inner join Product on Product_ID = Product.ID_Product inner join ProductOrderRequest on ProductOrderRequest_ID = ProductOrderRequest.ID_ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on ProductOrderRequest.Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty",
		L"RequisitionPosition"
	},
	{
		{L"��� �������", L"������"},
		L"select ID_Status as '��� �������', Name_Status as '�������� �������' from Status_",
		L"Status_"
	},
	{
		{L"��� ���� ������", L"��� ������"},
		L"select ID_Type_Of_Product as '��� ���� ������', Name_Type_Of_Product as '�������� ���� ������' from TypeOfProduct",
		L"TypeOfProduct"
	},
	{
		{L"��� ������", L"����� ������",L"����� ������", L"����������� ������", L"������� �������� ������"},
		L"select ID_Warehouse as '��� ������', Warehouse_Number as '����� ������', Warehouse_Address as '����� ������', Warehouse_Capacity as '����������� ������', Current_Warehouse_Load as '������� �������� ������'  from Warehouse",
		L"Warehouse"
	}
};

