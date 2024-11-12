#include "player.h"

#include <iostream>
#include <vector>

#define OFFSETX 7
#define OFFSETY 13

void Player::chooseColor(Color color) {
    switch (color) {
        case WHITE:
            file += "white/";
            break;
        case GREY:
            file += "grey/";
            break;
        case ORANGE:
            file += "orange/";
            break;
        case YELLOW:
            file += "yellow/";
            break;
        default:
            break;
    }
}

void Player::initializeWingImage(WingState wingState) {
    std::string wingType = file + wingState_to_string(wingState);
    // Crear el objeto Image y luego inicializarlo
    Image* image = new Image();
    image->initialize(rend, wingType);
    wings.push_back(image);
}

void Player::initialiceDuckImages(DuckState state) {
    std::vector<Image*> images;
    std::string action = file + duckState_to_string(state);

    if (state == DuckState::WALK) {
        for (int i = 1; i <= 5; i++) {
            std::string walk_action = action + std::to_string(i) + ".png";
            Image* additionalImage = new Image();
            additionalImage->initialize(rend, walk_action);
            images.push_back(additionalImage);
        }
    } else {
        // Crear el objeto Image y luego inicializarlo
        Image* image = new Image();
        image->initialize(rend, action);
        images.push_back(image);
    }

    ducks.emplace(state, std::move(images));
}


Player::Player(SDL_Renderer* rend, Color color):
        rend(rend), flip(SDL_FLIP_NONE), file("img_src/ducks/"), weaponON(false) {

    walk = 0;
    chooseColor(color);


    // Crea el primer pato y lo agrega al hashmap
    for (int i = int(DuckState::STANDING); i <= int(DuckState::PLAY_DEAD); i++) {
        DuckState duckState = static_cast<DuckState>(i);
        initialiceDuckImages(duckState);
    }

    duck = ducks[DuckState::STANDING][0];

    // Crea el ala normal y la agrega al hashmap
    for (int j = int(WingState::NORMAL); j <= int(WingState::FLAPDOWN); j++) {
        WingState wingState = static_cast<WingState>(j);
        initializeWingImage(wingState);
    }

    wing = wings[int(WingState::NORMAL)];
}

void Player::defineSize(int height, int width) {
    this->height = height;
    this->width = width;
    for (const auto& pair: ducks) {
        const std::vector<Image*>& patos = pair.second;  // Obtener el vector de imágenes
        for (Image* pato: patos) {
            pato->queryTexture();
            pato->defineSize(height, width);
        }
    }

    for (Image* ala: wings) {
        ala->queryTexture();
        ala->defineSize(int(15 * height / 25), int(15 * width / 25));
    }
    // El tamaño original de los png son del pato 24x24 y del ala 15x15
}

void Player::updateWing(int x, int y) {

    // Actualiza imagen del ala
    if (state == DuckState::SLOW_FALL) {
        if (flapup) {
            wing = wings[int(WingState::FLAPUP)];
            flapup = false;
        } else {
            wing = wings[int(WingState::FLAPDOWN)];
            flapup = true;
        }
    } else {
        if (weaponON) {
            wing = wings[int(WingState::HOLD)];
        } else {
            wing = wings[int(WingState::NORMAL)];
        }
    }

    uint offset_x = width / 4;
    uint offset_y = (height) / 4;

    // Actualiza posicion del ala
    if (flip == SDL_FLIP_HORIZONTAL) {
        wing->position(x + offset_x, y + offset_y);
    } else {
        wing->position(x + 0.5 * offset_x, y + offset_y);
    }
}

void Player::update(int x, int y, DuckState state, Side side) {
    this->state = state;
    this->x = x;
    this->y = y;

    // Actualizo la imagen del pato y su posicion
    if (state == DuckState::WALK) {
        duck = ducks[state][this->walk];
        if (this->walk == 4) {
            this->walk = 0;
        } else {
            this->walk++;
        }
    } else {
        duck = ducks[state][0];
    }

    duck->position(x, y);
    // std::cout << "player position: " << x << " , " << y << std::endl;

    if (side == LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }

    // Actualizo la image del ala y su posicion
    updateWing(x, y);
}

void Player::fill() {
    // Dibujo el cueerpo dl pato
    duck->fill(flip);

    // Dibujo el arma que tiene el pato
    if (weaponON && (state != DuckState::SLOW_FALL) && (state != DuckState::PLAY_DEAD)) {
        // weapon.fill(flip);
    }

    // Dibujo el ala del pato
    if (state != DuckState::PLAY_DEAD) {
        wing->fill(flip);
    }
}

void Player::weapon() {
    if (weaponON) {  // Dropeo
        weaponON = false;
        // Actualizo pos del arma cuando la suelto
        /* y suelto el arma que tenia */
    } else {
        weaponON = true;
        /* me llega y actualizo el arma que tengo*/
    }
}

void Player::shoot() {
    if (!weaponON) {
        return;  // Si no tiene unn arma no hace nada
    }

    /*
        Disparo el arma
        Me fijo cuantos usos le quedan
        En caso de quedarse sin usos la dropeo (la mato), weaponON = false y actualizo el alita

    */
}

std::pair<int, int> Player::getPosition() { return std::make_pair(x, y); }

Player::~Player() {
    for (Image* wing: wings) {
        delete wing;
    }

    for (const auto& pair: ducks) {
        const std::vector<Image*>& images = pair.second;  // Obtener el vector de imágenes
        for (Image* image: images) {
            delete image;
        }
    }
}
