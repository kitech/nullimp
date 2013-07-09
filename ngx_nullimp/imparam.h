// imparma.h --- 
// 
// Author: liuguangzhao
// Copyright (C) 2007-2013 liuguangzhao@users.sf.net
// URL: 
// Created: 2013-07-08 20:43:11 +0000
// Version: $Id$
// 

#ifndef _IMPARMA_H_
#define _IMPARMA_H_

#include <string>

class Imparam 
{
public:
    // /nimp?a1_b2_c3.jpg
    explicit Imparam(const char *path, int length);
    virtual ~Imparam();

    bool parseParam();
    void dumpParam();

    bool isParsed;

    enum {OP_NONE, OP_RESIZE, OP_CLIP, OP_KEYPOINT, OP_PHASH,
          OP_DESCRIPTION, OP_CRACK_OCR, OP_EXIF};
    std::string m_raw_source_path;
    char m_source_path[64];
    int m_operator; // 
    int m_source_type;
    int m_quality;

    int m_resize_width;
    int m_resize_height;

    int m_clip_x;
    int m_clip_y;
    int m_clip_width;
    int m_clip_height;

    static const char m_param_seprator = '_';
    // fn,op,s,sl,c,qa,os,wm,
};

#endif /* _IMPARMA_H_ */
