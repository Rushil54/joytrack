#include <iostream>
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "Xinput9_1_0.lib")

const double BASE_SENSITIVITY = 10.0;
const int DEADZONE = 8000;
bool speedBoost = false;
bool prevDpadUp = false, prevDpadDown = false, prevDpadLeft = false, prevDpadRight = false;
bool prevA = false, prevB = false, prevX = false;
bool prevRB = false, prevLB = false;
bool altHeld = false;
bool prevStart = false;

// Function to get cursor sensitivity
double getSensitivity() {
    return speedBoost ? BASE_SENSITIVITY * 2 : BASE_SENSITIVITY;
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
void keyPress(WORD key, bool hold = false) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    SendInput(1, &input, sizeof(INPUT));
    
    if (!hold) {
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
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
            bool xPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
            bool yPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
            bool dpadUp = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
            bool dpadDown = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
            bool dpadLeft = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
            bool dpadRight = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
            bool selectPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
            bool startPressed = state.Gamepad.wButtons & XINPUT_GAMEPAD_START;

            // Speed Boost Toggle
            speedBoost = yPressed;

            // Apply Deadzone for Left Joystick (Cursor Movement)
            int moveX = 0, moveY = 0;
            if (abs(lx) > DEADZONE) moveX = (lx * getSensitivity()) / 32768;
            if (abs(ly) > DEADZONE) moveY = -(ly * getSensitivity()) / 32768;
            moveMouse(moveX, moveY);

            // Apply Deadzone for Right Joystick (Precision Movement, Reduced Speed)
            int precisionX = 0, precisionY = 0;
            if (abs(rx) > DEADZONE) precisionX = (rx * getSensitivity() / 2) / 32768;
            if (abs(ry) > DEADZONE) precisionY = -(ry * getSensitivity() / 2) / 32768;
            moveMouse(precisionX, precisionY);

            // Click Actions (Single Click)
            if (aPressed && !prevA) clickMouse(MOUSEEVENTF_LEFTDOWN);
            if (bPressed && !prevB) clickMouse(MOUSEEVENTF_RIGHTDOWN);
            if (xPressed && !prevX) clickMouse(MOUSEEVENTF_MIDDLEDOWN);
            prevA = aPressed;
            prevB = bPressed;
            prevX = xPressed;

            // Scroll Actions
            int scrollAmount = (speedBoost) ? 240 : 30;
            if (state.Gamepad.bRightTrigger > 50) scrollMouse(-scrollAmount);
            if (state.Gamepad.bLeftTrigger > 50) scrollMouse(scrollAmount);

            // D-Pad Actions (Single Press)
            if (dpadUp && !prevDpadUp) keyPress(VK_MEDIA_PLAY_PAUSE);
            if (dpadDown && !prevDpadDown) keyPress(0x46); // 'F' for fullscreen
            if (dpadLeft && !prevDpadLeft) keyPress(VK_LEFT); // Seek Backwards
            if (dpadRight && !prevDpadRight) keyPress(VK_RIGHT); // Seek Forwards
            
            prevDpadUp = dpadUp;
            prevDpadDown = dpadDown;
            prevDpadLeft = dpadLeft;
            prevDpadRight = dpadRight;

            // X and Y Buttons
            if (yPressed) speedBoost = true;

            // RB & LB Actions (System-Wide Back/Forward)
            if (rb && !prevRB) keyPress(VK_BROWSER_FORWARD);
            if (lb && !prevLB) keyPress(VK_BROWSER_BACK);
            prevRB = rb;
            prevLB = lb;

            // Alt + Tab Handling
            if (selectPressed && !altHeld) {
                keyPress(VK_MENU, true); // Hold Alt
                altHeld = true;
            }
            if (startPressed && !prevStart) keyPress(VK_TAB); // Single Tab Press
            if (!selectPressed && altHeld) {
                keyPress(VK_MENU, false); // Release Alt
                altHeld = false;
            }
			prevStart = startPressed;
        }
        Sleep(10);
    }
    return 0;
}
