#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "image.h"

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Crea una ventana
    SDL_Window* win = SDL_CreateWindow("DUCK GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       800,                     // Ancho de la ventana
                                       600,                     // Alto de la ventana
                                       SDL_WINDOW_RESIZABLE);

    // Configura las opciones del renderizador (aceleración por hardware)
    // TODO: A chequear los flags
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // --------------------Imagenes--------------------
    Image background(rend, "img_src/background/day.webp");
    Image player(rend, "img_src/ducks/grey");
    Image otherPlayer(rend, "img_src/ducks/white");

    // --------------------QueryTexture--------------------
    /*
     * //Agrego un dest y una linea Query por imagen
     * SDL_Rect dest;
     * SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
     */

    int close = 0; // Variable para controlar si se debe cerrar la ventana
    int speed = 200; // Velocidad de movimiento del objeto

    // Bucle principal del programa
    while (!close) {
        SDL_Event event;

        // Procesa los eventos en la cola
        while (SDL_PollEvent(&event)) {
            /*
                switch(event.type) { }
            */ 
        }

        // Renderiza el objeto en la ventana
        SDL_RenderClear(rend); // Limpia la pantalla
        /*
            Dibuja fondos, pesonajes y extras
        */
        SDL_RenderPresent(rend); // Muestra el renderizado en la ventana

        // Controla la frecuencia de cuadros por segundo (FPS)
        SDL_Delay(1000 / 60); // Espera para mantener 60 FPS
    }

    // Libera de recursos
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}




