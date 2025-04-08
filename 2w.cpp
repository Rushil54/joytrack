#include <iostream>
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "Xinput.lib")

const double MOUSE_SENSITIVITY = 2.0;
const int DEADZONE = 8000;

void moveMouse(int dx, int dy) {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    std::cout << "Controller detected. Press Ctrl+C to exit.\n";

    while (true) {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        if (XInputGetState(0, &state) == ERROR_SUCCESS) {
            int lx = state.Gamepad.sThumbLX;
            int ly = state.Gamepad.sThumbLY;

            if (abs(lx) > DEADZONE || abs(ly) > DEADZONE) {
                int moveX = (abs(lx) > DEADZONE) ? (lx * MOUSE_SENSITIVITY) / 32768 : 0;
                int moveY = (abs(ly) > DEADZONE) ? (-ly * MOUSE_SENSITIVITY) / 32768 : 0;

                moveMouse(moveX, moveY);
            }
        }

        Sleep(5); // Sleep to prevent high CPU usage
    }

    return 0;
}
