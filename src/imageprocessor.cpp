/**
 *
 *
 *
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "opencv/cv.h"
#include "opencv2/nonfree/nonfree.hpp"

#include "GraphicsMagick/wand/wand_api.h"

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
    QString src1, src2, src3;

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
    } else if (op == "sobel") {
        src1 = args.at(1);
        this->sobel_it(src1);
    } else if (op == "laplace") {
        src1 = args.at(1);
        this->laplace_it(src1);
    } else if (op == "canny") {
        src1 = args.at(1);
        this->canny_it(src1);
    } else if (op == "hough") {
        src1 = args.at(1);
        this->hough_it(src1);
    } else if (op == "remap") {
        src1 = args.at(1);
        this->remap_it(src1);
    } else if (op == "affine") {
        src1 = args.at(1);
        this->affine_it(src1);
    } else if (op == "hist") {
        src1 = args.at(1);
        this->hist_it(src1);
    } else if (op == "comphist") {
        src1 = args.at(1);
        src2 = args.at(2);
        src3 = args.at(3);
        this->comp_hist_it(src1, src2, src3);
    } else if (op == "backproj") {
        src1 = args.at(1);
        this->back_projection_it(src1);
    }  else if (op == "tplmatch") {
        src1 = args.at(1);
        src2 = args.at(2);
        this->template_match_it(src1, src2);
    } else if (op == "contours") {
        src1 = args.at(1);
        this->find_contous_it(src1);
    } else if (op == "hull") {
        src1 = args.at(1);
        this->find_convexhull_it(src1);
    } else if (op == "boxcircle") {
        src1 = args.at(1);
        this->find_box_circle_it(src1);
    } else if (op == "boxellipse") {
        src1 = args.at(1);
        this->find_box_ellipse_it(src1);
    } else if (op == "moment") {
        src1 = args.at(1);
        this->moment_it(src1);
    } else if (op == "polygon") {
        src1 = args.at(1);
        this->polygon_it(src1);
    } else if (op == "haar") {
        src1 = args.at(1);
        this->haar_it(src1);
    } else if (op == "bc_gm_resize") {
        src1 = args.at(1);
        this->bc_gm_thumb(src1);
    } else if (op == "surfdt") {
        src1 = args.at(1);
        src2 = args.at(2);
        src3 = args.at(3);
        this->surf_detect_it(src1, src2, src3);
    }  else if (op == "cvextor") {
        src1 = args.at(1);
        src2 = args.at(2);
        QString algo = args.at(3);
        QString hisen = args.at(4);
        this->cvextor_it(src1, src2, algo, hisen);
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

bool ImageProcessor::sobel_it(QString srcfile)
{
    Mat src, src_gray;
    Mat grad;
    char* window_name = "Sobel Demo - Simple Edge Detector";
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    int c;

    /// Load an image
    // src = imread( argv[1] );
    src = imread(this->get_cpath(srcfile));

    if( !src.data )
    { return false; }


    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// Convert it to gray
    cvtColor( src, src_gray, CV_RGB2GRAY );

    /// Create window
    // namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), grad);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor:: laplace_it(QString srcfile)
{
    Mat src, src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    char* window_name = "Laplace Demo";

    int c;

    /// Load an image
    // src = imread( argv[1] );
    src = imread(this->get_cpath(srcfile));

    if( !src.data )
      { return false; }

    /// Remove noise by blurring with a Gaussian filter
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// Convert the image to grayscale
    cvtColor( src, src_gray, CV_RGB2GRAY );

    /// Create window
    // namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Apply Laplace function
    Mat abs_dst;

    Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( dst, abs_dst );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), abs_dst);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor::canny_it(QString srcfile)
{
    /// Global variables

    Mat src, src_gray;
    Mat dst, detected_edges;

    int edgeThresh = 1;
    int lowThreshold;
    int const max_lowThreshold = 100;
    int ratio = 3;
    int kernel_size = 3;
    char* window_name = "Edge Map";

    /// Load an image
    // src = imread( argv[1] );
    src = imread(this->get_cpath(srcfile));

    if( !src.data )
    { return false; }

    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );

    /// Convert the image to grayscale
    cvtColor( src, src_gray, CV_BGR2GRAY );

    /// Create a window
    // namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Create a Trackbar for user to enter threshold
    // createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
    lowThreshold = this->margs.at(2).toInt();

    /// Show the image
    // CannyThreshold(0, 0);

    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);

    src.copyTo( dst, detected_edges);

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), detected_edges);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}
bool ImageProcessor::hough_it(QString srcfile)
{

    if (this->margs.at(2) == "0") {
        return this->hough_line_it(srcfile);
    } else {
        return this->hough_circle_it(srcfile);
    }
}

bool ImageProcessor::hough_line_it(QString srcfile)
{
    // const char* filename = argc >= 2 ? argv[1] : "pic1.jpg";

    // Mat src = imread(filename, 0);
    Mat src = imread(this->get_cpath(srcfile), 0);
    if(src.empty())
    {
        // help();
        // cout << "can not open " << filename << endl;
        return false;
    }

    Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);

    #if 0
     vector<Vec2f> lines;
     HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

     for( size_t i = 0; i < lines.size(); i++ )
     {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
     }
    #else
     vector<Vec4i> lines;
     HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
     for( size_t i = 0; i < lines.size(); i++ )
     {
       Vec4i l = lines[i];
       line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
     }
    #endif

     QString resfile = this->get_tpath(srcfile, this->margs.at(0), "line");
     bool bret = imwrite(this->get_cpath(resfile), cdst);
     this->mreses << resfile;
     qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor::hough_circle_it(QString srcfile)
{
    Mat src, src_gray;

    /// Read the image
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile));

    if( !src.data )
      { return false; }

    /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );

    /// Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

    /// Draw the circles detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
     }

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "circle");
    bool bret = imwrite(this->get_cpath(resfile), src);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor::remap_it(QString srcfile)
{
    /// Global variables
    Mat src, dst;
    Mat map_x, map_y;
    char* remap_window = "Remap demo";
    int ind = 0;

    /// Load the image
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

   /// Create dst, map_x and map_y with the same size as src:
   dst.create( src.size(), src.type() );
   map_x.create( src.size(), CV_32FC1 );
   map_y.create( src.size(), CV_32FC1 );

   /// Create window
   // namedWindow( remap_window, CV_WINDOW_AUTOSIZE );

   ind = this->margs.at(2).toInt();
     /// Update map_x & map_y. Then apply remap
   // update_map();
   {
       ind = ind%4;

       for( int j = 0; j < src.rows; j++ )
       { for( int i = 0; i < src.cols; i++ )
           {
             switch( ind )
             {
               case 0:
                 if( i > src.cols*0.25 && i < src.cols*0.75 && j > src.rows*0.25 && j < src.rows*0.75 )
                   {
                     map_x.at<float>(j,i) = 2*( i - src.cols*0.25 ) + 0.5 ;
                     map_y.at<float>(j,i) = 2*( j - src.rows*0.25 ) + 0.5 ;
                    }
                 else
                   { map_x.at<float>(j,i) = 0 ;
                     map_y.at<float>(j,i) = 0 ;
                   }
                     break;
               case 1:
                     map_x.at<float>(j,i) = i ;
                     map_y.at<float>(j,i) = src.rows - j ;
                     break;
               case 2:
                     map_x.at<float>(j,i) = src.cols - i ;
                     map_y.at<float>(j,i) = j ;
                     break;
               case 3:
                     map_x.at<float>(j,i) = src.cols - i ;
                     map_y.at<float>(j,i) = src.rows - j ;
                     break;
             } // end of switch
           }
        }
   }
     remap( src, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

     /// Display results

     QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
     bool bret = imwrite(this->get_cpath(resfile), dst);
     this->mreses << resfile;
     qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor::affine_it(QString srcfile)
{
    Point2f srcTri[3];
    Point2f dstTri[3];

    Mat rot_mat( 2, 3, CV_32FC1 );
    Mat warp_mat( 2, 3, CV_32FC1 );
    Mat src, warp_dst, warp_rotate_dst;

    /// Load the image
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

    /// Set the dst image the same type and size as src
    warp_dst = Mat::zeros( src.rows, src.cols, src.type() );

    /// Set your 3 points to calculate the  Affine Transform
    srcTri[0] = Point2f( 0,0 );
    srcTri[1] = Point2f( src.cols - 1, 0 );
    srcTri[2] = Point2f( 0, src.rows - 1 );

    dstTri[0] = Point2f( src.cols*0.0, src.rows*0.33 );
    dstTri[1] = Point2f( src.cols*0.85, src.rows*0.25 );
    dstTri[2] = Point2f( src.cols*0.15, src.rows*0.7 );

    /// Get the Affine Transform
    warp_mat = getAffineTransform( srcTri, dstTri );

    /// Apply the Affine Transform just found to the src image
    warpAffine( src, warp_dst, warp_mat, warp_dst.size() );

    /** Rotating the image after Warp */

    /// Compute a rotation matrix with respect to the center of the image
    Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
    double angle = -50.0;
    double scale = 0.6;

    /// Get the rotation matrix with the specifications above
    rot_mat = getRotationMatrix2D( center, angle, scale );

    /// Rotate the warped image
    warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );

    /// Show what you got
    // namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    // imshow( source_window, src );

    // namedWindow( warp_window, CV_WINDOW_AUTOSIZE );
    // imshow( warp_window, warp_dst );

    // namedWindow( warp_rotate_window, CV_WINDOW_AUTOSIZE );
    // imshow( warp_rotate_window, warp_rotate_dst );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "warp");
    bool bret = imwrite(this->get_cpath(resfile), warp_dst);
    this->mreses << resfile;
    resfile = this->get_tpath(srcfile, this->margs.at(0), "rotate");
    bret = imwrite(this->get_cpath(resfile), warp_rotate_dst);
    this->mreses << resfile;
    qLogx()<<bret << resfile << QFileInfo(resfile).size();

    return true;
}

