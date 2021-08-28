#include "AudioOutput.h"
#include "Decoder.h"

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
    // TODO: We will need this.
    //connect(m_audio_output, SIGNAL(notify()), this, SLOT(processNotification()));
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
    m_audio_output->reset();
}

void AudioOutput::playSamples(const QByteArray& samples)
{
    stopPlayback();
    m_buffer.buffer().append(samples);
    m_audio_output->start(&m_buffer);
}

void AudioOutput::pausePlayback()
{
    m_audio_output->suspend();
}

void AudioOutput::resumePlayback()
{
    m_audio_output->resume();
}

void AudioOutput::stopPlayback()
{
    resetDevice();
}

AudioOutput::~AudioOutput() noexcept
{
    m_buffer.close();
    m_audio_output->stop();
    delete m_audio_output;
}