#include <QObject>
#include "Decoder.h"
#include "AudioOutput.h"

class Player : public QObject
{
Q_OBJECT

private:
    Decoder m_decoder;
    // Why is it possible to create AudioOutput devices without parameters?
    AudioOutput m_device;

void playAudioFile (const QString&);

public:

signals:
    void pauseRequested();
    void resumeRequested();
    void stopRequested();
    void skipRequested(unsigned seconds);
};