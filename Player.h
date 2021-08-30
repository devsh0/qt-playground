#include "AudioOutput.h"
#include "Decoder.h"
#include <QPushButton>
#include <QMainWindow>
#include <QPaintEvent>

class Player : public QMainWindow {
    Q_OBJECT

private:
    Decoder m_decoder;
    AudioOutput m_device;
    QWidget* m_widget;
    QLayout* m_layout;

private:
    void setupGUI();
    void setupSongInfoWidget(QWidget*);
    inline QWidget& main_widget() { return *m_widget; }
    inline QLayout& main_layout() { return *m_layout; };
private slots:
    void pausePlayback();
    void resumePlayback();
    void stopPlayback();
    void setPlaybackSource();

public:
    Player(const QAudioFormat&);
    void playAudioFile(const QString&);

protected:
    virtual void paintEvent(QPaintEvent*);
};