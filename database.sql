CREATE TABLE TypeOfProduct (
	ID_Type_Of_Product INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Type_Of_Product NVARCHAR(50) NOT NULL UNIQUE
);


CREATE TABLE TypeOfCounterparty (
	ID_Type_Of_Counterparty INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Type_Of_Counterparty NVARCHAR(50) NOT NULL UNIQUE
);


CREATE TABLE Post (
	ID_Post INTEGER PRIMARY KEY IDENTITY(1,1),
	Name_Post NVARCHAR(50) NOT NULL UNIQUE
);


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
	Warehouse_ID INTEGER NULL,
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
	FOREIGN KEY (Counterparty_ID) REFERENCES Counterparty (ID_Counterparty),
	FOREIGN KEY (Employee_ID) REFERENCES Employee(ID_Employee)
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


select ID_DeliveryNote, DeliveryNote_Number, Date_Of_Formation, Contract_Number, Start_Date_Contract, End_Date_Contract, Contract_Terms, Name_Status from DeliveryNote inner join Contract_ on Contract_ID = Contract_.ID_Contract inner join Status_ on Status_ID = Status_.ID_Status

select ID_Post as 'Код должности', Name_Post as 'Название'  from Post

select ID_Type_Of_Counterparty as 'Код типа контрагента', Name_Type_Of_Counterparty as 'Название'  from TypeOfCounterparty

select ID_Type_Of_Product as 'Код типа товара', Name_Type_Of_Product as 'Название типа товара' from TypeOfProduct

select ID_Status as 'Код статуса', Name_Status as 'Название статуса' from Status_

select ID_Warehouse as 'Код склада', Warehouse_Number as 'Номер склада', Warehouse_Address as 'Адрес склада', Warehouse_Capacity as 'Вместимость склада', Current_Warehouse_Load as 'Текущая загрузка склада'  from Warehouse

select ID_Contract as 'Код договора', Contract_Number as 'Номер договора', Start_Date_Contract as 'Дата заключения', End_Date_Contract as 'Дата окончания', Contract_Terms as 'Условия договора', Name_Status as 'Статус договора'  from Contract_ inner join Status_ on Status_ID = Status_.ID_Status

select ID_DeliveryNote as 'Код накладной', DeliveryNote_Number as 'Номер накладной', Date_Of_Formation as 'Дата формирования', Contract_Number as 'Номер договора', Start_Date_Contract as 'Дата заключения договора', End_Date_Contract as 'Дата окончания договора', Contract_Terms as 'Условия договора', Name_Status as 'Статус договора' from DeliveryNote inner join Contract_ on Contract_ID = Contract_.ID_Contract inner join Status_ on Status_ID = Status_.ID_Status 

select ID_Delivery, Delivery_Number, Delivery_Date, Name_Status, Warehouse_Number, DeliveryNote_Number , Date_Of_Formation , Contract_Number from Delivery inner join DeliveryNote on DeliveryNote_ID = DeliveryNote.ID_DeliveryNote inner join Warehouse on Warehouse_ID = Warehouse.ID_Warehouse inner join Contract_ on Contract_ID = Contract_.ID_Contract inner join Status_ on Delivery.Status_ID = Status_.ID_Status 

select ID_Employee, Surname, Name, Patronymic, Email, Login_Employee, Name_Post from Employee inner join Post on Post_ID = Post.ID_Post 

select ID_Counterparty, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Contact_Person, Terms_Of_Cooperation, Country, City, Name_Type_Of_Counterparty from Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty

select ID_ProductOrderRequest, Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as 'ФИО', Email , Commentary, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Contact_Person, Terms_Of_Cooperation, Country, City, Name_Type_Of_Counterparty from ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join Counterparty on Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty

select ID_Product, Name_Product, Purchase_Price, Selling_Price, Article, Quantity_Of_Product, Date_Of_Receipt, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty from Product inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty

select ID_RequisitionPosition, Position_Number, Quantity_Of_Product_In_Requisition, Unit_Price , Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as 'ФИО', Email, Name_Product, Purchase_Price, Article, Quantity_Of_Product, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty from RequisitionPosition inner join Product on Product_ID = Product.ID_Product inner join ProductOrderRequest on ProductOrderRequest_ID = ProductOrderRequest.ID_ProductOrderRequest inner join Employee on Employee_ID = Employee.ID_Employee inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product inner join Counterparty on ProductOrderRequest.Counterparty_ID = Counterparty.ID_Counterparty inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty

select ID_DeliveryPosition, ID_RequisitionPosition, Position_Number, Quantity_Of_Product_In_Requisition, Unit_Price , Request_Number, Date_Of_Creation, Surname + ' ' + Name + ' ' + Patronymic as 'ФИО', Email, Name_Product, Purchase_Price, Article, Quantity_Of_Product, Name_Type_Of_Product, Name_Counterparty, Phone_Counterparty, Email_Counterparty, Country, City, Name_Type_Of_Counterparty, Delivery_Number, Delivery_Date, Warehouse_Number, DeliveryNote_Number , Date_Of_Formation , Contract_Number from DeliveryPosition 
inner join RequisitionPosition on RequisitionPosition_ID = RequisitionPosition.ID_RequisitionPosition
inner join Product on Product_ID = Product.ID_Product
inner join ProductOrderRequest on ProductOrderRequest_ID = ProductOrderRequest.ID_ProductOrderRequest 
inner join Employee on Employee_ID = Employee.ID_Employee 
inner join TypeOfProduct on TypeOfProduct_ID = TypeOfProduct.ID_Type_Of_Product 
inner join Counterparty on ProductOrderRequest.Counterparty_ID = Counterparty.ID_Counterparty 
inner join TypeOfCounterparty on TypeOfCounterparty_ID = TypeOfCounterparty.ID_Type_Of_Counterparty 
inner join Delivery on Delivery_ID = Delivery.ID_Delivery inner join DeliveryNote on DeliveryNote_ID = DeliveryNote.ID_DeliveryNote 
inner join Warehouse on Warehouse_ID = Warehouse.ID_Warehouse 
inner join Contract_ on Contract_ID = Contract_.ID_Contract

