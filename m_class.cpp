// #include "m_class.cpp"

// void MClass::read_dir()
// {
//     parser_parametr();
//     cout << parser_path() << endl;

//     DIR *dp;
//     struct dirent *dirp;
//     struct stat buf;

//     if ((dp = opendir(parser_path())) == nullptr)
//         cout << "невозможно открыть" << endl;

//     while ((dirp = readdir(dp)) != nullptr)
//     {
//         file_type.clear();

//         cout << "dirname: " << dirp->d_name << " ";
//         type_file(dirp->d_name, &buf);
//         xwr_file(dirp->d_name, &buf);
//         owner_file(dirp->d_name, &buf);

//         // break;
//     }

//     closedir(dp);
//     exit(0);
// }

// /**
//  * @brief тип файла
//  *
//  * @param filename
//  */
// void MClass::type_file(const char *filename, struct stat *buf)
// {
//     if (lstat(filename, buf) < 0)
//     {
//         cout << "Ошибка вызова функции lstat";
//     }

//     if (S_ISREG(buf->st_mode))
//         file_type.push_back('-');
//     else if (S_ISDIR(buf->st_mode))
//         file_type.push_back('d');
//     else if (S_ISCHR(buf->st_mode))
//         file_type.push_back('c');
//     else if (S_ISBLK(buf->st_mode))
//         file_type.push_back('b');
//     else if (S_ISFIFO(buf->st_mode))
//         file_type.push_back('p');
//     else if (S_ISLNK(buf->st_mode))
//         file_type.push_back('l');
//     else if (S_ISSOCK(buf->st_mode))
//         file_type.push_back('s');
//     else
//         cout << "неизвестный тип файла" << endl;

//     cout << file_type << endl;
// }

// void MClass::xwr_file(const char *filename, struct stat *buf)
// {
//     if (lstat(filename, buf) < 0)
//     {
//         cout << "Ошибка вызова функции lstat";
//     }
//     cout << std::oct << (unsigned long)buf->st_mode << endl;
//     uint16_t mode = buf->st_mode;

//     vector<bool> v_bool;
//     for (int i = 0; i < 8; ++i)
//     {
//         v_bool.push_back(mode & 0xFE);
//         mode >>= i;
//     }

//     for (auto i : v_bool)
//         cout << int(i);
//     cout << endl;
// }

// void MClass::owner_file(const char *filename, struct stat *buf)
// {
//     if (lstat(filename, buf) < 0)
//     {
//         cout << "Ошибка вызова функции lstat";
//     }
//     struct passwd *pwd;
//     pwd = getpwuid(buf->st_uid);
//     cout << pwd->pw_name << endl;
// }