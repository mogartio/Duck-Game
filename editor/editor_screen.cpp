#include "editor_screen.h"
#include <cmath>


EditorScreen::EditorScreen(int columns, int rows, std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps)
    : map_of_maps(map_of_maps), columns(columns), rows(rows), scale(1.0), isDragging(false), offsetX(0), offsetY(0) {
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(1920, 1080); // Ensure the editor screen is fixed to 1920x1080
    
    currentTile = "";
    isPainting = false;
    isErasing = false;
    gridVisible = true;
    // Initialize the matrix with 0s. Each cell is actually 4x4 server tiles
    editor_matrix.resize(rows, std::vector<int>(columns, Id::EMPTY)); 

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
            int cellValue = editor_matrix[row][col];

            std::shared_ptr<QPixmap> tile;
            std::string category;
            std::string itemName;
            
            switch (cellValue) {
                case Id::ROCK: category = "tiles"; itemName = "rock"; break;
                case Id::GRASS: category = "tiles"; itemName = "grass"; break;
                case Id::COL: category = "tiles"; itemName = "column"; break;
                case Id::AK_47: category = "weapons"; itemName = "ak47"; break;
                case Id::BANANA: category = "weapons"; itemName = "banana"; break;
                case Id::COWBOY_PISTOL: category = "weapons"; itemName = "cowboy pistol"; break;
                case Id::DUEL_PISTOL: category = "weapons"; itemName = "duel pistol"; break;
                case Id::SHOTGUN: category = "weapons"; itemName = "shotgun"; break;
                case Id::GRENADE: category = "weapons"; itemName = "grenade"; break;
                case Id::MAGNUM: category = "weapons"; itemName = "magnum"; break;
                case Id::SNIPER: category = "weapons"; itemName = "sniper"; break;
                case Id::LASER_RIFLE: category = "weapons"; itemName = "laser rifle"; break;
                case Id::PEW_PEW_LASER: category = "weapons"; itemName = "pew pew laser"; break;
                case Id::PLAYER1: category = "players"; itemName = "player1"; break;
                case Id::PLAYER2: category = "players"; itemName = "player2"; break;
                case Id::PLAYER3: category = "players"; itemName = "player3"; break;
                case Id::PLAYER4: category = "players"; itemName = "player4"; break;
                case Id::HELMET: category = "armor"; itemName = "knight"; break;
                // case Id::HELMET2: category = "armor"; itemName = "normal"; break;
                // case Id::HELMET3: category = "armor"; itemName = "tinfoil"; break;
                case Id::CHEST: category = "armor"; itemName = "chest"; break;
                default: break;
            }

            // Debug statement to check the category and itemName

            if (!category.empty() && !itemName.empty()) {
                tile = map_of_maps[category][itemName];
            }

            if (tile && !tile->isNull()) {
                QPixmap scaledTile;
                QRect itemRect;
                auto scaleTile = [&](double widthFactor, double heightFactor, double yOffsetFactor) {
                    scaledTile = tile->scaled(cellSize * widthFactor, cellSize * heightFactor, Qt::KeepAspectRatio, Qt::FastTransformation);
                    int itemWidth = scaledTile.width();
                    int itemHeight = scaledTile.height();
                    itemRect = QRect(cellRect.center().x() - itemWidth / 2, cellRect.bottom() - itemHeight * yOffsetFactor, itemWidth, itemHeight);
                };

                if (category == "weapons") {
                    if (itemName == "sniper" || itemName == "shotgun" || itemName == "ak47" || itemName == "laser rifle") {
                        scaleTile(1.0, 1.0, 1.0);
                    } else if (itemName == "grenade" || itemName == "duel pistol") {
                        scaleTile(0.45, 0.45, 1.0);
                    } else {
                        scaleTile(0.65, 0.65, 1.0);
                    }
                } else if (category == "armor") {
                    if (itemName == "chest") {
                        scaleTile(1.5, 1.5, 0.70);
                    } else if (itemName == "tinfoil") {
                        scaleTile(1.0, 1.0, 0.40);
                    } else {
                        scaleTile(1.0, 1.0, 0.57);
                    }
                } else if (category == "players") {
                    scaleTile(1.0, 1.0, 1.0);
                } else if (category == "tiles") {
                    painter.drawPixmap(cellRect, *tile);
                }

                painter.drawPixmap(itemRect, scaledTile);
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
        
        auto placeTile = [&](int id, const std::string& player = "") {
            editor_matrix[row][col] = id;
            if (!player.empty()) {
                players_set.insert(player);
            }
        };

        auto eraseTile = [&]() {
            int item = editor_matrix[row][col];
            switch (item) {
                case Id::PLAYER1: players_set.erase("player1"); break;
                case Id::PLAYER2: players_set.erase("player2"); break;
                case Id::PLAYER3: players_set.erase("player3"); break;
                case Id::PLAYER4: players_set.erase("player4"); break;
            }
            editor_matrix[row][col] = Id::EMPTY;
        };

        if (editor_matrix[row][col] == Id::EMPTY) { // Place tile only on empty cells
            if (currentTile == "rock") placeTile(Id::ROCK);
            else if (currentTile == "grass") placeTile(Id::GRASS);
            else if (currentTile == "column") placeTile(Id::COL);
            else if (currentTile == "ak47") placeTile(Id::AK_47);
            else if (currentTile == "banana") placeTile(Id::BANANA);
            else if (currentTile == "cowboy pistol") placeTile(Id::COWBOY_PISTOL);
            else if (currentTile == "duel pistol") placeTile(Id::DUEL_PISTOL);
            else if (currentTile == "shotgun") placeTile(Id::SHOTGUN);
            else if (currentTile == "grenade") placeTile(Id::GRENADE);
            else if (currentTile == "magnum") placeTile(Id::MAGNUM);
            else if (currentTile == "sniper") placeTile(Id::SNIPER);
            else if (currentTile == "laser rifle") placeTile(Id::LASER_RIFLE);
            else if (currentTile == "pew pew laser") placeTile(Id::PEW_PEW_LASER);
            else if (currentTile == "") placeTile(Id::EMPTY);
            else if (currentTile == "player1" && players_set.find("player1") == players_set.end()) placeTile(Id::PLAYER1, "player1");
            else if (currentTile == "player2" && players_set.find("player2") == players_set.end()) placeTile(Id::PLAYER2, "player2");
            else if (currentTile == "player3" && players_set.find("player3") == players_set.end()) placeTile(Id::PLAYER3, "player3");
            else if (currentTile == "player4" && players_set.find("player4") == players_set.end()) placeTile(Id::PLAYER4, "player4");
            else if (currentTile == "chest") placeTile(Id::CHEST);
            else if (currentTile == "knight") placeTile(Id::HELMET);
            // else if (currentTile == "normal") placeTile(Id::HELMET2);
            // else if (currentTile == "tinfoil") placeTile(Id::HELMET3);
        } else if (isErasing) {
            eraseTile();
        }
        update(); // Trigger a repaint
    }
}

