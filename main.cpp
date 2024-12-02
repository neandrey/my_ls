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
#include "m_class.h"
using namespace std;

int main(int argc, char **argv)
{
#ifdef DEBUG
    // для отладки
    argc = 3;
    argv[0] = "main";
    argv[1] = "-l";
    argv[2] = "/projectC/'hel'lo'";
#endif

    MClass m_class(argc, argv);
    m_class.print();
}