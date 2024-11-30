#include "window.h"
#include <iostream>

Window::Window(int w, int h) {
    int errCode = SDL_CreateWindowAndRenderer(w, h, SDL_RENDERER_ACCELERATED, &win, &rend);
    if ((errCode == -1)) {
        std::cout << "Error de creacion de window y renderer " << std::endl;
        throw std::runtime_error(SDL_GetError());
    }
}

SDL_Renderer* Window::get_rend() {
    return rend;
}

void Window::clear() {
    SDL_RenderClear(rend);
}

void Window::fill() {
    SDL_RenderPresent(this->rend);
}

Window::~Window() {
    if (rend != nullptr) {
        SDL_DestroyRenderer(rend);
        rend = nullptr;
    }
    if (win != nullptr) {
        SDL_DestroyWindow(win);
        win = nullptr;
    }
}