////////

#include "gmimp.h"

GmImp::GmImp()
    : Cimp()
{
    this->wand = NULL;
    InitializeMagick(0);
}

GmImp::~GmImp()
{

}


////////
bool GmImp::do_imp()
{
    return false;
}



