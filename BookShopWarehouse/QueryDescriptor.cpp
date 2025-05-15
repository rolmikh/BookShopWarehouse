#include "QueryDescriptor.h"

const std::vector<QueryDescriptor> Queries = {
	{
		{ L"��� ���������",L"��������" },
		L"select ID_Post as '��� ���������', Name_Post as '��������'  from Post",
		L"Post"
	},
	{
		{ L"��� ���� �����������", L"��������" },
		L"select ID_Type_Of_Counterparty as '��� ���� �����������', Name_Type_Of_Counterparty as '��������'  from TypeOfCounterparty",
		L"TypeOfCounterparty"
	},
	{
		{ L"��� ��������", L"����� ��������", L"���� ����������", L"���� ���������", L"������� ��������", L"������ ��������" },
		L"select ID_Contract as '��� ��������', Contract_Number as '����� ��������', Start_Date_Contract as '���� ����������', End_Date_Contract as '���� ���������', Contract_Terms as '������� ��������', Name_Status as '������ ��������'  from Contract_ inner join Status_ on Status_ID = Status_.ID_Status"
		L"Contract_"
	}

};
