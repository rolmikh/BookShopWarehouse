#include "DatabaseConnection.h"
#include <tchar.h>
#include <sql.h>
#include <sqlext.h>


// Конструктор
DatabaseConnection::DatabaseConnection(HWND hDbStatusLabel) {
    ConnectToDatabase(hDbStatusLabel);
}

// Деструктор
DatabaseConnection::~DatabaseConnection() {
    DisconnectFromDatabase();
}

// Функция подключения к базе данных
void DatabaseConnection::ConnectToDatabase(HWND hDbStatusLabel) {
   
    SQLRETURN returnCode;

    returnCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hODbcEnvironment);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        SetWindowText(hDbStatusLabel, _T("Ошибка инициализации ODBC"));
        return;
    }

    returnCode = SQLSetEnvAttr(hODbcEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        SetWindowText(hDbStatusLabel, _T("Ошибка установки версии ODBC"));
        SQLFreeHandle(SQL_HANDLE_ENV, hODbcEnvironment);
        return;
    }

    returnCode = SQLAllocHandle(SQL_HANDLE_DBC, hODbcEnvironment, &hDatabaseConnection);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        SetWindowText(hDbStatusLabel, _T("Ошибка выделения дескриптора соединения"));
        SQLFreeHandle(SQL_HANDLE_ENV, hODbcEnvironment);
        return;
    }

    returnCode = SQLDriverConnect(hDatabaseConnection, NULL, (SQLWCHAR*)L"Driver={ODBC Driver 18 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=BookShopWarehouse;Trusted_Connection=yes;charset=UTF-8;", SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        SetWindowText(hDbStatusLabel, _T("Ошибка подключения к SQL Server"));
        SQLFreeHandle(SQL_HANDLE_DBC, hDatabaseConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, hODbcEnvironment);
        return;
    }

    returnCode = SQLAllocHandle(SQL_HANDLE_STMT, hDatabaseConnection, &hQueryStatement);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        SetWindowText(hDbStatusLabel, _T("Ошибка выделения дескриптора для запроса"));
        SQLFreeHandle(SQL_HANDLE_DBC, hDatabaseConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, hODbcEnvironment);
        return;
    }

    returnCode = SQLExecDirect(hQueryStatement, (SQLWCHAR*)L"SELECT DB_NAME();", SQL_NTS);
    if (returnCode != SQL_SUCCESS && returnCode != SQL_SUCCESS_WITH_INFO) {
        SetWindowText(hDbStatusLabel, _T("Ошибка выполнения запроса к базе данных"));
        SQLFreeHandle(SQL_HANDLE_STMT, hQueryStatement);
        SQLFreeHandle(SQL_HANDLE_DBC, hDatabaseConnection);
        SQLFreeHandle(SQL_HANDLE_ENV, hODbcEnvironment);
        return;
    }

    SQLWCHAR dbName[256];
    if (SQLFetch(hQueryStatement) == SQL_SUCCESS) {
        SQLGetData(hQueryStatement, 1, SQL_C_WCHAR, dbName, sizeof(dbName), NULL);
        TCHAR text[256];
        swprintf_s(text, sizeof(text) / sizeof(TCHAR), _T("Подключено к базе: %s"), dbName);
        SetWindowText(hDbStatusLabel, text);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hQueryStatement);

}

void DatabaseConnection::DisconnectFromDatabase() {

    if (hQueryStatement) {
        SQLFreeHandle(SQL_HANDLE_STMT, hQueryStatement);
    }
    if (hDatabaseConnection) {
        SQLFreeHandle(SQL_HANDLE_DBC, hDatabaseConnection);
    }
    if (hODbcEnvironment) {
        SQLFreeHandle(SQL_HANDLE_ENV, hODbcEnvironment);
    }
}