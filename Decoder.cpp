#include "Decoder.h"
#include <QBuffer>

Decoder::Decoder()
{
    connect(&m_decoder, SIGNAL(bufferReady()), this, SLOT(handleBufferReady()));
    connect(&m_decoder, SIGNAL(finished()), this, SLOT(handleDecodeFinished()));
    connect(&m_decoder, SIGNAL(sourceChanged()), this, SLOT(handleSourceChanged()));
}

void Decoder::resetDecoder()
{
    m_decode_buffer.clear();
    m_decoder.stop();
}

QByteArray Decoder::decodeFile(const QString& source, const QAudioFormat& format)
{
    m_decoder.setSourceFilename(source);
    m_decoder.setAudioFormat(format);
    m_decoder.start();
    return m_decode_buffer;
}

void Decoder::handleBufferReady()
{
    auto audio_buffer = m_decoder.read();
    char* data = (char*)audio_buffer.data();
    size_t size = audio_buffer.byteCount();
    for (size_t i = 0; i < size; i++)
        m_decode_buffer.append(data[i]);
}

void Decoder::handleDecodeFinished()
{
    qDebug() << "Decode finished: " << m_decode_buffer.size() << "\n";
    emit decodeFinished(m_decode_buffer);
    resetDecoder();
}

void Decoder::handleSourceChanged()
{
    resetDecoder();
    emit decodeInterrupted();
}

size_t Decoder::getDecodedDataSize() const
{
    return m_decode_buffer.size();
}