// int flags, opt;
// int nsecs, tfnd;

// void read_option()
// {
// }
// typedef int Myfunc(const char *, const struct stat *, int);

// static Myfunc myfunc;
// static int myftw(char *, Myfunc *);
// static int dopath(Myfunc *);

// static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

// void read_directory()
// {
//     DIR *dp;
//     struct dirent *dirp;

//     if (argc != 2)
//         cout << "Использование: ls  имя_каталога";

//     if ((dp = opendir(argv[1])) == NULL)
//         printf("невозможно открыть %s", argv[1]);

//     while ((dirp = readdir(dp)) != NULL)
//         printf("%s\n", dirp->d_name);

//     closedir(dp);
//     exit(0);
// }

// void print_pid()
// {

//     printf("привет от процесса с идентификатором %d\n", (long)getpid());
// }

/*
    int ret;

    ret = myftw(argv[2], myfunc);

    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;

    if (ntot == 0)
        ntot = 1;
    cout << "Обычные файлы = " << nreg << " " << (nreg * 100.0 / ntot);
    cout << "каталоги = " << ndir << " " << (ndir * 100.0 / ntot);
    cout << "специальные файлы блочных устройств = " << nblk
         << " " << (nblk * 100.0 / ntot);
    cout << "специальные файлы символьных устройств = " << nchr
         << " " << (nchr * 100.0 / ntot);
    cout << "FIFO = " << nfifo << " " << (nfifo * 100.0 / ntot);
    cout << "символьные ссылкм = " << nslink << " " << (nslink * 100.0 / ntot);
    cout << "сокеты = " << nsock << " " << (nsock * 100.0 / ntot);
}

#define FTW_F 1   // файл не являющейся каталогам
#define FTW_D 2   // каталог
#define FTW_DNR 3 // каталог доступный для чтения
#define FTW_NS 4  // не возможно получить с помощью stat.

static char *fullpath;
static size_t pathlen;
static int myftw(char *pathname, Myfunc *func)
{
    fullpath = path_alloc(&len);

    if (pathlen <= strlen(pathname))
    {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == nullptr)
            cout << "Ошбика вызова realloc" << endl;
    }
    strcpy(fullpath, pathname);
    return (dopath(func));
}

static int dopath(Myfunc *func)
{
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;

    if (lstat(fullpath, &statbuf) < 0)
        return (func(fullpath, &statbuf, FTW_NS));
    if (S_ISDIR(statbuf.st_mode) == 0)
        return (func(fullpath, &statbuf, FTW_F));

    // каталог
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
        return ret;

    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen)) == nullptr)
            cout << "Ошбика вызова realloc" << endl;
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;

    if ((dp = opendir(fullpath)) == nullptr)
        return (func(fullpath, &statbuf, FTW_DNR));

    while ((dirp = readdir(dp)) != nullptr)
    {
        if (strcpy(dirp->d_name, ".") == 0 ||
            strcmp(dirp->d_name, "..") == 0)
            continue;
        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0)
            break;
    }
    fullpath[n - 1] = 0;

    if (closedir(dp) < 0)
        cout << "невозможно закрыть каталог " << fullpath << endl;
    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
    switch (type)
    {
    case FTW_F:
        switch (statptr->st_mode & S_IFMT)
        {
        case /* constant-expression */
/* code */