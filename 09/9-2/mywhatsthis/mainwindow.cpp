#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWhatsThis>
#include "assistant.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *action = QWhatsThis::createAction(this);
    ui->mainToolBar->addAction(action);
    QAction *help = new QAction("help", this);
    ui->mainToolBar->addAction(help);
    connect(help, &QAction::triggered, this, &MainWindow::startAssistant);
    assistant = new Assistant;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete assistant;
}

void MainWindow::startAssistant()
{
    assistant->showDocumentation("index.html");
}
