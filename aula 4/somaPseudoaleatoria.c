#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t start_time, end_time;
    double cpu_time_used;
    int num_aleatorio;
    long long soma = 0;
    int quantidade = 200000;
    int limite_superior = 1000; 


    srand(time(NULL));

    start_time = clock(); 

    
    for (int i = 0; i < quantidade; i++) {
        num_aleatorio = rand() % limite_superior;
        soma += num_aleatorio;
    }

    end_time = clock(); 
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Soma de %d numeros pseudoaleatorios (entre 0 e %d): %lld \n",  quantidade, limite_superior - 1, soma);
    printf("Tempo de CPU usado: %f segundos\n", cpu_time_used);

    return 0;
}