#pragma once

#include <QAudioOutput>
#include <QBuffer>
#include <QtMultimedia/QAudioDecoder>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QMediaPlayer>

class Decoder : public QObject {
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

    void decodeFile(const QString& source, const QAudioFormat& format);
    size_t getDecodedDataSize() const;

signals:
    void decodeFinished(const QByteArray&);
    void decodeInterrupted();
};
