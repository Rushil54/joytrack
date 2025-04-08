# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -mwindows -lcomctl32 -lXinput -luxtheme

# Source and object files
SRC = \
    src/main.cpp \
    src/tray.cpp \
    src/app.cpp \
    src/window.cpp \
    src/style/ui.cpp

RES = res/icon.res
OUT = JoyTrack.exe

all: $(OUT)

$(OUT): $(SRC) $(RES)
	$(CXX) $(CXXFLAGS) $(SRC) $(RES) -o $(OUT) $(LDFLAGS)

res/icon.res: res/icon.rc res/app.ico
	windres res/icon.rc -O coff -o res/icon.res

clean:
	del /Q $(OUT) res\icon.res 2>nul || exit 0

.PHONY: all clean

# windres res/icon.rc -O coff -o res/icon.res  
# g++ -std=c++17 -O2 src/main.cpp src/tray.cpp src/app.cpp src/window.cpp src/style/ui.cpp res/icon.res -o JoyTrack.exe -mwindows -lcomctl32 -lXinput -luxtheme