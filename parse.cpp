#include "parse.h"
#include <iostream>
#include <unistd.h> // for getopt()
#include <regex>
#include <algorithm>

using std::any_of;
using std::cout;
using std::endl;
using std::regex;
using std::search;
using std::string;
using std::vector;

/**
 * @brief разгребаем введенные опции
 *
 */
void Input::parser_flag()
{
    int opt;
    while ((opt = getopt(argc, argv, "lrh")) != -1)
    {
        opterr = 0;
        switch (opt)
        {
        case 'l':
            set_flags.f_long = true;
            break;
        case 'r':
            set_flags.f_rev = true;
            break;
        case 'h':
            set_flags.f_hum = true;
            break;
        default:
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }
    my_optind = optind; // наследие С, переменная на след позицию полсе опций
}

/**
 * @brief
 *
 * @param c_str
 * @param pos
 * @return string
 */
string Input::char_to_str(char **c_str, size_t pos)
{
    string r_val;
    char *first_char = c_str[pos];
    for (int i = 0; *first_char != '\0'; ++i)
        r_val.push_back(*first_char++);
    return r_val;
}

/**
 * @brief
 *
 */
void Input::parser_path_regex()
{
    // FIXME: реализовать поиск по пробелам
    regex r("(/|./){1}(([a-z,A-Z,0-9,_.'])+/?)+");
    s_path = char_to_str(argv, my_optind);
    bool valu = (regex_match(s_path, r)) ? true : false;
}

/**
 * @brief
 *
 */
void Input::parser_path()
{
    // FIXME: допилить вывод строки с ошибкой.
    s_path = char_to_str(argv, my_optind);
    if (parser_sep(s_path.begin(), s_path.end(), sep))
        cout << "error parse" << endl;
}

bool Input::parser_sep(c_iter begin, c_iter end, string sep)
{
    bool is_check{false};
    auto c = begin, i = begin;
    while ((c = search(i, end, sep.begin(), sep.end())) != end)
    {
        if (c == begin && c != end)
        {
            i++;
            continue;
        }

        if (parser_dir(i, c))
        {
            is_check = true;
            break;
        }
        i = c + sep.size();
    }
    if (!is_check)
        return parser_dir(i, c);
    return is_check;
}

bool Input::parser_dir(c_iter begin, c_iter end)
{
    bool res_flag{false};
    if (*begin == '\'' and *(end - 1) == '\'')
    {
        res_flag = any_of(begin, end, with_space);
        if (res_flag)
            std::cout << *find_if(begin, end, with_space) << std::endl;
    }
    else
    {
        res_flag = any_of(begin, end, with_not_space);
        if (res_flag)
            std::cout << *find_if(begin, end, with_not_space) << std::endl;
    }

    return res_flag;
}

bool Input::with_not_space(char c)
{
    string url_ch = "_.";
    return !(isalnum(c) ||
             find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

bool Input::with_space(char c)
{
    string url_ch_ = "_.' ";
    return !(isalnum(c) ||
             find(url_ch_.begin(), url_ch_.end(), c) != url_ch_.end());
}