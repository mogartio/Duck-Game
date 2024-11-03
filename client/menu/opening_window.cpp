#include "opening_window.h"

OpeningWindow::OpeningWindow(QWidget *parent) : QWidget(parent) {
    resize(400, 300);
    setWindowTitle("Duck Game");

    // set background image 
    setStyleSheet("background-image: url(../client/img_src/img1.png);");

    layout = new QVBoxLayout(this);

    // label = new QLabel("Hello World", this);
    // layout->addWidget(label);

    button = new QPushButton("CLICK Me", this);
    layout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, this, &OpeningWindow::onButtonClicked);
}

void OpeningWindow::onButtonClicked() {
    std::cout << "Apretaste el boton!" << std::endl;
    // Add your custom action here
}

