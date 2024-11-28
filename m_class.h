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

    size_t len_xwr{0}, len_owner{0}, len_size{0}, len_date{0}, len_name{0};

    void read_file_dir(const char *path);
    void read_lstat(const char *filename);

    // тип-файла
    const char type_file(struct stat *);

    // права пользователей
    std::string xwr_file(struct stat *);
    std::string owner_rights(struct stat *);
    std::string group_rights(struct stat *);
    std::string other_rights(struct stat *);

    // имя владельца и группы
    std::string name_group_owner(struct stat *);
    std::string name_owner(struct stat *);
    std::string group_owner(struct stat *);

    // размер файла
    int get_size(struct stat *);

    // время создания файла
    void get_time(struct stat *);

    void formating_string(struct stat *, std::string name);
    void append_data(struct stat *);

    void main_func(const char *path);

public:
    MClass(int argc, char **argv)
    {
        in = new Input(argc, argv);
        main_func(in->get_path());
    }

    void print();
};

#endif