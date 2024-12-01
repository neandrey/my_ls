#include "m_class.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <regex>

using std::cerr;
using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::reverse;
using std::sort;
using std::string;
using std::to_string;

void MClass::main_func(const char *path, flags f_val)
{
    read_file_dir(path);

    sort(v_dir_name.begin(), v_dir_name.end());

    if (f_val.f_rev)
    {
        reverse(v_dir_name.begin(), v_dir_name.end());
    }

    regex reg("(\\.|\\..){1}([\\d,\\w,\\S]+)?"); // для удаления . или ..
    for (auto name_file : v_dir_name)
    {
        if (regex_match(name_file, reg))
            continue;

        read_lstat(name_file.c_str());
        max_len_string(name_file, f_val);
        append_data(name_file, f_val);
    }
}

void MClass::append_data(const string &name, flags f_val)
{
    v_res.push_back(
        FileData{
            type_and_xwr(),
            get_link(),
            name_and_group(),
            get_size(f_val),
            get_date(),
            name});
};

void MClass::max_len_string(const string &name, flags f_val)
{
    size_t curr_len_type_and_xwr = type_and_xwr().size();
    size_t curr_len_owner = name_and_group().size();
    size_t curr_len_size = get_size(f_val).size();
    size_t curr_len_name = name.size();
    size_t curr_len_link = to_string(get_link()).size();
    size_t curr_len_date = get_date().size();

    len_xwr = (curr_len_type_and_xwr > len_xwr)
                  ? curr_len_type_and_xwr
                  : len_xwr;

    len_link = (curr_len_link > len_link)
                   ? curr_len_link
                   : len_link;

    len_owner = (curr_len_owner > len_owner)
                    ? curr_len_owner
                    : len_owner;

    len_size = (curr_len_size > len_size)
                   ? curr_len_size
                   : len_size;

    len_date = (curr_len_date > len_size)
                   ? curr_len_date
                   : len_date;

    len_name = (curr_len_name > len_name)
                   ? curr_len_name
                   : len_name;
}

void MClass::read_file_dir(const char *path)
{
    DIR *dp;
    struct dirent *dirp;
#ifdef DEBUG
    cout << path << endl;
#endif

    if ((dp = opendir(path)) == nullptr)
    {
        cerr << "невозможно открыть директорию" << endl;
        closedir(dp);
        exit(EXIT_FAILURE);
    }

    if (chdir(path) == -1)
    {
        cerr << "chdir ошбка смены каталога" << endl;
        exit(EXIT_FAILURE);
    }

    while ((dirp = readdir(dp)) != nullptr)
    {
        // cout << dirp->d_name << endl;
        v_dir_name.push_back(dirp->d_name);
    }

    closedir(dp);
}

void MClass::read_lstat(const char *filename)
{
    if (lstat(filename, &buf) < 0)
    {
        // cout << filename << endl;
        cerr << "невозможно прочитать lstat " << endl;
        exit(EXIT_FAILURE);
    }
}

const char MClass::type_file()
{
    char res;
    if (S_ISREG(buf.st_mode))
        res = ('-');
    else if (S_ISDIR(buf.st_mode))
        res = ('d');
    else if (S_ISCHR(buf.st_mode))
        res = ('c');
    else if (S_ISBLK(buf.st_mode))
        res = ('b');
    else if (S_ISFIFO(buf.st_mode))
        res = ('p');
    else if (S_ISLNK(buf.st_mode))
        res = ('l');
    else if (S_ISSOCK(buf.st_mode))
        res = ('s');
    else
    {
        cout << "неизвестный тип файла" << endl;
        exit(EXIT_FAILURE);
    }

    return res;
}

string MClass::type_and_xwr()
{
    string ret;

    ret.push_back(type_file());
    owner_rights(ret);
    group_rights(ret);
    other_rights(ret);

    return ret;
}

int MClass::get_link()
{
    return buf.st_nlink;
}

const string MClass::name_owner()
{
    struct passwd *pwd;
    pwd = getpwuid(buf.st_uid);

    return string(pwd->pw_name);
}

const string MClass::group_owner()
{
    struct group *grp;
    grp = getgrgid(buf.st_gid);

    return string(grp->gr_name);
}

const string MClass::name_and_group()
{
    return name_owner() + " " + group_owner();
}

string MClass::get_date()
{
    // FIXME: допилить вывод времени
    std::stringstream MyTime;
    MyTime << std::put_time(std::gmtime(&buf.st_ctim.tv_sec), "%b %y");
    return MyTime.str();
}

string MClass::get_size(flags f_val)
{
    // 1024 = 1K
    string res;
    off_t val_byte = buf.st_size;
    if (f_val.f_hum)
    {
        int count = 1;
        while (val_byte / K_BYTE != 0)
        {
            val_byte /= K_BYTE;
            count++;
        }
        res = to_string(val_byte);

        switch (count)
        {
        case 2:
            res.push_back('K');
            break;
        case 3:
            res.push_back('M');
            break;
        case 4:
            res.push_back('G');
            break;
        case 5:
            res.push_back('T');
            break;
        }
    }
    else
        res = to_string(val_byte);
    return res;
}

void MClass::owner_rights(string &s)
{
    s.push_back((buf.st_mode & S_IRUSR) ? 'r' : '-');
    s.push_back((buf.st_mode & S_IWUSR) ? 'w' : '-');
    s.push_back((buf.st_mode & S_IXUSR) ? 'x' : '-');
}

void MClass::group_rights(string &s)
{
    s.push_back((buf.st_mode & S_IRGRP) ? 'r' : '-');
    s.push_back((buf.st_mode & S_IWGRP) ? 'w' : '-');
    s.push_back((buf.st_mode & S_IXUSR) ? 'x' : '-');
}

void MClass::other_rights(string &s)
{
    s.push_back((buf.st_mode & S_IROTH) ? 'r' : '-');
    s.push_back((buf.st_mode & S_IWOTH) ? 'w' : '-');
    s.push_back((buf.st_mode & S_IXOTH) ? 'x' : '-');
}

void MClass::print()
{
    for (auto i : v_res)
    {
        cout.setf(std::ios::left);
        cout << std::setw(len_xwr + 1) << i.group_type_and_xwr
             << std::setw(len_link + 1) << i.link
             << std::setw(len_owner + 1) << i.group_owner_and_group
             << std::setw(len_size + 1) << i.size
             << std::setw(len_date + 1) << i.date
             << std::setw(len_name + 1) << i.name_file
             << endl;
    }
}