#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "logo_screen.h"
#include "connection_screen.h" // Assuming you have another screen called OpeningScreen

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showConnectionScreen();
    void showLogoScreen();

private:
    QStackedWidget *stackedWidget;
    LogoScreen *logoScreen;
    ConnectionScreen *openingScreen;
};

#endif // MAIN_WINDOW_H