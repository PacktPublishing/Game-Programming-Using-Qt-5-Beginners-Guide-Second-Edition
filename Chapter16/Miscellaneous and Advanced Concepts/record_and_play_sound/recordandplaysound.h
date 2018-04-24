#ifndef RECORDANDPLAYSOUND_H
#define RECORDANDPLAYSOUND_H

#include <QMainWindow>
#include <QtMultimedia>

namespace Ui {
class RecordAndPlaySound;
}

class RecordAndPlaySound : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecordAndPlaySound(QWidget *parent = 0);
    ~RecordAndPlaySound();

private slots:
    void on_input_currentIndexChanged(int index);
    void on_record_toggled(bool checked);
    void on_play_toggled(bool checked);
    void playbackStateChanged(QMediaPlayer::State state);

private:
    Ui::RecordAndPlaySound *ui;
    QString m_file;
    QAudioRecorder *m_recorder;
    QMediaPlayer *m_player;
};

#endif // RECORDANDPLAYSOUND_H
