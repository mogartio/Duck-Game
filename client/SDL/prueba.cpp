#include <SDL2/SDL.h>            // Incluye la biblioteca principal de SDL
#include <SDL2/SDL_image.h>      // Incluye la biblioteca para manejar imágenes
#include <SDL2/SDL_timer.h>      // Incluye la biblioteca para manejar temporizadores

int main(int argc, char* argv[]) {
    // Inicializa todos los subsistemas de SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError()); // Imprime el error si la inicialización falla
        return 1; // Sale del programa con código de error
    }

    // Crea una ventana de 800x600 píxeles, centrada en la pantalla y redimensionable
    SDL_Window* win = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED, // Posición X centrada
                                       SDL_WINDOWPOS_CENTERED, // Posición Y centrada
                                       800,                     // Ancho de la ventana
                                       600,                     // Alto de la ventana
                                       SDL_WINDOW_RESIZABLE);  // Permite que la ventana sea redimensionable

    // Configura las opciones del renderizador (aceleración por hardware)
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags); // Crea el renderizador asociado a la ventana

    // Carga la imagen de fondo
    SDL_Surface* backgroundSurface = IMG_Load("img_src/background/day.png"); // Asegúrate de usar el camino correcto a tu imagen
    SDL_Texture* backgroundTex = SDL_CreateTextureFromSurface(rend, backgroundSurface);
    SDL_FreeSurface(backgroundSurface); // Libera la superficie una vez que la textura está creada

    // Carga una imagen desde un archivo y la convierte en una superficie
    SDL_Surface* surface = IMG_Load("img_src/ducks/grey/standing.png"); // Asegúrate de que el archivo "cuadrado" esté en la misma carpeta
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface); // Crea una textura a partir de la superficie
    SDL_FreeSurface(surface); // Libera la superficie original, ya no se necesita

    SDL_Surface* grayWing = IMG_Load("img_src/ducks/grey/wing/normal.png"); // Asegúrate de que el archivo "cuadrado" esté en la misma carpeta
    SDL_Texture* texGrayWing = SDL_CreateTextureFromSurface(rend, grayWing); // Crea una textura a partir de la superficie
    SDL_FreeSurface(grayWing); // Libera la superficie original, ya no se necesita

    // Carga una imagen desde un archivo y la convierte en una superficie
    SDL_Surface* surface2 = IMG_Load("img_src/ducks/white/standing.png"); // Asegúrate de que el archivo "cuadrado2" esté en la misma carpeta
    SDL_Texture* tex2 = SDL_CreateTextureFromSurface(rend, surface2); // Crea una textura a partir de la superficie
    SDL_FreeSurface(surface2); // Libera la superficie original, ya no se necesita

    SDL_Surface* whiteWing = IMG_Load("img_src/ducks/white/wing/normal.png"); // Asegúrate de que el archivo "cuadrado" esté en la misma carpeta
    SDL_Texture* texWhiteWing = SDL_CreateTextureFromSurface(rend, whiteWing); // Crea una textura a partir de la superficie
    SDL_FreeSurface(whiteWing); // Libera la superficie original, ya no se necesita


    // Crea un rectángulo para controlar la posición y el tamaño de la textura
    SDL_Rect dest, dest2, destWing, destWing2;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h); // Consulta el ancho y alto de la textura
    SDL_QueryTexture(tex2, NULL, NULL, &dest2.w, &dest2.h);
    SDL_QueryTexture(texGrayWing, NULL, NULL, &destWing.w, &destWing.h);
    SDL_QueryTexture(texWhiteWing, NULL, NULL, &destWing2.w, &destWing2.h);

    dest.w = 50; // Reduce el ancho a 50 de ccuadrado
    dest.h = 50; // Reduce la altura a 50 de cuadrado
    dest.x = (800 - dest.w) / 2; // Centra horizontalmente el rectángulo en la ventana
    dest.y = (600 - dest.h) / 2; // Centra verticalmente el rectángulo en la ventana

    destWing.w = 23; 
    destWing.h = 23; 
    destWing.x = (794 - destWing.w) / 2; 
    destWing.y = (600 - destWing.h) / 2; 

    dest2.w = 50; 
    dest2.h = 50; 
    dest2.x = (800 - dest2.w) / 2 + 150; 
    dest2.y = (600 - dest2.h) / 2 + 150;

    destWing2.w = 23; 
    destWing2.h = 23; 
    destWing2.x = (794 - destWing2.w) / 2 + 150; 
    destWing2.y = (600 - destWing2.h) / 2 + 150; 

    // Variables de control del programa
    int close = 0; // Variable para controlar si se debe cerrar la ventana
    int speed = 200; // Velocidad de movimiento del objeto
    int window_width = 800; // Ancho de la ventana
    int window_height = 600; // Alto de la ventana

    // Variables para controlar el movimiento en ambas direcciones
    int vel_x = 0; // Velocidad en la dirección X
    int vel_y = 0; // Velocidad en la dirección Y

    int vel_x2 = 0;
    int vel_y2 = 0;

    SDL_RendererFlip flip1 = SDL_FLIP_NONE;
    SDL_RendererFlip flip2 = SDL_FLIP_NONE;

    int offsetX = 10;

    // Bucle principal del programa
    while (!close) {
        SDL_Event event; // Estructura para manejar eventos

        // Procesa los eventos en la cola
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: // Evento de cerrar la ventana
                    close = 1; // Establece la variable para cerrar el programa
                    break;

                case SDL_WINDOWEVENT: // Evento relacionado con la ventana
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        // Si la ventana ha sido redimensionada, actualiza sus dimensiones
                        window_width = event.window.data1; // Nuevo ancho
                        window_height = event.window.data2; // Nuevo alto
                    }
                    break;

                case SDL_KEYDOWN: // Evento de tecla presionada
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W: // Tecla W
                            vel_y2 = -speed / 30; // Mueve hacia arriba
                            break;
                        case SDL_SCANCODE_UP: // Flecha arriba
                            vel_y = -speed / 30; // Mueve hacia arriba
                            break;
                        case SDL_SCANCODE_S: // Tecla S
                            vel_y2 = speed / 30; // Mueve hacia abajo
                            break;
                        case SDL_SCANCODE_DOWN: // Flecha abajo
                            vel_y = speed / 30; // Mueve hacia abajo
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                            vel_x2 = -speed / 30; // Mueve hacia la izquierda
                            flip2 = SDL_FLIP_HORIZONTAL;
                            break;
                        case SDL_SCANCODE_LEFT: // Flecha izquierda
                            vel_x = -speed / 30; // Mueve hacia la izquierda
                            flip1 = SDL_FLIP_HORIZONTAL;
                            break;
                        case SDL_SCANCODE_D: // Tecla D
                            vel_x2 = speed / 30; // Mueve hacia la derecha
                            flip2 = SDL_FLIP_NONE;
                            break;
                        case SDL_SCANCODE_RIGHT: // Flecha derecha
                            vel_x = speed / 30; // Mueve hacia la derecha
                            flip1 = SDL_FLIP_NONE;
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;

                case SDL_KEYUP: // Evento de tecla soltada
                    // Detiene el movimiento cuando se sueltan las teclas
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W: // Tecla W
                        case SDL_SCANCODE_S: // Tecla S
                            vel_y2 = 0; // Detiene el movimiento vertical
                            break;
                        case SDL_SCANCODE_UP: // Flecha arriba
                        case SDL_SCANCODE_DOWN: // Flecha abajo
                            vel_y = 0; // Detiene el movimiento vertical
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                        case SDL_SCANCODE_D: // Tecla D
                            vel_x2 = 0; // Detiene el movimiento horizontal
                            break;
                        case SDL_SCANCODE_LEFT: // Flecha izquierda
                        case SDL_SCANCODE_RIGHT: // Flecha derecha
                            vel_x = 0; // Detiene el movimiento horizontal
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;
            }
        }

        // Actualiza la posición del objeto basándose en su velocidad
        dest.x += vel_x; // Actualiza la posición X
        dest.y += vel_y; // Actualiza la posición Y
        destWing.y += vel_y;

        if (flip1 == SDL_FLIP_HORIZONTAL) {
            destWing.x = dest.x + 1.7*offsetX;
        } else {
            destWing.x = dest.x + offsetX;
        }

        dest2.x += vel_x2;
        dest2.y += vel_y2;
        destWing2.y += vel_y2;

        if (flip2 == SDL_FLIP_HORIZONTAL) {
            destWing2.x = dest2.x + 1.7*offsetX;
        } else {
            destWing2.x = dest2.x + offsetX;
        }

        // Asegura que el objeto no salga de los límites de la ventana
        if (dest.x + dest.w > window_width) dest.x = window_width - dest.w; // Límite derecho
        if (dest.x < 0) dest.x = 0; // Límite izquierdo
        if (dest.y + dest.h > window_height) dest.y = window_height - dest.h; // Límite inferior
        if (dest.y < 0) dest.y = 0; // Límite superior

        if (destWing.x + destWing.w > window_width) destWing.x = window_width - destWing.w;
        if (destWing.x < 0) destWing.x = 0;
        if (destWing.y + destWing.h > window_height) destWing.y = window_height - destWing.h;
        if (destWing.y < 0) destWing.y = 0;

        if (dest2.x + dest2.w > window_width) dest2.x = window_width - dest2.w;
        if (dest2.x < 0) dest2.x = 0;
        if (dest2.y + dest2.h > window_height) dest2.y = window_height - dest2.h;
        if (dest2.y < 0) dest2.y = 0;

        if (destWing2.x + destWing2.w > window_width) destWing2.x = window_width - destWing2.w;
        if (destWing2.x < 0) destWing2.x = 0;
        if (destWing2.y + destWing2.h > window_height) destWing2.y = window_height - destWing2.h;
        if (destWing2.y < 0) destWing2.y = 0;

        // Renderiza el objeto en la ventana
        SDL_RenderClear(rend); // Limpia la pantalla
        SDL_RenderCopy(rend, backgroundTex, NULL, NULL); // Dibuja la textura de fondo
        SDL_RenderCopyEx(rend, tex, NULL, &dest, 0, NULL, flip1);
        SDL_RenderCopyEx(rend, texGrayWing, NULL, &destWing, 0, NULL, flip1);
        SDL_RenderCopyEx(rend, tex2, NULL, &dest2, 0, NULL, flip2);
        SDL_RenderCopyEx(rend, texWhiteWing, NULL, &destWing2, 0, NULL, flip2);
        SDL_RenderPresent(rend); // Muestra el renderizado en la ventana

        // Controla la frecuencia de cuadros por segundo (FPS)
        SDL_Delay(1000 / 60); // Espera para mantener 60 FPS
    }

    // Limpieza de recursos
    SDL_DestroyTexture(tex); // Libera la textura
    SDL_DestroyTexture(texGrayWing);
    SDL_DestroyTexture(tex2);
    SDL_DestroyTexture(texWhiteWing);
    SDL_DestroyTexture(backgroundTex); // Libera la textura del fondo
    SDL_DestroyRenderer(rend); // Libera el renderizador
    SDL_DestroyWindow(win); // Libera la ventana
    SDL_Quit(); // Finaliza SDL

    return 0; // Termina el programa correctamente
}

