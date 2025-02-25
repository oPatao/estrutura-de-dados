#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;
    fp = fopen("arquivo.txt", "w");
    
    if (fp == NULL)
    {
        printf("ERROR 404, ARQUIVO NAO ENCONTRADO");
        exit(1);
    }
    fclose(fp);
    return 0;
}