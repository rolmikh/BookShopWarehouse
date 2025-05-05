#pragma once
#include "DatabaseConnection.h"
#include <vector>
#include <string>

using namespace std;

class DatabaseManager
{
public:
	DatabaseManager(DatabaseConnection& dbConnection);
	~DatabaseManager();

	vector<vector<wstring>> ExecuteQuery(const wstring& query);
	void PrintTableData(const vector<vector<wstring>>& data);

private:
	DatabaseConnection& dbConnection;

};

