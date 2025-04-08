// #include "window.h"
// #include "style/ui.h"
// #include "style/fonts.h"
// #include "resource.h"

// HWND hAppWindow = NULL;

// LRESULT CALLBACK AppWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//     switch (message) {
//         case WM_CLOSE:
//             ShowWindow(hWnd, SW_HIDE); // Just hide on close
//             return 0;
//             case WM_COMMAND:
//             if (LOWORD(wParam) == 1) {  // GitHub link clicked
//                 ShellExecute(NULL, TEXT("open"), TEXT("https://github.com/yourusername/yourrepo"), NULL, NULL, SW_SHOWNORMAL);
//                 return 0;
//             }
//             break;

//     }
    
//     return DefWindowProc(hWnd, message, wParam, lParam);
// }

// void ShowAppWindow(HINSTANCE hInstance) {
//     if (!hAppWindow) {
//         const TCHAR CLASS_NAME[] = TEXT("JoyTrackAppWindow");

//         WNDCLASS wc = {};
//         wc.lpfnWndProc = AppWindowProc;
//         wc.hInstance = hInstance;
//         wc.lpszClassName = CLASS_NAME;
//         wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
//         RegisterClass(&wc);

//         hAppWindow = CreateWindow(CLASS_NAME, TEXT("JoyTrack Controls"),
//                                   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
//                                   CW_USEDEFAULT, CW_USEDEFAULT,
//                                   500, 400,
//                                   NULL, NULL, hInstance, NULL);

//         HFONT fontTitle = CreateUIFont(20);
//         HFONT fontHeader = CreateUIFont(14);
//         HFONT fontBody = CreateUIFont(12);

//         HWND hLogo = CreateWindow(TEXT("STATIC"), NULL,
//                                   WS_VISIBLE | WS_CHILD | SS_ICON,
//                                   20, 20, 32, 32,
//                                   hAppWindow, NULL, hInstance, NULL);
//         SendMessage(hLogo, STM_SETICON, (WPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON)), 0);

//         HWND hAppName = CreateWindow(TEXT("STATIC"), TEXT("JoyTrack"),
//                                      WS_VISIBLE | WS_CHILD,
//                                      60, 25, 300, 30,
//                                      hAppWindow, NULL, hInstance, NULL);
//         SendMessage(hAppName, WM_SETFONT, (WPARAM)fontTitle, TRUE);

//         HWND hSectionHeader = CreateWindow(TEXT("STATIC"), TEXT("Controller-to-Mouse Controls:"),
//                                            WS_VISIBLE | WS_CHILD,
//                                            20, 70, 300, 25,
//                                            hAppWindow, NULL, hInstance, NULL);
//         SendMessage(hSectionHeader, WM_SETFONT, (WPARAM)fontHeader, TRUE);

//         const TCHAR* controlsText[] = {
//             TEXT("Left Stick  → Mouse Movement"),
//             TEXT("Right Trigger (RT) → Scroll Down"),
//             TEXT("Left Trigger (LT)  → Scroll Up"),
//             TEXT("RB + LB      → Toggle Cursor Speed"),
//             TEXT("A Button      → Left Click"),
//             TEXT("B Button      → Right Click")
//         };
        

//         int y = 110;
//         for (int i = 0; i < 6; ++i, y += 30) {
//             HWND hLine = CreateWindow(TEXT("STATIC"), controlsText[i],
//                                       WS_VISIBLE | WS_CHILD,
//                                       40, y, 400, 25,
//                                       hAppWindow, NULL, hInstance, NULL);
//             SendMessage(hLine, WM_SETFONT, (WPARAM)fontBody, TRUE);
//         }
//         HWND hFooter = CreateWindow(TEXT("STATIC"), TEXT("© Rushil Maradugula 2025"),
//         WS_VISIBLE | WS_CHILD | SS_CENTER,
//         0, 350, 500, 25,
//         hAppWindow, NULL, hInstance, NULL);
//         SendMessage(hFooter, WM_SETFONT, (WPARAM)fontBody, TRUE);
//         HWND hGitHub = CreateWindow(TEXT("STATIC"), TEXT("GitHub Repository"),
//         WS_VISIBLE | WS_CHILD | SS_NOTIFY,
//         170, 320, 160, 25,
//         hAppWindow, (HMENU)1, hInstance, NULL);
//         SendMessage(hGitHub, WM_SETFONT, (WPARAM)fontBody, TRUE);
//         SetWindowTextColor(hGitHub, RGB(0, 102, 204));  // Optional: blue like a link



