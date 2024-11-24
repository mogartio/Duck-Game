#include "editor_main_window.h"

EditorMainWindow::EditorMainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Duck Game - Level Editor");
    resize(1920, 1080);

    // hide top bar
    // setWindowFlags(Qt::FramelessWindowHint);

    stackedWidget = std::make_shared<QStackedWidget>(this);
    setCentralWidget(stackedWidget.get());

    setInitialValuesScreen = std::make_shared<SetInitialValuesScreen>();

    stackedWidget->addWidget(setInitialValuesScreen.get());

    stackedWidget->setCurrentWidget(setInitialValuesScreen.get());

    // Connect the signal from the SetInitialValuesScreen to the EditorMainWindow to receive columns and rows values
    connect(setInitialValuesScreen.get(), &SetInitialValuesScreen::sendInitialValues, this, &EditorMainWindow::receiveValues);

}

void EditorMainWindow::receiveValues(int columns, int rows, std::string theme) {
    this->columns = columns;
    this->rows = rows;
    this->theme = theme;
    loadImagesGivenTheme(theme);
    showEditorScreen();
}

void EditorMainWindow::showEditorScreen() {    
    editorScreen = std::make_shared<EditorScreen>(columns, rows, map_of_maps);
    stackedWidget->addWidget(editorScreen.get());

    QWidget *overlay = new QWidget(this);
    overlay->setStyleSheet("background-color: black;");
    overlay->setGeometry(this->rect());
    overlay->show();

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    overlay->setGraphicsEffect(effect);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(1000);
    fadeOut->setStartValue(0);
    fadeOut->setEndValue(1);

    connect(fadeOut, &QPropertyAnimation::finished, [this, overlay]() {
        stackedWidget->setCurrentWidget(editorScreen.get());
        QPropertyAnimation *fadeIn = new QPropertyAnimation(overlay->graphicsEffect(), "opacity");
        fadeIn->setDuration(1000);
        fadeIn->setStartValue(1);
        fadeIn->setEndValue(0);

        connect(fadeIn, &QPropertyAnimation::finished, overlay, &QWidget::deleteLater);
        fadeIn->start(QPropertyAnimation::DeleteWhenStopped);
    });

    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
}

void EditorMainWindow::loadImagesGivenTheme(std::string theme) {
    // for now only load the light theme + weapons + players

    // load tiles
    std::map<std::string, std::shared_ptr<QPixmap>> tiles_map;
    tiles_map["grass"] = std::make_shared<QPixmap>("assets/game_assets/tiles/dayTiles/grass.png");
    tiles_map["rock"] = std::make_shared<QPixmap>("assets/game_assets/tiles/dayTiles/rock.png");
    tiles_map["column"] = std::make_shared<QPixmap>("assets/game_assets/tiles/dayTiles/column.png");
    tiles_map["background"] = std::make_shared<QPixmap>("assets/game_assets/background/day.png");

    map_of_maps["tiles"] = tiles_map;

    // load weapons
    std::map<std::string, std::shared_ptr<QPixmap>> weapons;
    weapons["ak47"] = std::make_shared<QPixmap>("assets/game_assets/weapons/ak47.png");
    weapons["banana"] = std::make_shared<QPixmap>("assets/game_assets/weapons/banana.png");
    weapons["cowboy pistol"] = std::make_shared<QPixmap>("assets/game_assets/weapons/cowboy.png");
    weapons["duel pistol"] = std::make_shared<QPixmap>("assets/game_assets/weapons/duelos.png");
    weapons["shotgun"] = std::make_shared<QPixmap>("assets/game_assets/weapons/escopeta.png");
    weapons["grenade"] = std::make_shared<QPixmap>("assets/game_assets/weapons/granada.png");
    weapons["laser rifle"] = std::make_shared<QPixmap>("assets/game_assets/weapons/laserRifle.png");
    weapons["magnum"] = std::make_shared<QPixmap>("assets/game_assets/weapons/magnum.png");
    weapons["pew pew laser"] = std::make_shared<QPixmap>("assets/game_assets/weapons/pewpewlaser.png");
    weapons["sniper"] = std::make_shared<QPixmap>("assets/game_assets/weapons/sniper.png");
    
    map_of_maps["weapons"] = weapons;

    // load armor 
    std::map<std::string, std::shared_ptr<QPixmap>> armor;
    armor["armor1"] = std::make_shared<QPixmap>("assets/game_assets/armor/armor.png");
    armor["knight helmet"] = std::make_shared<QPixmap>("assets/game_assets/helmets/knight.png");

    map_of_maps["armor"] = armor;

    // load player
    std::map<std::string, std::shared_ptr<QPixmap>> players;
    players["player1"] = std::make_shared<QPixmap>("assets/game_assets/ducks/white/standing.png");
    players["player2"] = std::make_shared<QPixmap>("assets/game_assets/ducks/yellow/standing.png");
    players["player3"] = std::make_shared<QPixmap>("assets/game_assets/ducks/orange/standing.png");
    players["player4"] = std::make_shared<QPixmap>("assets/game_assets/ducks/grey/standing.png");

    map_of_maps["players"] = players;

}