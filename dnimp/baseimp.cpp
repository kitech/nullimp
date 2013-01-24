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
