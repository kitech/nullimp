// cimp.h --- 
// 
// Author: liuguangzhao
// Copyright (C) 2007-2012 liuguangzhao@users.sf.net
// URL: 
// Created: 2012-11-25 21:39:22 +0000
// Version: $Id$
// 
#ifndef _CIMP_H_
#define _CIMP_H_

class Cimp
{
public:
    Cimp();
    virtual ~Cimp();

    bool process(char *path);
    char *get_result();

protected:
    bool parse_path();
    bool do_imp();
    
protected:
    char ori_path[256];
    int scale;
    int thumb_width;
    int thumb_height;
    int quality;

private:

};

#endif
