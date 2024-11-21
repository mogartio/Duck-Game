#ifndef EDITOR_MAIN_WINDOW_H_
#define EDITOR_MAIN_WINDOW_H_

#include <QMainWindow>
#include <memory>
#include "set_initial_values_screen.h"
#include <QStackedWidget>

class EditorMainWindow : public QMainWindow {
    Q_OBJECT
private:
    int rows; // rows & columns in the grid
    int columns;
    QPixmap background; // background image

public:
    EditorMainWindow(QWidget *parent = nullptr);
    
private:
    std::shared_ptr<QStackedWidget> stackedWidget;
    std::shared_ptr<SetInitialValuesScreen> setInitialValuesScreen;
};


#endif // EDITOR_MAIN_WINDOW_H_