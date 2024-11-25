#include "editor_screen.h"
#include <cmath>


EditorScreen::EditorScreen(int columns, int rows, std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps)
    : map_of_maps(map_of_maps), columns(columns), rows(rows), scale(1.0), isDragging(false), offsetX(0), offsetY(0) {
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(1920, 1080); // Ensure the editor screen is fixed to 1920x1080
    
    currentTile = "";
    isPainting = false;
    isErasing = false;\
    gridVisible = true;
    // Initialize the matrix with 0s. Each cell is actually 4x4 server tiles
    editor_matrix.resize(rows, std::vector<int>(columns, 0)); 

    // Load custom font
    int fontId = QFontDatabase::addApplicationFont("assets/menu_assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = new QFont(fontFamily);
    // Load button sound
    buttonSound = new QSound("assets/menu_assets/Retro3.wav");

    // Extract the background tile from the map of maps
    background_tile = map_of_maps["tiles"]["background"];
    if (!background_tile || background_tile->isNull()) {
        QMessageBox::warning(this, "Error", "Failed to load background tile.");
        return;
    }
    *background_tile = background_tile->scaled(1920, 1080, Qt::KeepAspectRatioByExpanding);

    // rectangle where the buttons will be
    RoundedRectangle* roundedRectangle = new RoundedRectangle(this, 0, 0, 1920, 60, QColor(255, 255, 255, 150), QColor(255, 255, 255, 150), 10);
    roundedRectangle->setParent(this);

    // draw tiles button -> dropdown menu
    tilesMenuButton = new QPushButton("Tiles", this);
    tilesMenuButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    tilesMenuButton->setFont(*customFont);
    tilesMenuButton->setGeometry(10, 10, 100, 40);
    // add menu
    QFont actionFont = *customFont;
    actionFont.setPointSize(20);

    tilesMenu = new QMenu(this);
    tilesMenu->setFont(actionFont);
    tilesMenu->setFixedWidth(150);
    QAction *grass = new QAction(QIcon("assets/game_assets/tiles/dayTiles/grass.png"), "grass", this);
    tilesMenu->addAction(grass);
    QAction *rock = new QAction(QIcon("assets/game_assets/tiles/dayTiles/rock.png"), "rock", this);
    tilesMenu->addAction(rock);
    QAction *column = new QAction(QIcon("assets/game_assets/tiles/dayTiles/column.png"), "column", this);
    tilesMenu->addAction(column);

    connect(tilesMenuButton, &QPushButton::clicked, this, &EditorScreen::showTilesMenu);

    connect(grass, &QAction::triggered, this, [this]() { startDrag("tiles"); });
    connect(rock, &QAction::triggered, this, [this]() { startDrag("tiles"); });
    connect(column, &QAction::triggered, this, [this]() { startDrag("tiles"); });
    
    setAcceptDrops(true);

    // add weapons menu
    weaponsMenuButton = new QPushButton("Weapons", this);
    weaponsMenuButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    weaponsMenuButton->setFont(*customFont);
    weaponsMenuButton->setGeometry(120, 10, 150, 40);
    // add menu
    weaponsMenu = new QMenu(this);
    weaponsMenu->setFont(actionFont);
    weaponsMenu->setFixedWidth(250);
    QAction *ak47 = new QAction(QIcon("assets/game_assets/weapons/ak47.png"), "ak47", this);
    weaponsMenu->addAction(ak47);
    QAction *banana = new QAction(QIcon("assets/game_assets/weapons/banana.png"), "banana", this);
    weaponsMenu->addAction(banana);
    QAction *cowboy_pistol = new QAction(QIcon("assets/game_assets/weapons/cowboy.png"), "cowboy pistol", this);
    weaponsMenu->addAction(cowboy_pistol);
    QAction *duelos = new QAction(QIcon("assets/game_assets/weapons/duelos.png"), "duel pistol", this);
    weaponsMenu->addAction(duelos);
    QAction *shotgun = new QAction(QIcon("assets/game_assets/weapons/escopeta.png"), "shotgun", this);
    weaponsMenu->addAction(shotgun);
    QAction *grenade = new QAction(QIcon("assets/game_assets/weapons/granada.png"), "grenade", this);
    weaponsMenu->addAction(grenade);
    QAction *magnum = new QAction(QIcon("assets/game_assets/weapons/magnum.png"), "magnum", this);
    weaponsMenu->addAction(magnum);
    QAction *sniper = new QAction(QIcon("assets/game_assets/weapons/sniper.png"), "sniper", this);
    weaponsMenu->addAction(sniper);
    QAction *laserRifle = new QAction(QIcon("assets/game_assets/weapons/laserRifle.png"), "laser rifle", this);
    weaponsMenu->addAction(laserRifle);
    QAction *pewpewlaser = new QAction(QIcon("assets/game_assets/weapons/pewpewlaser.png"), "pew pew laser", this);
    weaponsMenu->addAction(pewpewlaser);

    connect(weaponsMenuButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        weaponsMenu->exec(weaponsMenuButton->mapToGlobal(QPoint(0, weaponsMenuButton->height())));
    });

    connect(ak47, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(banana, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(cowboy_pistol, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(duelos, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(shotgun, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(grenade, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(magnum, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(sniper, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(laserRifle, &QAction::triggered, this, [this]() { startDrag("weapons"); });
    connect(pewpewlaser, &QAction::triggered, this, [this]() { startDrag("weapons"); });

    // add players button
    players_set = std::set<std::string>();
    playersMenuButton = new QPushButton("Players", this);
    playersMenuButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    playersMenuButton->setFont(*customFont);
    playersMenuButton->setGeometry(280, 10, 150, 40);
    // add menu
    playersMenu = new QMenu(this);
    playersMenu->setFont(actionFont);
    playersMenu->setFixedWidth(150);
    QAction *player1 = new QAction(QIcon("assets/game_assets/ducks/white/standing.png"), "player1", this);
    playersMenu->addAction(player1);
    QAction *player2 = new QAction(QIcon("assets/game_assets/ducks/yellow/standing.png"), "player2", this);
    playersMenu->addAction(player2);
    QAction *player3 = new QAction(QIcon("assets/game_assets/ducks/orange/standing.png"), "player3", this);
    playersMenu->addAction(player3);
    QAction *player4 = new QAction(QIcon("assets/game_assets/ducks/grey/standing.png"), "player4", this);
    playersMenu->addAction(player4);

    connect(playersMenuButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        playersMenu->exec(playersMenuButton->mapToGlobal(QPoint(0, playersMenuButton->height())));
    });

    connect(player1, &QAction::triggered, this, [this]() { startDrag("players"); });
    connect(player2, &QAction::triggered, this, [this]() { startDrag("players"); });
    connect(player3, &QAction::triggered, this, [this]() { startDrag("players"); });
    connect(player4, &QAction::triggered, this, [this]() { startDrag("players"); });

    // add armor menu
    armorMenuButton = new QPushButton("armor", this);
    armorMenuButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    armorMenuButton->setFont(*customFont);
    armorMenuButton->setGeometry(440, 10, 130, 40);
    // add menu
    armorMenu = new QMenu(this);
    armorMenu->setFont(actionFont);
    armorMenu->setFixedWidth(150);

    QAction *chest = new QAction(QIcon("assets/game_assets/armor/armor.png"), "chest", this);
    QAction *knight= new QAction(QIcon("assets/game_assets/helmets/knight.png"), "knight", this);
    QAction *normal = new QAction(QIcon("assets/game_assets/helmets/normal.png"), "normal", this);
    QAction *tinfoil = new QAction(QIcon("assets/game_assets/helmets/tinfoil.png"), "tinfoil", this);

    armorMenu->addAction(chest);
    armorMenu->addAction(knight);
    armorMenu->addAction(normal);
    armorMenu->addAction(tinfoil);

    connect(armorMenuButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        armorMenu->exec(armorMenuButton->mapToGlobal(QPoint(0, armorMenuButton->height())));
    });

    connect(chest, &QAction::triggered, this, [this]() { startDrag("armor"); });
    connect(knight, &QAction::triggered, this, [this]() { startDrag("armor"); });
    connect(normal, &QAction::triggered, this, [this]() { startDrag("armor"); });
    connect(tinfoil, &QAction::triggered, this, [this]() { startDrag("armor"); });

    // add erase button 
    QPushButton *eraseButton = new QPushButton(QIcon("assets/menu_assets/eraser.png"), "", this);
    eraseButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 0px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    eraseButton->setFont(*customFont);
    eraseButton->setGeometry(580, 10, 40, 40);
    connect(eraseButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        currentTile = "";
        if (isErasing) {
            isErasing = false;
        } else {
            isPainting = false;
            isDragging = false;
            isErasing = true;
        }
        
        placeTileAtPosition(QCursor::pos());
    });

    // add drag button
    QPushButton *dragButton = new QPushButton(QIcon("assets/menu_assets/arrow_cross.png"), "", this);
    dragButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 0px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    dragButton->setFont(*customFont);
    dragButton->setGeometry(630, 10, 40, 40);

    connect(dragButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        currentTile = "";
        isPainting = false;
        isDragging = true;
        isErasing = false;
    });

    // add show/hide grid
    QPushButton *gridButton = new QPushButton(QIcon("assets/menu_assets/grid.png"), "", this);
    gridButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 0px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    gridButton->setFont(*customFont);
    gridButton->setGeometry(680, 10, 40, 40);
    connect(gridButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        gridVisible = !gridVisible;
        update();
    });

    // add save map button
    QPushButton *saveButton = new QPushButton("Save map", this);
    saveButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    saveButton->setFont(*customFont);
    saveButton->setGeometry(1760, 10, 150, 40);
    connect(saveButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        onSaveMap();
    });

    // add back to menu button
    QPushButton *backButton = new QPushButton("Back to menu", this);
    backButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"        
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    backButton->setFont(*customFont);
    backButton->setGeometry(1535, 10, 220, 40);
    connect(backButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        emit switchToMenu();
    });

}

void EditorScreen::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw the background tile to cover the entire screen
    if (background_tile) {
        painter.drawPixmap(rect(), *background_tile);
    }

    int screenWidth = width();
    int screenHeight = height();

    // Padding around the grid
    int padding = 50;

    // Available space for the matrix
    int availableWidth = screenWidth - 2 * padding;
    int availableHeight = screenHeight - 2 * padding;

    // Determine the base size of each cell
    int baseCellWidth = availableWidth / columns;
    int baseCellHeight = availableHeight / rows;
    int baseCellSize = std::min(baseCellWidth, baseCellHeight);

    // Adjust cell size with scaling factor
    int cellSize = static_cast<int>(baseCellSize * scale);

    // Calculate the total matrix size
    int matrixWidth = cellSize * columns;
    int matrixHeight = cellSize * rows;

    // Calculate initial offsets to center the matrix
    int xOffset = (screenWidth - matrixWidth) / 2 + offsetX;
    int yOffset = (screenHeight - matrixHeight) / 2 + offsetY;

    // Draw the matrix
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QRect cellRect(xOffset + col * cellSize, yOffset + row * cellSize, cellSize, cellSize);

            if (editor_matrix[row][col] == 5) {
                auto tile = map_of_maps["tiles"]["rock"]; // Example: Use grass for now
                if (tile && !tile->isNull()) {
                    painter.drawPixmap(cellRect, *tile);
                }
            } else if (editor_matrix[row][col] == 6) {
                auto tile = map_of_maps["tiles"]["grass"]; // Example: Use grass for now
                if (tile && !tile->isNull()) {
                    painter.drawPixmap(cellRect, *tile);
                }
            } else if (editor_matrix[row][col] == 7) {
                auto tile = map_of_maps["tiles"]["column"]; // Example: Use grass for now
                if (tile && !tile->isNull()) {
                    painter.drawPixmap(cellRect, *tile);
                } 
            } else if (editor_matrix[row][col] >= 8 && editor_matrix[row][col] <= 17) { // Updated range to include all weapons
                std::string weaponName;
                switch (editor_matrix[row][col]) {
                    case 8: weaponName = "ak47"; break;
                    case 9: weaponName = "banana"; break;
                    case 10: weaponName = "cowboy pistol"; break;
                    case 11: weaponName = "duel pistol"; break;
                    case 12: weaponName = "shotgun"; break;
                    case 13: weaponName = "grenade"; break;
                    case 14: weaponName = "magnum"; break;
                    case 15: weaponName = "sniper"; break;
                    case 16: weaponName = "laser rifle"; break;
                    case 17: weaponName = "pew pew laser"; break;
                }
                auto tile = map_of_maps["weapons"][weaponName];
                if (tile && !tile->isNull()) {
                    // Scale the weapon image according to the current scale factor
                    QPixmap scaledTile;
                    if (weaponName == "sniper" || weaponName == "shotgun" || weaponName == "ak47" || weaponName == "laser rifle") {
                        scaledTile = tile->scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    } else if (weaponName == "grenade" || weaponName == "duel pistol") {
                        scaledTile = tile->scaled(cellSize * 0.45, cellSize * 0.45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    } else {
                        scaledTile = tile->scaled(cellSize * 0.65, cellSize * 0.65, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    }
                    // Calculate the position to center the weapon image in the cell
                    int weaponWidth = scaledTile.width();
                    int weaponHeight = scaledTile.height();
                    QRect weaponRect(cellRect.center().x() - weaponWidth / 2, cellRect.bottom() - weaponHeight, weaponWidth, weaponHeight);
                    painter.drawPixmap(weaponRect, scaledTile);
                }
            } else if (editor_matrix[row][col] >= 18 && editor_matrix[row][col] <= 21) { 
                std::string playerName;
                switch (editor_matrix[row][col]) {
                    case 18: playerName = "player1"; break;
                    case 19: playerName = "player2"; break;
                    case 20: playerName = "player3"; break;
                    case 21: playerName = "player4"; break;
                }
                auto tile = map_of_maps["players"][playerName];
                if (tile && !tile->isNull()) {
                    // Scale the player image according to the current scale factor
                    QPixmap scaledTile = tile->scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    // Calculate the position to center the player image in the cell
                    int playerWidth = scaledTile.width();
                    int playerHeight = scaledTile.height();
                    QRect playerRect(cellRect.center().x() - playerWidth / 2, cellRect.bottom() - playerHeight, playerWidth, playerHeight);
                    painter.drawPixmap(playerRect, scaledTile);
                } 
            } else if (editor_matrix[row][col] >= 22 && editor_matrix[row][col] <= 25) { 
                std::string armorName;
                switch (editor_matrix[row][col]) {
                    case 22: armorName = "chest"; break;
                    case 23: armorName = "knight"; break;
                    case 24: armorName = "normal"; break;
                    case 25: armorName = "tinfoil"; break;
                }
                auto tile = map_of_maps["armor"][armorName];
                if (tile && !tile->isNull()) {
                    QPixmap scaledTile;
                    QRect armorRect;
                    if (armorName == "chest") {
                        scaledTile = tile->scaled(cellSize * 1.5, cellSize * 1.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                        int armorWidth = scaledTile.width();
                        int armorHeight = scaledTile.height();
                        armorRect = QRect(cellRect.center().x() - armorWidth/2, cellRect.bottom() - armorHeight/1.5, armorWidth, armorHeight);
                    } else if (armorName == "tinfoil") {
                        scaledTile = tile->scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                        int armorWidth = scaledTile.width();
                        int armorHeight = scaledTile.height();
                        armorRect = QRect(cellRect.center().x() - armorWidth/2, cellRect.bottom() - armorHeight*0.40, armorWidth, armorHeight);
                    } else {
                        scaledTile = tile->scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                        int armorWidth = scaledTile.width();
                        int armorHeight = scaledTile.height();
                        armorRect = QRect(cellRect.center().x() - armorWidth/2, cellRect.bottom() - armorHeight*0.57, armorWidth, armorHeight);
                    }
                    
                    painter.drawPixmap(armorRect, scaledTile);
                } 
            }

            if (gridVisible) {
                painter.setPen(QPen(Qt::black, 1));
            } else {
                painter.setPen(QPen(Qt::transparent, 1));
            }
            painter.drawRect(cellRect);
        }
    }
}

void EditorScreen::wheelEvent(QWheelEvent* event) {
    const double zoomFactor = 0.1; // Amount to zoom per scroll
    if (event->angleDelta().y() > 0) {
        // Zoom in
        scale += zoomFactor;
    } else {
        // Zoom out
        scale -= zoomFactor;
        if (scale < 0.1) scale = 0.1; // Prevent scale from becoming too small
    }

    update(); // Trigger a repaint with the new scale
}

void EditorScreen::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (isPainting) {
            isErasing = false;
            placeTileAtPosition(event->pos());
        } else if (isErasing) {
            placeTileAtPosition(event->pos());
        } else {
            isDragging = true;
            lastMousePosition = event->pos();
        }
    }
}

