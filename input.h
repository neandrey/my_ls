#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>
#include <unistd.h> // for getopt()

class Input
{
    std::vector<std::string> v_str;
    bool f_long{false}, f_reverse{false}, f_human{false};

    int argc;
    char **argv;

public:
    Input(int _argc, char **_argv) : argc(_argc), argv(_argv)
    {
    }

    void parser_parametr();
    void parser_path();
};

/**
 * @brief разгребаем введенные опции
 *
 */
void Input::parser_parametr()
{
    int opt;
    while ((opt = getopt(argc, argv, "lrh")) != -1)
    {
        switch (opt)
        {
        case 'l':
            f_long = true;
            break;
        case 'r':
            f_reverse = true;
            break;
        case 'h':
            f_human = true;
            break;
        default:
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

/**
 * @brief разгребаем введенную строку
 *
 */
void Input::parser_path()
{
}

#endif