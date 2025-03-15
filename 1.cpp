#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <libevdev/libevdev.h>

const double MOUSE_SENSITIVITY = 2.0;
const int DEADZONE = 8000;

void moveMouse(int dx, int dy) {
    // Simulate mouse movement with the X, Y delta
    // Linux doesn't have native mouse simulation in evdev. You can use xdotool for that
    system(("xdotool mousemove_relative -- " + std::to_string(dx) + " " + std::to_string(dy)).c_str());
}

int main() {
    const char* joystick_path = "/dev/input/eventX"; // Replace with your joystick's event device path
    
    int fd = open(joystick_path, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Unable to open joystick device: " << joystick_path << std::endl;
        return 1;
    }

    struct libevdev* dev = NULL;
    int rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        std::cerr << "Failed to initialize libevdev" << std::endl;
        return 1;
    }

    std::cout << "Joystick detected. Press Ctrl+C to exit.\n";

    while (true) {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);

        if (rc == 0 && ev.type == EV_ABS) {
            if (ev.code == ABS_X || ev.code == ABS_Y) {
                int value = ev.value;

                // Apply deadzone filtering and sensitivity adjustments
                if (abs(value) > DEADZONE) {
                    int moveX = (ev.code == ABS_X) ? (value * MOUSE_SENSITIVITY) / 32768 : 0;
                    int moveY = (ev.code == ABS_Y) ? (value * MOUSE_SENSITIVITY) / 32768 : 0;

                    moveMouse(moveX, moveY);
                }
            }
        }

        usleep(5000); // Sleep for 5ms to avoid overwhelming the CPU
    }

    libevdev_free(dev);
    close(fd);
    return 0;
}
