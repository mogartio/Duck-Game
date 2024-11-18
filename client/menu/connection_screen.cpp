#include "connection_screen.h"
#include "rounded_rectangle.h"
#include <QPainter>
#include <QResizeEvent>
#include <qboxlayout.h>
#include <QLabel>
#include <QLineEdit>
#include <qfontdatabase.h>
#include <QPushButton>
#include <QDebug> 
#include <iostream>
#include <QSound>
#include <string>
#include <iostream>
ConnectionScreen::ConnectionScreen(Queue<std::shared_ptr<GenericMsg>>* send_queue, Queue<std::shared_ptr<GenericMsg>>* recv_queue, Client* client) : send_queue(send_queue), recv_queue(recv_queue), client(client) {
    setWindowState(Qt::WindowFullScreen); // Set window to full-screen mode

    // Set focus policy to receive key events
    setFocusPolicy(Qt::StrongFocus);

    keyPressSound = std::make_unique<QSound>("assets/Retro8.wav", this);

    // Create ParallaxBackground layers
    QVBoxLayout *layout = new QVBoxLayout(this);
    layer0 = std::make_unique<ParallaxBackground>(this, "assets/parallax_background_layer_1.png", 0.5f);
    layer1 = std::make_unique<ParallaxBackground>(this, "assets/parallax_background_layer_2.png", 0.75f);
    layer2 = std::make_unique<ParallaxBackground>(this, "assets/parallax_background_layer_3.png", 1.0f);
    layer3 = std::make_unique<ParallaxBackground>(this, "assets/parallax_background_layer_4.png", 1.25f);

    layer0->start();
    layer1->start();
    layer2->start();
    layer3->start();
    setLayout(layout);

    // Center of the screen: (1920 / 2, 1080 / 2) = (960, 540)
    // Top-left corner of the rectangle: (960 - 500 / 2, 540 - 400 / 2) = (710, 340)
    RoundedRectangle * baseRectangle = new RoundedRectangle(this, 650, 200, 620, 660, QColor(213, 226, 224, 100), QColor(213, 226, 224, 100));

    int fontId = QFontDatabase::addApplicationFont("assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily);

    // Create label  "Connect to server"
    QLabel *connectLabel = new QLabel("Connect to server", this);
    connectLabel->setStyleSheet("QLabel { color: #ced4da; font-size: 52px; }");
    connectLabel->setFont(customFont);
    connectLabel->setGeometry(690, 260, 550, 50);
    
    QLabel *hostnameLabel = new QLabel("hostname", this);
    QLabel *portLabel = new QLabel("port", this);
    hostnameLabel->setStyleSheet("QLabel { color: #ced4da; font-size: 38px; }");
    portLabel->setStyleSheet("QLabel { color: #ced4da; font-size: 38px; }");
    hostnameLabel->setFont(customFont);
    portLabel->setFont(customFont);
    hostnameLabel->setGeometry(710, 350, 500, 50);
    portLabel->setGeometry(710, 450, 500, 50);

    baseRectangle->setParent(this);

    // Create the input fields
    hostname = std::make_unique<QLineEdit>(this);
    port = std::make_unique<QLineEdit>(this);

    hostname->setGeometry(710, 400, 500, 50);
    port->setGeometry(710, 500, 500, 50);

    hostname->setStyleSheet(
        "QLineEdit {"
        "background-color:rgba(206, 212, 218, 255);"     // Light gray background
        "color: #80858a;"                // Text color
        "font-size: 30px;"               // Font size
        "border: 0px solid #555555;"     // Border color and size
        "border-radius: 20px;"            // Rounded corners
        "padding: 10px;"                  // Padding inside the QLineEdit
        "}"
        "QLineEdit:hover {"
        "background-color: rgba(189, 194, 199, 255);"     // Slightly darker on hover
        "}"
    );

    port->setStyleSheet(
        "QLineEdit {"
        "background-color: rgba(206, 212, 218, 255);"     // Light gray background
        "color: #80858a;"                // Text color
        "font-size: 30px;"               // Font size
        "border: 0px solid #555555;"     // Border color and size
        "border-radius: 20px;"            // Rounded corners
        "padding: 10px;"                  // Padding inside the QLineEdit
        "}"
        "QLineEdit:hover {"
        "background-color: rgba(189, 194, 199, 255);"     // Slightly darker on hover
        "}"
        );

    hostname->setFont(customFont);
    port->setFont(customFont);

    // Create the connect button
    QPushButton *connectButton = new QPushButton("CONNECT", this);
    connectButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 48px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
        "}"
    );
    connectButton->setFont(customFont);

    connectButton->setGeometry(845, 600, 240, 100);

    // Connect the button's clicked signal to a slot
    connect(connectButton, &QPushButton::clicked, this, &ConnectionScreen::onConnectButtonClicked);

    // Create the quit button
    QPushButton *quitButton = new QPushButton("QUIT", this);
    quitButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(240, 140, 0, 100);"        
        "color: #ced4da;"                     
        "font-size: 42px;"                  
        "border: 0px solid #555555;"        
        "border-radius: 15px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(232, 89, 12, 100);"
        "}"
    );
    quitButton->setFont(customFont);
    quitButton->setGeometry(880, 710, 160, 70);

    connect(quitButton, &QPushButton::clicked, this, &ConnectionScreen::onQuitButtonClicked); 
}

void ConnectionScreen::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    // Trigger a repaint to adjust the background and rectangle
    layer0->resizeImages();
    layer1->resizeImages();
    layer2->resizeImages();
    layer3->resizeImages();
    update();
}

void ConnectionScreen::onConnectButtonClicked() {
    keyPressSound->play();
    if (hostname->text().isEmpty() || port->text().isEmpty()) {
        drawEmptyFieldsError();
        return;
    }
    try {
        std::string hostnameStr = hostname->text().toStdString();
        std::string portStr = port->text().toStdString();
        Socket skt(hostnameStr.c_str(), portStr.c_str());
        client = new Client(std::move(skt), send_queue, recv_queue);
        // successful connection
        emit switchToMainMenuScreen();
    } catch (const std::exception &e) {
        drawConnectionRefusedError();
    }
}

void ConnectionScreen::onQuitButtonClicked() {
    keyPressSound->play();
    emit quitApplication();
}

void ConnectionScreen::drawEmptyFieldsError() {
    // Create a QLabel to display the error message
    QLabel *errorLabel = new QLabel("Please fill in all fields", this);
    errorLabel->setStyleSheet("QLabel { color: #800404; font-size: 24px; }");
    errorLabel->setFont(QFont(customFont));
    errorLabel->setGeometry(710, 550, 500, 50);
    errorLabel->show();
    // Remove the error message after 2 seconds
    QTimer::singleShot(2000, errorLabel, &QObject::deleteLater);
}

void ConnectionScreen::drawConnectionRefusedError() {
    // Create a QLabel to display the error message
    QLabel *errorLabel = new QLabel("Connection refused", this);
    errorLabel->setStyleSheet("QLabel { color: #800404; font-size: 24px; }");
    errorLabel->setFont(QFont(customFont));
    errorLabel->setGeometry(710, 550, 500, 50);
    errorLabel->show();
    // Remove the error message after 2 seconds
    QTimer::singleShot(2000, errorLabel, &QObject::deleteLater);
}
