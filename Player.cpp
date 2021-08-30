#include "Player.h"
#include "CustomPlayButton.h"
#include "CustomPlaylistNavButton.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QStyle>

constexpr size_t device_notification_period = { 1000 };

Player::Player(const QAudioFormat& format)
    : m_device(format, device_notification_period)
    , m_decoder(format)
    , m_widget(new QWidget(this))
    , m_layout(new QVBoxLayout)
{
    setupGUI();
    connect(&m_decoder, SIGNAL(decodeFinished(const QByteArray&)), &m_device, SLOT(playSamples(const QByteArray&)));
}

void Player::setupGUI()
{
    setFixedSize(500, 400);
    setWindowTitle("Music Player");
    main_widget().setLayout(&main_layout());
    main_layout().setContentsMargins({0, 0, 0, 0});

    int w = 100;
    int h = w;
    auto* play_button = new CustomPlayButton(&main_widget());
    play_button->setFixedSize(w, h);
    main_layout().addWidget(play_button);
    
    auto* nav_left_button = new CustomPlaylistNavButton(this, true);
    nav_left_button->setFixedSize(w, h);
    main_layout().addWidget(nav_left_button);

    auto* nav_right_button = new CustomPlaylistNavButton(this, false);
    nav_right_button->setFixedSize(w, h);
    main_layout().addWidget(nav_right_button);

    setCentralWidget(&main_widget());
}

void Player::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QLinearGradient gradient({300, 130}, {300, 350});
    QColor color("#333");
    gradient.setColorAt(0, color);
    gradient.setColorAt(1, color.darker());
    QRect rectangle(0, 0, 600, 400);
    painter.fillRect(rectangle, gradient);
}

void Player::playAudioFile(const QString& source)
{
    m_decoder.decodeFile(source);
}

void Player::pausePlayback()
{
    m_device.pausePlayback();
}

void Player::resumePlayback()
{
    m_device.resumePlayback();
}

void Player::stopPlayback()
{
    m_device.stopPlayback();
}

void Player::setPlaybackSource()
{
    static QString primary = "/home/ragnarok/CLionProjects/qt-playground/test.mp3";
    static QString secondary = "/home/ragnarok/CLionProjects/qt-playground/test2.mp3";
    static QString current = primary;

    bool playing_primary = current == primary;
    if (playing_primary) {
        playAudioFile(secondary);
        current = secondary;
    } else {
        playAudioFile(primary);
        current = primary;
    }
}