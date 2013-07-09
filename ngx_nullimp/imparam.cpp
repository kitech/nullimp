// imparma.cpp --- 
// 
// Author: liuguangzhao
// Copyright (C) 2007-2013 liuguangzhao@users.sf.net
// URL: 
// Created: 2013-07-08 20:45:35 +0000
// Version: $Id$
// 

#include <iostream>
#include <string.h>

#include "imparam.h"

Imparam::Imparam(const char *path, int length)
{
    this->m_raw_source_path = std::string(path, length);
    this->isParsed = false;
}


Imparam::~Imparam()
{


}

bool Imparam::parseParam()
{
    char buf[128];
    const char *phead, *pstart, *pend;

    if (this->isParsed) {
        return true;
    }

    phead = strchr(this->m_raw_source_path.c_str() + 1, '/');

    if (phead) {
        phead ++;
    } else {
        return false;
    }

    std::cout<<"rhead:"<<phead<<std::endl;

    while (phead) {
        if (strncmp(phead, "fn", 2) == 0) {
            pend = strpbrk(phead, "_.");
            strncpy(this->m_source_path, phead + 2, pend - phead - 2);
            this->m_source_path[pend - phead - 2] = '\0';
            phead = pend + 1;
        } else if (strncmp(phead, "op", 2) == 0) {
            pend = strpbrk(phead, "_.");
            strncpy(buf, phead + 2, pend - phead - 2);
            buf[pend - phead - 2] = '\0';
            phead = pend + 1;

            this->m_operator = OP_NONE;
            if (strcmp(buf, "resize") == 0) {
                this->m_operator = OP_RESIZE;
            } else if (strcmp(buf, "clip") == 0) {
                this->m_operator = OP_CLIP;
            } else if (strcmp(buf, "keypoint") == 0) {
                this->m_operator = OP_KEYPOINT;
            } else if (strcmp(buf, "phash") == 0) {
                this->m_operator = OP_PHASH;
            } else if (strcmp(buf, "description") == 0) {
                this->m_operator = OP_DESCRIPTION;
            } else if (strcmp(buf, "crackocr") == 0) {
                this->m_operator = OP_CRACK_OCR;
            } else if (strcmp(buf, "exif") == 0) {
                this->m_operator = OP_EXIF;
            } else {
            }
        } else if (strncmp(phead, "sl", 2) == 0) {
            
        } else if (strncmp(phead, "s", 1) == 0) {

        } else if (strncmp(phead, "c", 1) == 0) {

        } else if (strncmp(phead, "qa", 2) == 0) {

        } else if (strncmp(phead, "os", 2) == 0) {

        } else if (strncmp(phead, "wm", 2) == 0) {

        } else {
            break;
        }
    }

    this->isParsed = true;

    return true;
}


void Imparam::dumpParam()
{
    std::cout<<"raw path:"<<this->m_raw_source_path<<std::endl;
    std::cout<<"src path:"<<this->m_source_path<<std::endl;
    std::cout<<"optype:"<<this->m_operator<<std::endl;
}

