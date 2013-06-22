
#include "wand/wand_api.h"
#include "wand/magick_wand.h"


#include "baseimp.h"
#include "gmagickimp.h"

GmagickImp::GmagickImp()
    : BaseImp()
{
}

GmagickImp::~GmagickImp()
{
}

std::string GmagickImp::resizeFile(const char *file, int width, int height)
{
    MagickWand *wand;
    MagickPassFail status = MagickPass;

    InitializeMagick(0);
    wand = NewMagickWand();

    status = MagickReadImage(wand, file);

    MagickResizeImage(wand, width, height, UndefinedFilter, 0);

    char *dtname = tempnam("/tmp", "gmagickimp_");
    MagickWriteImage(wand, dtname);

    DestroyMagickWand(wand);

    DestroyMagick();
    /*
      unsigned int MagickResizeImage( MagickWand *wand, const unsigned long columns,
      const unsigned long rows, const FilterTypes filter,
      const double blur );
    */

    std::string edtname(dtname);
    free(dtname);

    return edtname;
    return nullptr;
}

std::string GmagickImp::resizeFile(const char *file, int percent)
{
    return nullptr;
}

std::string GmagickImp::resizeBuffer(const unsigned char *buffer, int width, int height)
{
    return nullptr;
}

std::string GmagickImp::resizeBuffer(const unsigned char *buffer, int percent)
{
    return nullptr;
}


std::string GmagickImp::watermarkFile(const char *wmfile, const char *srcfile, int wmp)
{
    return nullptr;
}

std::string GmagickImp::packFiles() 
{
    return nullptr;
}

