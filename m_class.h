#ifndef M_CLASS_H
#define M_CLASS_H
#include "parse.h"
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>

class MClass
{
    Input *in;
    std::vector<std::string> v_dir_name;
    std::vector<std::string> v_res;

    DIR *dp;
    struct dirent *dirp;
    struct stat buf;

    void type_file(struct stat *);
    void xwr_file(struct stat *);
    void owner_file(struct stat *);
    void get_time(struct stat *);
    void get_size(struct stat *);
    void read_file_dir(const char *path);
    void read_lstat(const char *filename);

    // xwr-group
    void owner_rights(struct stat *);
    void group_rights(struct stat *);
    void other_rights(struct stat *);

    void main_func(const char *path);

public:
    MClass(int argc, char **argv)
    {
        in = new Input(argc, argv);
        main_func(in->get_path());
    }
};

#endif