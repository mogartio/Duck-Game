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
    startButtonRect = new RoundedRectangle(this, 687, 510, 545, 450, QColor(0, 0, 0, 100), QColor(0, 0, 0, 100));
    startButtonRect->setParent(this);
    startButtonRect->hide();


    // Draw "SET MAP DIMENSIONS. MAX 500x500" label
    setMapDimensionsLabel = new QLabel("SET MAP DIMENSIONS \nMAX 75x75; MIN 3x3", this);
    setMapDimensionsLabel->setStyleSheet("color: #ffffff; font-size: 36px;");
    setMapDimensionsLabel->setFont(*customFont);
    setMapDimensionsLabel->setGeometry(635, 525, 650, 60);
    setMapDimensionsLabel->setAlignment(Qt::AlignCenter);
    setMapDimensionsLabel->hide();
    // Draw the input fields for the width and height and its corresponding labels
    // width 
    columnsLabel = new QLabel("columns", this);
    columnsLabel->setStyleSheet("color: #ffffff; font-size: 32px;");
    columnsLabel->setFont(*customFont);
    columnsLabel->setAlignment(Qt::AlignCenter);
    columnsLabel->setGeometry(740, 600, 150, 60);
    columnsLabel->hide();
    // columns QLineEdit
    columnsInput = new QLineEdit(this);
    columnsInput->setStyleSheet(
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
    columnsInput->setFont(*customFont);
    columnsInput->setGeometry(740, 660, 150, 50);
    columnsInput->hide();
    // height
    rowsLabel = new QLabel("rows", this);
    rowsLabel->setStyleSheet("color: #ffffff; font-size: 32px;");
    rowsLabel->setFont(*customFont);
    rowsLabel->setAlignment(Qt::AlignCenter);
    rowsLabel->setGeometry(740, 710, 150, 60);
    rowsLabel->hide();
    // rows QLineEdit
    rowsInput = new QLineEdit(this);
    rowsInput->setStyleSheet(
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
    rowsInput->setFont(*customFont);
    rowsInput->setGeometry(740, 770, 150, 50);
    rowsInput->hide();

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
    startEditingButton->setGeometry(785, 845, 350, 80);
    startEditingButton->setFont(*customFont);
    startEditingButton->hide();

    connect(startEditingButton, &QPushButton::clicked, this, &SetInitialValuesScreen::onStartEditingButtonClicked);

    // theme label
    themeLabel = new QLabel("Theme", this);
    themeLabel->setStyleSheet("color: #ffffff; font-size: 32px;");
    themeLabel->setFont(*customFont);
    themeLabel->setAlignment(Qt::AlignCenter);
    themeLabel->setGeometry(980, 600, 150, 60);
    themeLabel->hide();
    // rectangle
    themeRect = new RoundedRectangle(this, 980, 660, 170, 160, QColor(212, 212, 212, 150), QColor(212, 212, 212, 150));
    themeRect->setParent(this);
    themeRect->hide();

    // initialize buttons
    lightTheme = new QRadioButton("Light", this);
    nightTheme = new QRadioButton("Night", this);

    lightTheme->setStyleSheet(
        "QRadioButton {"
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #ffffff;"        
        "padding: 10px;"                    
        "}"
        "QRadioButton::indicator {"
        "width: 20px;"
        "height: 20px;"
        "}"
        "QRadioButton::indicator::unchecked {"
        "border: 2px solid #ffffff;"
        "border-radius: 10px;"
        "}"
        "QRadioButton::indicator::checked {"
        "background-color: #ffffff;"
        "border: 2px solid #ffffff;"
        "border-radius: 10px;"
        "}"
    );
    lightTheme->setFont(*customFont);

    nightTheme->setStyleSheet(
        "QRadioButton {"
        "color: #ffffff;"                     
        "font-size: 28px;"                  
        "border: 0px solid #ffffff;"        
        "padding: 10px;"                    
        "}"
        "QRadioButton::indicator {"
        "width: 20px;"
        "height: 20px;"
        "}"
        "QRadioButton::indicator::unchecked {"
        "border: 2px solid #ffffff;"
        "border-radius: 10px;"
        "}"
        "QRadioButton::indicator::checked {"
        "background-color: #ffffff;"
        "border: 2px solid #ffffff;"
        "border-radius: 10px;"
        "}"
    );
    nightTheme->setFont(*customFont);

    lightTheme->setGeometry(995, 680, 130, 50);
    nightTheme->setGeometry(995, 740, 130, 50);

    lightTheme->setChecked(true);
    // hidden
    lightTheme->hide();
    nightTheme->hide();

    connect(lightTheme, &QRadioButton::clicked, this, &SetInitialValuesScreen::onThemeChanged);
    connect(nightTheme, &QRadioButton::clicked, this, &SetInitialValuesScreen::onThemeChanged);
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
    columnsLabel->show();
    columnsInput->show();
    rowsLabel->show();
    rowsInput->show();    
    startEditingButton->show();
    themeRect->show();
    lightTheme->show();
    nightTheme->show();
    themeLabel->show();
}

void SetInitialValuesScreen::onStartEditingButtonClicked() {
    buttonSound->play();
    // get the values from the input fields
    int columns = columnsInput->text().toInt();
    int rows = rowsInput->text().toInt();
    // check if the values are numeric and within the range
    if (columns >= 3 && rows >= 3 && columns <= 75 && rows <= 75) {
        // emit signal to send the values to the main window
        emit sendInitialValues(columns, rows, choosenTheme);
    }
    else {
        // show draw message
        QLabel *errorMsg = new QLabel("Enter numeric values within range", this);
        errorMsg->setAlignment(Qt::AlignCenter);
        errorMsg->setStyleSheet("color: #ff1900; font-size: 24px;");
        errorMsg->setFont(*customFont);
        errorMsg->setGeometry(610, 910, 700, 60);
        errorMsg->show();
        QTimer::singleShot(2000, errorMsg, &QObject::deleteLater);
    }
}

void SetInitialValuesScreen::onThemeChanged() {
    if (lightTheme->isChecked()) {
        choosenTheme = "light";
    }
    else if (nightTheme->isChecked()) {
        choosenTheme = "night";
    }
    else {
        choosenTheme = "light";
    }
}