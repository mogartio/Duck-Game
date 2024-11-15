#include "player.h"

#include <iostream>
#include <vector>

// ----------------- Initialize Images -----------------

void Player::initializeWingImage(WingState wingState) {
    std::string wingType = file + wingState_to_string(wingState);

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
        Image* image = new Image();
        image->initialize(rend, action);
        images.push_back(image);
    }

    ducks.emplace(state, std::move(images));
}

// ----------------- Constructor -----------------

Player::Player(SDL_Renderer* rend, Color color):
        rend(rend), flip(SDL_FLIP_NONE), file("img_src/ducks/"), weaponON(false), armorOn(false), helmetOn(false) {

    walk = 0;
    file += color_to_string(color);

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

// ----------------- Player -----------------

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
        ala->defineSize(height, width);
    }
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

    // Actualiza posicion del ala
    wing->position(x, y);
}

void Player::update(int x, int y, DuckState state, Side side) {
    this->state = state;

    // Actualizo la imagen del pato y su posicion
    if (state == DuckState::WALK) {
        duck = ducks[state][this->walk];
        if (this->walk == 4) {
            this->walk = 0;
        } else {
            this->walk++;
        }
    } else {
        duck = ducks[this->state][0];
    }

    duck->position(x, y);

    if (side == LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }

    // Actualizo la image del ala y su posicion
    updateWing(x, y);

    // Actualizo posicion de armadura
    if (armorOn) {
        _armor->position(x, y);
        _hombro->position(x, y);
    }

    // Actualizo posicion del arma
    if(weaponON) { // Falta agregar offsets (perdon facu)
        _weapon->position(x, y);
    }

    // Actualizo posicion del casco
    if (helmetOn) {
        _helmet->position(x, y - 8);
    }
}

void Player::dropEverithing() {
    weaponON = false;
    armorOn = false;
    helmetOn = false;
}

// ----------------- Weapon -----------------

void Player::weapon(Image* weapon) {
    _weapon = weapon;
    weaponON = true;
}

void Player::dropWeapon() {
    weaponON = false;
}

void Player::shoot() {
    if (!weaponON) {
        return;  // Si no tiene un arma no hace nada
    }

    /*
        Disparo el arma
    */
}

// ----------------- Armor -----------------

void Player::armor(Image* armor, Image* hombro) {
    if (armorOn) {
        armorOn = false;
        return;
    }
    _armor = armor;
    _hombro = hombro;
    std::pair<int, int> position = duck->getPosition();
    _armor->position(position.first, position.second);
    _hombro->position(position.first, position.second);
    armorOn = true;
}

// ----------------- Helmet -----------------

void Player::helmet(Image* helmet) {
    if (helmetOn) {
        helmetOn = false;
        return;
    }
    _helmet = helmet;
    std::pair<int, int> position = duck->getPosition();
    _helmet->position(position.first, position.second - 8);
    helmetOn = true;
}

// ----------------- Fill -----------------

void Player::fill() { // Esta todo en el orden en el que debe ser dibujado
    // Dibujo el cueerpo dl pato
    duck->fill(flip);

    // Dibujo el casco que tiene el pato
    if (helmetOn) {
        _helmet->fill(flip);
    }

    // Dibujo la armadura que tiene el pato
    if (armorOn) {
        _armor->fill(flip);
    }

    // Dibujo el arma que tiene el pato
    if (weaponON && (state != DuckState::SLOW_FALL) && (state != DuckState::PLAY_DEAD)) {
        _weapon->fill(flip);
    }

    // Dibujo el ala del pato
    if (state != DuckState::PLAY_DEAD) {
        wing->fill(flip);
    }

    // Dibujo el hombro de la armadura
    if (armorOn) {
        _hombro->fill(flip);
    }
}

// ----------------- Get Position -----------------

std::pair<int, int> Player::getPosition() const {
    return duck->getPosition();
}

// ----------------- Destructor -----------------

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
