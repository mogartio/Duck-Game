#include "editor_screen.h"
#include <cmath>


EditorScreen::EditorScreen(int columns, int rows, std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps)
    : map_of_maps(map_of_maps), columns(columns), rows(rows), scale(1.0), isDragging(false), offsetX(0), offsetY(0) {
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(1920, 1080); // Ensure the editor screen is fixed to 1920x1080
    
    currentTile = "";
    isPainting = false;
    isErasing = false;
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
    RoundedRectangle* roundedRectangle = new RoundedRectangle(this, 0, 0, 1920, 60, QColor(255, 0, 0, 200), QColor(255, 0, 0, 200), 10);
    roundedRectangle->setParent(this);

    // draw tiles button -> dropdown menu
    tilesMenuButton = new QPushButton("Tiles", this);
    tilesMenuButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
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

    // add drag button
    QPushButton *dragButton = new QPushButton(QIcon("assets/menu_assets/arrow_cross.png"), "", this);
    dragButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 0px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
        "}"
    );
    dragButton->setFont(*customFont);
    dragButton->setGeometry(120, 10, 40, 40);
    connect(dragButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        currentTile = "";
        isPainting = false;
        isDragging = true;
        isErasing = false;
    });

    // add weapons menu
    weaponsMenuButton = new QPushButton("Weapons", this);
    weaponsMenuButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
        "}"
    );
    weaponsMenuButton->setFont(*customFont);
    weaponsMenuButton->setGeometry(170, 10, 150, 40);
    // add menu
    weaponsMenu = new QMenu(this);
    weaponsMenu->setFont(actionFont);
    weaponsMenu->setFixedWidth(200);
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

    // add erase button 
    QPushButton *eraseButton = new QPushButton(QIcon("assets/menu_assets/eraser.png"), "", this);
    eraseButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 28px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 0px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
        "}"
    );
    eraseButton->setFont(*customFont);
    eraseButton->setGeometry(330, 10, 40, 40);
    connect(eraseButton, &QPushButton::clicked, [this](){
        buttonSound->play();
        currentTile = "";
        isPainting = false;
        isDragging = false;
        isErasing = true;
        placeTileAtPosition(QCursor::pos());
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
            }
        } else if (isErasing) {
            editor_matrix[row][col] = 0;
        }

        update(); // Trigger a repaint
    }
}
