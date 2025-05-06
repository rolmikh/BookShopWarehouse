#pragma once
#include "DatabaseConnection.h"
#include <vector>
#include <string>


class DatabaseManager
{
public:
	DatabaseManager(DatabaseConnection& dbConnection);
	~DatabaseManager();

	std::vector<std::vector<std::wstring>> ExecuteQuery(const std::wstring& query);
	void PrintTableData(const std::vector<std::vector<std::wstring>>& data);

private:
	DatabaseConnection& dbConnection;

};

