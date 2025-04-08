#include "ui.h"

// HFONT CreateUIFont(int size, bool bold) {
//     return CreateFont(
//         size, 0, 0, 0,
//         bold ? FW_BOLD : FW_NORMAL,
//         FALSE, FALSE, FALSE,
//         ANSI_CHARSET,
//         OUT_DEFAULT_PRECIS,
//         CLIP_DEFAULT_PRECIS,
//         DEFAULT_QUALITY,
//         DEFAULT_PITCH | FF_SWISS,
//         TEXT("Segoe UI")
//     );
// }

void CenterWindow(HWND hWnd) {
    RECT rect;
    GetWindowRect(hWnd, &rect);

    int winWidth = rect.right - rect.left;
    int winHeight = rect.bottom - rect.top;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int x = (screenWidth - winWidth) / 2;
    int y = (screenHeight - winHeight) / 2;

    SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}
