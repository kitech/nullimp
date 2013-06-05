// params.h --- 
// 
// Author: liuguangzhao
// Copyright (C) 2007-2013 liuguangzhao@users.sf.net
// URL: 
// Created: 2013-06-05 21:48:57 +0000
// Version: $Id$
// 
#ifndef _PARAMS_H_
#define _PARAMS_H_

class Params
{
public:
    explicit Params(std::string param);
    virtual ~Params();
    
    // s1x2_t2_qa3.jpg
    bool parse(std::string param);
private:
    std::string m_raw_param;

public:
    int m_scale_width;
    int m_scale_height;
    float m_scale_rate;
    int m_quality;
    std::string m_ext_name;
};

#endif /* _PARAMS_H_ */
