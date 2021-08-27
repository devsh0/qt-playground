#pragma once

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
    QByteArray m_decode_buffer;

    void resetDecoder();
private slots:

    void handleBufferReady();
    void handleDecodeFinished();
    void handleSourceChanged();

public:
    Decoder();

    QByteArray decodeFile(const QString &source, const QAudioFormat &format);
    size_t getDecodedDataSize() const;

    signals:
    void decodeFinished(QByteArray&);
    void decodeInterrupted();
};
