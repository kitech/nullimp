////////


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

    status = MagickReadImage(this->wand, this->file_path);
    if (status == MagickPass) {
        
    } else {
        assert(1 == 2);
    }

    iret = MagickResizeImage(this->wand, 100, 100, UndefinedFilter, 1.2);

    return false;
}



