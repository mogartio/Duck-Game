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
#include "rounded_rectangle.h"
class EditorScreen : public QWidget {
    Q_OBJECT
private:
    std::vector<std::vector<int>> matrix;
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

    // buttons
    QPushButton *tilesMenuButton;
    QMenu *tilesMenu;

    std::vector<std::vector<int>> convertToServerMatrix();


private slots:
    void showTilesMenu();

public: 
    EditorScreen(int columns, int rows, std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps);
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    std::vector<std::vector<int>> getMatrix();
};

#endif // EDITOR_SCREEN_H_
