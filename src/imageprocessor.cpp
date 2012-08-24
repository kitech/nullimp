/**
 *
 *
 *
 */

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
    } else if (op == "pyramids") {
        src1 = args.at(1);
        this->pyramids_it(src1);
    } else if (op == "threshold") {
        src1 = args.at(1);
        this->threshold_it(src1);
    } else if (op == "filter2d") {
        src1 = args.at(1);
        this->filter2d_it(src1);
    } else if (op == "border") {
        src1 = args.at(1);
        this->border_it(src1);
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

std::string ImageProcessor::get_cxxpath(const QString &srcfile)
{
    std::string cxxpath = srcfile.toStdString();

    return cxxpath;
}

QString ImageProcessor::get_tpath(const QString &srcfile, const QString &prefix, const QString &subprefix)
{
    QString utmp = QDir::tempPath();
    QString tpath = utmp + "/" + prefix +   "_" + subprefix +  "_" + QFileInfo(srcfile).fileName();
    return tpath;
    // return "/tmp/" + prefix +   "_" + subprefix +  "_" + QFileInfo(srcfile).fileName();
}

std::string ImageProcessor::get_txxpath(const QString &srcfile, const QString &prefix, const QString &subprefix)
{
    QString utmp = QDir::tempPath();
    QString tpath = utmp + "/" + prefix +   "_" + subprefix +  "_" + QFileInfo(srcfile).fileName();
    return tpath.toStdString();
}

//////
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
    // resfile = "/tmp/smooth_blur_" + QFileInfo(srcfile).fileName();
    resfile = this->get_tpath(srcfile, "smooth", "blur");
    cv::imwrite(resfile.toAscii().data(), dst);
    this->mreses << resfile;

    dst = src.clone();
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        cv::GaussianBlur( src, dst, cv::Size( i, i ), 0, 0 );
    }
    // resfile = "/tmp/smooth_gblur_" + QFileInfo(srcfile).fileName();
    resfile = this->get_tpath(srcfile, "smooth", "gblur");
    cv::imwrite(resfile.toAscii().data(), dst);
    this->mreses << resfile;

    dst = src.clone();
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        cv::medianBlur ( src, dst, i );

    }
    // resfile = "/tmp/smooth_mblur_" + QFileInfo(srcfile).fileName();
    resfile = this->get_tpath(srcfile, "smooth", "mblur");
    cv::imwrite(resfile.toAscii().data(), dst);
    this->mreses << resfile;

    dst = src.clone();
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        cv::bilateralFilter ( src, dst, i, i*2, i/2 );

    }
    // resfile = "/tmp/smooth_bilateral_" + QFileInfo(srcfile).fileName();
    resfile = this->get_tpath(srcfile, "smooth", "bilateral");
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

bool ImageProcessor::pyramids_it(QString srcfile)
{
    /// Global variables
    Mat src, dst, tmp;
//    char* window_name = "Pyramids Demo";

    /// Test image - Make sure it s divisible by 2^{n}
    // src = imread( "../images/chicky_512.jpg" );
    src = imread(this->get_cpath(srcfile));
    if( !src.data ) {
        printf(" No data! -- Exiting the program \n");
        return false;
    }

    tmp = src;
    dst = tmp;

    /// Create window
    //namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    //imshow( window_name, dst );

    int scale_rate = this->margs.at(3).toInt();
    // scale_rate = 3;

    /// Loop
    // 这两个函数中的*2和/2操作是固定的，只能是按2的倍数处理。
    for (int i = 0; i < scale_rate; i ++) {
        qLogx()<<i << "up:" << tmp.cols << tmp.rows;
        if (this->margs.at(2) == "up") {
            pyrUp( tmp, dst, Size( tmp.cols*2, tmp.rows*2 ) );
        } else {
            pyrDown( tmp, dst, Size( tmp.cols/2, tmp.rows/2 ) );
        }
        tmp  = dst;
    }

    QString resfile = this->get_tpath(srcfile, "pyramids", this->margs.at(2));
    bool bret = imwrite(this->get_cpath(resfile), dst);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor:: threshold_it(QString srcfile)
{
    /// Global variables

    int threshold_value = 0;
    int threshold_type = 3;;
    int const max_value = 255;
    int const max_type = 4;
    int const max_BINARY_value = 255;

    Mat src, src_gray, dst;

    /// Load an image
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile));

    if (this->margs.at(2) == "bin") threshold_type = 0;
    if (this->margs.at(2) == "binvert") threshold_type = 1;
    if (this->margs.at(2) == "threshold") threshold_type = 2;
    if (this->margs.at(2) == "th2zero") threshold_type = 3;
    if (this->margs.at(2) == "th2zeroinvert") threshold_type = 4;
    threshold_value = this->margs.at(3).toInt();

    /// Convert the image to Gray
    cvtColor( src, src_gray, CV_RGB2GRAY );

    /* 0: Binary
       1: Binary Inverted
       2: Threshold Truncated
       3: Threshold to Zero
       4: Threshold to Zero Inverted
     */

    threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
    QString resfile = this->get_tpath(srcfile, this->margs.at(0), this->margs.at(2));
    bool bret = imwrite(this->get_cpath(resfile), dst);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor:: filter2d_it(QString srcfile)
{
    /// Declare variables
    Mat src, dst;

    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    //    char* window_name = "filter2D Demo";

    int c;

    /// Load an image
    // src = imread( argv[1] );
    src = imread(this->get_cpath(srcfile));

    if( !src.data )
    { return false; }

    /// Create window
    //namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Initialize arguments for the filter
    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;

    kernel_size = 3+2*(this->margs.at(2).toInt() % 5);
    kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);

    /// Apply filter
    filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );


    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), dst);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor::border_it(QString srcfile)
{
    /// Global Variables
    Mat src, dst;
    int top, bottom, left, right;
    int borderType;
    Scalar value;
    // char* window_name = "copyMakeBorder Demo";
    RNG rng(12345);

      int c;

      /// Load an image
      // src = imread( argv[1] );
      src = imread(this->get_cpath(srcfile));

      if( !src.data )
      {
          return false;
          printf(" No data entered, please enter the path to an image file \n");
      }

      /// Brief how-to for this program
      printf( "\n \t copyMakeBorder Demo: \n" );
      printf( "\t -------------------- \n" );
      printf( " ** Press 'c' to set the border to a random constant value \n");
      printf( " ** Press 'r' to set the border to be replicated \n");
      printf( " ** Press 'ESC' to exit the program \n");

      /// Create window
      // namedWindow( window_name, CV_WINDOW_AUTOSIZE );

      borderType = this->margs.at(2).toInt() == 0 ? BORDER_CONSTANT : BORDER_REPLICATE;

      /// Initialize arguments for the filter
      top = (int) (0.05*src.rows); bottom = (int) (0.05*src.rows);
      left = (int) (0.05*src.cols); right = (int) (0.05*src.cols);
      dst = src;

      // imshow( window_name, dst );

      value = Scalar( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
      copyMakeBorder( src, dst, top, bottom, left, right, borderType, value );

      QString resfile = this->get_tpath(srcfile, this->margs.at(0), this->margs.at(2));
      bool bret = imwrite(this->get_cpath(resfile), dst);
      this->mreses << resfile;
      qLogx()<<bret << resfile << QFileInfo(resfile).size();


    return true;
}
