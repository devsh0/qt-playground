#pragma once

#include <QWidget>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioDecoder>
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>
#include <QBuffer>

class Decoder : public QObject
{
    Q_OBJECT

private:
    QAudioDecoder m_decoder;
    QBuffer m_buffer;
    QAudioOutput* m_audio_output;

    void setupDecoder(const QAudioFormat&, const QString&);
    void setupAudioOutputDevice(const QAudioFormat&);

private slots:
    void readBuffer();
    void onDecodeFinished();
    void onStateChanged(QAudio::State);
    void processNotification();

public:
    explicit Decoder(QObject* parent, const QString&);
};
