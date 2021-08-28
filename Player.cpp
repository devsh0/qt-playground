#include "Player.h"

constexpr size_t device_notification_period = { 1000 };

Player::Player(const QAudioFormat& format)
    : m_device(format, device_notification_period)
    , m_decoder(format)
{
    connect(&m_decoder, SIGNAL(decodeFinished(const QByteArray &)), &m_device, SLOT(playSamples(const QByteArray &)));
}

void Player::playAudioFile(const QString& source)
{
    m_decoder.decodeFile(source);
}