//         CenterWindow(hAppWindow);
//     }

//     ShowWindow(hAppWindow, SW_SHOW);
//     SetForegroundWindow(hAppWindow);
// }

// #include "window.h"
// #include "style/fonts.h"
// #include "style/ui.h"
// #include <uxtheme.h>
// #include <windowsx.h>
// #include "resource.h"
// #pragma comment(lib, "uxtheme.lib")

// HWND hAppWindow = NULL;

// LRESULT CALLBACK AppWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//     switch (message) {
//         case WM_CLOSE:
//             ShowWindow(hWnd, SW_HIDE);
//             return 0;

//         case WM_COMMAND:
//             if (LOWORD(wParam) == 1) { // ID of the GitHub label
//                 ShellExecute(NULL, TEXT("open"), TEXT("https://github.com/Rushil54/joytrack"), NULL, NULL, SW_SHOWNORMAL);
//                 return 0;
//             }
//             break;
//         case WM_SETCURSOR:
//             if ((HWND)wParam == GetDlgItem(hWnd, 1)) {
//                 SetCursor(LoadCursor(NULL, IDC_HAND));
//                 return TRUE;
//             }
//             break;

//     }
//     return DefWindowProc(hWnd, message, wParam, lParam);
// }


// void ShowAppWindow(HINSTANCE hInstance) {
//     if (!hAppWindow) {
//         const TCHAR CLASS_NAME[] = TEXT("JoyTrackAppWindow");

//         WNDCLASS wc = {};
//         wc.lpfnWndProc = AppWindowProc;
//         wc.hInstance = hInstance;
//         wc.lpszClassName = CLASS_NAME;
//         wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
//         RegisterClass(&wc);

//         hAppWindow = CreateWindow(CLASS_NAME, TEXT("JoyTrack Controls"),
//                                     WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
//                                     CW_USEDEFAULT, CW_USEDEFAULT,
//                                     500, 420,
//                                     NULL, NULL, hInstance, NULL);

//         HFONT fontTitle  = CreateUIFont(20);
//         HFONT fontHeader = CreateUIFont(14);
//         HFONT fontBody   = CreateUIFont(12);

//         // Logo
//         HWND hLogo = CreateWindow(TEXT("STATIC"), NULL,
//                                   WS_VISIBLE | WS_CHILD | SS_ICON,
//                                   20, 20, 32, 32,
//                                   hAppWindow, NULL, hInstance, NULL);
//         SendMessage(hLogo, STM_SETICON, (WPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON)), 0);

//         // App Name
//         HWND hAppName = CreateWindow(TEXT("STATIC"), TEXT("JoyTrack"),
//                                      WS_VISIBLE | WS_CHILD,
//                                      60, 25, 300, 30,
//                                      hAppWindow, NULL, hInstance, NULL);
//         SendMessage(hAppName, WM_SETFONT, (WPARAM)fontTitle, TRUE);

//         // Header
//         HWND hSectionHeader = CreateWindow(TEXT("STATIC"), TEXT("Controller-to-Mouse Controls:"),
//                                            WS_VISIBLE | WS_CHILD,
//                                            20, 70, 300, 25,
//                                            hAppWindow, NULL, hInstance, NULL);
//         SendMessage(hSectionHeader, WM_SETFONT, (WPARAM)fontHeader, TRUE);

