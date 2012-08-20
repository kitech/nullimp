/**
 *
 *
 */

#include <QtGui>

#include "simplelog.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/imageprocessor.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 *
 * TODO 改用JSON传递参数，或者可以用下protobuf
 */

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
    QObject::connect(this->ui->pushButton_3, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_7, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_9, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_13, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_17, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));

    QObject::connect(this->ui->pushButton, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->pushButton_5, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->pushButton_11, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->pushButton_15, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->pushButton_19, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
}

void MainWindow::onSelectSrc()
{
    QString srcfile = QFileDialog::getOpenFileName(this, QString(), "~/dlnk/");

    QPushButton *btn = (QPushButton*)(sender());

    if (btn == this->ui->pushButton_3) {
        this->ui->lineEdit->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_7) {
        this->ui->lineEdit_3->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_8->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_9) {
        this->ui->lineEdit_5->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_10->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_13) {
        this->ui->lineEdit_7->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_24->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_17) {
        this->ui->lineEdit_9->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_30->setPixmap(tpic);
    }
}

void MainWindow::onProcessImage()
{
    QPushButton *btn = (QPushButton*)(sender());

    // smooth
    if (btn == this->ui->pushButton) {
        QString srcfile = this->ui->lineEdit->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "smooth" << srcfile;

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    // erode
    if (btn == this->ui->pushButton_5) {
        QString srcfile = this->ui->lineEdit_3->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "erode" << srcfile
             << QString::number(this->ui->horizontalSlider->value())
             << QString::number(this->ui->horizontalSlider_2->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    // dilate
    if (btn == this->ui->pushButton_11) {
        QString srcfile = this->ui->lineEdit_5->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "dilate" << srcfile
             << QString::number(this->ui->horizontalSlider_3->value())
             << QString::number(this->ui->horizontalSlider_4->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    // morphology
    if (btn == this->ui->pushButton_15) {
        QString srcfile = this->ui->lineEdit_7->text();
        QString subtran = "";

        if (this->ui->radioButton->isChecked()) subtran = "open";
        if (this->ui->radioButton_2->isChecked()) subtran = "close";
        if (this->ui->radioButton_3->isChecked()) subtran = "morph";
        if (this->ui->radioButton_4->isChecked()) subtran = "tophat";
        if (this->ui->radioButton_5->isChecked()) subtran = "blackhat";

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "morph" << srcfile
             << QString::number(this->ui->horizontalSlider_5->value())
             << QString::number(this->ui->horizontalSlider_6->value())
             << subtran;

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// pyramids
    if (btn == this->ui->pushButton_19) {
        QString srcfile = this->ui->lineEdit_9->text();
        QString updown;

        if (this->ui->radioButton_11->isChecked()) updown = "down";
        if (this->ui->radioButton_12->isChecked()) updown = "up";

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "pyramids" << srcfile
             << updown
             << QString::number(this->ui->horizontalSlider_8->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }
}

void MainWindow:: onImageProcessorDone()
{
    ImageProcessor *proc = (ImageProcessor*)(sender());
    QStringList reses = proc->getResult();

    qLogx()<<"process result:"<< reses;

    QString op = reses.at(0);

    if (op == "smooth") {
        QPixmap r1 = QPixmap(reses.at(2)).scaledToWidth(300);
        QPixmap r2 = QPixmap(reses.at(3)).scaledToWidth(300);
        QPixmap r3 = QPixmap(reses.at(4)).scaledToWidth(300);
        QPixmap r4 = QPixmap(reses.at(5)).scaledToWidth(300);

        this->ui->label_2->setPixmap(r1);
        this->ui->label_5->setPixmap(r2);
        this->ui->label_6->setPixmap(r3);
        this->ui->label_7->setPixmap(r4);
    }


    if (op == "erode") {
        QPixmap r1 = QPixmap(reses.at(4)).scaledToWidth(500);
        this->ui->label_9->setPixmap(r1);
    }

    if (op == "dilate") {
        QPixmap r1 = QPixmap(reses.at(4)).scaledToWidth(500);
        this->ui->label_11->setPixmap(r1);

    }

    if (op == "morph") {
        QPixmap r1 = QPixmap(reses.at(5)).scaledToWidth(500);
        this->ui->label_25->setPixmap(r1);

    }

    if (op == "pyramids") {
        QPixmap r1 = QPixmap(reses.at(4));  // .scaledToWidth(500);
        this->ui->label_31->setPixmap(r1);
    }

    delete proc;
}
