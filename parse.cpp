#include "parse.h"
#include <iostream>
#include <unistd.h> // for getopt()
#include <regex>
#include <algorithm>
#include <linux/limits.h>

using std::any_of;
using std::cerr;
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
        // opterr = 0;
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
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (set_flags.f_long != true)
    {
        cerr << "Обязательно должен быть введен флаг long." << endl;
        exit(EXIT_FAILURE);
    }
    my_optind = optind; // наследие С, переменная на след позицию полсе опций
#ifdef DEBUG
    cout << my_optind << endl;
#endif
}

string Input::char_to_str(char **c_str, size_t pos)
{
    string r_val;
    char *first_char = c_str[pos];
    for (int i = 0; *first_char != '\0'; ++i)
        r_val.push_back(*first_char++);
    return r_val;
}

void Input::parser_path()
{
    if (my_optind < 2)
    {
        char cwd[PATH_MAX];
        s_path = getcwd(cwd, sizeof(cwd));
        return;
    }

    s_path = char_to_str(argv, my_optind);
    if (parser_sep(s_path.begin(), s_path.end()))
    {
        // FIXME: допилить вывод строки с ошибкой.
        cerr << "В пути присутствуют недопустимые символы." << endl;
        exit(EXIT_FAILURE);
    }
}

bool Input::parser_sep(c_iter begin, c_iter end)
{
    auto c = begin, i = begin;
    while ((c = search(i, end, sep_path.begin(), sep_path.end())) != end)
    {
        if (*i == *c)
        {
            i += sep_path.size();
            continue;
        }

        if (parser_dir(i, c - 1))
            return true;

        i = c + sep_path.size();
    }
    return parser_dir(i, c);
}

bool Input::parser_dir(c_iter begin, c_iter end)
{

    bool first_sep{false};
    auto c = begin, i = begin;
    while ((c = search(i, end, sep_white_dir.begin(), sep_white_dir.end())) != end)
    {
        if (c == begin)
        {
            first_sep = true;
            i += sep_white_dir.size();
            continue;
        }

        if (c == end - 1 and first_sep)
        {
            return any_of(begin + 1, end - 1, with_space);
        }
        i = c + sep_white_dir.size();
    }

    return any_of(begin, end, with_not_space);
}

bool Input::with_not_space(char c)
{
    string valid_symbol = "_.";
    return !(isalnum(c) ||
             find(valid_symbol.begin(), valid_symbol.end(), c) != valid_symbol.end());
}

bool Input::with_space(char c)
{
    string valid_symbol_ = "_. ";
    return !(isalnum(c) ||
             find(valid_symbol_.begin(), valid_symbol_.end(), c) != valid_symbol_.end());
}