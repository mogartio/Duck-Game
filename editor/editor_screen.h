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
#include "rounded_rectangle.h"
#include "save_map.h"
#include "../common/messages/generic_msg.h"

class EditorScreen : public QWidget {
    Q_OBJECT
private:
    std::vector<std::vector<int>> editor_matrix;
    std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps;
    int columns; 
    int rows;
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


    std::vector<std::vector<int>> convertToServerMatrix();
    void placeTileAtPosition(const QPoint& pos);

private slots:
    void showTilesMenu();
    void startDrag(std::string menu);
    void onSaveMap();
signals:
    void switchToMenu();

public: 
    EditorScreen(int columns, int rows, std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps);
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    std::vector<std::vector<int>> getMatrix();

    static const int EMPTY = 0;
    static const int ROCK = 17;
    static const int GRASS = 18;
    static const int COLUMN = 19;
    static const int AK_47 = static_cast<int>(ProjectilesId::AK_47);
    static const int BANANA = static_cast<int>(ProjectilesId::BANANA);
    static const int COWBOY_PISTOL = static_cast<int>(ProjectilesId::COWBOY_PISTOL);
    static const int DUEL_PISTOL = static_cast<int>(ProjectilesId::DUEL_PISTOL);
    static const int SHOTGUN = static_cast<int>(ProjectilesId::SHOTGUN);
    static const int GRENADE = static_cast<int>(ProjectilesId::GRENADE);
    static const int MAGNUM = static_cast<int>(ProjectilesId::MAGNUM);
    static const int SNIPER = static_cast<int>(ProjectilesId::SNIPER);
    static const int LASER_RIFLE = static_cast<int>(ProjectilesId::LASER_RIFLE);
    static const int PEW_PEW_LASER = static_cast<int>(ProjectilesId::PEW_PEW_LASER);
    static const int HELMET = static_cast<int>(ProjectilesId::HELMET);
    static const int CHEST = static_cast<int>(ProjectilesId::CHEST);
    static const int PLAYER1 = 20;
    static const int PLAYER2 = 21;
    static const int PLAYER3 = 22;
    static const int PLAYER4 = 23;
};

#endif // EDITOR_SCREEN_H_
