#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "simplelog.h"
#include "imageprocessor.h"

using namespace cv;

/**
 * @brief ImageProcessor::ImageProcessor
 * @param parent
 *
 * 图片处理线程类，使用线程异步处理，防止冻结GUI
 *
 */
ImageProcessor::ImageProcessor(QObject *parent) :
    QThread(parent)
{
}

/**
 * @brief ImageProcessor::run
 */
void ImageProcessor::run()
{
    QStringList args = this->margs;

    qLogx() << "haha" <<args;

    QString op = args.at(0);
    QString src1, src2;

    QDateTime btime = QDateTime::currentDateTime();

    if (op == "smooth") {
        src1 = args.at(1);

        this->smooth_it(src1);

    } else if (op == "erode") {
        src1 = args.at(1);
        this->erode_it(src1);
    } else if (op == "dilate") {
        src1 = args.at(1);
        this->dilate_it(src1);
    } else if (op == "morph") {
        src1 = args.at(1);
        this->morph_it(src1);
    } else {
        qLogx() << "unknown op: " + op;
    }

    QDateTime etime = QDateTime::currentDateTime();

    this->mbtime = btime;
    this->metime = etime;
    this->mdtime = btime.msecsTo(etime) / 1000.0;
}

/**
 * @brief ImageProcessor::run
 * @param args
 */
void ImageProcessor::run(QStringList args)
{
    this->margs = args;
    this->start();
}

/**
 * @brief ImageProcessor::getResult
 * @return
 */
QStringList ImageProcessor:: getResult()
{
    QStringList reses;

    reses << this->margs
          << this->mreses
          << this->mbtime.toString() << this->metime.toString() << QString::number(this->mdtime)
             ;

    return reses;
}

//////////////////////
char *ImageProcessor:: get_cpath(const QString &srcfile)
{
    char *cpath = srcfile.toAscii().data();

    qLogx()<< QString(cpath) << strlen(cpath) << srcfile ;

    memset(this->mshbuf, 0, sizeof(this->mshbuf));
    strncpy(this->mshbuf, srcfile.toAscii().data(), sizeof(this->mshbuf)-1);

    return this->mshbuf;
    return cpath;
}

QString ImageProcessor::get_tpath(const QString &srcfile, const QString &prefix, const QString &subprefix)
{
    return "/tmp/" + prefix +   "_" + subprefix +  "_" + QFileInfo(srcfile).fileName();
}

bool ImageProcessor::smooth_it(QString srcfile)
{
    /// Global Variables
    int DELAY_CAPTION = 1500;
    int DELAY_BLUR = 100;
    int MAX_KERNEL_LENGTH = 31;

    cv::Mat src; cv::Mat dst;
    char window_name[] = "Filter Demo 1";

    QString resfile;
    char *srcimg = srcfile.toAscii().data();
    /// Load the source image
    // src = cv::imread( "../images/lena.jpg", 1 );
    src = cv::imread( srcimg, 1 );


    dst = src.clone();

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        cv::blur( src, dst, cv::Size( i, i ), cv::Point(-1,-1) );

    }

    resfile = "/tmp/smooth_blur_" + QFileInfo(srcfile).fileName();
    cv::imwrite(resfile.toAscii().data(), dst);
    this->mreses << resfile;

    dst = src.clone();
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        cv::GaussianBlur( src, dst, cv::Size( i, i ), 0, 0 );
    }
    resfile = "/tmp/smooth_gblur_" + QFileInfo(srcfile).fileName();
    cv::imwrite(resfile.toAscii().data(), dst);
    this->mreses << resfile;

    dst = src.clone();
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        cv::medianBlur ( src, dst, i );

    }
    resfile = "/tmp/smooth_mblur_" + QFileInfo(srcfile).fileName();
    cv::imwrite(resfile.toAscii().data(), dst);
    this->mreses << resfile;

    dst = src.clone();
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        cv::bilateralFilter ( src, dst, i, i*2, i/2 );

    }
    resfile = "/tmp/smooth_bilateral_" + QFileInfo(srcfile).fileName();
    cv::imwrite(resfile.toAscii().data(), dst);
    this->mreses << resfile;


    return true;
}

bool ImageProcessor::erode_it(QString srcfile)
{
    /// Global variables
    Mat src, erosion_dst, dilation_dst;

    int erosion_elem = 0;
    int erosion_size = 0;
    int dilation_elem = 0;
    int dilation_size = 0;
    int const max_elem = 2;
    int const max_kernel_size = 21;

    QString resfile;
    erosion_elem = this->margs.at(2).toInt();
    erosion_size = this->margs.at(3).toInt();

    /// Load an image
    // src = imread( argv[1] );
    src = imread(this->get_cpath(srcfile));

    int erosion_type;
    if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement( erosion_type,
                                         Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                         Point( erosion_size, erosion_size ) );

    /// Apply the erosion operation
    erode( src, erosion_dst, element );

    resfile = this->get_tpath(srcfile, "erode");
    qLogx() << resfile << QString(this->get_cpath(resfile)).length();
    imwrite(this->get_cpath(resfile), erosion_dst);
    this->mreses << resfile;

    return true;
}

bool ImageProcessor::dilate_it(QString srcfile)
{
    /// Global variables
    Mat src, erosion_dst, dilation_dst;

    int erosion_elem = 0;
    int erosion_size = 0;
    int dilation_elem = 0;
    int dilation_size = 0;
    int const max_elem = 2;
    int const max_kernel_size = 21;

    QString resfile;
    dilation_elem = this->margs.at(2).toInt();
    dilation_size = this->margs.at(3).toInt();

    /// Load an image
    // src = imread( argv[1] );
    src = imread(this->get_cpath(srcfile));

    int dilation_type;
    if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
    else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
    else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }


    Mat element = getStructuringElement( dilation_type,
                                         Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                         Point( dilation_size, dilation_size ) );
    /// Apply the dilation operation
    dilate( src, dilation_dst, element );

    resfile = this->get_tpath(srcfile, "dilate");
    bool bret = imwrite(this->get_cpath(resfile), dilation_dst);
    this->mreses << resfile;
    qLogx()<< bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor::morph_it(QString srcfile)
{
    /// Global variables
    Mat src, dst;

    int morph_elem = 0;
    int morph_size = 0;
    int morph_operator = 0;
    int const max_operator = 4;
    int const max_elem = 2;
    int const max_kernel_size = 21;

    morph_elem = this->margs.at(2).toInt();
    morph_size = this->margs.at(3).toInt();
    if (this->margs.at(4) == "open") morph_operator = 0;
    if (this->margs.at(4) == "close") morph_operator = 1;
    if (this->margs.at(4) == "morph") morph_operator = 2;
    if (this->margs.at(4) == "tophat") morph_operator = 3;
    if (this->margs.at(4) == "blackhat") morph_operator = 4;

    /// Load an image
    // src = imread( argv[1] );
    src = imread(this->get_cpath(srcfile), 1);

    if( !src.data )
    { return false; }

    // Since MORPH_X : 2,3,4,5 and 6
    int operation = morph_operator + 2;

    Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

    /// Apply the specified morphology operation
    morphologyEx( src, dst, operation, element );

    QString resfile = this->get_tpath(srcfile, "morph", this->margs.at(4));
    bool bret = imwrite(this->get_cpath(resfile), dst);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

