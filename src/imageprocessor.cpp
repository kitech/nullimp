#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include "imageprocessor.h"


ImageProcessor::ImageProcessor(QObject *parent) :
    QThread(parent)
{
}

void ImageProcessor::run()
{
    QStringList args = this->margs;

    qDebug()<<"haha"<<args;

    QString src1, src2;

    if (args.at(0) == "smooth") {
        src1 = args.at(1);

        this->smooth_it(src1);


    }
}

void ImageProcessor::run(QStringList args)
{
    this->margs = args;
    this->start();
}

QStringList ImageProcessor:: getResult()
{
    QStringList reses;

    reses << this->margs
             << this->mreses;

    return reses;
}

bool ImageProcessor::smooth_it(QString srcfile)
{
    /// Global Variables
    int DELAY_CAPTION = 1500;
    int DELAY_BLUR = 100;
    int MAX_KERNEL_LENGTH = 31;

    cv::Mat src; cv::Mat dst;
    char window_name[] = "Filter Demo 1";

    char *srcimg = srcfile.toAscii().data();
    /// Load the source image
      // src = cv::imread( "../images/lena.jpg", 1 );
    src = cv::imread( srcimg, 1 );


      dst = src.clone();

      for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
          {
          cv::blur( src, dst, cv::Size( i, i ), cv::Point(-1,-1) );

      }

       for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
           {
                    cv::GaussianBlur( src, dst, cv::Size( i, i ), 0, 0 );
            }


        for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
            {
            cv::medianBlur ( src, dst, i );

        }

        for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
            {
            cv::bilateralFilter ( src, dst, i, i*2, i/2 );

        }

    return true;
}
