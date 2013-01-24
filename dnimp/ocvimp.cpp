
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

std::string OcvImp::resizeBuffer(const unsigned char *buffer, int width, int height)
{
    return nullptr;
}

std::string OcvImp::resizeBuffer(const unsigned char *buffer, int percent)
{
    return nullptr;
}

