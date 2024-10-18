CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf

TARGET = prueba
SRC = prueba.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(SDL_FLAGS)

clean:
	rm -f $(TARGET)
