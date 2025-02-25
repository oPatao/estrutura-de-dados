#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *arquivo;
    int numero = 125;
    char palavra [] = "esta palavra que sera gravada no arquivo!";

    arquivo = fopen("saida.txt", "w");

    if (arquivo == NULL)
    {
        printf("ERROR 404\nArquivo nao encontrado");
        exit(1);
    }
    
    fprintf(arquivo, "Numero: %d\n,Palavra: %s\n", numero,palavra);
    fclose(arquivo);

    return 0;
}