bool ImageProcessor::hist_it(QString srcfile)
{
    if (this->margs.at(2).toInt() == 1) {
        return this->hist_equal_it(srcfile);
    }
    return this->hist_calc_it(srcfile);
}

bool ImageProcessor::hist_equal_it(QString srcfile)
{
    Mat src, dst;

    char* source_window = "Source image";
    char* equalized_window = "Equalized Image";

    /// Load image
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

    if( !src.data )
      { // cout<<"Usage: ./Histogram_Demo <path_to_image>"<<endl;
        return false;}

    /// Convert to grayscale
    cvtColor( src, src, CV_BGR2GRAY );

    /// Apply Histogram Equalization
    equalizeHist( src, dst );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "equal");
    bool bret = imwrite(this->get_cpath(resfile), dst);
    this->mreses << resfile;

    return true;
}

bool ImageProcessor::hist_calc_it(QString srcfile)
{
    Mat src, dst;

    /// Load image
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

    if( !src.data )
      { return false; }

    /// Separate the image in 3 places ( B, G and R )
    vector<Mat> bgr_planes;
    split( src, bgr_planes );

    /// Establish the number of bins
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    /// Compute the histograms:
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                         Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                         Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                         Scalar( 0, 0, 255), 2, 8, 0  );
    }

    /// Display
    // namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
    // imshow("calcHist Demo", histImage );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "calc");
    bool bret = imwrite(this->get_cpath(resfile), histImage);
    this->mreses << resfile;


    return true;
}

