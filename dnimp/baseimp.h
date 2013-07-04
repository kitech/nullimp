#ifndef _BASEIMP_H_
#define _BASEIMP_H_

#include <string>

class BaseImp
{
public:
    explicit BaseImp();
    virtual ~BaseImp();

    enum WatermarkPosition {
        WMP_RIGHT_BOTTOM = 0,
        WMP_RIGHT, WMP_RIGHT_TOP, WMP_RIGHT_CENTER,
        WMP_CENTER_BOTTOM, WMP_CENTER_TOP,
        WMP_LEFT_BOTTOM, WMP_LEFT_TOP, WMP_LEFT_CENTER,
    };

    enum PackType {
        PT_AUTO = 0,
    };

    virtual std::string resizeFile(const char *file, int width, int height) = 0;
    virtual std::string resizeFile(const char *file, int percent) = 0;
    virtual std::string resizeBuffer(const unsigned char *buffer, int length, int width, int height) = 0;
    virtual std::string resizeBuffer(const unsigned char *buffer, int length,  int percent) = 0;
    virtual void setQuality(int qa);
    virtual std::string watermarkFile(const char *wmfile, const char *srcfile, int wmp = 0) = 0;
    virtual std::string packFiles() = 0;

    virtual std::string data() = 0;

protected:
    int m_quality;

private:
};


#endif /* _BASEIMP_H_ */
