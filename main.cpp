#include <QApplication>
#include <QAudioFormat>
#include "Decoder.h"

QString getSource ()
{
    return "/home/ragnarok/CLionProjects/qt-playground/test.mp3";
}

QAudioFormat getAudioFormat()
{
    QAudioFormat format;
    format.setChannelCount(2);
    format.setSampleRate(44100);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::BigEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setSampleSize(16);
    return format;
}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    auto source = getSource();
    auto format = getAudioFormat();
    Decoder decoder;
    decoder.decodeFile(source, format);
    return application.exec();
}