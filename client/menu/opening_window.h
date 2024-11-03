#ifndef OPENING_WINDOW_H
#define OPENING_WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QPixmap>

class OpeningWindow : public QWidget {
    Q_OBJECT

public:
    OpeningWindow(QWidget *parent = nullptr);
    ~OpeningWindow() = default;
private slots:
    void onButtonClicked();

private:
    QLabel *label;
    QPushButton *button;
    QVBoxLayout *layout;
};

#endif // OPENING_WINDOW_H