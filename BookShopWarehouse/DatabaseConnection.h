#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

class DatabaseConnection
{
public:

	DatabaseConnection(HWND hDbStatusLabel);
	~DatabaseConnection();

	void ConnectToDatabase(HWND hDbStatusLabel);
	void DisconnectFromDatabase();

private:
	SQLHENV hODbcEnvironment;
	SQLHDBC hDatabaseConnection;
	SQLHSTMT hQueryStatement;
};

