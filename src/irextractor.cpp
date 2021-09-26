#include "irextractor.h"
#include "ui_irextractor.h"

#include <QtGui>
#include <QtMultimedia>

#include <iostream>
#include <cstdlib>

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

QAudioDecoder *decoder = new QAudioDecoder();
// NOTE1: The whole sound processing should be ARRAY BASED and not file based !!! 
// NOTE2: This code should play and recors simultaneously but I didn't get sucess.
// The player plays for his own and the recoder records for his own but i cannot duplex both.
// I tried timers, maked the members static, used threads and connect all the
// signals from the player to the stop method of the recorder without any success.
// Cannot implement the rest of the signal analyze without the recording...
void IRExtractor::on_sweepButton_clicked()
{
    // PLAY
// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEB
// EBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBU
// BUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
//    QMediaPlayer* player = new QMediaPlayer();
//    QAudioOutput* audioOutput = new QAudioOutput;
//    audioOutput->setVolume(0.1);
//    player->setAudioOutput(audioOutput);
//    player->setSource(QUrl("qrc:/res/sweep.wav"));
//    player->play();
// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEB
// EBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBU
// BUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG

    system("/usr/bin/afplay /Users/christoph/Documents/DEVELOPMENT/Impulse-Response-Extractor/src/res/sweep.wav &");
    system("rm ~/Music/test.wav");

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

    // READ
    QAudioFormat desiredFormat;
    desiredFormat.setChannelCount(2);
    desiredFormat.setSampleFormat(QAudioFormat::Int16);
    desiredFormat.setSampleRate(48000);
    decoder->setAudioFormat(desiredFormat);
    decoder->setSource(QUrl::fromLocalFile("/Users/christoph/Music/test.wav"));
    connect(decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
    decoder->start();
}

QVector<int> samples;
void IRExtractor::readBuffer()
{
    qDebug() << "READ BUFFER";
    QAudioBuffer buffer = decoder->read();
    qDebug() << buffer.format();
    qDebug() << buffer.sampleCount();
    qDebug() << buffer.frameCount();
    quint16 *data = buffer.data<quint16>();
    for(int i=0; i<buffer.sampleCount(); i++)
    {
        samples.push_back(data[i]);
    }
    qDebug() << samples.size();
}
