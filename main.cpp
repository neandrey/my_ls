/**
 * @file main.cpp
 * @brief  Проект реализующий утилиту ls
 * @version 0.1
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
    argv[1] = "-lhr";
    argv[2] = "/";
#endif

    MClass m_class(argc, argv);
    m_class.print();
}