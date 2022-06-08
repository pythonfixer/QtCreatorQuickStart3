#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    file.setFileName("test.raw");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QAudioFormat format;
    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format))
    {
        format = info.nearestFormat(format);
    }

    QTimer::singleShot(10000, this, SLOT(stopRecording()));
    audioInput = new QAudioInput(format, this);
    audioInput->start(&file);
    ui->label->setText(tr("正在录制……"));
}

void MainWindow::on_pushButton_2_clicked()
{
    file.setFileName("test.raw");
    file.open(QIODevice::ReadOnly);

    QAudioFormat format;
    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format))
    {
        return;
    }

    audioOutput = new QAudioOutput(format, this);
    connect(audioOutput, SIGNAL(stateChanged(QAudio::State)), SLOT(finishedPlaying(QAudio::State)));
    audioOutput->start(&file);
    ui->label->setText(tr("正在播放……"));
}

void MainWindow::stopRecording()
{
    audioInput->stop();
    ui->label->setText(tr("停止录制！"));
    file.close();
    delete audioInput;
}

void MainWindow::finishedPlaying(QAudio::State state)
{
    if (state == QAudio::IdleState)
    {
        audioOutput->stop();
        ui->label->setText(tr("停止播放"));
        file.close();
        delete audioOutput;

    }
}
