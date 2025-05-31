#include <windows.h>
#include <stdio.h>
#include "DatabaseConnection.h"
#include "DatabaseManager.h"
#include "AdminWindow.h"
#include "WarehouseWorkerWindow.h"
#include <tchar.h>


// Идентификатор метки для статуса подключения
#define ID_LABEL 1

// Основная функция обработки окна
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hDbStatusLabel;
    static DatabaseConnection* dbConn = nullptr;
    static DatabaseManager* dbManager = nullptr;
    static AdminWindow* adminWindow = nullptr;
    static WarehouseWorkerWindow* warehouseWorkerWindow = nullptr;


    switch (uMsg) {
    case WM_CREATE: {
        // Создание метки для статуса подключения
        hDbStatusLabel = CreateWindow(
            _T("STATIC"),
            _T("Ожидание подключения..."),
            WS_VISIBLE | WS_CHILD,
            10, 10, 300, 20,
            hwnd,
            (HMENU)ID_LABEL,
            NULL,
            NULL
        );

        break;
    }

    case WM_LBUTTONDOWN: {
        if (!dbConn) {
            dbConn = new DatabaseConnection(hDbStatusLabel);
            dbConn->ConnectToDatabase(hDbStatusLabel);
        }
        
        if (!dbManager && dbConn) {
            dbManager = new DatabaseManager(*dbConn);
        }

        /*if (!adminWindow && dbManager) {
            
            adminWindow = new AdminWindow(*dbManager);
            adminWindow->CreateAdminWindow(hwnd, L"Окно администратора", GetModuleHandle(NULL));
           
            
        }*/

        warehouseWorkerWindow = new WarehouseWorkerWindow(*dbManager);
        warehouseWorkerWindow->CreateWarehouseWorkerWindow(hwnd, L"Окно сотрудника склада", GetModuleHandle(NULL));


        break;
    }

    case WM_DESTROY:
        delete adminWindow;
        delete dbManager;
        delete dbConn;
        PostQuitMessage(0);
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const TCHAR CLASS_NAME[] = _T("SampleWindowClass");

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        _T("Подключение к БД"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}