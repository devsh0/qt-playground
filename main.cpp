#include "Decoder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QString source = "/home/ragnarok/CLionProjects/qt-playground/test.mp3";
    Decoder window(nullptr, source);
    return application.exec();
}