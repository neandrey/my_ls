#ifndef INPUT_H
#define INPUT_H
#include "settings.h"
#include <string>

class Input
{
    typedef std::string::const_iterator c_iter;
    int argc;
    char **argv;
    // bool f_long{false}, f_reverse{false}, f_human{false};
    flags set_flags{false, false, false};

    std::string s_path;
    size_t my_optind{0};

    void parser_flag();
    void parser_path_regex();
    void parser_path();

    bool parser_sep(c_iter begin, c_iter end);
    bool parser_dir(c_iter begin, c_iter end);
    static bool with_space(char);
    static bool with_not_space(char);

    // erorr_info
    std::pair<int, char> error_info;

public:
    Input(int _argc, char **_argv) : argc(_argc), argv(_argv)
    {
        parser_flag();
        parser_path();
    }

    const char *get_path()
    {
        return s_path.c_str();
    }
    struct flags get_flags()
    {
        return set_flags;
    }
    static std::string char_to_str(char **c_str, size_t pos);
};
#endif