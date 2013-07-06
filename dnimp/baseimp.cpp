
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "baseimp.h"

BaseImp::BaseImp()
{
    this->m_quality = 50;
}

BaseImp::~BaseImp()
{
}

void BaseImp::setQuality(int qa)
{
    this->m_quality = qa;
}


bool BaseImp::isGif(const char *file)
{
    std::ifstream inFile;
    inFile.open(file,std::ios::in);
    unsigned char gif_type[4] = {0x47,0x49,0x46,'\0'};
    unsigned char file_head[4];
    file_head[3] = '\0';
    for (int i=0; i<3; ++i) {
        inFile>>file_head[i];
        if (file_head[i] != gif_type[i])
            return false;
    }
    inFile.close();
    return true;
}

bool BaseImp::isGif(const char *buffer, int length)
{

    unsigned char gif_type[4] = {0x47,0x49,0x46,'\0'};

    if (memcmp(buffer, gif_type, 3) == 0) {
        return true;
    }

    return false;
}


