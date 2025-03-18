#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int ID, Idade;
    char Nome[50];
} Pessoa;

int main(){
    Pessoa X[3];
    int i;
    char Cabecalho[50];

    FILE *fp;
    fp = fopen("dados.csv", "r");

    if (fp == NULL)
    {
        printf("ERROR 404\nArquivo nao encontrado");
        exit(1);
    }

    fscanf(fp, "%s", Cabecalho);
    printf("%s", Cabecalho);

    while (fscanf(fp,"%d,%*[^,],%d", &X[i].ID, X[i].Nome, &X[i].Idade ) == 3)
    {
        printf("%d\t%s\t%d\n", X[i].ID, X[i].Nome, X[i].Idade);      
        i++;
    }

    fclose(fp);
    return 0;

}