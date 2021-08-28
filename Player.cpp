#include "Player.h"

constexpr size_t device_notification_period = { 1000 };

Player::Player(const QAudioFormat& format)
    : m_device(format, device_notification_period)
    , m_decoder(format)
    , m_pause_button("Pause", this)
    , m_resume_button("Resume", this)
    , m_stop_button("Stop", this)
    , m_change_song_button("Change", this)
{
    setFixedSize(600, 400);
    setWindowTitle("Music Player");

    int base_width = m_pause_button.width();
    m_pause_button.move(0, 0);
    m_pause_button.show();
    m_resume_button.move(base_width, 0);
    m_resume_button.show();
    m_stop_button.move(base_width * 2, 0);
    m_stop_button.show();
    m_change_song_button.move(base_width * 3, 0);
    connect(&m_pause_button, SIGNAL(clicked(bool)), this, SLOT(pausePlayback()));
    connect(&m_resume_button, SIGNAL(clicked(bool)), this, SLOT(resumePlayback()));
    connect(&m_stop_button, SIGNAL(clicked(bool)), this, SLOT(stopPlayback()));
    connect(&m_change_song_button, SIGNAL(clicked(bool)), this, SLOT(setPlaybackSource()));

    connect(&m_decoder, SIGNAL(decodeFinished(const QByteArray&)), &m_device, SLOT(playSamples(const QByteArray&)));
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