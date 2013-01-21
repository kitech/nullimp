////////

#include <iostream>

#include "gmimp.h"



GmImp::GmImp()
    : Cimp()
{
    this->wand = nullptr;
    char *im_path = NULL;
    InitializeMagick(im_path);
    this->wand = NewMagickWand();
}

GmImp::~GmImp()
{
    if (this->wand != nullptr) {
        MagickResetIterator(this->wand);
        DestroyMagickWand(this->wand);
    }
}

unsigned char *GmImp::get_result(size_t *length)
{
    unsigned int rsize;

    rsize = MagickGetImageSize(this->wand);
    
    return MagickWriteImageBlob(this->wand, length);
}

////////
bool GmImp::do_imp()
{
    int iret;
    MagickPassFail status = MagickPass;

    // strcpy(this->file_path, "/mnt/sda7/serv/stow/nginx-1.1.3/html/libjpegtest5.jpeg");
    strcpy(this->file_path, "/serv/stow/nginx-1.3/html/libjpegtest5.jpeg");

    status = MagickReadImage(this->wand, this->file_path);

    if (status == MagickPass) {

    } else {
        this->get_errno();
        assert(1 == 2);
    }

    iret = MagickResizeImage(this->wand, 80, 80, UndefinedFilter, 1.2);

    return false;
}


char *GmImp::get_error()
{
    char *err;
    ExceptionType et;

    err = MagickGetException(this->wand, &et);
    std::cout<<"err:"<<err<<",eno:"<<et<<std::endl;
    return err;
}

int GmImp::get_errno()
{
    char *err;
    ExceptionType et;

    err = MagickGetException(this->wand, &et);
    std::cout<<"err:"<<err<<",eno:"<<et<<std::endl;
    return et;    
}

