import pyautogui
import inputs
import time
import threading

# Sensitivity settings
MOUSE_SENSITIVITY_X = 2  # Adjust horizontal sensitivity
MOUSE_SENSITIVITY_Y = 1.5  # Adjust vertical sensitivity separately
SCROLL_SENSITIVITY = 1
DEADZONE = 10  # Ignore small joystick movements
SMOOTHING_FACTOR = 0.3  # Exponential smoothing for smoother movement

prev_x, prev_y = 0, 0  # Store previous movement values for smoothing

def process_controller():
    global prev_x, prev_y
    while True:
        events = inputs.get_gamepad()
        for event in events:
            if event.ev_type == "Absolute":
                if event.code == "ABS_X":  # Left analog stick (horizontal)
                    move_x = (event.state - 128)
                    if abs(move_x) > DEADZONE:
                        move_x = (move_x / 128) * MOUSE_SENSITIVITY_X
                        move_x = (SMOOTHING_FACTOR * move_x) + ((1 - SMOOTHING_FACTOR) * prev_x)  # Apply smoothing
                        prev_x = move_x
                        pyautogui.moveRel(move_x, 0, duration=0)
                elif event.code == "ABS_Y":  # Left analog stick (vertical)
                    move_y = (event.state - 128)
                    if abs(move_y) > DEADZONE:
                        move_y = (move_y / 128) * MOUSE_SENSITIVITY_Y
                        move_y = (SMOOTHING_FACTOR * move_y) + ((1 - SMOOTHING_FACTOR) * prev_y)  # Apply smoothing
                        prev_y = move_y
                        pyautogui.moveRel(0, move_y, duration=0)
                elif event.code == "ABS_RY":  # Right analog stick (vertical) for scrolling
                    scroll = (event.state - 128)
                    if abs(scroll) > DEADZONE:
                        scroll = (scroll / 128) * SCROLL_SENSITIVITY
                        pyautogui.scroll(-int(scroll))
            elif event.ev_type == "Key":
                if event.code == "BTN_SOUTH" and event.state == 1:  # A button for left-click
                    pyautogui.click()
                elif event.code == "BTN_EAST" and event.state == 1:  # B button for right-click
                    pyautogui.rightClick()
        time.sleep(0.005)  # Reduce sleep time for lower latency

if __name__ == "__main__":
    print("Controller-to-Mouse script running... Press Ctrl+C to stop.")
    thread = threading.Thread(target=process_controller)
    thread.daemon = True
    thread.start()
    while True:
        time.sleep(1)
