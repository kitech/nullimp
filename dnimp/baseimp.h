#ifndef _BASEIMP_H_
#define _BASEIMP_H_

#include <string>

class BaseImp
{
public:
    explicit BaseImp();
    virtual ~BaseImp();

    virtual std::string resizeFile(const char *file, int width, int height) = 0;
    virtual std::string resizeFile(const char *file, int percent) = 0;
    virtual std::string resizeBuffer(const unsigned char *buffer, int width, int height) = 0;
    virtual std::string resizeBuffer(const unsigned char *buffer, int percent) = 0;
    virtual void setQuality(int qa);

protected:
    int m_quality;

private:
};


#endif /* _BASEIMP_H_ */
