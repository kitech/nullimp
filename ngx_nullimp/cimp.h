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

    virtual char *get_error();
    virtual int get_errno();

    void dump_params();

protected:
    bool parse_path();
    virtual bool do_imp();
    
protected:
    char ori_path[256];
    char file_path[256];
    int pid;
    int mid;
    int scale;
    int thumb_width;
    int thumb_height;
    int quality;

private:

};

#endif
