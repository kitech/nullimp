
#include <stdio.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>


using namespace cv;


/*
 * 相比 haar_it (C版本的）效率更高，准确度更高
 */
bool haar_it_cpp(std::string srcfile)
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
    // bret = cascade->load("/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
    bret = cascade->load("./trdata/cascade.xml");
    std::cout<< bret << cascade->empty() << std::endl ;

    src = imread(srcfile.c_str(), 1);

    cv::cvtColor(src, gray, CV_RGB2GRAY);

    small_img = Mat(cvRound(src.rows / scale), cvRound(src.cols / scale), CV_8UC1);
    Size smallImgSize = small_img.size();

    resize(gray, small_img, smallImgSize, 0, 0, INTER_LINEAR);
    equalizeHist(small_img, small_img);

    vector<Rect> faces;
    cascade->detectMultiScale(small_img, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));
    std::cout<<faces.size()<<std::endl;

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

    std::string resfile = "symlight.bmp";
    bret = imwrite(resfile, src);
    // cvSaveImage(this->get_cpath(resfile), src);
    // this->mreses << resfile;

    delete cascade;

    return true;
}

// 这个训练的分类器的准确率也就50%

int main(int argc, char **argv)
{
    
    // haar_it_cpp("namefmt/verify.144.bmp.clear_noise.bmp");
    haar_it_cpp("namefmt/verify.53.bmp");
    return 0;
}
