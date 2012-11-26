////////
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#include "cimp.h"

Cimp::Cimp()
{
}

Cimp::~Cimp()
{
    
}

bool Cimp::process(char *path)
{
    bool bret;

    strncpy(this->ori_path, path, sizeof(this->ori_path)-1);
    bret = this->parse_path();
    if (!bret) {
        return false;
    }

    bret = this->do_imp();

    if (!bret) {
        return false;
    }

    return true;
}

unsigned char *Cimp::get_result(size_t *length)
{
    *length = 0;
    return NULL;
}

/*
  7a/59/6/3f4c1ee14901c2a1c18931538ed_p2_mk4.jpg
 */
bool Cimp::parse_path()
{
    char *p0, *p1, *p2, *p3;
    char *path = NULL;
    char tmp[128];
    int state = 0;

    p0 = p1 = this->ori_path;

    while ((p2 = strpbrk(p1, "_")) != NULL) {
        if (path == NULL) {
            path = p0;
            strncpy(this->file_path, path, p2 - p0);
        }
        p2 ++;
        p0 = p2;
        if (p2 == NULL) {
            assert(p2 != NULL);
        }

        p2 = strchr(p0, '_');
        if (strncmp(p0, "mk", 2) == 0) {
            strncpy(tmp, p0+2, p2 - (p0+2));
            this->mid = strtol(tmp, &p3, 10);
        } else if (strncmp(p0, "wm", 2) == 0) {

        } else if (strncmp(p0, "qa", 2) == 0) {

        } else if (strncmp(p0, "os", 2) == 0) {

        } else if (strncmp(p0, "bc", 2) == 0) {

        } else if (strncmp(p0, "p", 1) == 0) {
            strncpy(tmp, p0+2, p2 - (p0+2));
            this->pid = strtol(tmp, &p3, 10);
        } else if (strncmp(p0, "s", 1) == 0) {

        } else if (strncmp(p0, "t", 1) == 0) {

        } else if (strncmp(p0, "c", 1) == 0) {

        } else {
            assert(1 == 2);
        }

        p1 = ++ p2;
    }
    
    return true;
}

void Cimp::dump_params()
{
    std::cout << "ori_path:" << this->ori_path
              << "file_path:" << this->file_path
              << "pid:" << this->pid
              << "mid:" << this->mid
              << std::endl;
        ;
}

char *Cimp::get_error()
{
    return NULL;
}

int Cimp::get_errno()
{
    return 0;
}

////////// protected
bool Cimp::do_imp()
{
    assert(1 == 2);
    return false;
}