//         // Controls
//         const char* controlsText[] = {
//             "Left Stick          → Mouse Movement",
//             "Right Trigger (RT)  → Scroll Down",
//             "Left Trigger (LT)   → Scroll Up",
//             "RB + LB             → Toggle Cursor Speed",
//             "A Button            → Left Click",
//             "B Button            → Right Click"
//         };

//         int y = 110;
//         for (int i = 0; i < 6; ++i, y += 30) {
//             HWND hLine = CreateWindowA("STATIC", controlsText[i],
//                                        WS_VISIBLE | WS_CHILD,
//                                        40, y, 400, 25,
//                                        hAppWindow, NULL, hInstance, NULL);
//             SendMessage(hLine, WM_SETFONT, (WPARAM)fontBody, TRUE);
//         }
//         HWND hFooter = CreateWindow(TEXT("STATIC"), TEXT("© Rushil Maradugula 2025"),
//         WS_VISIBLE | WS_CHILD | SS_CENTER,
//         0, 350, 500, 25,
//         hAppWindow, NULL, hInstance, NULL);
//         SendMessage(hFooter, WM_SETFONT, (WPARAM)fontBody, TRUE);

//         // GitHub Link
//         HWND hGitHub = CreateWindow(TEXT("STATIC"), TEXT("View on GitHub"),
//                                     WS_VISIBLE | WS_CHILD | SS_NOTIFY,
//                                     40, y + 20, 200, 25,
//                                     hAppWindow, (HMENU)1, hInstance, NULL);
//         SendMessage(hGitHub, WM_SETFONT, (WPARAM)fontHeader, TRUE);
//         SetWindowTheme(hGitHub, L"Explorer", NULL); // Optional: modern link look

//         CenterWindow(hAppWindow);
//     }

//     ShowWindow(hAppWindow, SW_SHOW);
//     SetForegroundWindow(hAppWindow);
// }

// window.cpp - Updated with proper DPI, background, font, and character rendering
// window.cpp - Updated with proper DPI, background, font, and character rendering
#define UNICODE
#define _UNICODE

#include "style/ui.h"
#include "style/fonts.h"
#include <windows.h>
#include <shellapi.h>
#include <uxtheme.h>
#include "resource.h"
// #pragma comment(lib, "uxtheme.lib")

//static HINSTANCE hAppInstance = NULL;
static HINSTANCE storedInstance = NULL;
HWND hGitHub;

//extern HINSTANCE hInstance;
HWND hAppWindow = NULL;

LRESULT CALLBACK AppWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void OpenGitHubRepo() {
    ShellExecute(NULL, L"open", L"https://github.com/Rushil54/joytrack", NULL, NULL, SW_SHOWNORMAL);
}

