
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
#include "opencv2/nonfree/nonfree.hpp"


#include "baseimp.h"
#include "ocvimp.h"

OcvImp::OcvImp()
    : BaseImp()
{
}

OcvImp::~OcvImp()
{
}


std::string OcvImp::resizeFile(const char *file, int width, int height)
{
    this->m_src = cv::imread(file);

    cv::resize(this->m_src, this->m_dest, cv::Size(width, height));

    char *dtname = tempnam("/tmp", "ocvimp_");
    std::string edtname(dtname);
    free(dtname);

    edtname.append(".jpg");
    std::cout<<"fname:"<<edtname<<(&edtname)<<std::endl;

    std::vector<int> params = {CV_IMWRITE_JPEG_QUALITY, this->m_quality,
                               CV_IMWRITE_PNG_COMPRESSION, (100 - this->m_quality) / 10};
    cv::imwrite(edtname, this->m_dest, params);

    std::cout<<"fname:"<<edtname<<(&edtname)<<std::endl;
    return edtname;
    return nullptr;
}

std::string OcvImp::resizeFile(const char *file, int percent)
{
    this->m_src = cv::imread(file);

    cv::Size tosize(this->m_src.size().width * percent / 100.0, this->m_src.size().height * percent / 100.0);
    cv::resize(this->m_src, this->m_dest, tosize);

    char *dtname = tempnam("/tmp", "ocvimp_");
    std::string edtname(dtname);
    free(dtname);

    edtname.append(".jpg");
    cv::imwrite(edtname, this->m_dest);

    return edtname;
    return nullptr;
}

std::string OcvImp::resizeBuffer(const unsigned char *buffer, int length, int width, int height)
{
    unsigned char *data = (unsigned char*)calloc(1, length);
    memcpy(data, buffer, length);
    cv::Mat imgbuf = cv::Mat(480, 640, CV_8U, data);

    this->m_src = cv::imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);


    /*
// decode jpg (or other image from a pointer)
// imageBuf contains the jpg image
    cv::Mat imgbuf = cv::Mat(480, 640, CV_8U, imageBuf);
    cv::Mat imgMat = cv::imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);
// imgMat is the decoded image

// encode image into jpg
    cv::vector<uchar> buf;
    cv::imencode(".jpg", imgMat, buf, std::vector<int>() );
// encoded image is now in buf (a vector)
    imageBuf = (unsigned char *) realloc(imageBuf, buf.size());
    memcpy(imageBuf, &buf[0], buf.size());
//  size of imageBuf is buf.size();
*/


    return nullptr;
}

std::string OcvImp::resizeBuffer(const unsigned char *buffer, int length, int percent)
{
    return nullptr;
}


std::string OcvImp::watermarkFile(const char *wmfile, const char *srcfile, int wmp)
{
    return nullptr;
}

std::string OcvImp::packFiles() 
{
    return nullptr;
}

std::string OcvImp::data()
{
    cv::vector<uchar> buf;
    cv::imencode(".jpg", this->m_src, buf, std::vector<int>());
    
    unsigned char *imageBuf = (unsigned char*)calloc(buf.size(), 1);
    memcpy(imageBuf, &buf[0], buf.size());

    std::string d = std::string((char*)imageBuf, buf.size());
    std::string d1 = std::string((char*)&buf[0], buf.size());

    assert(d == d1);

    return d;
}
