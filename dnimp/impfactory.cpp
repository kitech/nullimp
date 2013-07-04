
#include "baseimp.h"
#include "ocvimp.h"
#include "gmagickimp.h"

#include "impfactory.h"

BaseImp *ImpFactory::m_inst[ImpFactory::IMP_TYPE_COUNT] = {nullptr};

BaseImp *ImpFactory::create(int imp_type, bool force_new)
{
    BaseImp * imp = nullptr;

    // TODO need lock
    if (imp_type >= ImpFactory::IMP_TYPE_OPENCV && imp_type <= ImpFactory::IMP_TYPE_VIPS) {
        if (ImpFactory::m_inst[imp_type] == nullptr) {
            switch (imp_type) {
            case ImpFactory::IMP_TYPE_OPENCV:
                ImpFactory::m_inst[imp_type] = new OcvImp();
                break;
            case ImpFactory::IMP_TYPE_GMAGICK:
                // ImpFactory::m_inst[imp_type] = new GmagickImp();
                break;
            case ImpFactory::IMP_TYPE_VIPS:
                // ImpFactory::m_inst[imp_type] = new VipsImp();
                break;
            default:
                break;
            }
        }
        return ImpFactory::m_inst[imp_type];
    }

    return nullptr;
}


ImpFactory::ImpFactory(int imp_type, bool force_new)
{
}

ImpFactory::~ImpFactory()
{
}

