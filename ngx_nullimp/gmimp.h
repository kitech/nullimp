// gmimp.h --- 
// 
// Author: liuguangzhao
// Copyright (C) 2007-2012 liuguangzhao@users.sf.net
// URL: 
// Created: 2012-11-26 13:32:15 +0800
// Version: $Id$
// 

#ifndef _GMIMP_H_
#define _GMIMP_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <wand/magick_wand.h>

#include "cimp.h"

class GmImp : public Cimp
{
public:
    GmImp();
    virtual ~GmImp();

    virtual unsigned char *get_result(size_t *length);
    virtual char *get_error();
    virtual int get_errno();

protected:
    virtual bool do_imp() override;

private:
    MagickWand *wand;
    
};

#endif
