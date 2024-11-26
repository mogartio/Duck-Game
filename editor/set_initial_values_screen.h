#ifndef SET_INITIAL_VALUES_SCREEN_H_
#define SET_INITIAL_VALUES_SCREEN_H_

#include <QPixmap>
#include <QPushButton>
#include "parallax_background.h"
#include "rounded_rectangle.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QLineEdit>
#include <iostream>
#include <QTimer>
#include <QFont>
#include <QFontDatabase>
#include <QSound>
#include <QRadioButton>

class SetInitialValuesScreen : public QWidget {
    Q_OBJECT
public:
    SetInitialValuesScreen();
private: 
    ParallaxBackground *bg;
    void resizeEvent(QResizeEvent *event) override;
    QPushButton *startButton;
    QPushButton *startEditingButton;
    QLineEdit *columnsInput;
    QLineEdit *rowsInput;
    QLabel *columnsLabel;
    QLabel *rowsLabel;
    QFont *customFont;
    QSound *buttonSound;
    QLabel *logoLabel;
    QLabel *setMapDimensionsLabel;

    RoundedRectangle *startButtonRect;
    std::string choosenTheme;

    QLabel *themeLabel;
    QRadioButton *lightTheme;
    QRadioButton *nightTheme;
    RoundedRectangle *themeRect;

private slots:
    void onStartButtonClicked();
    void onStartEditingButtonClicked();
    void onThemeChanged();
    void onQuitButtonClicked();
signals: 
    void sendInitialValues(int columns, int rows, std::string choosenTheme);
    void quitApp();
};

#endif // SET_INITIAL_VALUES_SCREEN_H_