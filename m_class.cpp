#include "m_class.h"
#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

void MClass::main_func(const char *path)
{

    read_file_dir(path);

    for (auto name_dir : v_dir_name)
    {
        read_lstat(name_dir.c_str());
        type_file(&buf);
        xwr_file(&buf);
        owner_file(&buf);
        get_size(&buf);
        // get_time(&buf);
    }
}

void MClass::read_file_dir(const char *path)
{
    if ((dp = opendir(path)) == nullptr)
        cout << "невозможно открыть" << endl;

    while ((dirp = readdir(dp)) != nullptr)
    {
        v_dir_name.push_back(dirp->d_name);
        cout << "dirname: " << dirp->d_name << endl;
    }

    // closedir(dp);
    // exit(0);
}

void MClass::read_lstat(const char *filename)
{
    if (lstat(filename, &buf) < 0)
        cout << "невозможно прочитать lstat " << endl;
}

/**
 * @brief тип файла
 *
 * @param filename
 */
void MClass::type_file(struct stat *buf)
{
    if (S_ISREG(buf->st_mode))
        v_res.push_back("-");
    else if (S_ISDIR(buf->st_mode))
        v_res.push_back("d");
    else if (S_ISCHR(buf->st_mode))
        v_res.push_back("c");
    else if (S_ISBLK(buf->st_mode))
        v_res.push_back("b");
    else if (S_ISFIFO(buf->st_mode))
        v_res.push_back("p");
    else if (S_ISLNK(buf->st_mode))
        v_res.push_back("l");
    else if (S_ISSOCK(buf->st_mode))
        v_res.push_back("s");
    else
        cout << "неизвестный тип файла" << endl;
}

void MClass::xwr_file(struct stat *buf)
{
    owner_rights(buf);
    group_rights(buf);
    other_rights(buf);
}

void MClass::owner_file(struct stat *buf)
{
    struct passwd *pwd;
    pwd = getpwuid(buf->st_uid);
    cout << pwd->pw_name << endl;

    struct group *grp;
    grp = getgrgid(buf->st_gid);
    cout << grp->gr_name << endl;
}

void MClass::get_time(struct stat *buf)
{
    // cout << buf->st_ctim << endl;
}

void MClass::get_size(struct stat *buf)
{
    cout << buf->st_size << endl;
}

void MClass::owner_rights(struct stat *buf)
{
    cout << bool(buf->st_mode & S_IRUSR) << endl;
    cout << bool(buf->st_mode & S_IWUSR) << endl;
    cout << bool(buf->st_mode & S_IXUSR) << endl;
}

void MClass::group_rights(struct stat *buf)
{
    cout << bool(buf->st_mode & S_IRGRP) << endl;
    cout << bool(buf->st_mode & S_IWGRP) << endl;
    cout << bool(buf->st_mode & S_IXUSR) << endl;
}

void MClass::other_rights(struct stat *buf)
{
    cout << bool(buf->st_mode & S_IROTH) << endl;
    cout << bool(buf->st_mode & S_IWOTH) << endl;
    cout << bool(buf->st_mode & S_IXOTH) << endl;
}
