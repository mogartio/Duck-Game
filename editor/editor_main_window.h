#ifndef EDITOR_MAIN_WINDOW_H_
#define EDITOR_MAIN_WINDOW_H_

#include <QMainWindow>
#include <memory>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "set_initial_values_screen.h"
#include "editor_screen.h"
class EditorMainWindow : public QMainWindow {
    Q_OBJECT
private:
    int width; // rows & columns in the grid
    int height; 
    void showEditorScreen();

public:
    EditorMainWindow(QWidget *parent = nullptr);
    
private:
    std::shared_ptr<QStackedWidget> stackedWidget;
    std::shared_ptr<SetInitialValuesScreen> setInitialValuesScreen;
    std::shared_ptr<EditorScreen> editorScreen;

private slots:
    void receiveValues(int width, int height);
};


#endif // EDITOR_MAIN_WINDOW_H_