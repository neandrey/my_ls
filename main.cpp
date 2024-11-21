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
#include <unistd.h>
#include <dirent.h>
#include <string.h>
using namespace std;

#define MAXLINE 4096
int main(int argc, char **argv)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;
    }
}
