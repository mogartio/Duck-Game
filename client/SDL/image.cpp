#include "image.h"

Image::Image(SDL_Renderer* rend, std::string img) : rend(rend), img(img) {
    SDL_Surface* imgSurface = IMG_Load(img.c_str()); // Asegúrate de usar el camino correcto a tu imagen
    SDL_Texture* imgTex = SDL_CreateTextureFromSurface(rend, imgSurface);
    this->imgTex = imgTex;
    SDL_FreeSurface(imgSurface); // Libera la superficie una vez que la textura está creada
}

void Image::fill(SDL_Rect* dest) {
    SDL_RenderCopy(rend, imgTex, NULL, dest); // Dibuja
}

Image::~Image() {
    SDL_DestroyTexture(imgTex); // Libera la textura del fondo
}

