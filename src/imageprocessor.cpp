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
