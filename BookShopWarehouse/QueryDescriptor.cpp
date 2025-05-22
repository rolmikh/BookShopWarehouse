#include "QueryDescriptor.h"

const std::vector<QueryDescriptor> Queries = {
	{
		{ L"Код должности",L"Название" },
		L"select ID_Post, Name_Post from Post",
		L"Post"
	},
	{
		{ L"Код типа контрагента", L"Название" },
		L"select ID_Type_Of_Counterparty, Name_Type_Of_Counterparty  from TypeOfCounterparty",
		L"TypeOfCounterparty"
	},
	{
		{ L"Код договора", L"Номер договора", L"Дата заключения", L"Дата окончания", L"Условия договора", L"Статус договора" },
		L"select ID_Contract, Contract_Number, Start_Date_Contract, End_Date_Contract, Contract_Terms, Name_Status from Contract_ inner join Status_ on Status_ID = Status_.ID_Status",
		L"Contract_"
	},
	{
		{L"Код контрагента", L"Название контрагента", L"Телефон", L"Электронная почта", L"Контакты", L"Условия сотрудничества", L"Страна", L"Город", L"Название типа контрагента", },
		L"select ID_Counterparty, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Contact_Person, Terms_Of_Cooperation, Country, City, Name_Type_Of_Counterparty from Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty",
		L"Counterparty"
	},
	{
		{L"Код поставки", L"Номер поставки", L"Дата поставки", L"Статус", L"Номер склада", L"Номер накладной", L"Дата формирования", L"Номер договора"},
		L"select ID_Delivery, Delivery_Number, Delivery_Date, Name_Status, Warehouse_Number, DeliveryNote_Number , Date_Of_Formation , Contract_Number from Delivery inner join DeliveryNote on DeliveryNote_ID = DeliveryNote.ID_DeliveryNote inner join Warehouse on Warehouse_ID = Warehouse.ID_Warehouse inner join Contract_ on Contract_ID = Contract_.ID_Contract inner join Status_ on Delivery.Status_ID = Status_.ID_Status ",
		L"Delivery"
	} ,
	{
		{L"Код накладной", L"Номер накладной", L"Дата формирования", L"Номер договора", L"Дата заключения договора", L"Дата окончания договора", L"Условия договора", L"Статус договора" },
		L"select ID_DeliveryNote, DeliveryNote_Number, Date_Of_Formation, Contract_Number, Start_Date_Contract, End_Date_Contract, Contract_Terms, Name_Status from DeliveryNote inner join Contract_ on Contract_ID = Contract_.ID_Contract inner join Status_ on Status_ID = Status_.ID_Status ",
		L"DeliveryNote"
	},
	{
		{L"Код позиции поставки", L"Номер позиции заявки", L"Количество товара в заявке", L"Стоимость товара в заявке", L"Номер заявки",  L"Дата создания", L"ФИО сотрудника", L"Электронная почта", L"Название продукта", L"Цена закупки", L"Артикул", L"Количество товара", L"Название типа продукта", L"Название контрагента", L"Телефон контрагента", L"Электронная почта контрагента", L"Страна", L"Город", L"Название типа контрагента", L"Номер поставки", L"Дата поставки", L"Номер склада", L"Номер накладной", L"Дата формирования", L"Номер договора"},
		L"select ID_DeliveryPosition, Position_Number, Quantity_Of_Product_In_Requisition, Unit_Price , Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as 'ФИО', Email, Name_Product, Purchase_Price, Article, Quantity_Of_Product, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty, Delivery_Number, Delivery_Date, Warehouse_Number, DeliveryNote_Number , Date_Of_Formation , Contract_Number from DeliveryPosition  inner join RequisitionPosition on RequisitionPosition_ID = RequisitionPosition.ID_RequisitionPosition inner join Product on Product_ID = Product.ID_Product inner join ProductOrderRequest on ProductOrderRequest_ID = ProductOrderRequest.ID_ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on ProductOrderRequest.Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty inner join Delivery on Delivery_ID = Delivery.ID_Delivery inner join DeliveryNote on DeliveryNote_ID = DeliveryNote.ID_DeliveryNote inner join Warehouse on Warehouse_ID = Warehouse.ID_Warehouse inner join Contract_ on Contract_ID = Contract_.ID_Contract",
		L"DeliveryPosition"
	},
	{
		{L"Код сотрудника", L"Фамилия", L"Имя", L"Отчество", L"Электронная почта", L"Логин", L"Должность"},
		L"select ID_Employee, Surname, Name, Patronymic, Email, Login_Employee, Name_Post from Employee inner join Post on Post_ID = Post.ID_Post ",
		L"Employee"
	},
	{
		{L"Код товара", L"Название товара", L"Цена закупки", L"Цена продажи", L"Артикул", L"Количество товара", L"Дата поступления", L"Название типа товара", L"Название контрагента",L"Телефон контрагента", L"Электронная почта", L"Страна", L"Город", L"Название типа контрагента"},
		L"select ID_Product, Name_Product, Purchase_Price, Selling_Price, Article, Quantity_Of_Product, Date_Of_Receipt, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty from Product inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty",
		L"Product"
	},
	{
		{L"Код заявки на заказ товара", L"Номер заявки", L"Дата создания", L"ФИО сотрудника", L"Электронная почта сотрудника", L"Комментарий", L"Название контрагента", L"Телефон контрагента", L"Электронная почта контрагента",L"Контактное лицо", L"Условия сотрудничества", L"Страна", L"Город", L"Название типа контрагента"},
		L"select ID_ProductOrderRequest, Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as 'ФИО', Email , Commentary, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Contact_Person, Terms_Of_Cooperation, Country, City, Name_Type_Of_Counterparty from ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join Counterparty on Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty",
		L"ProductOrderRequest"
	},
	{
		{L"Код позиции заявки", L"Номер позиции заявки", L"Количество товаров в заявке", L"Цена за единицу", L"Номер заявки", L"Дата создания", L"ФИО сотрудника", L"Электронная почта сотрудника", L"Название товара", L"Цена закупки", L"Артикул", L"Количество товара", L"Название типа продукта", L"Название контрагента", L"Телефон контрагента", L"Электронная почта контрагента", L"Страна", L"Город", L"Название типа контрагента"},
		L"select ID_RequisitionPosition, Position_Number, Quantity_Of_Product_In_Requisition, Unit_Price , Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as 'ФИО', Email, Name_Product, Purchase_Price, Article, Quantity_Of_Product, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty from RequisitionPosition inner join Product on Product_ID = Product.ID_Product inner join ProductOrderRequest on ProductOrderRequest_ID = ProductOrderRequest.ID_ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on ProductOrderRequest.Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty",
		L"RequisitionPosition"
	},
	{
		{L"Код статуса", L"Статус"},
		L"select ID_Status as 'Код статуса', Name_Status as 'Название статуса' from Status_",
		L"Status_"
	},
	{
		{L"Код типа товара", L"Тип товара"},
		L"select ID_Type_Of_Product as 'Код типа товара', Name_Type_Of_Product as 'Название типа товара' from TypeOfProduct",
		L"TypeOfProduct"
	},
	{
		{L"Код склада", L"Номер склада",L"Адрес склада", L"Вместимость склада", L"Текущая загрузка склада"},
		L"select ID_Warehouse as 'Код склада', Warehouse_Number as 'Номер склада', Warehouse_Address as 'Адрес склада', Warehouse_Capacity as 'Вместимость склада', Current_Warehouse_Load as 'Текущая загрузка склада'  from Warehouse",
		L"Warehouse"
	}
};

