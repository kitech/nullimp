
#include <unistd.h>
#include <string>
#include <iostream>

#include "impfactory.h"
#include "baseimp.h"

// #include "wand/wand_api.h"
// #include "wand/magick_wand.h"

// #include "vips/vipscpp.h"
//// #include "vips/vips.h"

#include "benchmark.h"

// 100ms
void benchmark_opencv_resize()
{
    // cv::Mat src, thumb;

    // src = cv::imread("/home/gzleo/shots/nshots93.jpg");

    // cv::resize(src, thumb, cv::Size(300, 400));

    // cv::imwrite("/tmp/abc.jpg", thumb);

    BaseImp *himp = ImpFactory::create(ImpFactory::IMP_TYPE_OPENCV);
    std::string tname = himp->resizeFile("/home/gzleo/shots/nshots93.jpg", 500, 400);
    std::cout<<"file name:" << tname<<(&tname) << std::endl;
    
    // unlink(tname.c_str());
}

// 120ms
void benchmark_gmagick_resize()
{
    BaseImp *himp = ImpFactory::create(ImpFactory::IMP_TYPE_GMAGICK);
    std::string tname = himp->resizeFile("/home/gzleo/shots/nshots93.jpg", 500, 400);
    std::cout<<"file name:" << tname<<(&tname) << std::endl;
    
    unlink(tname.c_str());
    
    /*
    MagickWand *wand;
    MagickPassFail status = MagickPass;

    InitializeMagick(0);
    wand = NewMagickWand();
    status = MagickReadImage(wand, "/home/gzleo/shots/nshots93.jpg");

    MagickResizeImage(wand, 300, 400, UndefinedFilter, 0);

    char *out_file = "/tmp/efg.jpg";
    MagickWriteImage(wand, out_file);

    DestroyMagickWand(wand);
    DestroyMagick();
    */
    /*
      unsigned int MagickResizeImage( MagickWand *wand, const unsigned long columns,
      const unsigned long rows, const FilterTypes filter,
      const double blur );
    */
}

// 160ms
void benchmark_vips_resize()
{
    // vips::VImage fred ("/home/gzleo/shots/nshots93.jpg");

    // make a 3x3 sharpen mask
    /*
    VIMask sharp (3, 3, 8, 0,
                  -1, -1, -1,
                  -1, 16, -1,
                  -1, -1, -1);
    */        
    // brighten and sharpen
    // VImage jim = (fred * 1.2).conv (sharp);
    // vips::VImage jim = fred.resize_linear(300, 400);
    
    // write to file argv[2]
    // jim.write ("/tmp/hi.jpg");
}

