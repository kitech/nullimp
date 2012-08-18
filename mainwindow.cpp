
#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/imageprocessor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->installConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::installConnection()
{
    QObject::connect(this->ui->pushButton, SIGNAL(clicked()),
                     this, SLOT(onSmoothImage()));

    QObject::connect(this->ui->pushButton_3, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));


}

void MainWindow::onSelectSrc()
{
    QString srcfile = QFileDialog::getOpenFileName(this);

    this->ui->lineEdit->setText(srcfile);

    QPixmap pic(srcfile);
    QPixmap tpic  = pic.scaledToWidth(500);
    this->ui->label->setPixmap(tpic);
}

void MainWindow:: onImageProcessorDone()
{
    ImageProcessor *proc = (ImageProcessor*)(sender());
    QStringList reses = proc->getResult();

    qDebug()<<"process result:"<< reses;
}

void MainWindow::onSmoothImage()
{
    QString srcfile = this->ui->lineEdit->text();

    ImageProcessor  * proc = new ImageProcessor();
    QStringList args;
    args << "smooth" << srcfile;

    QObject::connect(proc, SIGNAL(finished()),
                     this, SLOT(onImageProcessorDone()));
    proc->run(args);
}

