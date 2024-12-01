#ifndef EDITOR_MAIN_WINDOW_H_
#define EDITOR_MAIN_WINDOW_H_

#include <QMainWindow>
#include <memory>
#include <QStackedWidget>
#include <QApplication>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "set_initial_values_screen.h"
#include "editor_screen.h"

class EditorMainWindow : public QMainWindow {
    Q_OBJECT
private:
    int columns; // rows & columns in the grid
    int rows; 
    std::string theme; // theme of the grid

    std::map<std::string, std::map<std::string, std::shared_ptr<QPixmap>>> map_of_maps;

    void showEditorScreen();
    void loadImagesGivenTheme(std::string theme);
    void showSetInitialValuesScreen();

public:
    EditorMainWindow(QWidget *parent = nullptr);
    
private:
    std::shared_ptr<QStackedWidget> stackedWidget;
    std::shared_ptr<SetInitialValuesScreen> setInitialValuesScreen;
    std::shared_ptr<EditorScreen> editorScreen;

private slots:
    void receiveValues(int columns, int rows, std::string theme);
    void onBackSignal();
    void handleQuitApp();
};


#endif // EDITOR_MAIN_WINDOW_H_