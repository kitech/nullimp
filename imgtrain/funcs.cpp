

#include "funcs.h"

using namespace std;
using namespace cv;

cv::Mat detect_background(cv::Mat src)
{
    cv::Mat dst;
    cv::BackgroundSubtractorMOG2 bg; // for video
    // bg.nmixtures = 3;
    // bg.bShawdowDetect = true;

    
    /// Separate the image in 3 places ( B, G and R )
    vector<Mat> bgr_planes;
    split(src, bgr_planes );

    /// Establish the number of bins
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 255 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    /// Compute the histograms:
    calcHist( &src, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    // calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    // calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    // calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    std::cout<<histSize << "|" << b_hist.size() << "|"  << b_hist<<std::endl;

    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    // normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    // normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                         Scalar( 255, 0, 0), 2, 8, 0  );
        /*
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                         Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                         Scalar( 0, 0, 255), 2, 8, 0  );
        */
    }

    // 滤噪管用了
    cv::Mat ker(3, 3, CV_8UC1, cv::Scalar::all(255));
    cv::dilate(src, src, ker);
    // 再返过来强化一下被滤掉的部分
    cv::Mat ker2(3, 3, CV_8UC1, cv::Scalar::all(255));
    cv::erode(src, src, ker2);

    std::cout<<src<<std::endl;
    cv::imwrite("gray2.bmp", src);
    cv::imwrite("hist.bmp", histImage);
    
    return dst;
}


