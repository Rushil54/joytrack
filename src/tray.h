#ifndef TRAY_H
#define TRAY_H

#include <windows.h>

#define ID_TRAY_OPEN 9000
#define ID_TRAY_EXIT 9001
#define WM_TRAYICON (WM_USER + 1)

void AddTrayIcon(HWND hWnd, HINSTANCE hInstance);
void RemoveTrayIcon();
void TrayIconClicked(HWND hWnd);

#endif
