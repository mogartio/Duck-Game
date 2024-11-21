#include "set_initial_values_screen.h"


SetInitialValuesScreen::SetInitialValuesScreen() {
    setFocusPolicy(Qt::StrongFocus);

    // load font and sound
    int fontId = QFontDatabase::addApplicationFont("assets/menu_assets/HomeVideo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = new QFont(fontFamily);
    buttonSound = new QSound("assets/menu_assets/Retro3.wav");

    // show background
    bg = new ParallaxBackground(this, "assets/game_assets/background/day.png", 1.5f);
    bg->start();

    RoundedRectangle *baseRectangle = new RoundedRectangle(this, 687, 100, 545, 380, QColor(0, 0, 0, 100), QColor(0, 0, 0, 100));
    baseRectangle->setParent(this);
    // draw the logo of the game at the top of the screen and text "Level Editor"
    QPixmap logo("assets/menu_assets/duck_game_logo.png");
    logo = logo.scaled(logo.width() / 2, logo.height() / 2);
    logoLabel = new QLabel(this);
    logoLabel->setPixmap(logo);
    logoLabel->setGeometry(960 - logo.width() / 2-10, 100, logo.width(), logo.height());
    logoLabel->show();
    QLabel *levelEditorLabel = new QLabel("Level Editor", this);
    levelEditorLabel->setStyleSheet("color: #ffffff; font-size: 56px;");
    levelEditorLabel->setGeometry(760, 400, 400, 60);
    levelEditorLabel->setAlignment(Qt::AlignCenter);
    levelEditorLabel->setFont(*customFont);
    levelEditorLabel->show();

    // Draw the start button (only appears at the start of the program and it leads to the next screen where the user has to enter the width and height)
    startButton = new QPushButton("Start", this);
    startButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(235, 141, 0, 150);"        
        "color: #ffffff;"                     
        "font-size: 56px;"                  
        "border: 0px solid #ffffff;"        
        "border-radius: 20px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(201, 121, 0, 150);"
        "}"
    );
    startButton->setGeometry(835, 620, 250, 100);
    startButton->setFont(*customFont);
    startButton->show();
    connect(startButton, &QPushButton::clicked, this, &SetInitialValuesScreen::onStartButtonClicked);

    // Draw hidden rounded rectangle
    startButtonRect = new RoundedRectangle(this, 687, 510, 545, 410, QColor(0, 0, 0, 100), QColor(0, 0, 0, 100));
    startButtonRect->setParent(this);
    startButtonRect->hide();


    // Draw "SET MAP DIMENSIONS. MAX 500x500" label
    setMapDimensionsLabel = new QLabel("SET MAP DIMENSIONS \nMAX 500x500; MIN 18x18", this);
    setMapDimensionsLabel->setStyleSheet("color: #ffffff; font-size: 36px;");
    setMapDimensionsLabel->setFont(*customFont);
    setMapDimensionsLabel->setGeometry(635, 520, 650, 60);
    setMapDimensionsLabel->setAlignment(Qt::AlignCenter);
    setMapDimensionsLabel->hide();
    // Draw the input fields for the width and height and its corresponding labels
    // width 
    widthLabel = new QLabel("Width", this);
    widthLabel->setStyleSheet("color: #ffffff; font-size: 32px;");
    widthLabel->setFont(*customFont);
    widthLabel->setAlignment(Qt::AlignCenter);
    widthLabel->setGeometry(787, 600, 150, 60);
    widthLabel->hide();
    // width QLineEdit
    widthInput = new QLineEdit(this);
    widthInput->setStyleSheet(
        "QLineEdit {"
        "background-color: rgba(212, 212, 212, 150);"        
        "color: #ffffff;"                     
        "font-size: 32px;"                  
        "border: 0px solid #ffffff;"        
        "border-radius: 20px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
    );
    widthInput->setFont(*customFont);
    widthInput->setGeometry(787, 660, 150, 50);
    widthInput->hide();
    // height
    heightLabel = new QLabel("Height", this);
    heightLabel->setStyleSheet("color: #ffffff; font-size: 32px;");
    heightLabel->setFont(*customFont);
    heightLabel->setAlignment(Qt::AlignCenter);
    heightLabel->setGeometry(982, 600, 150, 60);
    heightLabel->hide();
    // height QLineEdit
    heightInput = new QLineEdit(this);
    heightInput->setStyleSheet(
        "QLineEdit {"
        "background-color: rgba(212, 212, 212, 150);" 
        "color: #ffffff;"                     
        "font-size: 32px;"                  
        "border: 0px solid #ffffff;"        
        "border-radius: 20px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
    );
    heightInput->setFont(*customFont);
    heightInput->setGeometry(982, 660, 150, 50);
    heightInput->hide();

    // Draw the start editing button
    startEditingButton = new QPushButton("Start Editing", this);
    startEditingButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(212, 212, 212, 150);"        
        "color: #ffffff;"                     
        "font-size: 42px;"                  
        "border: 0px solid #ffffff;"        
        "border-radius: 20px;"              
        "padding: 10px;"                    
        "text-align: center;"               
        "}"
        "QPushButton:hover {"
        "background-color: rgba(227, 227, 227, 150);"
        "}"
    );
    startEditingButton->setGeometry(785, 760, 350, 80);
    startEditingButton->setFont(*customFont);
    startEditingButton->hide();

    connect(startEditingButton, &QPushButton::clicked, this, &SetInitialValuesScreen::onStartEditingButtonClicked);
}

void SetInitialValuesScreen::resizeEvent(QResizeEvent *event) {
    bg->resizeImages();
}

void SetInitialValuesScreen::onStartButtonClicked() {
    buttonSound->play();
    startButton->hide();
    // show labels and qlineedits
    startButtonRect->show();
    setMapDimensionsLabel->show();
    widthLabel->show();
    widthInput->show();
    heightLabel->show();
    heightInput->show();    
    startEditingButton->show();

}

void SetInitialValuesScreen::onStartEditingButtonClicked() {
    buttonSound->play();
    // get the values from the input fields
    int width = widthInput->text().toInt();
    int height = heightInput->text().toInt();
    // check if the values are numeric and within the range
    if (width >= 18 && height >= 18 && width <= 500 && height <= 500) {
        // emit signal to send the values to the main window
        emit sendInitialValues(width, height);
    }
    else {
        // show draw message
        QLabel *errorMsg = new QLabel("Invalid values\nEnter numeric values within range", this);
        errorMsg->setAlignment(Qt::AlignCenter);
        errorMsg->setStyleSheet("color: #ff1900; font-size: 24px;");
        errorMsg->setFont(*customFont);
        errorMsg->setGeometry(610, 855, 700, 60);
        errorMsg->show();
        QTimer::singleShot(2000, errorMsg, &QObject::deleteLater);
    }
}