bool ImageProcessor::comp_hist_it(QString src1file, QString src2file, QString src3file)
{
    Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down;

    /// Load three images with different environment settings
//    if( argc < 4 )
//      { printf("** Error. Usage: ./compareHist_Demo <image_settings0> <image_setting1> <image_settings2>\n");
//        return -1;
//      }

    // src_base = imread( argv[1], 1 );
    // src_test1 = imread( argv[2], 1 );
    // src_test2 = imread( argv[3], 1 );
    src_base = imread(this->get_cpath(src1file), 1);
    src_test1 = imread(this->get_cpath(src2file), 1);
    src_test2 = imread(this->get_cpath(src3file), 1);

    /// Convert to HSV
    cvtColor( src_base, hsv_base, CV_BGR2HSV );
    cvtColor( src_test1, hsv_test1, CV_BGR2HSV );
    cvtColor( src_test2, hsv_test2, CV_BGR2HSV );

    hsv_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );

    /// Using 30 bins for hue and 32 for saturation
    int h_bins = 50; int s_bins = 60;
    int histSize[] = { h_bins, s_bins };

    // hue varies from 0 to 256, saturation from 0 to 180
    float h_ranges[] = { 0, 256 };
    float s_ranges[] = { 0, 180 };

    const float* ranges[] = { h_ranges, s_ranges };

    // Use the o-th and 1-st channels
    int channels[] = { 0, 1 };

    /// Histograms
    MatND hist_base;
    MatND hist_half_down;
    MatND hist_test1;
    MatND hist_test2;

    /// Calculate the histograms for the HSV images
    calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
    normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
    normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
    normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false );
    normalize( hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat() );

    QStringList resstrs;
    QString resstr;
    /// Apply the histogram comparison methods
    for( int i = 0; i < 4; i++ )
       { int compare_method = i;
         double base_base = compareHist( hist_base, hist_base, compare_method );
         double base_half = compareHist( hist_base, hist_half_down, compare_method );
         double base_test1 = compareHist( hist_base, hist_test1, compare_method );
         double base_test2 = compareHist( hist_base, hist_test2, compare_method );

         printf( " Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n", i, base_base, base_half , base_test1, base_test2 );
         resstr = QString(" Method [%1] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %2, %3, %4, %5 \n")
                 .arg(QString::number(i), QString::number(base_base), QString::number(base_half), QString::number(base_test1), QString::number(base_test2));
         resstrs << resstr;
       }

    printf( "Done \n" );

    QString resall = resstrs.join("\n");
    // bool bret = imwrite(this->get_cpath(resfile), histImage);
    this->mreses << resall;

    return true;
}

