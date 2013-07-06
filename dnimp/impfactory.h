#ifndef _IMPFACTORY_H_
#define _IMPFACTORY_H_

class BaseImp;

class ImpFactory
{
public:
    static const int IMP_TYPE_OPENCV = 0;
    static const int IMP_TYPE_GMAGICK = 1;
    static const int IMP_TYPE_VIPS = 2;

    static BaseImp *create(int imp_type, bool force_new = false);
    static bool free(BaseImp *himp, int imp_type);
    
protected:
    explicit ImpFactory(int imp_type, bool force_new = false);
    virtual ~ImpFactory();

private:
    static const int IMP_TYPE_COUNT = 3;
    static BaseImp *m_inst[ImpFactory::IMP_TYPE_COUNT];
};


#endif /* _IMPFACTORY_H_ */