void EditorScreen::mouseMoveEvent(QMouseEvent* event) {
    if (isDragging) {
        // Calculate the displacement
        QPoint delta = event->pos() - lastMousePosition;
        offsetX += delta.x();
        offsetY += delta.y();
        lastMousePosition = event->pos();
        update(); // Repaint with the new offsets
    } else if (isPainting) {
        placeTileAtPosition(event->pos());
    }
}

void EditorScreen::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
}

void EditorScreen::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void EditorScreen::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasText()) {
        QString tileName = event->mimeData()->text();
        currentTile = tileName;

        // Switch to painting mode after dropping the tile
        isPainting = true;
        isDragging = false;

        QPoint pos = event->pos();
        placeTileAtPosition(pos);
    }
}

std::vector<std::vector<int>> EditorScreen::getMatrix() {
    return editor_matrix;
}

std::vector<std::vector<int>> EditorScreen::convertToServerMatrix() {
    int serverRows = rows * 4;
    int serverColumns = columns * 4;
    std::vector<std::vector<int>> serverMatrix(serverRows, std::vector<int>(serverColumns, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int value = editor_matrix[i][j];
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 4; ++l) {
                    serverMatrix[i * 4 + k][j * 4 + l] = value;
                }
            }
        }
    }

    return serverMatrix;
}