bool ImageProcessor::back_projection_it(QString srcfile)
{
    /// Global Variables
    Mat src; Mat hsv; Mat hue;
    int bins = 25;

    /// Read the image
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);
    /// Transform it to HSV
    cvtColor( src, hsv, CV_BGR2HSV );

    /// Use only the Hue value
    hue.create( hsv.size(), hsv.depth() );
    int ch[] = { 0, 0 };
    mixChannels( &hsv, 1, &hue, 1, ch, 1 );

    bins = this->margs.at(2).toInt();

    MatND hist;
    int histSize = MAX( bins, 2 );
    float hue_range[] = { 0, 180 };
    const float* ranges = { hue_range };

    /// Get the Histogram and normalize it
    calcHist( &hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
    normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

    /// Get Backprojection
    MatND backproj;
    calcBackProject( &hue, 1, 0, hist, backproj, &ranges, 1, true );

    /// Draw the backproj
    // imshow( "BackProj", backproj );

    /// Draw the histogram
    int w = 400; int h = 400;
    int bin_w = cvRound( (double) w / histSize );
    Mat histImg = Mat::zeros( w, h, CV_8UC3 );

    for( int i = 0; i < bins; i ++ )
       { rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 0, 0, 255 ), -1 ); }

    // imshow( "Histogram", histImg );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "hist");
    bool bret = imwrite(this->get_cpath(resfile), histImg);
    this->mreses << resfile;
    resfile = this->get_tpath(srcfile, this->margs.at(0), "back");
    bret = imwrite(this->get_cpath(resfile), backproj);
    this->mreses << resfile;

    return true;
}

bool ImageProcessor::template_match_it(QString src1file, QString src2file)
{
    /// Global Variables
    Mat img; Mat templ; Mat result;
    char* image_window = "Source Image";
    char* result_window = "Result window";

    int match_method;
    int max_Trackbar = 5;

    /// Load image and template
    // img = imread( argv[1], 1 );
    // templ = imread( argv[2], 1 );
    img = imread(this->get_cpath(src1file), 1);
    templ = imread(this->get_cpath(src2file), 1);

    /// Create windows
    // namedWindow( image_window, CV_WINDOW_AUTOSIZE );
    // namedWindow( result_window, CV_WINDOW_AUTOSIZE );

    /// Create Trackbar
    char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    // createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

    // MatchingMethod( 0, 0 );

    match_method = this->margs.at(3).toInt();

    /// Source image to display
    Mat img_display;
    img.copyTo( img_display );

    /// Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create( result_cols, result_rows, CV_32FC1 );

    /// Do the Matching and Normalize
    matchTemplate( img, templ, result, match_method );
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
      { matchLoc = minLoc; }
    else
      { matchLoc = maxLoc; }

    /// Show me what you got
    rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

    //imshow( image_window, img_display );
    //imshow( result_window, result );

    QString resfile = this->get_tpath(src1file, this->margs.at(0), "img");
    bool bret = imwrite(this->get_cpath(resfile), img_display);
    this->mreses << resfile;
    resfile = this->get_tpath(src1file, this->margs.at(0), "result");
    bret = imwrite(this->get_cpath(resfile), result);
    this->mreses << resfile;

    return true;
}

