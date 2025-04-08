// ui_style.h
#ifndef UI_STYLE_H
#define UI_STYLE_H

#include <windows.h>
#include <tchar.h>

// Colors
#define BG_COLOR RGB(245, 245, 245)  // Light gray
#define TEXT_COLOR RGB(30, 30, 30)   // Dark gray

// Fonts
HFONT CreateAppFont(int size = 16, bool bold = false);

// Layout helpers
void CenterWindow(HWND hwnd);

#endif // UI_STYLE_H
