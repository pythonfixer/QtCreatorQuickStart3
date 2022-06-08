#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <phonon>
#include <QDebug>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Phonon::MediaObject *mediaObject = new Phonon::MediaObject(this);
    mediaObject->setCurrentSource(Phonon::MediaSource("../myPhonon1/mysong.mp3"));
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);
    mediaObject->play();

    QList<Phonon::EffectDescription> effectDescriptions = Phonon::BackendCapabilities::availableAudioEffects();
    qDebug() << effectDescriptions;
    Phonon::EffectDescription effectDescription = effectDescriptions.at(5);
    Phonon::Effect *effect = new Phonon::Effect(effectDescription);
    path.insertEffect(effect);
    Phonon::EffectWidget *effectWidget = new Phonon::EffectWidget(effect);
    effectWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
