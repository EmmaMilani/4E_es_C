#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <ctype.h>
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Numero argomenti errato.");
        exit(1);
    }
    int pid, p1p2[2], p2p0[2];
    char buffer[100], strimporto[100], *ptr;
    double totale;
    pipe(p1p2);
    pid = fork();
    if (pid == 0) // P1
    {
        close(p1p2[0]);
        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);
        execl("/usr/bin/cat", "cat", argv[1], NULL);
        return -1;
    }
    pipe(p2p0);
    pid = fork();
    if (pid == 0) // P2
    {
        close(p2p0[0]);
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);
        close(1);
        dup(p2p0[1]);
        close(p2p0[1]);
        execl("/usr/bin/awk", "awk", "{print $3}", p1p2[0], NULL);//il terzo argomenti mi serve a estrapolare la terza colonna
        return -1;
    }
    close(p1p2[0]);
    close(p1p2[1]);
    close(p2p0[1]);
    //la stringa dentro la pipe è fatta così: 10\n200\n456\n --> se trova lo \n vuol dire che ha trovato il primo numero
    while (read(p2p0[0], buffer, sizeof(buffer)) > 0)
    {
        strncat(strimporto, &buffer[0], sizeof(buffer[0]));
        if()
        {
            printf("Importo ricevuto: %s", strimporto);
            totale = totale + strtod(strimporto, &ptr);//converto il numero e me lo salvo nel totale
            strimporto[0] = '\0';//appena trovo uno \n resetto la stringa   
        }
    }
    close(p2p0[0]);
    printf("Il totale è: %.2lf\n", totale);//%.2lf ci stampa dopo la virgola solo due cifre
    return 0;
}