void EditorScreen::showTilesMenu() {
    buttonSound->play();
    tilesMenu->exec(tilesMenuButton->mapToGlobal(QPoint(0, tilesMenuButton->height())));
}

void EditorScreen::startDrag(std::string menu) {
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action) return;

    // Get the tile image associated with the action
    QString tileName = action->text();
    auto tile = map_of_maps[menu][tileName.toStdString()];
    if (!tile || tile->isNull()) {
        std::cout << "Tile: " << tileName.toStdString() << " not found." << std::endl;
        return;
    };
    // Create a mime data object
    QMimeData* mimeData = new QMimeData();
    mimeData->setText(tileName); // Use the tile name for identification

    // Create a drag object
    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*tile);
    drag->exec(Qt::CopyAction);
}

void EditorScreen::placeTileAtPosition(const QPoint& pos) {
    int padding = 50;

    // Calculate cell size
    int screenWidth = width();
    int screenHeight = height();
    int availableWidth = screenWidth - 2 * padding;
    int availableHeight = screenHeight - 2 * padding;

    int baseCellWidth = availableWidth / columns;
    int baseCellHeight = availableHeight / rows;
    int baseCellSize = std::min(baseCellWidth, baseCellHeight);
    int cellSize = static_cast<int>(baseCellSize * scale);

    // Calculate offsets
    int xOffset = (screenWidth - cellSize * columns) / 2 + offsetX;
    int yOffset = (screenHeight - cellSize * rows) / 2 + offsetY;

    // Convert screen coordinates to matrix indices
    int col = (pos.x() - xOffset) / cellSize;
    int row = (pos.y() - yOffset) / cellSize;

    if (pos.x() >= xOffset && pos.x() < xOffset + cellSize * columns &&
        pos.y() >= yOffset && pos.y() < yOffset + cellSize * rows &&
        row >= 0 && row < rows && col >= 0 && col < columns) {
        if (editor_matrix[row][col] == 0) { // Place tile only on empty cells
            if (currentTile == "rock") {
                editor_matrix[row][col] = 5;
            } else if (currentTile == "grass") {
                editor_matrix[row][col] = 6;
            } else if (currentTile == "column") {
                editor_matrix[row][col] = 7;
            } else if (currentTile == "ak47") { // despues las armas van a ser spawn points, no van a estar en la matriz cuando se guarde
                editor_matrix[row][col] = 8;
            } else if (currentTile == "banana") {
                editor_matrix[row][col] = 9;
            } else if (currentTile == "cowboy pistol") {
                editor_matrix[row][col] = 10;
            } else if (currentTile == "duel pistol") {
                editor_matrix[row][col] = 11;
            } else if (currentTile == "shotgun") {
                editor_matrix[row][col] = 12;
            } else if (currentTile == "grenade") {
                editor_matrix[row][col] = 13;
            } else if (currentTile == "magnum") {
                editor_matrix[row][col] = 14;
            } else if (currentTile == "sniper") {
                editor_matrix[row][col] = 15;
            } else if (currentTile == "laser rifle") {
                editor_matrix[row][col] = 16;
            } else if (currentTile == "pew pew laser") {
                editor_matrix[row][col] = 17;
            } else if (currentTile == "") {
                editor_matrix[row][col] = 0;
            } else if (currentTile == "player1" && players_set.find("player1") == players_set.end()) {
                editor_matrix[row][col] = 18;
                players_set.insert("player1");
            } else if (currentTile == "player2" && players_set.find("player2") == players_set.end()) {
                editor_matrix[row][col] = 19;
                players_set.insert("player2");
            } else if (currentTile == "player3" && players_set.find("player3") == players_set.end()) {
                editor_matrix[row][col] = 20;
                players_set.insert("player3");
            } else if (currentTile == "player4" && players_set.find("player4") == players_set.end()) {
                editor_matrix[row][col] = 21;
                players_set.insert("player4");
            } else if (currentTile == "chest") {
                editor_matrix[row][col] = 22;
            } else if (currentTile == "knight") {
                editor_matrix[row][col] = 23;
            } else if (currentTile == "normal") {
                editor_matrix[row][col] = 24;
            } else if (currentTile == "tinfoil") {
                editor_matrix[row][col] = 25;
            } else {
                editor_matrix[row][col] = 0;
            }
        } else if (isErasing) {
            int item = editor_matrix[row][col];
            switch (item) {
                case 18: players_set.erase("player1"); break;
                case 19: players_set.erase("player2"); break;
                case 20: players_set.erase("player3"); break;
                case 21: players_set.erase("player4"); break;
            }
            editor_matrix[row][col] = 0;
        }
        update(); // Trigger a repaint
    }
}

void EditorScreen::onSaveMap() {
    // show dialog to get the filename and confirmation
    QInputDialog inputDialog(this);
    inputDialog.setWindowTitle("Save map");
    inputDialog.setLabelText("Enter filename:");
    inputDialog.setFont(*customFont);
    inputDialog.setStyleSheet(
        "QInputDialog {"
        "background-color: rgba(240, 240, 240, 255);"
        "}"
        "QLabel {"
        "font-size: 20px;"
        "color: #333333;"
        "}"
        "QLineEdit {"
        "font-size: 18px;"
        "padding: 5px;"
        "border: 1px solid #555555;"
        "border-radius: 5px;"
        "}"
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"
        "color: #ffffff;"
        "font-size: 18px;"
        "border: 0px solid #555555;"
        "border-radius: 10px;"
        "padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    bool ok = inputDialog.exec() == QDialog::Accepted;
    QString filename = inputDialog.textValue();
    if (ok && !filename.isEmpty()) {
        std::vector<std::vector<int>> server_matrix = convertToServerMatrix();
        saveMap(server_matrix, filename.toStdString());
    }
}