#include "editor_screen.h"

EditorScreen::EditorScreen(int width, int height) {
    setFocusPolicy(Qt::StrongFocus);
    
    // each number of width and height represents a tile in the game, then the height and width will draw a matrix
    this->width = width;
    this->height = height;

}