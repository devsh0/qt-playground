#include "AudioOutput.h"
#include "Decoder.h"

// TODO: Clean this mess. Decoder SHOULD NOT be here.
AudioOutput::AudioOutput(const QAudioFormat& format, size_t ms_notification_interval)
    : m_audio_output(new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format))
{
    m_buffer.open(QBuffer::ReadOnly);
    setupAudioOutputDevice(format, ms_notification_interval);
}

void AudioOutput::setupAudioOutputDevice(const QAudioFormat& format, size_t ms_notification_interval)
{
    m_audio_output->setNotifyInterval(ms_notification_interval);
    m_audio_output->start(&m_buffer);
    connect(m_audio_output, SIGNAL(notify()), this, SLOT(processNotification()));
    connect(m_audio_output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChange(QAudio::State)));
}

void AudioOutput::handleStateChange(QAudio::State state)
{
    switch (state) {
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
}

void AudioOutput::resetDevice()
{
    m_buffer.buffer().clear();
    m_buffer.seek(0);
}

void AudioOutput::playSamples(const QByteArray& samples)
{
    resetDevice();
    m_buffer.buffer().append(samples);
    m_audio_output->start(&m_buffer);
}

AudioOutput::~AudioOutput() noexcept
{
    m_buffer.close();
    m_audio_output->stop();
    delete m_audio_output;
}