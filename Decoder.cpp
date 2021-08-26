#include "Decoder.h"
#include <iostream>
#include <QBuffer>

Decoder::Decoder(QObject *parent, const QString& source) :
        QObject(parent)
{
    QAudioFormat audio_format;
    audio_format.setChannelCount(2);
    audio_format.setCodec("audio/pcm");
    audio_format.setSampleType(QAudioFormat::SignedInt);
    audio_format.setByteOrder(QAudioFormat::BigEndian);
    audio_format.setSampleRate(44100);
    audio_format.setSampleSize(16);

    setupAudioOutputDevice(audio_format);
    setupDecoder(audio_format, source);
    m_decoder.start();
}

void Decoder::setupDecoder(const QAudioFormat& format, const QString& source)
{
    m_decoder.setAudioFormat(format);
    m_decoder.setSourceFilename(source);
    connect(&m_decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
    connect(&m_decoder, SIGNAL(finished()), this, SLOT(onDecodeFinished()));
    connect(m_audio_output, SIGNAL(notify()), this, SLOT(processNotification()));
    connect(m_audio_output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(onStateChanged(QAudio::State)));
}

void Decoder::setupAudioOutputDevice(const QAudioFormat& format)
{
    m_audio_output = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format);
    m_audio_output->setNotifyInterval(1000);
    m_buffer.open(QBuffer::ReadWrite);
    m_audio_output->start(&m_buffer);
}

void Decoder::readBuffer()
{
    auto audio_buffer = m_decoder.read();
    m_buffer.write((char*)audio_buffer.data(), audio_buffer.byteCount());
}

void Decoder::onDecodeFinished()
{
    m_decoder.stop();
    m_buffer.seek(0);
}

void Decoder::onStateChanged(QAudio::State state)
{
    switch(state) {
        case QAudio::StoppedState:
            qDebug() << "AudioOutput device stopped.\n";
            break;
        case QAudio::IdleState:
            qDebug() << "AudioOutput device idling.\n";
            break;
        default:
            qDebug() << "Whatever it is we don't care.\n";
            break;
    }
}

void Decoder::processNotification()
{
    double seconds = m_audio_output->processedUSecs() * 1e-6;
    qDebug() << "Processed audio duration: " << seconds << "\n";
    m_buffer.seek(m_buffer.pos() + 1000000);
}