#include "lobby_screen.h"

LobbyScreen::LobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue) : send_queue(send_queue), recv_queue(recv_queue) {
    quakSound = new QSound("client/menu/assets/Duck Game - Quack Sound.wav");
    white_cuak_sprite_sheet = new QPixmap("client/menu/assets/white_duck_cuak.png");

    // Initialize the label
    white_cuak_label = new QLabel(this);
    white_cuak_label->setGeometry(1280, 530, 128, 128); // Adjust size as needed
    white_cuak_label->show();

    // Initialize the timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LobbyScreen::updateAnimationFrame);

    // 
}


void LobbyScreen::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_C) {
        quakSound->play();
        timer->start(100); // Adjust the interval as needed (milliseconds)
    }
}

void LobbyScreen::updateAnimationFrame() {
    int frame_width = 32;
    int frame_height = 32;
    int frames_per_row = white_cuak_sprite_sheet->width() / frame_width;

    // Calculate the x and y coordinates of the current frame
    int x = (current_frame % frames_per_row) * frame_width;
    int y = (current_frame / frames_per_row) * frame_height;

    // Crop the current frame
    QPixmap cropped_pixmap = white_cuak_sprite_sheet->copy(x, y, frame_width, frame_height);

    // Scale the cropped pixmap to the desired size
    QPixmap scaled_pixmap = cropped_pixmap.scaled(frame_width * 4, frame_height * 4, Qt::KeepAspectRatio);

    // Update the label with the new frame
    white_cuak_label->setPixmap(scaled_pixmap);

    // Move to the next frame
    current_frame++;

    // Stop the animation when all frames have been displayed
    if (current_frame >= 4) {
        timer->stop();
        current_frame = 0;
        // crop the first frame
        QPixmap first_frame = white_cuak_sprite_sheet->copy(0, 0, frame_width, frame_height);
        QPixmap scaled_first_frame = first_frame.scaled(frame_width * 4, frame_height * 4, Qt::KeepAspectRatio);
        white_cuak_label->setPixmap(scaled_first_frame);
    }
}