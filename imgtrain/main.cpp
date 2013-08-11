#include <stdio.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>

cv::Mat getRotatedImage(cv::Mat src, cv::RotatedRect rrect)
{
    // rect is the RotatedRect (I got it from a contour...)
    cv::RotatedRect rect = rrect;
    // matrices we'll use
    cv::Mat M, rotated, cropped;
    // get angle and size from the bounding box
    float angle = rect.angle;
    cv::Size rect_size = rect.size;
    // thanks to http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
    if (rect.angle < -45.) {
        angle += 90.0;
        std::swap(rect_size.width, rect_size.height);
    }
    // get the rotation matrix
    M = cv::getRotationMatrix2D(rect.center, angle, 1.0);
    std::cout<<M<<angle;
    // perform the affine transformation
    cv::warpAffine(src, rotated, M, src.size(), cv::INTER_CUBIC);
    // crop the resulting image
    cv::getRectSubPix(rotated, rect_size, rect.center, cropped);

    return cropped;
}

int main(int argc, char **argv)
{
    cv::Mat ms,md,md2;
    cv::Mat flt(1, 3, 4);

    ms = cv::imread("verify1.bmp");

    // 转灰
    cv::cvtColor(ms,md, CV_BGR2GRAY, 1);
    // cv::blur(md, ms, cv::Size(5, 5));
    // cv::bilateralFilter(md, md2, 9, 260, 260);
    // cv::GaussianBlur(md, md2, cv::Size(5, 5), 60);
    // cv::sepFilter2D(md, md2, -1, flt, flt);
    // cv::erode(md, md2, cv::Mat(), cv::Point(-1, -1), 2);
    // cv::dilate(md2, md, cv::Mat(), cv::Point(-1, -1), 2);
    // cv::fastNlMeansDenoising(md, md2, 20);
   
    if (1) {
    std::cout<< md.dims << md.channels() << (short)md.at<uchar>(0, 0) << md.total();
    for (int i = 0; i < md.rows; i ++) {
        for (int j = 0; j < md.cols; j ++) {
            if (i == 0 || i == md.rows-1 || j == 0 || j == md.cols-1) {
                md.at<uchar>(i, j) = 255;
            } else if ((short)md.at<uchar>(i, j) >= 237) {
                md.at<uchar>(i, j) = 255;
            } else if ((short)md.at<uchar>(i, j) < 237 ) {
                md.at<uchar>(i, j) = 0;
            }
        }
    }

    // row
    for (int i = 0; i < md.rows; i ++) {
        for (int j = 0; j < md.cols-1; j ++) {
            if ((short)md.at<uchar>(i, j) == 0) {
                int zcnt = 0;
                for (int k = j; k < md.cols; k++) {
                    if ((short)md.at<uchar>(i, k) > 0) break;
                    if ((short)md.at<uchar>(i, k) == 0) {
                        zcnt++;
                    }
                }
                if (zcnt <= 2) {
                    md.at<uchar>(i, j) = 255;
                    md.at<uchar>(i, j+1) = 255;
                    // md.at<uchar>(i, j+2) = 255;
                    // md.at<uchar>(i, j+3) = 255;
                    // md.at<uchar>(i, j+4) = 255;
                }
                j += zcnt;
            }
        }
    }

    if (1) {
    for (int j = 0; j < md.cols; j ++) {
        for (int i = 0; i < md.rows-1; i ++) {
            if ((short)md.at<uchar>(i, j) == 0) {
                int zcnt = 0;
                for (int k = i; k < md.rows-1; k++) {
                    if ((short)md.at<uchar>(k, j) > 0) break;
                    if ((short)md.at<uchar>(k, j) == 0) {
                        zcnt++;
                    }
                }
                if (zcnt <= 2) {
                    md.at<uchar>(i, j) = 255;
                    md.at<uchar>(i+1, j) = 255;
                    // md.at<uchar>(i, j+2) = 255;
                    // md.at<uchar>(i, j+3) = 255;
                    // md.at<uchar>(i, j+4) = 255;
                }
                i += zcnt;
            }
        }
    }
    }

    }

    cv::Mat nobg = md.clone();

    // 反转
    for (int i = 0; i < md.rows; i ++) {
        for (int j = 0; j < md.cols; j ++) {
            if ((short)md.at<uchar>(i, j) == 0) {
                md.at<uchar>(i, j) = 255;
            } else {
                md.at<uchar>(i, j) = 0;
            }
        }
    }

    cv::Canny(md, md2, 50, 200, 3);
    // cv::cvtColor(md2, md, CV_GRAY2BGR);
    // std::cout<<md2;
    cv::imwrite("canny.bmp", md2);

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hia;
    cv::findContours(md, contours, hia, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    // 好像这个连接区域检测效果很差啊

    std::cout<< "\n" << contours.size() << "\n";
    for (int i = 0; i < contours.size(); i ++) {
        std::vector<cv::Point> c1 = contours.at(i);
        std::cout<< "" << c1.size() << "," << hia[i] << "\n";        

        for (int j = 0; j < contours.at(i).size(); j++) {
            // std::cout << contours.at(i).at(j) << std::endl;
            md.at<uchar>(contours.at(i).at(j)) = 255;
        }

    }

    int nc = 7;
    std::vector<std::vector<cv::Point> > ct;
    ct.push_back(contours.at(nc));

    cv::RotatedRect area = cv::minAreaRect(contours.at(nc));
    std::cout<<area.angle<<std::endl;
    area.size = cv::Size(area.size.width + 1, area.size.height + 2);

    cv::Mat mask = cv::Mat::zeros(ms.rows, ms.cols, CV_8UC1);
    cv::drawContours(mask, ct, -1, cv::Scalar(255), CV_FILLED);

    cv::Rect drect = area.boundingRect();
    cv::rectangle(mask, drect, cv::Scalar(255, 0, 0), 2);

    cv::Mat chimg = getRotatedImage(nobg, area);

    cv::imwrite("gray.bmp", chimg);
    cv::imwrite("graymy.bmp", md);

    return 0;
}
