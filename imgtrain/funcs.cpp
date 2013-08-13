

#include "funcs.h"

using namespace std;
using namespace cv;

/**
   
   remove_border();
   custom_dilate();
   remove_backgroup();
   custom_erode();

   ==> 白底黑字图
 */

cv::Mat remove_border(cv::Mat src)
{
    
    for (int i = 0; i < src.rows; i ++) {
        for (int j = 0; j < src.cols; j ++) {
            if (i == 0 || i == src.rows-1 || j == 0 || j == src.cols-1) {
                src.at<uchar>(i, j) = 255;
            }
        }
    }

    return src;
}

cv::Mat custom_dilate(cv::Mat src, int bgcolor)
{   
    // 滤噪管用了，但这个滤不够好，对线条细的线给滤没了
    // cv::Mat ker(3, 3, CV_8UC1, cv::Scalar::all(255));
    // cv::dilate(src, src, ker);
 
    return src;
}

// 这个还是挺管用的，还可用于检测图像的大体色彩
cv::Mat remove_backgroup(cv::Mat src, int *pbgcolor)
{
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
    
    int bgcolor = 1;
    float bgrate = 0.0, ftmp;
    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                         Scalar( 255, 0, 0), 2, 8, 0  );
        
        ftmp = b_hist.at<float>(i);
        if (ftmp > bgrate) {
            bgcolor = i;
            bgrate = ftmp;
        }
    }

    *pbgcolor = bgcolor;
    std::cout<<"bgcolor:"<<bgcolor<<"|" << bgrate<< std::endl;
    for (int i = 0; i < src.rows; i ++) {
        for (int j = 0; j < src.cols; j ++) {
            if (src.at<uchar>(i, j) == bgcolor) {
                src.at<uchar>(i, j) = 255;
            }
        }
    }

    cv::imwrite("hist.bmp", histImage);

    return src;
}

cv::Mat custom_erode(cv::Mat src, int bgcolor)
{
    // 再返过来强化一下被滤掉的部分
    cv::Mat ker2(3, 3, CV_8UC1, cv::Scalar::all(255));
    cv::erode(src, src, ker2);

    // get 分水岭的值
    /*
    /// Establish the number of bins
    int histSize = 256;
    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 255 } ;
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
    Mat b_hist, g_hist, r_hist;
    /// Compute the histograms:
    calcHist( &src, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    std::cout<<histSize << "|" << b_hist.size() << "|"  << b_hist<<std::endl;

    int bgcolor = 1;
    float bgrate = 0.0, ftmp;
    for( int i = 0; i < histSize; i++ ) {
        float tmp = b_hist.at<float>(i);
        if (tmp > 0.0) {
            // std::cout<<"i:"<<i<<"|"<<tmp<<std::endl;
        }
        if (tmp > bgrate) {
            bgrate = tmp;
            bgcolor = i;
        }
    }
    */

    // 这个分水岭的值不好计算啊
    // std::cout<<"bgcolor222:"<<bgcolor<<"|" << bgrate<< std::endl;
    bgcolor = 210;
    // std::cout<<"bgcolor333:"<<bgcolor<<"|" << bgrate<< std::endl;
    for (int i = 0; i < src.rows; i ++) {
        for (int j = 0; j < src.cols; j ++) {
            if (src.at<uchar>(i, j) < bgcolor) {
                src.at<uchar>(i, j) = 0;
            } else {
                src.at<uchar>(i, j) = 255;
            }
        }
    }

    // blur一下
    cv::blur(src, src, cv::Size(1, 1));

    cv::Mat ker(3, 3, CV_8UC1, cv::Scalar::all(255));
    cv::dilate(src, src, ker);
    cv::dilate(src, src, ker);

    return src;
}

cv::Mat detect_background(cv::Mat src)
{
    cv::Mat dst;
    cv::BackgroundSubtractorMOG2 bg; // for video
    // bg.nmixtures = 3;
    // bg.bShawdowDetect = true;
    int bgcolor = 255;

    src = remove_border(src);
   
    src = remove_backgroup(src, &bgcolor);
    cv::imwrite("remove_backgroup.bmp", src);

    src = custom_dilate(src, bgcolor);
    cv::imwrite("custom_dilate.bmp", src);

    src = custom_erode(src, bgcolor);

    // std::cout<<src<<std::endl;
    cv::imwrite("custom_erode.bmp", src);

    dst = src;
    return dst;
}


