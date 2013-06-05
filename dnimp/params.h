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

private:
    std::string m_raw_param;
};

#endif /* _PARAMS_H_ */