insert into	TypeOfCounterparty (Name_Type_Of_Counterparty)
values(N'Издательство'),(N'Производитель')

insert into	Post (Name_Post)
values(N'Администратор баз данных'),(N'Сотрудник склада')


insert into Status_ (Name_Status)
values 
(N'Активный'),
(N'В пути'),
(N'Завершён')

insert into TypeOfProduct (Name_Type_Of_Product)
values (N'Книга'), (N'Мягкие игрушки'), (N'Канцелярия')

insert into Warehouse (Warehouse_Number, Warehouse_Address, Warehouse_Capacity, Current_Warehouse_Load)
values 
(N'WH001', N'Московская область, г. Подольск, ул. Складская, д. 10', 10000, 6000),
(N'WH002', N'Московская область, г. Одинцово, ул. Магистральная, д. 5', 8000, 4500)

insert into Contract_ (Contract_Number, Start_Date_Contract, End_Date_Contract, Contract_Terms, Status_ID)
values 
(N'CT001', '2025-01-15', '2026-01-15', N'Поставка книг ежеквартально', 3),
(N'CT002', '2025-03-10', '2026-03-10', N'Ежемесячная поставка канцелярии', 2),
(N'CT003', '2025-04-15', '2026-04-15', N'Разовая поставка мягких игрушек', 1)

insert into DeliveryNote (DeliveryNote_Number, Date_Of_Formation, Contract_ID)
values 
(N'DN001', '2025-02-01', 1),
(N'DN002', '2025-03-01', 2),
(N'DN003', '2025-04-01', 3)

insert into Delivery (Delivery_Number, Delivery_Date, Warehouse_ID, DeliveryNote_ID, Status_ID)
values 
(N'DL001', '2025-02-05', 1, 1, 3),
(N'DL002', '2025-04-05', 2, 2, 2),
(N'DL003', '2025-05-05', 1, 3, 1)

insert into Counterparty (Name_Counterparty, Phone_Counterparty, Email_Counterparty, Contact_Person, Terms_Of_Cooperation, Country, City, TypeOfCounterparty_ID)
values 
(N'ООО "Книготорг"', N'89123456789', N'books@supplier.ru', N'Алексей Алексеевич Книжников', N'По договору', N'Россия', N'Москва', 1),
(N'ИП Петров', N'89223456789', N'toys@supplier.com', N'Ольга Викторовна Иванова', N'Разово', N'Россия', N'Санкт-Петербург', 2),
(N'ООО "Канцторг"', N'89323456789', N'kanctorg@example.com', N'Виктор Михайлович Смирнов', N'Еженедельно', N'Россия', N'Екатеринбург', 2)


insert into Product (Name_Product, Purchase_Price, Selling_Price, Article, Quantity_Of_Product, Date_Of_Receipt, Counterparty_ID, TypeOfProduct_ID)
values 
(N'Энциклопедия для школьника', 400.00, 600.00, N'111111', 200, '2025-02-11', 4, 1),
(N'Мягкая игрушка "Мишка"', 150.00, 300.00, N'111112', 150, '2025-05-05', 5, 2),
(N'Формат А4, пачка 500 листов', 120.00, 200.00, N'111113', 300, '2025-05-15', 6, 3)

insert into Employee (Surname, Name, Patronymic, Email, Login_Employee, Password_Employee, Post_ID, Salt)
values 
(N'Иванов', N'Иван', N'Иванович', N'ivanov@warehouse.com', N'ivanov', N'pass123', 5, N'salt1'),
(N'Петров', N'Петр', N'Петрович', N'petrov@warehouse.com', N'petrov', N'pass456', 4, N'salt2'),
(N'Сидорова', N'Мария', N'Сергеевна', N'sidorova@warehouse.com', N'ms', N'pass789', 6, N'salt3')

insert into ProductOrderRequest (Request_Number, Date_Of_Creation, Employee_ID, Commentary, Counterparty_ID)
values 
(N'REQ001', '2025-03-20', 3, N'Срочно', 4),
(N'REQ002', '2025-04-10', 4, N'Не срочно', 5),
(N'REQ003', '2025-04-03', 5, N'Первый заказ', 6)

insert into RequisitionPosition (Position_Number, Product_ID, ProductOrderRequest_ID, Quantity_Of_Product_In_Requisition, Unit_Price)
values 
(N'POS001', 3, 3, 50, 600.00),
(N'POS002', 4, 4, 100, 200.00),
(N'POS003', 5, 5, 200, 300.00)

insert into DeliveryPosition (RequisitionPosition_ID, Delivery_ID)
values 
(3, 1),
(4, 2),
(5, 3)

