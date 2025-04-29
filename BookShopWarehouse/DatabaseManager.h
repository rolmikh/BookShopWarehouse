#pragma once
#include "DatabaseConnection.h"
#include <vector>
#include <string>

using namespace std;

class DatabaseManager
{
	DatabaseManager(DatabaseConnection& dbConnection);
	~DatabaseManager();

	vector<vector<wstring>> ExecuteQuery

};

