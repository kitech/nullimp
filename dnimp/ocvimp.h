#ifndef _OCVIMP_H_
#define _OCVIMP_H_

#include "opencv/cv.h"

class BaseImp;

class OcvImp : public BaseImp
{
public:
    explicit OcvImp();
    virtual ~OcvImp();

    virtual std::string resizeFile(const char *file, int width, int height);
    virtual std::string resizeFile(const char *file, int percent);
    virtual std::string resizeBuffer(const char *buffer, int width, int height);
    virtual std::string resizeBuffer(const char *buffer, int percent);

private:
    cv::Mat m_src;
    cv::Mat m_src1;
    cv::Mat m_src2;
    cv::Mat m_dest;
    cv::Mat m_dest1;
    cv::Mat m_dest2;
    cv::Mat m_tmp;
    cv::Mat m_tmp1;
    cv::Mat m_tmp2;
};

#endif /* _OCVIMP_H_ */
