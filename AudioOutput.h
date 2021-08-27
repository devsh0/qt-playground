#pragma once

#include "Decoder.h"
#include <QAudioOutput>
#include <QBuffer>
#include <QDebug>
#include <QObject>

class AudioOutput : public QObject {
    Q_OBJECT;

private:
    QAudioOutput* const m_audio_output;
    QBuffer m_buffer;
    void setupAudioOutputDevice(const QAudioFormat&, size_t);

private slots:
    void handleStateChange(QAudio::State);
    void processNotification();
    void resetDevice();
    void playSamples(const QByteArray&);

public:
    AudioOutput() = delete;
    explicit AudioOutput(const QAudioFormat& format, size_t);

    ~AudioOutput() noexcept override;
};