#include <stdio.h>
#include <stdlib.h>
int massimo(int argc, char*argv[])
{
    int max = atoi(argv[1]), pos=0;
    for(int i = 2; i < argc; i++)
    {
        int numero = atoi(argv[i]);
        if(numero > max)
        {
            max = numero;
            pos = i;
        }
    }
    return pos;
}
int pari(int argc, char*argv[], int nPari[])
{
    int k=0, numero, i, contaP;
    for(i = 1; i < argc; i++)
    {
        numero = atoi(argv[i]);
        if(numero % 2 == 0)
        {
            nPari[k] = numero;
            k++;
            contaP++;
        }
    }
    return contaP;
}
int main (int argc, char* argv[])
{
    int pos = massimo(argc, argv);
    printf("Il numero più grande è: %d\n\n", atoi(argv[pos]));
    int nPari[argc], contaPa;
    contaPa = pari(argc, argv, nPari);
    printf("I numeri pari sono:\n");
    for(int i = 0; i < contaPa; i++)
    {
        printf("%d\n", nPari[i]);
    }
    return 0;
}