void ShowAppWindow(HINSTANCE hInstance) {
    storedInstance = hInstance;
    SetProcessDPIAware();

    if (hAppWindow) {
        ShowWindow(hAppWindow, SW_SHOW);
        SetForegroundWindow(hAppWindow);
        return;
    }

    const wchar_t CLASS_NAME[] = L"JoyTrackAppWindow";

    WNDCLASS wc = { };
    wc.lpfnWndProc = AppWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!GetClassInfo(hInstance, CLASS_NAME, &wc)) {
        RegisterClass(&wc);
    }

    hAppWindow = CreateWindowEx(
        0,
        CLASS_NAME, TEXT("JoyTrack Controls"),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 900, 695,
        NULL, NULL, hInstance, NULL);

    // Font setup
    HFONT fontTitle   = CreateUIFont(24, true);
    HFONT fontSection = CreateUIFont(18, true);
    HFONT fontBody    = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                   DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
                                   CLEARTYPE_QUALITY, FIXED_PITCH, TEXT("Consolas")); // Monospace!
    HFONT fontFooter  = CreateUIFont(14);

    // Title
    HWND hTitle = CreateWindow(TEXT("STATIC"), TEXT("JoyTrack"),
                               WS_VISIBLE | WS_CHILD | SS_CENTER,
                               (900 - 300) / 2, 20, 300, 40,
                               hAppWindow, NULL, hInstance, NULL);
    SendMessage(hTitle, WM_SETFONT, (WPARAM)fontTitle, TRUE);

    // Section Header
    HWND hSection = CreateWindow(TEXT("STATIC"), TEXT("Controller-to-Mouse Controls:"),
                                 WS_VISIBLE | WS_CHILD | SS_LEFT,
                                 40, 80, 620, 25,
                                 hAppWindow, NULL, hInstance, NULL);
    SendMessage(hSection, WM_SETFONT, (WPARAM)fontSection, TRUE);

    // Controls text (with extra spacing for alignment)
    LPCWSTR controlsText[] = {
        L"Left Stick        → Mouse Movement 1x",
        L"Right Stick       → Mouse Movement 0.5x",
        L"RT                → Scroll Down",
        L"LT                → Scroll Up",
        L"RB                → Go Forward",
        L"LB                → Go Back",
        L"A Button          → Left Click",
        L"B Button          → Right Click",
        L"X Button          → Scroll Button",
        L"Y Button          → 2x Speed Boost",
        L"D_PAD Up          → Pause/Play",
        L"D_PAD Down        → Full Screen(F)",
        L"D_PAD Left        → Left Arrow(→)",
        L"D_PAD Right       → Right Arrow(←)",
        L"Select + Start    → Alt + Tab",
    };

    int y = 120;
    for (int i = 0; i < 15; ++i, y += 30) {
        HWND hLine = CreateWindow(TEXT("STATIC"), controlsText[i],
                                  WS_VISIBLE | WS_CHILD | SS_LEFT,
                                  40, y, 620, 25,
                                  hAppWindow, NULL, hInstance, NULL);
        SendMessage(hLine, WM_SETFONT, (WPARAM)fontBody, TRUE);
    }

    // GitHub link
    hGitHub = CreateWindow(TEXT("STATIC"), TEXT("View on GitHub"),
                           WS_VISIBLE | WS_CHILD | SS_NOTIFY,
                           20, 620, 200, 20,
                           hAppWindow, (HMENU)1, hInstance, NULL);
    SendMessage(hGitHub, WM_SETFONT, (WPARAM)fontSection, TRUE);
    SetWindowTheme(hGitHub, L"Explorer", NULL);  // gives blue look

    CreateWindow(TEXT("STATIC"), NULL,
                                   WS_VISIBLE | WS_CHILD | SS_ETCHEDHORZ,
                                   20, 610, 860, 2,
                                   hAppWindow, NULL, hInstance, NULL);

    // Footer centered at bottom
    HWND hFooter = CreateWindow(TEXT("STATIC"), TEXT("© Rushil Maradugula 2025"),
                                WS_VISIBLE | WS_CHILD | SS_RIGHT,
                                580, 620, 300, 20,
                                hAppWindow, NULL, hInstance, NULL);
    SendMessage(hFooter, WM_SETFONT, (WPARAM)fontFooter, TRUE);

    ShowWindow(hAppWindow, SW_SHOW);
    SetForegroundWindow(hAppWindow);
}


LRESULT CALLBACK AppWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); // Light background

    switch (uMsg) {
        case WM_CLOSE:
            ShowWindow(hwnd, SW_HIDE);
            return 0;

        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            HWND hwndStatic = (HWND)lParam;

            if (hwndStatic == hGitHub) {
                SetTextColor(hdcStatic, RGB(0, 102, 204));  // Blue
                SetBkMode(hdcStatic, TRANSPARENT);
            }

            return (INT_PTR)hBrush;  // Use your custom white background brush
        }

        case WM_SETCURSOR: {
            if ((HWND)wParam == hGitHub) {
                SetCursor(LoadCursor(NULL, IDC_HAND));
                return TRUE;
            }
            break;
        }

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                OpenGitHubRepo();
                return 0;
            }
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void ShowAppWindow() {
    if (storedInstance) {
        ShowAppWindow(storedInstance);
    }
}