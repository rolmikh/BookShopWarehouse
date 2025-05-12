CREATE TABLE TypeOfProduct (
	ID_Type_Of_Product INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Type_Of_Product NVARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE TypeOfCounterparty (
	ID_Type_Of_Counterparty INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Type_Of_Counterparty NVARCHAR(50) NOT NULL UNIQUE
);

INSERT INTO	TypeOfCounterparty (Name_Type_Of_Counterparty)
VALUES(N'Издательство'),(N'Производитель')
GO

CREATE TABLE Post (
	ID_Post INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Post NVARCHAR(50) NOT NULL UNIQUE
);

INSERT INTO	Post (Name_Post)
VALUES(N'Администратор баз данных'),(N'Сотрудник склада')
GO

SELECT * FROM Post
GO

select ID_Post as 'Код должности', Name_Post as 'Название'  from Post

CREATE TABLE Status_ (
	ID_Status INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Status NVARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE Warehouse (
	ID_Warehouse INTEGER PRIMARY KEY IDENTITY(1,1),
	Warehouse_Number NVARCHAR(8) NOT NULL UNIQUE,
	Warehouse_Address NVARCHAR(255) NOT NULL,
	Warehouse_Capacity INTEGER NOT NULL,
	Current_Warehouse_Load INTEGER NOT NULL
);

CREATE TABLE Contract_ (
	ID_Contract INTEGER PRIMARY KEY IDENTITY(1,1),
	Contract_Number NVARCHAR(8) NOT NULL UNIQUE,
	Start_Date_Contract DATETIME NOT NULL,
	End_Date_Contract DATETIME NOT NULL,
	Contract_Terms NVARCHAR(MAX)  NOT NULL,
	Status_ID INTEGER NOT NULL,
	FOREIGN KEY (Status_ID) REFERENCES Status_ (ID_Status)
);



CREATE TABLE DeliveryNote (
	ID_DeliveryNote INTEGER PRIMARY KEY IDENTITY(1,1),
	DeliveryNote_Number NVARCHAR(8) NOT NULL UNIQUE,
	Date_Of_Formation DATETIME NOT NULL,
	Contract_ID INTEGER NOT NULL,
	FOREIGN KEY (Contract_ID) REFERENCES Contract_ (ID_Contract)
);

CREATE TABLE Delivery (
	ID_Delivery INTEGER PRIMARY KEY IDENTITY(1,1),
	Delivery_Number NVARCHAR(8) NOT NULL UNIQUE,
	Delivery_Date DATETIME NOT NULL,
	Warehouse_ID INTEGER NOT NULL,
	DeliveryNote_ID INTEGER NOT NULL,
	Status_ID INTEGER NOT NULL,
	FOREIGN KEY (Warehouse_ID) REFERENCES Warehouse (ID_Warehouse),
	FOREIGN KEY (DeliveryNote_ID) REFERENCES DeliveryNote (ID_DeliveryNote),
	FOREIGN KEY (Status_ID) REFERENCES Status_ (ID_Status)
);

CREATE TABLE Employee (
	ID_Employee INTEGER PRIMARY KEY IDENTITY(1,1),
	Surname NVARCHAR(50) NOT NULL,
	Name NVARCHAR(50) NOT NULL,
	Patronymic NVARCHAR(50) NULL,
	Email NVARCHAR(100) NOT NULL,
	Login_Employee NVARCHAR(50) NOT NULL,
	Password_Employee NVARCHAR(100) NOT NULL,
	Post_ID INTEGER NOT NULL,
	Salt NVARCHAR(50) NOT NULL,
	FOREIGN KEY (Post_ID) REFERENCES Post (ID_Post)
);

CREATE TABLE Counterparty (
	ID_Counterparty INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Counterparty NVARCHAR(100) NOT NULL,
	Phone_Counterparty NVARCHAR(15) NOT NULL,
	Email_Counterparty NVARCHAR(100) NOT NULL,
	Contact_Person NVARCHAR(100) NOT NULL,
	Terms_Of_Cooperation NVARCHAR(100) NOT NULL,
	Country NVARCHAR(50) NOT NULL,
	City NVARCHAR(50) NOT NULL,
	TypeOfCounterparty_ID INTEGER NOT NULL,
	FOREIGN KEY (TypeOfCounterparty_ID) REFERENCES TypeOfCounterparty (ID_Type_Of_Counterparty)
);

CREATE TABLE ProductOrderRequest (
	ID_ProductOrderRequest INTEGER PRIMARY KEY IDENTITY(1,1),
	Request_Number NVARCHAR(10) NOT NULL,
	Date_Of_Creation DATETIME NOT NULL,
	Employee_ID INTEGER NOT NULL,
	Commentary NVARCHAR(50) NOT NULL,
	Counterparty_ID INTEGER NOT NULL,
	FOREIGN KEY (Counterparty_ID) REFERENCES Counterparty (ID_Counterparty)
);

CREATE TABLE Product (
	ID_Product INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Product NVARCHAR(100) NOT NULL,
	Purchase_Price DECIMAL(10,2) NOT NULL,
	Selling_Price DECIMAL(10,2) NOT NULL,
	Article NVARCHAR(15) NOT NULL,
	Quantity_Of_Product INTEGER NOT NULL,
	Date_Of_Receipt DATETIME NOT NULL,
	Counterparty_ID INTEGER NOT NULL,
	TypeOfProduct_ID INTEGER NOT NULL,
	FOREIGN KEY (Counterparty_ID) REFERENCES Counterparty (ID_Counterparty),
	FOREIGN KEY (TypeOfProduct_ID) REFERENCES TypeOfProduct (ID_Type_Of_Product)
);

CREATE TABLE RequisitionPosition (
	ID_RequisitionPosition INTEGER PRIMARY KEY IDENTITY(1,1),
	Position_Number NVARCHAR(50) NOT NULL,
	Product_ID INTEGER NOT NULL,
	ProductOrderRequest_ID INTEGER NOT NULL,
	Quantity_Of_Product_In_Requisition INTEGER NOT NULL,
	Unit_Price DECIMAL(10,2) NOT NULL,
	FOREIGN KEY (Product_ID) REFERENCES Product (ID_Product),
	FOREIGN KEY (ProductOrderRequest_ID) REFERENCES ProductOrderRequest (ID_ProductOrderRequest)
);

CREATE TABLE DeliveryPosition (
	ID_DeliveryPosition INTEGER PRIMARY KEY IDENTITY(1,1),
	RequisitionPosition_ID INTEGER NOT NULL,
	Delivery_ID INTEGER NOT NULL,
	FOREIGN KEY (RequisitionPosition_ID) REFERENCES RequisitionPosition (ID_RequisitionPosition),
	FOREIGN KEY (Delivery_ID) REFERENCES Delivery (ID_Delivery)
);

select ID_Contract as 'Код договора', Contract_Number as 'Номер договора', Start_Date_Contract as 'Дата заключения', End_Date_Contract as 'Дата окончания', Contract_Terms as 'Условия договора', Name_Status as 'Статус договора'  from Contract_ inner join Status_ on Status_ID = Status_.ID_Status