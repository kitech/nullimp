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
    QObject::connect(this->ui->pushButton_27, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_51, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_53, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_59, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_61, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_67, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_69, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_75, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_77, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_83, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    /////////////
    QObject::connect(this->ui->pushButton_21, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_22, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_23, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    ////////////////
    QObject::connect(this->ui->pushButton_89, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_95, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_96, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_97, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_101, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_105, SIGNAL(clicked()),
                     this, SLOT(onSelectSrc()));
    QObject::connect(this->ui->pushButton_109, SIGNAL(clicked()),
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
    QObject::connect(this->ui->pushButton_25, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_7, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_25, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_49, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_17, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_49, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_55, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_18, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_55, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_57, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->pushButton_63, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->pushButton_65, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_21, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_65, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_71, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_22, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_71, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_73, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_23, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_73, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_79, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->pushButton_81, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_25, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_81, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_85, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->pushButton_87, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_26, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_87, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_91, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_27, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_91, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_93, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_28, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_93, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_99, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_29, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_99, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_103, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_30, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_103, SIGNAL(clicked()));
    QObject::connect(this->ui->pushButton_107, SIGNAL(clicked()),
                     this, SLOT(onProcessImage()));
    QObject::connect(this->ui->horizontalSlider_31, SIGNAL(valueChanged(int)),
                     this->ui->pushButton_107, SIGNAL(clicked()));

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

    if (btn == this->ui->pushButton_27) {
        this->ui->lineEdit_13->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_38->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_51) {
        this->ui->lineEdit_25->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_76->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_53) {
        this->ui->lineEdit_27->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_78->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_59) {
        this->ui->lineEdit_29->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_84->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_61) {
        this->ui->lineEdit_31->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_90->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_67) {
        this->ui->lineEdit_33->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_94->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_69) {
        this->ui->lineEdit_35->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_99->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_75) {
        this->ui->lineEdit_37->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_105->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_77) {
        this->ui->lineEdit_39->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_111->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_83) {
        this->ui->lineEdit_41->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_114->setPixmap(tpic);
    }

    /////////////
    if (btn == this->ui->pushButton_21) {
        this->ui->lineEdit_11->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(300);
        this->ui->label_119->setPixmap(tpic);
    }
    if (btn == this->ui->pushButton_22) {
        this->ui->lineEdit_12->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(300);
        this->ui->label_33->setPixmap(tpic);
    }
    if (btn == this->ui->pushButton_23) {
        this->ui->lineEdit_15->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(300);
        this->ui->label_34->setPixmap(tpic);
    }
    //////////////////

    if (btn == this->ui->pushButton_89) {
        this->ui->lineEdit_43->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_120->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_95) {
        this->ui->lineEdit_47->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(400);
        this->ui->label_127->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_96) {
        this->ui->lineEdit_48->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(100);
        this->ui->label_128->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_97) {
        this->ui->lineEdit_45->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_132->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_101) {
        this->ui->lineEdit_49->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_137->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_105) {
        this->ui->lineEdit_51->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_142->setPixmap(tpic);
    }

    if (btn == this->ui->pushButton_109) {
        this->ui->lineEdit_53->setText(srcfile);

        QPixmap pic(srcfile);
        QPixmap tpic  = pic.scaledToWidth(500);
        this->ui->label_147->setPixmap(tpic);
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

    ///// threshold
    if (btn == this->ui->pushButton_25) {
        QString srcfile = this->ui->lineEdit_13->text();
        QString subtran = "";

        if (this->ui->radioButton_6->isChecked()) subtran = "bin";
        if (this->ui->radioButton_7->isChecked()) subtran = "binvert";
        if (this->ui->radioButton_8->isChecked()) subtran = "threshold";
        if (this->ui->radioButton_9->isChecked()) subtran = "th2zero";
        if (this->ui->radioButton_10->isChecked()) subtran = "th2zeroinvert";

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "threshold" << srcfile
             << subtran
             << QString::number(this->ui->horizontalSlider_7->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// filter2d
    if (btn == this->ui->pushButton_49) {
        QString srcfile = this->ui->lineEdit_25->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "filter2d" << srcfile
             << QString::number(this->ui->horizontalSlider_17->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// border
    if (btn == this->ui->pushButton_55) {
        QString srcfile = this->ui->lineEdit_27->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "border" << srcfile
             << QString::number(this->ui->horizontalSlider_18->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// sobel
    if (btn == this->ui->pushButton_57) {
        QString srcfile = this->ui->lineEdit_29->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "sobel" << srcfile;
            // << QString::number(this->ui->horizontalSlider_18->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// laplace
    if (btn == this->ui->pushButton_63) {
        QString srcfile = this->ui->lineEdit_31->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "laplace" << srcfile;
            // << QString::number(this->ui->horizontalSlider_18->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// canny
    if (btn == this->ui->pushButton_65) {
        QString srcfile = this->ui->lineEdit_33->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "canny" << srcfile
            << QString::number(this->ui->horizontalSlider_21->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// hough
    if (btn == this->ui->pushButton_71) {
        QString srcfile = this->ui->lineEdit_35->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "hough" << srcfile
            << QString::number(this->ui->horizontalSlider_22->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// remap
    if (btn == this->ui->pushButton_73) {
        QString srcfile = this->ui->lineEdit_37->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "remap" << srcfile
            << QString::number(this->ui->horizontalSlider_23->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// affine
    if (btn == this->ui->pushButton_79) {
        QString srcfile = this->ui->lineEdit_39->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "affine" << srcfile;
           // << QString::number(this->ui->horizontalSlider_23->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// hist
    if (btn == this->ui->pushButton_81) {
        QString srcfile = this->ui->lineEdit_41->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "hist" << srcfile
            << QString::number(this->ui->horizontalSlider_25->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// comp hist
    if (btn == this->ui->pushButton_85) {
        QString src1file = this->ui->lineEdit_11->text();
        QString src2file = this->ui->lineEdit_12->text();
        QString src3file = this->ui->lineEdit_15->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "comphist" << src1file << src2file << src3file;
            // << QString::number(this->ui->horizontalSlider_25->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// back proj
    if (btn == this->ui->pushButton_87) {
        QString srcfile = this->ui->lineEdit_43->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "backproj" << srcfile
             << QString::number(this->ui->horizontalSlider_26->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// template match
    if (btn == this->ui->pushButton_91) {
        QString src1file = this->ui->lineEdit_47->text();
        QString src2file = this->ui->lineEdit_48->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "tplmatch" << src1file << src2file
             << QString::number(this->ui->horizontalSlider_27->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// find contours
    if (btn == this->ui->pushButton_93) {
        QString srcfile = this->ui->lineEdit_45->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "contours" << srcfile
             << QString::number(this->ui->horizontalSlider_28->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// find convexhull
    if (btn == this->ui->pushButton_99) {
        QString srcfile = this->ui->lineEdit_49->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "hull" << srcfile
             << QString::number(this->ui->horizontalSlider_29->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// find box circle
    if (btn == this->ui->pushButton_103) {
        QString srcfile = this->ui->lineEdit_51->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "boxcircle" << srcfile
             << QString::number(this->ui->horizontalSlider_30->value());

        QObject::connect(proc, SIGNAL(finished()),
                         this, SLOT(onImageProcessorDone()));
        proc->run(args);
    }

    ///// find box circle
    if (btn == this->ui->pushButton_107) {
        QString srcfile = this->ui->lineEdit_53->text();

        ImageProcessor  * proc = new ImageProcessor();
        QStringList args;
        args << "boxellipse" << srcfile
             << QString::number(this->ui->horizontalSlider_31->value());

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

    if (op == "threshold") {
        QPixmap r1 = QPixmap(reses.at(4)).scaledToWidth(500);
        this->ui->label_39->setPixmap(r1);
    }

    if (op == "filter2d") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_77->setPixmap(r1);
    }

    if (op == "border") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_79->setPixmap(r1);
    }

    if (op == "sobel") {
        QPixmap r1 = QPixmap(reses.at(2)).scaledToWidth(500);
        this->ui->label_85->setPixmap(r1);
    }

    if (op == "laplace") {
        QPixmap r1 = QPixmap(reses.at(2)).scaledToWidth(500);
        this->ui->label_91->setPixmap(r1);
    }

    if (op == "canny") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_95->setPixmap(r1);
    }

    if (op == "hough") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_100->setPixmap(r1);
    }

    if (op == "remap") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_106->setPixmap(r1);
    }

    if (op == "affine") {
        QPixmap r1 = QPixmap(reses.at(2)).scaledToWidth(500);
        this->ui->label_112->setPixmap(r1);
        QPixmap r2 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_32->setPixmap(r2);
    }

    if (op == "hist") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_115->setPixmap(r1);
    }

    if (op == "comphist") {
        QString rs = reses.at(4);
        this->ui->textEdit->setText(rs);
    }

    if (op == "backproj") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(300);
        this->ui->label_123->setPixmap(r1);
        QPixmap r2 = QPixmap(reses.at(4)).scaledToWidth(300);
        this->ui->label_36->setPixmap(r2);
    }

    if (op == "tplmatch") {
        QPixmap r1 = QPixmap(reses.at(4)).scaledToWidth(300);
        this->ui->label_37->setPixmap(r1);
        QPixmap r2 = QPixmap(reses.at(5)).scaledToWidth(300);
        this->ui->label_41->setPixmap(r2);
    }

    if (op == "contours") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_133->setPixmap(r1);
    }

    if (op == "hull") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_138->setPixmap(r1);
    }

    if (op == "boxcircle") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_143->setPixmap(r1);
    }

    if (op == "boxellipse") {
        QPixmap r1 = QPixmap(reses.at(3)).scaledToWidth(500);
        this->ui->label_148->setPixmap(r1);
    }

    delete proc;
}