bool ImageProcessor::find_contous_it(QString srcfile)
{
    Mat src; Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;
    RNG rng(12345);

    /// Load source image and convert it to gray
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    char* source_window = "Source";
    // namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    // imshow( source_window, src );

    // createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
    // thresh_callback( 0, 0 );

    thresh = this->margs.at(2).toInt();

    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
       {
         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
       }

    /// Show in a window
    //namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    // imshow( "Contours", drawing );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), drawing);
    this->mreses << resfile;


    return true;
}

bool ImageProcessor::find_convexhull_it(QString srcfile)
{
    Mat src; Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;
    RNG rng(12345);

    /// Load source image and convert it to gray
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    char* source_window = "Source";
    // namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    // imshow( source_window, src );

    // createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
    // thresh_callback( 0, 0 );
    thresh  = this->margs.at(2).toInt();

    Mat src_copy = src.clone();
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using Threshold
    threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );

    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Find the convex hull object for each contour
    vector<vector<Point> >hull( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
       {  convexHull( Mat(contours[i]), hull[i], false ); }

    /// Draw contours + hull results
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
       {
         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
         drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       }

    /// Show in a window
    // namedWindow( "Hull demo", CV_WINDOW_AUTOSIZE );
    // imshow( "Hull demo", drawing );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), drawing);
    this->mreses << resfile;

    return true;
}

bool ImageProcessor::find_box_circle_it(QString srcfile)
{
    Mat src; Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;
    RNG rng(12345);

    /// Load source image and convert it to gray
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    char* source_window = "Source";
    // namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    // imshow( source_window, src );

    // createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
    // thresh_callback( 0, 0 );
    thresh = this->margs.at(2).toInt();

    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using Threshold
    threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
       { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
         boundRect[i] = boundingRect( Mat(contours_poly[i]) );
         minEnclosingCircle( contours_poly[i], center[i], radius[i] );
       }


    /// Draw polygonal contour + bonding rects + circles
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
       {
         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
         rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
         circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
       }

    /// Show in a window
    // namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    // imshow( "Contours", drawing );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), drawing);
    this->mreses << resfile;

    return true;
}

