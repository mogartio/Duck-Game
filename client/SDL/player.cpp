#include "player.h"

#define OFFSETX 10

enum Color {
    WHITE,
    GREY,
    ORANGE,
    YELLOW
};

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

void Player::checkWingHashmap(WingState wingState) {
    if (wings.find(wingState) == wings.end()) {
        wingType = file + "wing/" + to_string(wingState);
        wings[wingState] = Image(rend, wingType);
    }

    *wing = wings[wingState];
}

void Player::updateWing(int x, int y) {
    if (state == SLOW_FALL) {
        if (flapup) {
            checkWingHashmap(FLAPUP);
            flapup = false;
        } else {
            checkWingHashmap(FLAPDOWN);
            flapup = true;
        }
    } else {
        if (weaponON) {
            checkWingHashmap(HOLD);
        } else {
            checkWingHashmap(NORMAL);
        }
    }

    if (flip = SDL_FLIP_HORIZONTAL) {
        wing->position(x + 1.7*OFFSETX, y);
    } else {
        wing->position(x + OFFSETX, y);
    }

}

Player::Player(SDL_Renderer* rend, Color color): rend(rend), flip(SDL_FLIP_NONE), file("img_src/ducks/"), weaponON(false), walk1(true) {
    
    chooseColor(color);

    // Crea el primer pato y lo agrega al hashmap
    action = file + "standing.png";
    ducks[STANDING] = Image(rend, action);
    *(this->duck) = ducks[STANDING];
    
    // Crea el ala normal y la agrega al hashmap
    wingType = file + "wing/normal.png";
    wings[NORMAL] = Image(rend, wingType);
    *(this->wing) = wings[NORMAL];

    // -------- QueryTexture --------
    this->duck->queryTexture();
    this->wing->queryTexture();
}

void Player::defineSize(int height, int width) {
    duck->defineSize(height, width);
    wing->defineSize(int(15*height/32), int(15*width/32));
    // El tamaño original de los png son del pato 32x32 y del ala 15x15
}


void Player::update(int x, int y, DuckState state, Side side) {
    this->state = state;

    if (ducks.find(state) == ducks.end()) { 
        if (!walk1) {
            action = file + to_string(state, false);
        } else {
            action = file + to_string(state);
        }
        ducks[state] = Image(rend, action);
    }

    *duck = ducks[state];
    duck->position(x, y);
    
    if (side == LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    updateWing(x, y);
}

void Player::fill() {
    duck->fill(flip);
    if (weaponON) {
        //weapon.fill();
    }

    if (state != PLAY_DEAD) {
        wing->fill(flip);
    }
}

void Player::weapon() {
    if (weaponON) {
        weaponON = false;
        /* y suelto el arma que tenia */
    } else {
        weaponON = true;
        /* me llega y actualizo el arma que tengo*/
    }
}

void Player::shoot() {
    if (!weaponON) {
        return; // Si no tiene unn arma no hace nada
    }

    /*
        Disparo el arma
        Me fijo cuantos usos le quedan
        En caso de quedarse sin usos la dropeo (la mato), weaponON = false y actualizo el alita
        
    */
}
