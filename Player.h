#include "AudioOutput.h"
#include "Decoder.h"
#include <QObject>

class Player : public QObject {
    Q_OBJECT

private:
    Decoder m_decoder;
    AudioOutput m_device;

public:
    void playAudioFile(const QString&);
    Player(const QAudioFormat&);
};