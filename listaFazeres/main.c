#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarefa {
    int id;
    char descricao[100];
    int prioridade;
    struct Tarefa *anterior;
    struct Tarefa *proximo;
} Tarefa;


Tarefa* CriarTarefa(int id, const char* descricao, int prioridade) {
    Tarefa* nova = (Tarefa*) malloc(sizeof(Tarefa));
    nova->id = id;
    strcpy(nova->descricao, descricao);
    nova->prioridade = prioridade;
    nova->anterior = NULL;
    nova->proximo = NULL;
    return nova;
}


void InserirTarefa(Tarefa** lista, int id, const char* descricao, int prioridade) {
    Tarefa* nova = CriarTarefa(id, descricao, prioridade);
    if (*lista == NULL) {
        *lista = nova;
        return;
    }
    Tarefa* atual = *lista;
    while (atual->proximo != NULL)
        atual = atual->proximo;
    atual->proximo = nova;
    nova->anterior = atual;
}


void RemoverTarefa(Tarefa** lista, int id) {
    Tarefa* atual = *lista;
    while (atual != NULL && atual->id != id)
        atual = atual->proximo;
    if (atual == NULL) return;

    if (atual->anterior)
        atual->anterior->proximo = atual->proximo;
    else
        *lista = atual->proximo;

    if (atual->proximo)
        atual->proximo->anterior = atual->anterior;

    free(atual);
}

void MoverPrioridadeParaInicio(Tarefa** lista, int prioridade) {
    Tarefa* atual = *lista;
    Tarefa* novaLista = NULL;

    while (atual != NULL) {
        Tarefa* proxima = atual->proximo;
        if (atual->prioridade == prioridade) {

            if (atual->anterior)
                atual->anterior->proximo = atual->proximo;
            else
                *lista = atual->proximo;
            if (atual->proximo)
                atual->proximo->anterior = atual->anterior;


            atual->anterior = atual->proximo = NULL;
            if (novaLista == NULL) {
                novaLista = atual;
            } else {
                Tarefa* temp = novaLista;
                while (temp->proximo)
                    temp = temp->proximo;
                temp->proximo = atual;
                atual->anterior = temp;
            }
        }
        atual = proxima;
    }


    if (novaLista != NULL) {
        Tarefa* fimNova = novaLista;
        while (fimNova->proximo)
            fimNova = fimNova->proximo;
        fimNova->proximo = *lista;
        if (*lista)
            (*lista)->anterior = fimNova;
        *lista = novaLista;
    }
}

void InverterIntervalo(Tarefa* lista, int idInicio, int idFim) {
    Tarefa *ini = NULL, *fim = NULL, *atual = lista;

    while (atual != NULL) {
        if (atual->id == idInicio) ini = atual;
        if (atual->id == idFim) fim = atual;
        atual = atual->proximo;
    }

    if (ini == NULL || fim == NULL || ini == fim) return;

    atual = ini;
    while (atual != NULL && atual != fim)
        atual = atual->proximo;
    if (atual == NULL) {
        Tarefa* temp = ini;
        ini = fim;
        fim = temp;
    }

    Tarefa* prev = ini->anterior;
    Tarefa* next = fim->proximo;
    Tarefa* p = ini;
    Tarefa* temp = NULL;

    while (p != next) {
        temp = p->proximo;
        p->proximo = p->anterior;
        p->anterior = temp;
        p = temp;
    }

    if (prev)
        prev->proximo = fim;
    fim->anterior = prev;

    if (next)
        next->anterior = ini;
    ini->proximo = next;

    if (lista == ini)
        lista = fim;
}

void ExibirTarefas(Tarefa* lista) {
    printf("Lista de Tarefas:\n");
    while (lista != NULL) {
        printf("ID: %d | Desc: %s | Prioridade: %d\n", lista->id, lista->descricao, lista->prioridade);
        lista = lista->proximo;
    }
}

void LiberarLista(Tarefa* lista) {
    while (lista != NULL) {
        Tarefa* temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

int main() {
    Tarefa* lista = NULL;
    bool ok = true;

    InserirTarefa(&lista, 1, "Enviar relatorio", 2);
    InserirTarefa(&lista, 2, "Corrigir bugs", 1);
    InserirTarefa(&lista, 3, "Fazer backup", 3);
    InserirTarefa(&lista, 4, "Revisar codigo", 1);

/*     printf("Antes:\n");
    ExibirTarefas(lista);

    MoverPrioridadeParaInicio(&lista, 1);
    printf("\nApos mover prioridade 1 para inicio:\n");
    ExibirTarefas(lista);

    InverterIntervalo(lista, 2, 3);
    printf("\nApos inverter intervalo entre 2 e 3:\n");
    ExibirTarefas(lista);

    RemoverTarefa(&lista, 1);
    printf("\nApos remover tarefa com ID 1:\n");
    ExibirTarefas(lista);
*/
    while (ok == true) {
        int opcao;

        printf("1 - Inserir tarefa\n");
        printf("2 - Remover tarefa\n");
        printf("3 - Mover prioridade para inicio\n");
        printf("4 - Inverter intervalo entre dois IDs\n");
        printf("5 - Exibir tarefas\n");
        printf("6 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int id, prioridade;
                char descricao[100];
                printf("ID: ");
                scanf("%d", &id);
                printf("Prioridade: ");
                scanf("%d", &prioridade);
                printf("Descricao: ");
                scanf("%s", descricao);
                InserirTarefa(&lista, id, descricao, prioridade);
                break;
            }
            case 2: {
                int id;
                printf("ID: ");
                scanf("%d", &id);
                RemoverTarefa(&lista, id);
            }
            case 3: {
                int prioridade;
                printf("Prioridade: ");
                scanf("%d", &prioridade);
                MoverPrioridadeParaInicio(&lista, prioridade);
                break;
            }
            case 4: {
                int idInicio, idFim;
                printf("ID Inicio: ");
                scanf("%d", &idInicio);
                printf("ID Fim: ");
                scanf("%d", &idFim);
                InverterIntervalo(lista, idInicio, idFim);
            }
            case 5: {
                ExibirTarefas(lista);
                break;
            }
            case 6: {
                ok = false;
                break;
            }
            default: {
                printf("Opcao invalida!\n");
            }
        }
    }


    LiberarLista(lista);
    return 0;
}
