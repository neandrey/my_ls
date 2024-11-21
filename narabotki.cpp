int flags, opt;
int nsecs, tfnd;

void read_option()
{
}

void read_directory()
{
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2)
        cout << "Использование: ls  имя_каталога";

    if ((dp = opendir(argv[1])) == NULL)
        printf("невозможно открыть %s", argv[1]);

    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);

    closedir(dp);
    exit(0);
}

void print_pid()
{

    printf("привет от процесса с идентификатором %d\n", (long)getpid());
}