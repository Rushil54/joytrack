#include <iostream>
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "Xinput9_1_0.lib")

const double BASE_SENSITIVITY = 10.0; // Increased 5x from previous 2.0
const int DEADZONE = 8000;
bool speedBoost = false;

double getSensitivity() {
    return speedBoost ? BASE_SENSITIVITY * 2 : BASE_SENSITIVITY;
}

double getScrollSpeed() {
    return speedBoost ? 60 : 30; // Light scrolling, speed boost applied
}

void moveMouse(int dx, int dy) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

void clickMouse(DWORD flag) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = flag;
    SendInput(1, &input, sizeof(INPUT));
    
    // Release click
    input.mi.dwFlags = (flag == MOUSEEVENTF_LEFTDOWN) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void scrollMouse(int amount) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.mouseData = amount;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    bool prevA = false, prevB = false;

    std::cout << "Joystick detected. Move to control mouse...\n";

    while (true) {
        if (XInputGetState(0, &state) == ERROR_SUCCESS) {
            SHORT lx = state.Gamepad.sThumbLX;
            SHORT ly = state.Gamepad.sThumbLY;
            bool rb = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
            bool lb = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
            bool aPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
            bool bPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_B;

            // Speed Boost Toggle
            speedBoost = rb && lb;

            // Apply Deadzone
            int moveX = 0, moveY = 0;
            if (abs(lx) > DEADZONE) moveX = (lx * getSensitivity()) / 32768;
            if (abs(ly) > DEADZONE) moveY = -(ly * getSensitivity()) / 32768;

            moveMouse(moveX, moveY);

            // Click Actions (only trigger on button press, not hold)
            if (aPressed && !prevA) clickMouse(MOUSEEVENTF_LEFTDOWN);
            if (bPressed && !prevB) clickMouse(MOUSEEVENTF_RIGHTDOWN);

            prevA = aPressed;
            prevB = bPressed;

            // Inverted Scroll Actions (RT scrolls DOWN, LT scrolls UP)
            if (state.Gamepad.bRightTrigger > 50) scrollMouse(-getScrollSpeed()); // Scroll down
            if (state.Gamepad.bLeftTrigger > 50) scrollMouse(getScrollSpeed()); // Scroll up
        }
        Sleep(10);
    }
    return 0;
}