bool ImageProcessor::find_box_ellipse_it(QString srcfile)
{
    Mat src; Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;
    RNG rng(12345);

    /// Load source image and convert it to gray
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    char* source_window = "Source";
    // namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    // imshow( source_window, src );

    // createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
    // thresh_callback( 0, 0 );

    thresh = this->margs.at(2).toInt();

    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using Threshold
    threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Find the rotated rectangles and ellipses for each contour
    vector<RotatedRect> minRect( contours.size() );
    vector<RotatedRect> minEllipse( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
       { minRect[i] = minAreaRect( Mat(contours[i]) );
         if( contours[i].size() > 5 )
           { minEllipse[i] = fitEllipse( Mat(contours[i]) ); }
       }

    /// Draw contours + rotated rects + ellipses
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
       {
         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         // contour
         drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
         // ellipse
         ellipse( drawing, minEllipse[i], color, 2, 8 );
         // rotated rectangle
         Point2f rect_points[4]; minRect[i].points( rect_points );
         for( int j = 0; j < 4; j++ )
            line( drawing, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
       }

    /// Show in a window
    // namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    // imshow( "Contours", drawing );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), drawing);
    this->mreses << resfile;

    return true;
}


bool ImageProcessor::moment_it(QString srcfile)
{
    Mat src; Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;
    RNG rng(12345);


    /// Load source image and convert it to gray
    // src = imread( argv[1], 1 );
    src = imread(this->get_cpath(srcfile), 1);

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    char* source_window = "Source";
    // namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    // imshow( source_window, src );

    // createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
    // thresh_callback( 0, 0 );

    thresh = this->margs.at(2).toInt();

    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Get the moments
    vector<Moments> mu(contours.size() );
    for( int i = 0; i < contours.size(); i++ )
       { mu[i] = moments( contours[i], false ); }

    ///  Get the mass centers:
    vector<Point2f> mc( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
       { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
       {
         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
         circle( drawing, mc[i], 4, color, -1, 8, 0 );
       }

    /// Show in a window
    // namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    // imshow( "Contours", drawing );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "");
    bool bret = imwrite(this->get_cpath(resfile), drawing);
    this->mreses << resfile;

    /// Calculate the area with the moments 00 and compare with the result of the OpenCV function
    printf("\t Info: Area and Contour Length \n");
    for( int i = 0; i< contours.size(); i++ )
       {
         printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
         circle( drawing, mc[i], 4, color, -1, 8, 0 );
       }

    return true;
}


bool ImageProcessor::polygon_it(QString srcfile)
{
    /// Create an image
    const int r = 100;
    Mat src = Mat::zeros( Size( 4*r, 4*r ), CV_8UC1 );

    /// Create a sequence of points to make a contour:
    vector<Point2f> vert(6);

    vert[0] = Point( 1.5*r, 1.34*r );
    vert[1] = Point( 1*r, 2*r );
    vert[2] = Point( 1.5*r, 2.866*r );
    vert[3] = Point( 2.5*r, 2.866*r );
    vert[4] = Point( 3*r, 2*r );
    vert[5] = Point( 2.5*r, 1.34*r );

    /// Draw it in src
    for( int j = 0; j < 6; j++ )
       { line( src, vert[j],  vert[(j+1)%6], Scalar( 255 ), 3, 8 ); }

    /// Get the contours
    vector<vector<Point> > contours; vector<Vec4i> hierarchy;
    Mat src_copy = src.clone();

    findContours( src_copy, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    /// Calculate the distances to the contour
    Mat raw_dist( src.size(), CV_32FC1 );

    for( int j = 0; j < src.rows; j++ )
       { for( int i = 0; i < src.cols; i++ )
            { raw_dist.at<float>(j,i) = pointPolygonTest( contours[0], Point2f(i,j), true ); }
       }

    double minVal; double maxVal;
    minMaxLoc( raw_dist, &minVal, &maxVal, 0, 0, Mat() );
    minVal = abs(minVal); maxVal = abs(maxVal);

    /// Depicting the  distances graphically
    Mat drawing = Mat::zeros( src.size(), CV_8UC3 );

    for( int j = 0; j < src.rows; j++ )
       { for( int i = 0; i < src.cols; i++ )
            {
              if( raw_dist.at<float>(j,i) < 0 )
                { drawing.at<Vec3b>(j,i)[0] = 255 - (int) abs(raw_dist.at<float>(j,i))*255/minVal; }
              else if( raw_dist.at<float>(j,i) > 0 )
                { drawing.at<Vec3b>(j,i)[2] = 255 - (int) raw_dist.at<float>(j,i)*255/maxVal; }
              else
                { drawing.at<Vec3b>(j,i)[0] = 255; drawing.at<Vec3b>(j,i)[1] = 255; drawing.at<Vec3b>(j,i)[2] = 255; }
            }
       }

    /// Create Window and show your results
    char* source_window = "Source";
    // namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    // imshow( source_window, src );
    // namedWindow( "Distance", CV_WINDOW_AUTOSIZE );
    // imshow( "Distance", drawing );

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "draw");
    bool bret = imwrite(this->get_cpath(resfile), drawing);
    this->mreses << resfile;

    resfile = this->get_tpath(srcfile, this->margs.at(0), "src");
    bret = imwrite(this->get_cpath(resfile), src);
    this->mreses << resfile;

    return true;
}

bool ImageProcessor::haar_it(QString srcfile)
{
    return this->haar_it_cpp(srcfile);
    ///////////// c-mode????????
    CvMemStorage* storage = 0;
    CvHaarClassifierCascade* cascade = 0;
    Mat dest;
    IplImage*src, *gray, *small_img;
    bool bret;
    double scale = 1.3;

    CvScalar colors[] =
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

    // cascade = new CascadeClassifier();
    // bret = cascade->load("/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
    cascade = (CvHaarClassifierCascade*)cvLoad("/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
    qLogx()<<bret;

    storage = cvCreateMemStorage(0);

    // src = imread(this->get_cpath(srcfile), 1);
    src = cvLoadImage(this->get_cpath(srcfile), 1);

    // gray = Mat(src.rows, src.cols, CV_8UC1);
    // small_img = Mat(cvRound(src.rows/scale), cvRound(src.cols/1.3), CV_8UC1);
    gray = cvCreateImage( cvSize(src->width, src->height), 8, 1 );
    small_img = cvCreateImage( cvSize( cvRound (src->width/scale),
                                       cvRound (src->height/scale)),
                               8, 1 );

    /////
    cvCvtColor(src, gray, CV_BGR2GRAY);
    cvResize(gray, small_img, CV_INTER_LINEAR);
    cvEqualizeHist(small_img, small_img);
    cvClearMemStorage(storage);

    CvSeq * faces = 0;
    faces = cvHaarDetectObjects(small_img, cascade, storage);

    for( int i = 0; i < (faces ? faces->total : 0); i++ )
    {
        CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
        CvPoint center;
        int radius;
        center.x = cvRound((r->x + r->width*0.5)*scale);
        center.y = cvRound((r->y + r->height*0.5)*scale);
        radius = cvRound((r->width + r->height)*0.25*scale);
        cvCircle( src, center, radius, colors[i%8], 3, 8, 0 );
    }

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "src");
    // bret = imwrite(this->get_cpath(resfile), src);
    cvSaveImage(this->get_cpath(resfile), src);
    this->mreses << resfile;

    return true;
}

/*
 * 相比 haar_it (C版本的）效率更高，准确度更高
 */
bool ImageProcessor::haar_it_cpp(QString srcfile)
{
    Mat src, gray, small_img;
    cv::CascadeClassifier *cascade;
    bool bret;
    double scale = 1.3;

    CvScalar colors[] =
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

    cascade = new cv::CascadeClassifier();
    bret = cascade->load("/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
    qLogx()<< bret << cascade->empty() ;

    src = imread(this->get_cpath(srcfile), 1);

    cv::cvtColor(src, gray, CV_RGB2GRAY);

    small_img = Mat(cvRound(src.rows / scale), cvRound(src.cols / scale), CV_8UC1);
    Size smallImgSize = small_img.size();

    resize(gray, small_img, smallImgSize, 0, 0, INTER_LINEAR);
    equalizeHist(small_img, small_img);

    vector<Rect> faces;
    cascade->detectMultiScale(small_img, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for( int i = 0; i < faces.size(); i++ )
    {
        cv::Rect r = faces.at(i);
        cv::Point center;
        int radius;
        center.x = cvRound((r.x + r.width*0.5)*scale);
        center.y = cvRound((r.y + r.height*0.5)*scale);
        radius = cvRound((r.width + r.height)*0.25*scale);
        // cvCircle( src, center, radius, colors[i%8], 3, 8, 0 );
        cv::circle(src, center, radius, colors[i%8], 3, 8, 0);
    }

    QString resfile = this->get_tpath(srcfile, this->margs.at(0), "gray");
    bret = imwrite(this->get_cpath(resfile), src);
    // cvSaveImage(this->get_cpath(resfile), src);
    this->mreses << resfile;

    delete cascade;

    return true;
}

bool ImageProcessor:: bc_gm_thumb(QString srcfile)
{
    MagickWand *mw1 = NULL, *mw2 = NULL;
    MagickWand *mwc[1000] = {0};

    mw1 = NewMagickWand();
    int iret = MagickReadImage(mw1, this->get_cpath(srcfile));

    for (int i =0; i < 100; i++) {
        mw2 = CloneMagickWand(mw1);
        mwc[i] = mw2;
    }
    qLogx()<<"copies done."<<QDateTime::currentDateTime();

    QDateTime begin_time = QDateTime::currentDateTime();
    for (int i = 0; i < 100; i++) {
        iret = ::MagickScaleImage(mwc[i], 100, 80);
    }
    QDateTime end_time = QDateTime::currentDateTime();
    qLogx()<<"eclapse: " << begin_time.msecsTo(end_time) << " = " << begin_time.msecsTo(end_time) / 100.0 << "/s";

    ::DestroyMagickWand(mw1);
    this->mreses << "done";

    // 测试结果，大概100次resize操作使用2秒，也就是每次操作使用0.02秒，20毫秒。也不算快。
    return true;
}

bool ImageProcessor::surf_detect_it(QString src1file, QString src2file, QString src3file)
{
    Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down;

    /// Load three images with different environment settings
//    if( argc < 4 )
//      { printf("** Error. Usage: ./compareHist_Demo <image_settings0> <image_setting1> <image_settings2>\n");
//        return -1;
//      }

    // src_base = imread( argv[1], 1 );
    // src_test1 = imread( argv[2], 1 );
    // src_test2 = imread( argv[3], 1 );
    src_base = imread(this->get_cpath(src1file), 1);
    src_test1 = imread(this->get_cpath(src2file), 1);
    src_test2 = imread(this->get_cpath(src3file), 1);

    int minHession = 20000; // 400  - 30000

    cv::SurfFeatureDetector surfdt1(minHession);
    std::vector<cv::KeyPoint> kps1, kps2, kps3;
    cv::KeyPoint kpt;

    surfdt1.detect(src_base, kps1);
    surfdt1.detect(src_test1, kps2);
    surfdt1.detect(src_test2, kps3);

    qLogx()<< "Done"<<kps1.size()<<kps2.size()<<kps3.size();
    for (int i = 0; i < kps1.size(); i++) {
        kpt = kps1.at(i);
        // qLogx()<<i<<kpt.size<<kpt.hash();
    }

    QString resall = "" ;// resstrs.join("\n");


    this->mreses << resall;

    return true;
}

bool ImageProcessor::cvextor_it(QString src1file, QString src2file, QString algo, QString hisen)
{
    Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down;

    /// Load three images with different environment settings
//    if( argc < 4 )
//      { printf("** Error. Usage: ./compareHist_Demo <image_settings0> <image_setting1> <image_settings2>\n");
//        return -1;
//      }

    // src_base = imread( argv[1], 1 );
    // src_test1 = imread( argv[2], 1 );
    // src_test2 = imread( argv[3], 1 );
    src_base = imread(this->get_cpath(src1file), 1);
    src_test1 = imread(this->get_cpath(src2file), 1);

    int minHession = hisen.toInt(); // 400  - 30000
    // minHession = 600;

    cv::SiftFeatureDetector siftdt1(minHession);
    cv::SurfFeatureDetector surfdt1(minHession);
    cv::FastFeatureDetector fastdt1(minHession);
    cv::GoodFeaturesToTrackDetector gooddt1(minHession);
    cv::MserFeatureDetector mserdt1(minHession);
    cv::StarFeatureDetector stardt1(minHession);
    cv::DenseFeatureDetector densedt1(minHession);
    cv::OrbFeatureDetector orbdt1(minHession);

    HOGDescriptor hog;


    cv::BriefDescriptorExtractor brief_extor;
    cv::SurfDescriptorExtractor surf_extor;
    cv::SiftDescriptorExtractor sift_extor;
    //  cv::OpponentColorDescriptorExtractor oppo_extor;
    // cv::BOWImgDescriptorExtractor bow_extor;
    cv::OrbDescriptorExtractor orb_extor;
    cv::FREAK  freak_extor(minHession);



    std::vector<cv::KeyPoint> kps1, kps2, kps3;
    cv::KeyPoint kpt;
    cv::Mat desc_1, desc_2, desc_3;

    surfdt1.detect(src_base, kps1);
    surfdt1.detect(src_test1, kps2);

    qLogx()<< "Done"<<kps1.size()<<kps2.size()<<kps3.size();
    for (int i = 0; i < kps1.size(); i++) {
        kpt = kps1.at(i);
        // qLogx()<<i<<kpt.size<<kpt.hash();
    }

    // kps1.clear();
    // kps2.clear();
    surf_extor.compute(src_base, kps1, desc_1);
    surf_extor.compute(src_test1, kps2, desc_2);

    qLogx()<<"extor size:" << kps1.size() << kps2.size() << desc_1.elemSize() << desc_2.elemSize();

    cv::FlannBasedMatcher mater;
    std::vector<cv::DMatch> mates;

    mater.match(desc_1, desc_2, mates);

    qLogx()<<"mates:" << mates.size();

    cv::Mat img_matches;
    cv::drawMatches(src_base, kps1, src_test1, kps2, mates, img_matches);

    QString resfile = this->get_tpath(src1file, " ",  "mated");
    cv::imwrite(this->get_cpath(resfile), img_matches);

    QString resall = "" ;// resstrs.join("\n");

    this->mreses <<resfile << resall;
    return false;
}
