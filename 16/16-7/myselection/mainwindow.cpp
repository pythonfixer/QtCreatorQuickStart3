#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(7, 4, this);
    for (int row = 0; row < 7; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            QStandardItem *item = new QStandardItem(QString("%1").arg(row * 4 + column));
            model->setItem(row, column, item);
        }
    }
    tableView = new QTableView;
    tableView->setModel(model);
    setCentralWidget(tableView);

    QItemSelectionModel *selectionModel = tableView->selectionModel();
    QModelIndex topLeft;
    QModelIndex bottomRight;
    topLeft = model->index(1, 1, QModelIndex());
    bottomRight = model->index(5, 2, QModelIndex());
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Select);

    ui->mainToolBar->addAction(tr("当前项目"), this, &MainWindow::getCurrentItemData);
    ui->mainToolBar->addAction(tr("切换选择"), this, &MainWindow::toggleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getCurrentItemData()
{
    qDebug() << tr("当前项目的内容：") << tableView->selectionModel()->currentIndex().data().toString();
}

void MainWindow::toggleSelection()
{
    QModelIndex topLeft = tableView->model()->index(0, 0, QModelIndex());
    QModelIndex bottomRight = tableView->model()->index(tableView->model()->rowCount(QModelIndex()) - 1,
                                                        tableView->model()->columnCount(QModelIndex()) -1,
                                                        QModelIndex());
    QItemSelection curSelection(topLeft, bottomRight);
    tableView->selectionModel()->select(curSelection, QItemSelectionModel::Toggle);
}
