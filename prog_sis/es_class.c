#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
int main(int argc; char*argv[])
{
   if(argc != 2)
   {
        exit(0);
   }
   char word[strlen(argv[1])];
   int pid = fork();
   if(pid == 0)
   {
        for(int i = 0; i < strlen(argv[1]); i++)
        {
            word[i]= toupper(argv[1][i]);
        }
        printf("la stringa in maiuscolo è %s", word);
   }
    return 0;
}