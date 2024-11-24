/**
 * @file main.cpp
 * @author ne_andrey(sorokinac@gmail.com)
 * @brief  Проект реализующий утилиту ls
 * @version 0.1
 * @date 2024-11-21
 *
 * @copyright Copyright (c) 2024
 */
#include <iostream>
#include "input.h"
using namespace std;

int main(int argc, char **argv)
{
    // для отладки
    argc = 3;
    argv[0] = "main";
    argv[1] = "-l";
    argv[2] = "./home/ne_andrey/projectC/'my_ ls'";

    Input in(argc, argv);
    flags v_flags = in.get_flags();

    cout << v_flags.f_long << endl;
    cout << v_flags.f_hum << endl;
    cout << v_flags.f_rev << endl;
}