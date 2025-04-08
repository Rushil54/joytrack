#include <iostream>
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "Xinput9_1_0.lib")

const double BASE_SENSITIVITY = 10.0;
const double PRECISION_SENSITIVITY = BASE_SENSITIVITY / 4.0; // 4x slower for right joystick
const int DEADZONE = 8000;
bool speedBoost = false;
bool prevDpadUp = false, prevDpadDown = false, prevDpadLeft = false, prevDpadRight = false;
bool prevA = false, prevB = false;

// Function to get cursor sensitivity
double getSensitivity(bool precision) {
    return precision ? PRECISION_SENSITIVITY : (speedBoost ? BASE_SENSITIVITY * 2 : BASE_SENSITIVITY);
}

// Function to move the mouse
void moveMouse(int dx, int dy) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

// Function to simulate mouse clicks
void clickMouse(DWORD flag) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = flag;
    SendInput(1, &input, sizeof(INPUT));
    
    input.mi.dwFlags = (flag == MOUSEEVENTF_LEFTDOWN) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

// Function to scroll the mouse
void scrollMouse(int amount) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.mouseData = amount;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    SendInput(1, &input, sizeof(INPUT));
}

// Function to simulate keyboard key press
void keyPress(WORD key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    SendInput(1, &input, sizeof(INPUT));
    
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    
    std::cout << "Joystick detected. Move to control mouse...\n";

    while (true) {
        if (XInputGetState(0, &state) == ERROR_SUCCESS) {
            SHORT lx = state.Gamepad.sThumbLX;
            SHORT ly = state.Gamepad.sThumbLY;
            SHORT rx = state.Gamepad.sThumbRX;
            SHORT ry = state.Gamepad.sThumbRY;
            bool rb = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
            bool lb = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
            bool aPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
            bool bPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
            bool dpadUp = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
            bool dpadDown = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
            bool dpadLeft = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
            bool dpadRight = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
            bool selectPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
            bool startPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
            bool xPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
            bool yPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;

            // Speed Boost Toggle
            speedBoost = rb && lb;

            // Apply Deadzone & Move Mouse (Left Joystick)
            int moveX = 0, moveY = 0;
            if (abs(lx) > DEADZONE) moveX = (lx * getSensitivity(false)) / 32768;
            if (abs(ly) > DEADZONE) moveY = -(ly * getSensitivity(false)) / 32768;
            moveMouse(moveX, moveY);

            // Apply Deadzone & Move Mouse (Right Joystick - Precision)
            int moveRX = 0, moveRY = 0;
            if (abs(rx) > DEADZONE) moveRX = (rx * getSensitivity(true)) / 32768;
            if (abs(ry) > DEADZONE) moveRY = -(ry * getSensitivity(true)) / 32768;
            moveMouse(moveRX, moveRY);

            // Click Actions (Single Click)
            if (aPressed && !prevA) clickMouse(MOUSEEVENTF_LEFTDOWN);
            if (bPressed && !prevB) clickMouse(MOUSEEVENTF_RIGHTDOWN);
            prevA = aPressed;
            prevB = bPressed;

            // Scroll Actions
            int scrollAmount = (speedBoost) ? 240 : 30;
            if (state.Gamepad.bRightTrigger > 50) scrollMouse(scrollAmount);
            if (state.Gamepad.bLeftTrigger > 50) scrollMouse(-scrollAmount);

            // D-Pad Actions
            if (dpadLeft && !prevDpadLeft) keyPress(VK_LEFT);
            if (dpadRight && !prevDpadRight) keyPress(VK_RIGHT);
            if (dpadUp && !prevDpadUp) scrollMouse(120);
            if (dpadDown && !prevDpadDown) scrollMouse(-120);
            prevDpadLeft = dpadLeft;
            prevDpadRight = dpadRight;
            prevDpadUp = dpadUp;
            prevDpadDown = dpadDown;

            // System Navigation
            if (rb) keyPress(VK_MENU), keyPress(VK_RIGHT); // Alt + Right
            if (lb) keyPress(VK_MENU), keyPress(VK_LEFT); // Alt + Left

            // ALT+TAB replaced with WIN+TAB
            if ((selectPressed || startPressed) && !(prevDpadUp || prevDpadDown || prevDpadLeft || prevDpadRight)) {
                keyPress(VK_LWIN);
                keyPress(VK_TAB);
            }

            // X Button (Maximize Window)
            if (xPressed) {
                keyPress(VK_LWIN);
                keyPress(VK_UP);
            }

            // Y Button (Close Tab Fix)
            if (yPressed) {
                keyPress(VK_CONTROL);
                keyPress('W');
            }
        }
        Sleep(10);
    }
    return 0;
}
//shitty one dont follow