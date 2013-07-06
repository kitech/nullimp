
#include <unistd.h>
#include <sys/stat.h>


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
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
    // 在web模式运行时，可能会由于web server的运行权限问题读取失败
    this->m_src = cv::imread(file);

    std::cout<<"before resize:"<<this->m_src.empty() << "," << this->m_src.size() << "," << file << std::endl;
    cv::resize(this->m_src, this->m_dest, cv::Size(width, height));
    std::cout<<"end resize:"<<std::endl;

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

    if (0) {
        char *dtname = tempnam("/dev/shm/", "nimpsrc");
        std::string edtname(dtname);
        edtname.append(".jpg");
        free(dtname);

        int pos = 0;
        int rc;
        FILE *fp = fopen(edtname.c_str(), "wb+");

        while (pos < length) {
            rc = fwrite(buffer + pos, 1, 1000, fp);
            if (rc < 0) {
                break;
            }
            pos += rc;
        }

        fclose(fp);
        chmod(edtname.c_str(), 0755);
        

        std::string rname = this->resizeFile(edtname.c_str(), width, height);

        // unlink(edtname.c_str());

        return rname;
    }
    
    if (1) {
        std::cout<<__FILE__<<__LINE__<<std::endl;
        unsigned char *data = (unsigned char*)calloc(length, 1);
        memcpy(data, buffer, length);

        std::cout<<__FILE__<<__LINE__<<std::endl;
        // this->m_src = cv::Mat(480, 640, CV_8U, (unsigned char*)data);
        cv::Mat imgbuf = cv::Mat(640, 480, CV_8U, (unsigned char*)data);
        std::cout<<__FILE__<<__LINE__<<std::endl;
        this->m_src = cv::imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);

        std::cout<<this->m_src.empty() << "," << this->m_src.size().width << "," << this->m_src.size() << "\n";
    }

    if (0) {
        std::string rawbuf = std::string((const char*)buffer, length);
        std::vector<uchar> data = std::vector<uchar>(rawbuf.begin(), rawbuf.end());
        std::vector<uchar> data1 = std::vector<uchar>(buffer, buffer + length);

        cv::Mat imgbuf = cv::Mat(0, 0, 0, (void*)buffer);
        // this->m_src = cv::imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);
        // this->m_src = cv::imdecode(data, CV_LOAD_IMAGE_COLOR);

        std::cout<<data.size() << "," << rawbuf.length()<<","<<this->m_src.size().width<<"\n";
    }


    std::cout<<"before resize:"<<std::endl;
    cv::resize(this->m_src, this->m_dest, cv::Size(width, height));
    std::cout<<"end resize:"<<std::endl;


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

    std::string r = "abc";
    return r;
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
    // cv::imencode(".jpg", this->m_src, buf, std::vector<int>());
    cv::imencode(".jpg", this->m_dest, buf, std::vector<int>());
    
    unsigned char *imageBuf = (unsigned char*)calloc(buf.size(), 1);
    memcpy(imageBuf, &buf[0], buf.size());

    std::string d = std::string((char*)imageBuf, buf.size());
    std::string d1 = std::string((char*)&buf[0], buf.size());

    assert(d == d1);

    return d;
}

std::string OcvImp::mimeType()
{
    std::string mtype;

    mtype = "image/jpeg; charset=binary";

    return mtype;
}


int OcvImp::width()
{
    cv::Size sz = this->m_src.size();

    return sz.width;
    return 0;
}

int OcvImp::height()
{
    cv::Size sz = this->m_src.size();

    return sz.height;
    return 0;
}

