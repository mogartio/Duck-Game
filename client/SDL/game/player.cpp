#include "player.h"

#include <cassert>
#include <iostream>
#include <vector>

// ----------------- Initialize Images -----------------

void Player::initializeWingImage(WingState wingState) {
    std::string wingType = file + wingState_to_string(wingState);

    std::shared_ptr<Image> image = std::make_shared<Image>();
    image->initialize(rend, wingType);
    wings.push_back(image);
}

void Player::initialiceDuckImages(DuckState state) {
    std::vector<std::shared_ptr<Image>> images;
    std::string action = file + duckState_to_string(state);

    if (state == DuckState::WALK) {
        for (int i = 1; i <= 5; i++) {
            std::string walk_action = action + std::to_string(i) + ".png";
            std::shared_ptr<Image> additionalImage = std::make_shared<Image>();
            additionalImage->initialize(rend, walk_action);
            images.push_back(additionalImage);
        }
    } else {
        std::shared_ptr<Image> image = std::make_shared<Image>();
        image->initialize(rend, action);
        images.push_back(image);
    }

    ducks.emplace(state, std::move(images));
}

// ----------------- Constructor -----------------

Player::Player(SDL_Renderer* rend, Color color):
        rend(rend),
        flip(SDL_FLIP_NONE),
        file("assets/game_assets/ducks/"),
        weaponON(false),
        armorOn(false),
        helmetOn(false) {

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
        const std::vector<std::shared_ptr<Image>>& patos =
                pair.second;  // Obtener el vector de imágenes
        for (auto pato: patos) {
            pato->queryTexture();
            pato->defineSize(height, width);
        }
    }

    for (auto ala: wings) {
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
        this->side = LEFT;
    } else if (side == RIGHT) {
        flip = SDL_FLIP_NONE;
        this->side = RIGHT;
    }

    if ((side == UP) && (this->side == RIGHT)) {
        weaponAngle = -90.0;
    } else if ((side == UP) && (this->side == LEFT)) {
        weaponAngle = 90.0;
    } else {
        weaponAngle = 0.0;
    }

    // Actualizo la image del ala y su posicion
    updateWing(x, y);

    // Actualizo posicion de armadura
    if (armorOn) {
        _armor->position(x, y);
        _hombro->position(x, y);
    }

    // Actualizo posicion del arma
    if (weaponON) {  // Falta agregar offsets (perdon facu)
        _weapon->position(x, y);
    }

    // Actualizo posicion del casco
    if (helmetOn) {
        _helmet->position(x, y - 8);
    }
}

void Player::standing() {
    std::pair<int, int> position = duck->getPosition();
    state = DuckState::STANDING;
    duck = ducks[state][0];
    duck->position(position.first, position.second);
}

void Player::dropEverithing() {
    weaponON = false;
    armorOn = false;
    helmetOn = false;
}

// ----------------- Weapon -----------------

void Player::weapon(std::shared_ptr<Image> weapon) {
    _weapon = weapon;
    weaponON = true;
    weaponAngle = 0.0;
}

bool Player::dropWeapon() {
    bool originalWeaponstate = weaponON;
    weaponON = false;
    return originalWeaponstate;
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

void Player::armor(std::shared_ptr<Image> armor, std::shared_ptr<Image> hombro) {
    _armor = armor;
    _hombro = hombro;
    std::pair<int, int> position = duck->getPosition();
    _armor->position(position.first, position.second);
    _hombro->position(position.first, position.second);
    armorOn = true;
}

bool Player::dropArmor() {
    bool originalArmorState = armorOn;
    armorOn = false;
    return originalArmorState;
}

// ----------------- Helmet -----------------

void Player::helmet(std::shared_ptr<Image> helmet) {
    _helmet = helmet;
    std::pair<int, int> position = duck->getPosition();
    _helmet->position(position.first, position.second - 8);
    helmetOn = true;
}

bool Player::dropHelmet() {
    bool originalHelmetState = helmetOn;
    helmetOn = false;
    return originalHelmetState;
}

// ----------------- Fill -----------------

void Player::fill() {  // Esta todo en el orden en el que debe ser dibujado
    // Dibujo el cueerpo dl pato
    duck->fill(flip);

    std::pair<int, int> position = duck->getPosition();

    // Dibujo el casco que tiene el pato
    if (helmetOn) {
        _helmet->position(position.first, position.second - 13);
        _helmet->fill(flip);
    }

    // Dibujo la armadura que tiene el pato
    if (armorOn) {
        _armor->position(position.first, position.second);
        _armor->fill(flip);
    }

    // Dibujo el arma que tiene el pato
    if (weaponON && (state != DuckState::SLOW_FALL) && (state != DuckState::PLAY_DEAD)) {
        int wx = position.first + 5;
        int wy = position.second + 36;
        if (flip == SDL_FLIP_HORIZONTAL) {
            if (weaponAngle != 0.0) {
                wy -= 10;
                wx += 5;
            }
        } else {
            wx += 32;
            if (weaponAngle != 0.0) {
                wx -= 3;
                wy -= 7;
            }
        }
        _weapon->position(wx, wy);
        _weapon->fill(weaponAngle, flip);
    }

    // Dibujo el ala del pato
    if (state != DuckState::PLAY_DEAD) {
        wing->fill(flip);
    }

    // Dibujo el hombro de la armadura
    if (armorOn) {
        _hombro->position(position.first, position.second);
        _hombro->fill(flip);
    }
}

// ----------------- Get Position -----------------

std::pair<int, int> Player::getPosition() const { return duck->getPosition(); }

// ----------------- Destructor -----------------

Player::~Player() {
    // No se necesita liberar memoria de las imagenes porque se hace en el destructor de Image
}
