#include "m_class.h"
#include <iostream>
#include <cstring>
#include <ctime>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

void MClass::main_func(const char *path)
{

    read_file_dir(path);

    for (auto name_dir : v_dir_name)
    {
        if (name_dir == "." or name_dir == "..")
            continue;

        read_lstat(name_dir.c_str());
        formating_string(&buf, name_dir);

        // v_res.push_back(type_file(&buf) +
        //                 xwr_file(&buf) + ' ' +
        //                 name_owner(&buf) + ' ' +
        //                 group_owner(&buf) + ' ' +
        //                 std::to_string(get_size(&buf)) + ' ' + name_dir);
    }
}

void MClass::formating_string(struct stat *buf, string name)
{
    size_t curr_len_owner = name_group_owner(buf).size();
    size_t curr_len_size = to_string(get_size(buf)).size();
    size_t curr_len_name = name.size();

    len_xwr = 9;
    len_owner = (curr_len_owner > len_owner)
                    ? curr_len_owner
                    : len_owner;
    len_size = (curr_len_size > len_size)
                   ? curr_len_size
                   : len_size;
    // len_date
    len_name = (curr_len_name > len_name)
                   ? curr_len_name
                   : len_name;
}

void MClass::append_data(struct stat *)
{
}

void MClass::read_file_dir(const char *path)
{
    if ((dp = opendir(path)) == nullptr)
        cout << "невозможно открыть" << endl;

    while ((dirp = readdir(dp)) != nullptr)
    {
        v_dir_name.push_back(dirp->d_name);
        // cout << "dirname: " << dirp->d_name << endl;
    }

    closedir(dp);
    // exit(0);
}

void MClass::read_lstat(const char *filename)
{
    if (lstat(filename, &buf) < 0)
        cout << "невозможно прочитать lstat " << endl;
}

const char MClass::type_file(struct stat *buf)
{
    char res;
    if (S_ISREG(buf->st_mode))
        res = ('-');
    else if (S_ISDIR(buf->st_mode))
        res = ('d');
    else if (S_ISCHR(buf->st_mode))
        res = ('c');
    else if (S_ISBLK(buf->st_mode))
        res = ('b');
    else if (S_ISFIFO(buf->st_mode))
        res = ('p');
    else if (S_ISLNK(buf->st_mode))
        res = ('l');
    else if (S_ISSOCK(buf->st_mode))
        res = ('s');
    else
        cout << "неизвестный тип файла" << endl;

    return res;
}

string MClass::xwr_file(struct stat *buf)
{

    return (owner_rights(buf) +
            group_rights(buf) +
            other_rights(buf));
}

string MClass::name_owner(struct stat *buf)
{
    struct passwd *pwd;
    pwd = getpwuid(buf->st_uid);

    return string(pwd->pw_name);
}

string MClass::group_owner(struct stat *buf)
{
    struct group *grp;
    grp = getgrgid(buf->st_gid);

    return string(grp->gr_name);
}

string MClass::name_group_owner(struct stat *buf)
{
    return name_owner(buf) + " " + group_owner(buf);
}

void MClass::get_time(struct stat *buf)
{
    cout << buf->st_ctim << endl;
}

int MClass::get_size(struct stat *buf)
{
    return buf->st_size;
}

string MClass::owner_rights(struct stat *buf)
{
    string res;
    res.push_back((buf->st_mode & S_IRUSR) ? 'r' : '-');
    res.push_back((buf->st_mode & S_IWUSR) ? 'w' : '-');
    res.push_back((buf->st_mode & S_IXUSR) ? 'x' : '-');

    return res;
}

string MClass::group_rights(struct stat *buf)
{

    string res;
    res.push_back((buf->st_mode & S_IRGRP) ? 'r' : '-');
    res.push_back((buf->st_mode & S_IWGRP) ? 'w' : '-');
    res.push_back((buf->st_mode & S_IXUSR) ? 'x' : '-');

    return res;
}

string MClass::other_rights(struct stat *buf)
{
    string res;
    res.push_back((buf->st_mode & S_IROTH) ? 'r' : '-');
    res.push_back((buf->st_mode & S_IWOTH) ? 'w' : '-');
    res.push_back((buf->st_mode & S_IXOTH) ? 'x' : '-');

    return res;
}

void MClass::print()
{
    for (auto i : v_res)
    {
        cout << i << endl;
    }
}