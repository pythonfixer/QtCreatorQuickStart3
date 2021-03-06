#include "widget.h"
#include "ui_widget.h"
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QToolBar>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    Phonon::MediaObject *mediaObject = new Phonon::MediaObject(this);
    videoWidget = new Phonon::VideoWidget(this);
    Phonon::createPath(mediaObject, videoWidget);
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
    Phonon::createPath(mediaObject, audioOutput);
    mediaObject->setCurrentSource(Phonon::MediaSource("../myPhonon3/myVideo.WMV"));

    Phonon::SeekSlider *seekSlider = new Phonon::SeekSlider(mediaObject, this);

    QToolBar *toolBar = new QToolBar(this);
    QAction *playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("播放"), this);
    connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
    QAction *pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("暂停"), this);
    connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()));
    QAction *stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("停止"), this);
    connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));
    Phonon::VolumeSlider *volumeSlider = new Phonon::VolumeSlider(audioOutput, this);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    toolBar->addAction(playAction);
    toolBar->addAction(pauseAction);
    toolBar->addAction(stopAction);
    toolBar->addWidget(volumeSlider);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(videoWidget);
    mainLayout->addWidget(seekSlider);
    mainLayout->addWidget(toolBar);
    mainLayout->addWidget(ui->frame);
    setLayout(mainLayout);

    setContextMenuPolicy(Qt::CustomContextMenu);
    videoWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(videoWidget, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));
    createContextMenu();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    videoWidget->setBrightness(value / 10.0);
}

void Widget::on_horizontalSlider_2_valueChanged(int value)
{
    videoWidget->setHue(value / 10.0);
}

void Widget::on_horizontalSlider_3_valueChanged(int value)
{
    videoWidget->setSaturation(value / 10.0);
}

void Widget::on_horizontalSlider_4_valueChanged(int value)
{
    videoWidget->setContrast(value / 10.0);
}

void Widget::createContextMenu()
{
    mainMenu = new QMenu(this);

    QMenu *aspectMenu = mainMenu->addMenu(tr("宽高比"));
    QActionGroup *aspectGroup = new QActionGroup(aspectMenu);
    connect(aspectGroup, SIGNAL(triggered(QAction*)), this, SLOT(aspectChanged(QAction*)));
    aspectGroup->setExclusive(true);
    QAction *aspectActionAuto = aspectMenu->addAction(tr("自动"));
    aspectActionAuto->setCheckable(true);
    aspectActionAuto->setChecked(true);
    aspectGroup->addAction(aspectActionAuto);
    QAction *aspectActionScale = aspectMenu->addAction(tr("缩放"));
    aspectActionScale->setCheckable(true);
    aspectGroup->addAction(aspectActionScale);
    QAction *aspectAction16_9 = aspectMenu->addAction(tr("16:9"));
    aspectAction16_9->setCheckable(true);
    aspectGroup->addAction(aspectAction16_9);
    QAction *aspectAction4_3 = aspectMenu->addAction(tr("4:3"));
    aspectAction4_3->setCheckable(true);
    aspectGroup->addAction(aspectAction4_3);

    QMenu *scaleMenu = mainMenu->addMenu(tr("缩放模式"));
    QActionGroup *scaleGroup = new QActionGroup(scaleMenu);
    connect(scaleGroup, SIGNAL(triggered(QAction*)), this, SLOT(scaleChanged(QAction*)));
    scaleGroup->setExclusive(true);
    QAction *scaleActionFit = scaleMenu->addAction(tr("保持宽高比"));
    scaleActionFit->setCheckable(true);
    scaleActionFit->setChecked(true);
    scaleGroup->addAction(scaleActionFit);
    QAction *scaleActionCrop = scaleMenu->addAction(tr("缩放和裁剪"));
    scaleActionCrop->setCheckable(true);
    scaleGroup->addAction(scaleActionCrop);

    QAction *fullScreenAction = mainMenu->addAction(tr("全屏"));
    fullScreenAction->setCheckable(true);
    connect(fullScreenAction, SIGNAL(toggled(bool)), videoWidget, SLOT(setFullScreen(bool)));
}

void Widget::showContextMenu(const QPoint &pos)
{
    mainMenu->popup(videoWidget->isFullScreen() ? pos : mapToGlobal(pos));
}

void Widget::aspectChanged(QAction *action)
{
    if (action->text() == tr("16:9"))
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    else if (action->text() == tr("缩放"))
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatioWidget);
    else if (action->text() == tr("4:3"))
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatio4_3);
    else
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatioAuto);
}

void Widget::scaleChanged(QAction *action)
{
    if (action->text() == tr("缩放和裁剪"))
        videoWidget->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);
    else
        videoWidget->setScaleMode(Phonon::VideoWidget::FitInView);
}
