#include "editor_main_window.h"

EditorMainWindow::EditorMainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Duck Game - Level Editor");
    resize(1920, 1080);

    stackedWidget = std::make_shared<QStackedWidget>(this);
    setCentralWidget(stackedWidget.get());

    setInitialValuesScreen = std::make_shared<SetInitialValuesScreen>();

    stackedWidget->addWidget(setInitialValuesScreen.get());

    stackedWidget->setCurrentWidget(setInitialValuesScreen.get());

    // Connect the signal from the SetInitialValuesScreen to the EditorMainWindow to receive width and height values
    connect(setInitialValuesScreen.get(), &SetInitialValuesScreen::sendInitialValues, this, &EditorMainWindow::receiveValues);

}

void EditorMainWindow::receiveValues(int width, int height) {
    this->width = width;
    this->height = height;
    showEditorScreen();
}

void EditorMainWindow::showEditorScreen() {
    
    editorScreen = std::make_shared<EditorScreen>(width, height);
    stackedWidget->addWidget(editorScreen.get());

    QWidget *overlay = new QWidget(this);
    overlay->setStyleSheet("background-color: black;");
    overlay->setGeometry(this->rect());
    overlay->show();

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    overlay->setGraphicsEffect(effect);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(1000);
    fadeOut->setStartValue(0);
    fadeOut->setEndValue(1);

    connect(fadeOut, &QPropertyAnimation::finished, [this, overlay]() {
        stackedWidget->setCurrentWidget(editorScreen.get());
        QPropertyAnimation *fadeIn = new QPropertyAnimation(overlay->graphicsEffect(), "opacity");
        fadeIn->setDuration(1000);
        fadeIn->setStartValue(1);
        fadeIn->setEndValue(0);

        connect(fadeIn, &QPropertyAnimation::finished, overlay, &QWidget::deleteLater);
        fadeIn->start(QPropertyAnimation::DeleteWhenStopped);
    });

    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
}