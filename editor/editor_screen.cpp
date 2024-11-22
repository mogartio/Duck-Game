#include "editor_screen.h"
#include <cmath>


EditorScreen::EditorScreen(int columns, int rows, std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps)
    : map_of_maps(map_of_maps), columns(columns), rows(rows), scale(1.0), isDragging(false), offsetX(0), offsetY(0) {
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(1920, 1080); // Ensure the editor screen is fixed to 1920x1080
    
    currentTile = "";
    isPainting = false;
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

    connect(grass, &QAction::triggered, this, &EditorScreen::startDrag);
    connect(rock, &QAction::triggered, this, &EditorScreen::startDrag);
    connect(column, &QAction::triggered, this, &EditorScreen::startDrag);
    
    setAcceptDrops(true);
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

void EditorScreen::mouseMoveEvent(QMouseEvent* event) {
    if (isDragging) {
        // Calculate the displacement
        QPoint delta = event->pos() - lastMousePosition;
        offsetX += delta.x();
        offsetY += delta.y();
        lastMousePosition = event->pos();
        update(); // Repaint with the new offsets
    } else if (isPainting && !currentTile.isEmpty()) {
        QPoint pos = event->pos();
        placeTileAtPosition(pos);
    }
}

void EditorScreen::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (!currentTile.isEmpty()) {
            // Check if we're painting or starting a drag
            if (isPainting) {
                isPainting = true;  // Enable painting mode
                isDragging = false; // Disable dragging mode
                QPoint pos = event->pos();
                placeTileAtPosition(pos);
            } else {
                isDragging = true;  // Enable dragging mode
                QPoint pos = event->pos();
                lastMousePosition = pos; // Save initial position
            }
        }
    } else if (event->button() == Qt::RightButton) {
        currentTile = "";   // Disable painting mode
        isPainting = false;
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



void EditorScreen::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
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

void EditorScreen::startDrag() {
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action) return;

    // Get the tile image associated with the action
    QString tileName = action->text();
    auto tile = map_of_maps["tiles"][tileName.toStdString()];
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
            }
        }

        update(); // Trigger a repaint
    }
}
