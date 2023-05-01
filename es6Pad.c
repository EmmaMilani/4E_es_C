#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <stdlib.h>
// grep file.txt | wc -l
int main(int argc, char *argv[])
{
    int pid, p1p2[2], p2p0[2], nread, fd;
    char stringa[30], buff;
    if (argc != 2)
    {
        printf("Numero argomenti errato.");
        exit(1);
    }
    pipe(p1p2);
    printf("Inserisci una parola:");
    scanf("%s", stringa);
    pid = fork();
    if (pid == 0)
    {
        close(p1p2[0]);
        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);
        execl("/usr/bin/grep", "grep", stringa, argv[1], NULL);
        return -1;
    }
    pipe(p2p0);
    pid = fork();
    if (pid == 0)
    {
        close(p2p0[0]);
        close(p1p2[1]);
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);
        close(1);
        dup(p2p0[1]);
        close(p2p0[1]);
        execl("/usr/bin/wc", "wc", "-l", NULL);
        return -1;
    }
    close(p1p2[0]);
    close(p1p2[1]);
    close(p2p0[1]);
    fd = open("ris.txt", O_WRONLY | O_CREAT, 0777);
    while(nread = read(p2p0[0], &buff, sizeof(buff)) > 0)
    {
        write(fd, &buff, nread);
    }
    close(p2p0[0]);
    close(fd);
    return 0;
}