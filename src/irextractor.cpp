#include "irextractor.h"
#include "ui_irextractor.h"

#include <QtGui>
#include <QtMultimedia>

#include <iostream>

IRExtractor::IRExtractor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IRExtractor)
{
    ui->setupUi(this);
}

IRExtractor::~IRExtractor()
{
    delete ui;
}

void IRExtractor::on_sweepButton_clicked()
{
    // PLAY
    QMediaPlayer* player = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput;
    audioOutput->setVolume(0.1);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/res/sweep.wav"));
    player->play();

    // RECORD
    QMediaCaptureSession* session = new QMediaCaptureSession();
    QAudioInput* audioInput = new QAudioInput();
    QMediaRecorder* recorder = new QMediaRecorder();
    session->setAudioInput(audioInput);
    session->setRecorder(recorder);
    recorder->setMediaFormat(QMediaFormat::Wave);
    recorder->setOutputLocation(QUrl::fromLocalFile("test"));
    recorder->setAudioSampleRate(48000);
    recorder->setAudioChannelCount(1);
    recorder->record();
    QThread::msleep(3250);
    recorder->stop();
}
