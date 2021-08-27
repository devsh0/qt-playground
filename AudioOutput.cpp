#include "AudioOutput.h"

AudioOutput::AudioOutput(const QAudioFormat &format, size_t notification_interval)
        : m_audio_output(new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format))
{
    m_buffer.open(QBuffer::ReadWrite);
    setupAudioOutputDevice(format, notification_interval);
}

void AudioOutput::setupAudioOutputDevice(const QAudioFormat &format, size_t notification_interval)
{
    m_audio_output->setNotifyInterval(notification_interval);
    m_audio_output->start(&m_buffer);
    connect(m_audio_output, SIGNAL(notify()), this, SLOT(processNotification()));
    connect(m_audio_output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChange(QAudio::State)));
}

void AudioOutput::handleStateChange(QAudio::State state)
{
    switch (state)
    {
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

void AudioOutput::processNotification()
{
    double seconds = m_audio_output->processedUSecs() * 1e-6;
    qDebug() << "Processed audio duration: " << seconds << "\n";
    m_buffer.seek(m_buffer.pos() + 1000000);
}

AudioOutput::~AudioOutput() noexcept
{
    m_buffer.close();
    m_audio_output->stop();
    delete m_audio_output;
}