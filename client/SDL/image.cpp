#include <SDL2/SDL_image.h>

#include "image.h"

Image::Image(SDL_Renderer* rend, std::string img) : rend(rend) {
    SDL_Surface* imgSurface = IMG_Load(img.c_str());
    SDL_Texture* imgTex = SDL_CreateTextureFromSurface(rend, imgSurface);
    this->imgTex = imgTex;
    SDL_FreeSurface(imgSurface); // Libera la superficie una vez que la textura está creada
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

Image::~Image() {
    SDL_DestroyTexture(imgTex); // Libera la textura
}

