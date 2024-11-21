#ifndef EDITOR_SCREEN_H_
#define EDITOR_SCREEN_H_

#include <QWidget>
#include <iostream>

class EditorScreen : public QWidget {
    Q_OBJECT
private:
    QPixmap background; // background image
    int width; 
    int height;
public: 
    EditorScreen(int width, int height);

};

#endif // EDITOR_SCREEN_H_
