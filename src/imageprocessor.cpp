#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include "imageprocessor.h"


ImageProcessor::ImageProcessor(QObject *parent) :
    QThread(parent)
{
}

void ImageProcessor::run()
{

}

void ImageProcessor::run(QStringList args)
{

}
