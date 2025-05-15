#include "QueryDescriptor.h"

const std::vector<QueryDescriptor> Queries = {
	{
		{ L"Код должности",L"Название" },
		L"select ID_Post as 'Код должности', Name_Post as 'Название'  from Post",
		L"Post"
	},
	{
		{ L"Код типа контрагента", L"Название" },
		L"select ID_Type_Of_Counterparty as 'Код типа контрагента', Name_Type_Of_Counterparty as 'Название'  from TypeOfCounterparty",
		L"TypeOfCounterparty"
	},
	{
		{ L"Код договора", L"Номер договора", L"Дата заключения", L"Дата окончания", L"Условия договора", L"Статус договора" },
		L"select ID_Contract as 'Код договора', Contract_Number as 'Номер договора', Start_Date_Contract as 'Дата заключения', End_Date_Contract as 'Дата окончания', Contract_Terms as 'Условия договора', Name_Status as 'Статус договора'  from Contract_ inner join Status_ on Status_ID = Status_.ID_Status"
		L"Contract_"
	}

};
