#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>

struct flags
{
    bool f_long;
    bool f_rev;
    bool f_hum;
};

const long K_BYTE = 1024;

const std::string sep_path = "/";
const std::string sep_white_dir = "'";
// #define DEBUG 1 // раскоментировать для отладки

#endif