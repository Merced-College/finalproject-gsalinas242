# The Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++17 -O3

# The name of your app
TARGET = Fairy

# Source files
SOURCES = main.cpp Battery.cpp Companion.cpp Event.cpp Login.cpp Motivation_Messages.cpp Time.cpp Weather.cpp

# This converts the .cpp list into .o (object) files
OBJECTS = $(SOURCES:.cpp=.o)

# Detect the OS
UNAME := $(shell uname 2>/dev/null || echo Windows)

ifeq ($(UNAME), Darwin)
    # Detect if Apple Silicon or Intel
    ARCH := $(shell uname -m)

    ifeq ($(ARCH), arm64)
        # Apple Silicon (M1/M2/M3) - Homebrew at /opt/homebrew
        CPPFLAGS = -I/opt/homebrew/include -I/opt/homebrew/opt/raylib/include -I/opt/homebrew/opt/curl/include
        LDFLAGS  = -L/opt/homebrew/lib -L/opt/homebrew/opt/raylib/lib -L/opt/homebrew/opt/curl/lib
    else
        # Intel Mac - Homebrew at /usr/local
        CPPFLAGS = -I/usr/local/include -I/usr/local/opt/raylib/include -I/usr/local/opt/curl/include
        LDFLAGS  = -L/usr/local/lib -L/usr/local/opt/raylib/lib -L/usr/local/opt/curl/lib
    endif
 	# macOS Frameworks (same for both Intel and Apple Silicon)
    LIBS = -lraylib -lcurl -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
	
else ifeq ($(UNAME), Linux)
    # Linux
    CPPFLAGS = -I/usr/include
    LDFLAGS  = -L/usr/lib
    LIBS     = -lraylib -lcurl -lGL -lm -lpthread -ldl -lrt -lX11

else
    # Windows (MinGW)
    TARGET   = Fairy.exe
    CPPFLAGS = -IC:/raylib/include -IC:/curl/include
    LDFLAGS  = -LC:/raylib/lib -LC:/curl/lib
    LIBS     = -lraylib -lcurl -lopengl32 -lgdi32 -lwinmm -lws2_32
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all run clean