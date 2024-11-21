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

class SetInitialValuesScreen : public QWidget {
    Q_OBJECT
public:
    SetInitialValuesScreen();
private: 
    ParallaxBackground *bg;
    void resizeEvent(QResizeEvent *event) override;
    QPushButton *startButton;
    QPushButton *startEditingButton;
    QLineEdit *widthInput;
    QLineEdit *heightInput;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QFont *customFont;
    QSound *buttonSound;
    QLabel *logoLabel;
    QLabel *setMapDimensionsLabel;
    RoundedRectangle *startButtonRect;
private slots:
    void onStartButtonClicked();
    void onStartEditingButtonClicked();
signals: 
    void sendInitialValues(int width, int height);
};

#endif // SET_INITIAL_VALUES_SCREEN_H_