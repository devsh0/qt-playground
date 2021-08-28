#include "AudioOutput.h"
#include "Decoder.h"
#include <QPushButton>
#include <QMainWindow>

class Player : public QMainWindow {
    Q_OBJECT

private:
    Decoder m_decoder;
    AudioOutput m_device;

private:
    QPushButton m_pause_button;
    QPushButton m_resume_button;
    QPushButton m_stop_button;
    QPushButton m_change_song_button;
    void setupGUI();

private slots:
    void pausePlayback();
    void resumePlayback();
    void stopPlayback();
    void setPlaybackSource();

public:
    void playAudioFile(const QString&);
    Player(const QAudioFormat&);
};