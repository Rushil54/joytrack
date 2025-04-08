# 🎮 JoyTrack

**JoyTrack** is a lightweight Windows application that turns your plug-and-play USB controller into a fully functional mouse. It runs in the background with a system tray icon and provides seamless control over mouse movement, clicks, and scrolling using your game controller.

## ✨ Features

- 🕹️ Control your mouse using joysticks  
- 🖱️ Left/Right click mapped to controller buttons (A/B)  
- 🔄 Scroll using triggers (RT/LT)  
- ⚡ Change cursor speed with Y button  
- 🎯 Runs quietly in the background  
- ✅ Launches only one instance at a time  
- 🪟 Minimal tray UI with controls and GitHub link  

## Controls
- Left Stick        → Mouse Movement 1x
- Right Stick       → Mouse Movement 0.5x
- RT                → Scroll Down
- LT                → Scroll Up
- RB                → Go Forward
- LB                → Go Back
- A Button          → Left Click
- B Button          → Right Click
- X Button          → Scroll Button
- Y Button          → 2x Speed Boost
- D_PAD Up          → Pause/Play
- D_PAD Down        → Full Screen(F)
- D_PAD Left        → Left Arrow(→)
- D_PAD Right       → Right Arrow(←)
- Select + Start    → Alt + Tab

## 🚀 How to Use

1. Plug in your USB controller  
2. Launch `JoyTrack.exe`  
3. Click the tray icon to view app info and controls  
4. Use your controller to move and click like a mouse!  
5. Exit from the tray icon when you're done  

## Requirements
- Windows 10 or 11

## 🛠️ Building from Source

### Prerequisites
- `g++` with MinGW-w64  
- `windres` for embedding resources  
- `make` (optional, if you want to use the Makefile)  

### Build Instructions
```bash
windres res/icon.rc -O coff -o res/icon.res
g++ -std=c++17 -g -Wall -Wextra src/main.cpp src/tray.cpp src/app.cpp src/window.cpp src/style/ui.cpp res/icon.res -o JoyTrack.exe -mwindows -lcomctl32 -lXinput -luxtheme


