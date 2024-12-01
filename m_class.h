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

struct FileData
{
    std::string group_type_and_xwr;
    int link;
    std::string group_owner_and_group;
    std::string size;
    std::string date;
    std::string name_file;
};

class MClass
{
    Input *in;
    std::vector<std::string> v_dir_name;
    std::vector<FileData> v_res;

    struct stat buf;

    size_t len_xwr{0}, len_link{0}, len_owner{0}, len_size{0}, len_date{0}, len_name{0};

    void read_file_dir(const char *path);
    void read_lstat(const char *filename);

    // тип и права
    std::string type_and_xwr();

    // тип-файла
    const char type_file();

    // права пользователя, группы, остальных
    void owner_rights(std::string &s);
    void group_rights(std::string &s);
    void other_rights(std::string &s);

    // количество ссылок на файл
    int get_link();

    // имя владельца и имя группы
    const std::string name_and_group();
    const std::string name_owner();
    const std::string group_owner();

    // размер файла
    std::string get_size(flags f_val);

    // время создания файла
    std::string get_date();

    void max_len_string(const std::string &name, flags f_val);
    void append_data(const std::string &name, flags f_val);

    void main_func(const char *path, flags f_val);

public:
    MClass(int argc, char **argv)
    {
        in = new Input(argc, argv);
        main_func(in->get_path(), in->get_flags());
    }

    void print();
};

#endif