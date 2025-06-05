#include "DatabaseManager.h"
#include <sql.h>
#include <sqlext.h>
#include <iostream>

using namespace std;

DatabaseManager::DatabaseManager(DatabaseConnection& dbCon) : dbConnection(dbCon) {}

DatabaseManager::~DatabaseManager() {}

vector<vector<wstring>> DatabaseManager::ExecuteQuery(const wstring& query) {
	SQLRETURN returnCode;
	SQLHSTMT hStmt;
	SQLAllocHandle(SQL_HANDLE_STMT, dbConnection.GetDatabaseConnection(), &hStmt);

	returnCode = SQLExecDirect(hStmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
	if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
		wcerr << L"Ошибка запроса" << endl;
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return{};
	}

	vector<vector<wstring>> tableData;
	SQLSMALLINT numCols;
	SQLNumResultCols(hStmt, &numCols);

	while (SQLFetch(hStmt) == SQL_SUCCESS) {
		vector<wstring> row;
		for (SQLSMALLINT col = 1; col <= numCols; ++col) {
			SQLWCHAR columnData[256];
			SQLGetData(hStmt, col, SQL_C_WCHAR, columnData, sizeof(columnData), NULL);
			row.push_back(columnData);
		}
		tableData.push_back(row);
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	return tableData;
}

void DatabaseManager::PrintTableData(const vector<vector<wstring>>& data) {
	for (const auto& row : data) {
		for (const auto& cell : row) {
			wcout << cell << L"\t";
		}
		wcout << endl;
	}
}