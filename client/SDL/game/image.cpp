#include <SDL2/SDL_image.h>

#include "image.h"
#include <iostream>

Image::Image() : rend(nullptr), imgTex(nullptr) {}

void Image::initialize(SDL_Renderer* rend, const std::string& img) {
    this->rend = rend;
    imgTex = IMG_LoadTexture(rend, img.c_str());
    if (imgTex == nullptr) {
        std::cout << "Error de textura de imagen ";
        throw std::runtime_error(SDL_GetError());
    }

}

void Image::fill(bool background) {
    if (background) { // Dibuja el fondo
        SDL_RenderCopy(rend, imgTex, NULL, NULL); // Dibuja
    } else { // Dibuja los tiles y las armas que no pertenecen a ningun pato
        SDL_RenderCopy(rend, imgTex, NULL, &dest); // Dibuja
    }
}

void Image::fill(SDL_RendererFlip flip) {
    SDL_RenderCopyEx(rend, imgTex, NULL, &dest, 0, NULL, flip); // Dibuja
}

void Image::fill(double angle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(rend, imgTex, NULL, &dest, angle, NULL, flip); // Dibuja
}

void Image::queryTexture() {
    SDL_QueryTexture(imgTex, NULL, NULL, &dest.w, &dest.h);
}

void Image::defineSize(int height, int width) {
    dest.h = height;
    dest.w = width;
}

void Image::position(int x, int y) {
    dest.x = x;
    dest.y = y;
}

std::pair<int, int> Image::getPosition() const {
    return std::pair(dest.x, dest.y);
}

Image::~Image() {
    if (imgTex != nullptr) {
        SDL_DestroyTexture(imgTex); // Libera la textura
        imgTex = nullptr;
    }

}
