#include <stdio.h>

#include "benchmark.h"

int main(int argc, char **argv)
{

    benchmark_opencv_resize();
    // benchmark_gmagick_resize();
    // benchmark_vips_resize();

    return 0;
}
