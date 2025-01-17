#ifndef EDITOR_SCREEN_H_
#define EDITOR_SCREEN_H_

#include <QWidget>
#include <iostream>
#include <QPainter>
#include <QMouseEvent>
#include <QMenuBar>
#include <QWheelEvent>
#include <QPixmap>
#include <QMenu>
#include <QFont>
#include <QFontDatabase>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QAction>
#include <map>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QSound>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QDrag>
#include <set>
#include <QInputDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include "rounded_rectangle.h"
#include "save_map.h"
#include "items_ids.h"
class EditorScreen : public QWidget {
    Q_OBJECT
private:
    std::vector<std::vector<int>> editor_matrix;
    std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps;
    int columns; 
    int rows;
    int theme;
    double scale;
    QFont *customFont;
    QSound *buttonSound;
    bool isDragging;          // Tracks if the matrix is being dragged
    QPoint lastMousePosition; // Tracks the last position of the mouse
    int offsetX, offsetY;     // Tracks the current offsets for the matrix
    std::shared_ptr<QPixmap> background_tile;
    QString currentTile;
    bool isPainting;
    bool isErasing;
    bool gridVisible;
    // tiles menu
    QPushButton *tilesMenuButton;
    QMenu *tilesMenu;
    // weapons menu
    QPushButton *weaponsMenuButton;
    QMenu *weaponsMenu;
    // players menu. a player can be added only once
    std::set<std::string> players_set;
    QPushButton *playersMenuButton;
    QMenu *playersMenu;
    // armor menu
    QPushButton *armorMenuButton;
    QMenu *armorMenu;

    void placeTileAtPosition(const QPoint& pos);

private slots:
    void showTilesMenu();
    void startDrag(std::string menu);
    void onSaveMap();
signals:
    void switchToMenu();

public: 
    EditorScreen(int columns, int rows, std::string theme, std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps);
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

};

#endif // EDITOR_SCREEN_H_
