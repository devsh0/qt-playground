#include "Player.h"
#include <QApplication>
#include <QAudioFormat>

QString getPrimarySource()
{
    return "/home/ragnarok/CLionProjects/qt-playground/test.mp3";
}

QString getSecondarySource()
{
    return "/home/ragnarok/CLionProjects/qt-playground/test2.mp3";
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

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    auto primary_source = getPrimarySource();
    auto secondary_source = getSecondarySource();
    auto format = getAudioFormat();

    Player player(format);
    player.playAudioFile(primary_source);
    player.playAudioFile(secondary_source);
    return application.exec();
}