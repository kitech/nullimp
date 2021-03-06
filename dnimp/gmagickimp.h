#ifndef _GMAGICKIMP_H_
#define _GMAGICKIMP_H_

#include <string>

class BaseImp;

class GmagickImp : public BaseImp
{
public:
    explicit GmagickImp();
    virtual ~GmagickImp();

    virtual std::string resizeFile(const char *file, int width, int height);
    virtual std::string resizeFile(const char *file, int percent);
    virtual std::string resizeBuffer(const unsigned char *buffer, int width, int height);
    virtual std::string resizeBuffer(const unsigned char *buffer, int percent);

    virtual std::string watermarkFile(const char *wmfile, const char *srcfile, int wmp = 0);
    virtual std::string packFiles();

private:

};


#endif /* _GMAGICKIMP_H_ */
