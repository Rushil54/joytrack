// #include <windows.h>
// #include "tray.h"
// #include "app.h"

// HICON hIcon;  // Global handle for the icon
// HWND hWnd;    // Handle for the application window

// // Windows message handler
// LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//     switch (msg) {
//         case WM_CREATE:
//             hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(101)); // Load custom icon
//             SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon); // Set window icon
//             AddTrayIcon(hWnd, 101, "JoyTrack"); // Add tray icon with tooltip
//             break;

//         case WM_COMMAND:
//             if (LOWORD(wParam) == ID_TRAY_EXIT) { // Exit clicked from tray
//                 DestroyWindow(hWnd);
//             }
//             break;

//         case WM_DESTROY:
//             RemoveTrayIcon(hWnd);     // Cleanup tray icon
//             DestroyIcon(hIcon);       // Destroy icon resource
//             PostQuitMessage(0);       // Exit message loop
//             break;

//         default:
//             return DefWindowProc(hWnd, msg, wParam, lParam);
//     }
//     return 0;
// }

// // Entry point for a Win32 GUI app
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//     // Define window class
//     WNDCLASS wc = {};
//     wc.lpfnWndProc = WindowProc;
//     wc.hInstance = hInstance;
//     wc.lpszClassName = TEXT("JoyTrackClass");
//     RegisterClass(&wc);

//     // Create hidden window
//     hWnd = CreateWindowEx(
//         0,
//         TEXT("JoyTrackClass"),
//         TEXT("JoyTrack"),
//         WS_OVERLAPPEDWINDOW,
//         CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
//         NULL, NULL, hInstance, NULL
//     );

//     if (!hWnd) return 0;

//     ShowWindow(hWnd, SW_HIDE); // Hide window (background only)

//     // Start the controller-to-mouse logic
//     HandleControllerInput();

//     // Standard Windows message loop
//     MSG msg;
//     while (GetMessage(&msg, NULL, 0, 0)) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }

//     return 0;
// }
#include <windows.h>
#include <thread>
#include "tray.h"
#include "app.h" // your controller logic
#include "window.h" // now we move ShowAppWindow to this

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInstance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    // Prevent multiple instances
    HANDLE hMutex = CreateMutex(NULL, TRUE, TEXT("JoyTrack_SingleInstance"));
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        return 0; // Another instance is already running, exit silently
    }

    g_hInstance = hInstance;
    const TCHAR CLASS_NAME[] = TEXT("JoyTrackMainClass");

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(CLASS_NAME, TEXT("JoyTrack"),
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             300, 200,
                             NULL, NULL, hInstance, NULL);

    if (!hWnd) return -1;

    AddTrayIcon(hWnd, hInstance);

    // Start controller logic in background
    std::thread controllerThread(HandleControllerInput);
    controllerThread.detach();

    // Hide main window
    ShowWindow(hWnd, SW_HIDE);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    RemoveTrayIcon();

    // Release the mutex before exiting
    if (hMutex) CloseHandle(hMutex);

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_APP + 1:
            if (lParam == WM_RBUTTONUP) {
                TrayIconClicked(hWnd);
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_TRAY_OPEN:
                    ShowAppWindow(g_hInstance); // From open_window.cpp
                    break;
                case ID_TRAY_EXIT:
                    DestroyWindow(hWnd);
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