void EditorScreen::onSaveMap() {
    // if there isn't at least two players on the map, show a warning
    if (players_set.size() < 2) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Warning");
        msgBox.setText("You must place at least two players on the map.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setFont(*customFont);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setStyleSheet(
            "QMessageBox {"
            "background-color: rgba(240, 240, 240, 255);"
            "}"
            "QLabel {"
            "font-size: 32px;"
            "color: #333333;"
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
        msgBox.exec();
        return;
    }
    // show dialog to get the filename and confirmation
    QInputDialog inputDialog(this);
    inputDialog.setWindowTitle("Save map");
    inputDialog.setLabelText("Map name:");
    inputDialog.setFont(*customFont);
    inputDialog.setBaseSize(400, 200);
    inputDialog.setStyleSheet(
        "QInputDialog {"
        "background-color: rgba(240, 240, 240, 255);"
        "}"
        "QLabel {"
        "font-size: 32px;"
        "color: #333333;"
        "}"
        "QLineEdit {"
        "font-size: 24px;"
        "padding: 10px;"
        "border: 1px solid #555555;"
        "border-radius: 10px;"
        "}"
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 225);"
        "color: #ffffff;"
        "font-size: 18px;"
        "border: 0px solid #555555;"
        "border-radius: 10px;"
        "padding: 10px 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 255);"
        "}"
    );
    bool ok = inputDialog.exec() == QDialog::Accepted;
    QString filename = inputDialog.textValue();
    if (ok && !filename.isEmpty()) {
        saveMap(editor_matrix, filename.toStdString());
    }
}