#ifndef _BASEIMP_H_
#define _BASEIMP_H_

class BaseImp
{
public:
    explicit BaseImp();
    virtual ~BaseImp();

    virtual char *resizeFile(const char *file, int width, int height) = 0;
    virtual char *resizeFile(const char *file, int percent) = 0
    virtual char *resizeBuffer(const char *buffer, int width, int height) = 0;
    virtual char *resizeBuffer(const char *buffer, int percent) = 0;

protected:
    

private:
};


#endif /* _BASEIMP_H_ */
