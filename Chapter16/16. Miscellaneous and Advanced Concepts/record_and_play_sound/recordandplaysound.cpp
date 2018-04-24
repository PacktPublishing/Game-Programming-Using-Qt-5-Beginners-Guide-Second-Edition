#include "recordandplaysound.h"
#include "ui_recordandplaysound.h"

RecordAndPlaySound::RecordAndPlaySound(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecordAndPlaySound),
    m_recorder(new QAudioRecorder(this)),
    m_player(new QMediaPlayer(this))
{
    ui->setupUi(this);
    m_file = QDir(QCoreApplication::applicationDirPath())
        .absoluteFilePath("test.ogg");

    m_recorder->setOutputLocation(m_file);
    const QStringList inputs = m_recorder->audioInputs();
    for(const QString &input: inputs) {
        ui->input->addItem(m_recorder->audioInputDescription(input), input);
    }
    m_recorder->setAudioInput(ui->input->currentData().toString());

    qDebug() << "supportedAudioCodecs: " << m_recorder->supportedAudioCodecs();
    qDebug() << "supportedContainers: " << m_recorder->supportedContainers();
    QAudioEncoderSettings settings;
    settings.setCodec("audio/x-vorbis");
    m_recorder->setEncodingSettings(settings, QVideoEncoderSettings(),
                                    "audio/ogg");

    connect(m_player, &QMediaPlayer::stateChanged,
            this,     &RecordAndPlaySound::playbackStateChanged);
}

RecordAndPlaySound::~RecordAndPlaySound()
{
    delete ui;
}

void RecordAndPlaySound::on_input_currentIndexChanged(int index)
{
    m_recorder->setAudioInput(ui->input->itemData(index).toString());
}

void RecordAndPlaySound::on_record_toggled(bool checked)
{
    if (checked) {
        m_recorder->record();
    } else {
        m_recorder->stop();
    }
}

void RecordAndPlaySound::on_play_toggled(bool checked)
{
    if (checked) {
        m_player->setMedia(QUrl::fromLocalFile(m_file));
        m_player->play();
    } else {
        m_player->stop();
    }
}

void RecordAndPlaySound::playbackStateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState) {
        ui->play->setChecked(false);
    }
}
