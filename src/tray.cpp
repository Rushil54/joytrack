// #include <windows.h>
// #include <shellapi.h>
// #include <cstring>

// #include "tray.h"
// #include "resource.h"

// static NOTIFYICONDATA nid = {};
// //static NOTIFYICONDATAA nid;
// static HMENU hMenu;

// void AddTrayIcon(HWND hWnd, HINSTANCE hInstance) {
//     nid.cbSize = sizeof(nid);
//     nid.hWnd = hWnd;
//     nid.uID = 1;
//     nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
//     nid.uCallbackMessage = WM_APP + 1;
//     nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
//     lstrcpy(nid.szTip, TEXT("JoyTrack"));

//     Shell_NotifyIcon(NIM_ADD, &nid);
// }


// void RemoveTrayIcon(HWND hWnd) {
//     Shell_NotifyIcon(NIM_DELETE, &nid);
// }

// void TrayIconClicked(HWND hWnd) {
//     POINT pt;
//     GetCursorPos(&pt);

//     HMENU hMenu = CreatePopupMenu();
//     AppendMenuA(hMenu, MF_STRING, ID_TRAY_OPEN, "Open App");
//     AppendMenuA(hMenu, MF_SEPARATOR, 0, NULL);
//     AppendMenuA(hMenu, MF_STRING, ID_TRAY_EXIT, "Exit");

//     SetForegroundWindow(hWnd);
//     TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
//     DestroyMenu(hMenu);
// }
// void ShowTrayMenu(HWND hWnd) {
//     POINT p;
//     GetCursorPos(&p);

//     hMenu = CreatePopupMenu();
//     AppendMenuA(hMenu, MF_STRING, ID_TRAY_EXIT, "Exit");

//     SetForegroundWindow(hWnd);
//     int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY, p.x, p.y, 0, hWnd, NULL);

//     if (cmd == ID_TRAY_EXIT)
//         PostMessage(hWnd, WM_CLOSE, 0, 0);

//     DestroyMenu(hMenu);
// }
// #include <windows.h>
// #include "tray.h"

// NOTIFYICONDATA nid;

// void AddTrayIcon(HWND hWnd, HINSTANCE hInstance) {
//     nid.cbSize = sizeof(NOTIFYICONDATA);
//     nid.hWnd = hWnd;
//     nid.uID = 1;
//     nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
//     nid.uCallbackMessage = WM_APP + 1;
//     nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION)); 
//     strcpy_s(nid.szTip, "JoyTrack - Controller Mouse");

//     Shell_NotifyIcon(NIM_ADD, &nid);
// }

// void RemoveTrayIcon() {
//     Shell_NotifyIcon(NIM_DELETE, &nid);
// }

// void TrayIconClicked(HWND hWnd) {
//     POINT pt;
//     GetCursorPos(&pt);

//     HMENU hMenu = CreatePopupMenu();
//     AppendMenu(hMenu, MF_STRING, ID_TRAY_OPEN, "Open App");
//     AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
//     AppendMenu(hMenu, MF_STRING, ID_TRAY_EXIT, "Exit");

//     SetForegroundWindow(hWnd);
//     TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
//     DestroyMenu(hMenu);
// }

#include <windows.h>
#include <shellapi.h>
#include "tray.h"
#include "resource.h"

static NOTIFYICONDATA nid = {};  // Global NOTIFYICONDATA used by both Add and Remove

void AddTrayIcon(HWND hWnd, HINSTANCE hInstance) {
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hWnd;
    nid.uID = 1;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.uCallbackMessage = WM_APP + 1;

    // Load icon from resources using the defined ID
    HICON hIcon = (HICON)LoadImage(
        hInstance,
        MAKEINTRESOURCE(IDI_ICON1),
        IMAGE_ICON,
        0, 0,
        LR_DEFAULTSIZE | LR_SHARED
    );
    //if (!hIcon) MessageBox(NULL, TEXT("Icon failed to load!"), TEXT("Error"), MB_OK);
    nid.hIcon = hIcon;
    lstrcpy(nid.szTip, TEXT("JoyTrack"));

    Shell_NotifyIcon(NIM_ADD, &nid);
}



void RemoveTrayIcon() {
    Shell_NotifyIcon(NIM_DELETE, &nid);
}

void TrayIconClicked(HWND hWnd) {
    POINT pt;
    GetCursorPos(&pt);

    HMENU hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, ID_TRAY_OPEN, TEXT("Show Controls"));
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, ID_TRAY_EXIT, TEXT("Exit"));

    SetForegroundWindow(hWnd);
    TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
    DestroyMenu(hMenu);
}
