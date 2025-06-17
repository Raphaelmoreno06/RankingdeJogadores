#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

typedef struct jogador {
    int id;
    char nome[MAX_NOME];
    int pontuacao;
    struct jogador* prox;
} Jogador;

typedef struct {
    Jogador* inicio;
    Jogador* fim;
    int total;
} ListaDescritor;

// === Pilha ===
Jogador* topoPilha = NULL;

// === Fila ===
Jogador* inicioFila = NULL;
Jogador* fimFila = NULL;

// === Funções de Pilha ===
void push(Jogador* jogador) {
    Jogador* copia = (Jogador*)malloc(sizeof(Jogador));
    *copia = *jogador;
    copia->prox = topoPilha;
    topoPilha = copia;
}

void limparPilha() {
    while (topoPilha != NULL) {
        Jogador* temp = topoPilha;
        topoPilha = topoPilha->prox;
        free(temp);
    }
}

// === Funções de Fila ===
void enfileirar(Jogador* jogador) {
    Jogador* copia = (Jogador*)malloc(sizeof(Jogador));
    *copia = *jogador;
    copia->prox = NULL;
    if (fimFila == NULL) {
        inicioFila = fimFila = copia;
    } else {
        fimFila->prox = copia;
        fimFila = copia;
    }
}

void limparFila() {
    while (inicioFila != NULL) {
        Jogador* temp = inicioFila;
        inicioFila = inicioFila->prox;
        free(temp);
    }
    fimFila = NULL;
}

ListaDescritor* listaGlobal = NULL;

ListaDescritor* criarLista();
Jogador* criarJogador(int id, const char* nome, int pontuacao);
void inserirJogador(ListaDescritor* lista, int id, const char* nome, int pontuacao);
Jogador* buscarPorId(ListaDescritor* lista, int id);
void atualizarPontuacao(ListaDescritor* lista, int id, int novaPontuacao);
void imprimirLista(ListaDescritor* lista);
void ordenarLista(ListaDescritor* lista);
void salvarJogadores(ListaDescritor* lista);
void carregarJogadores(ListaDescritor* lista);
void excluirTabela(ListaDescritor* lista);
void liberarLista(ListaDescritor* lista);


ListaDescritor* criarLista() {
    ListaDescritor* lista = (ListaDescritor*)malloc(sizeof(ListaDescritor));
    lista->inicio = lista->fim = NULL;
    lista->total = 0;
    return lista;
}

Jogador* criarJogador(int id, const char* nome, int pontuacao) {
    Jogador* novo = (Jogador*)malloc(sizeof(Jogador));
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->pontuacao = pontuacao;
    novo->prox = NULL;
    return novo;
}

void inserirJogador(ListaDescritor* lista, int id, const char* nome, int pontuacao) {
    Jogador* novo = criarJogador(id, nome, pontuacao);


    if (lista->inicio == NULL) {
        lista->inicio = lista->fim = novo;
    } else {
        lista->fim->prox = novo;
        lista->fim = novo;
    }
    lista->total++;

    
    push(novo);          
    enfileirar(novo);   

    salvarJogadores(lista);
}

Jogador* buscarPorId(ListaDescritor* lista, int id) {
    Jogador* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->id == id) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void atualizarPontuacao(ListaDescritor* lista, int id, int novaPontuacao) {
    Jogador* jogador = buscarPorId(lista, id);
    if (jogador != NULL) {
        jogador->pontuacao = novaPontuacao;
        printf("Pontuacao atualizada com sucesso.\n");
        salvarJogadores(lista);
    } else {
        printf("Jogador nao encontrado.\n");
    }
}

void imprimirLista(ListaDescritor* lista) {
    if (lista->inicio == NULL) {
        printf("\n--- Nao ha jogadores cadastrados ---\n");
        return;
    }
    Jogador* atual = lista->inicio;
    printf("\n--- Ranking de Jogadores ---\n");
    while (atual != NULL) {
        printf("ID: %d | Nome: %s | Pontuacao: %d\n", atual->id, atual->nome, atual->pontuacao);
        atual = atual->prox;
    }
}

// === Merge Sort ===
Jogador* merge(Jogador* a, Jogador* b) {
    if (!a) return b;
    if (!b) return a;

    Jogador* resultado = NULL;
    if (a->pontuacao > b->pontuacao) {
        resultado = a;
        resultado->prox = merge(a->prox, b);
    } else {
        resultado = b;
        resultado->prox = merge(a, b->prox);
    }
    return resultado;
}

void dividirLista(Jogador* fonte, Jogador** frente, Jogador** tras) {
    Jogador* rapido;
    Jogador* lento;
    if (!fonte || !fonte->prox) {
        *frente = fonte;
        *tras = NULL;
    } else {
        lento = fonte;
        rapido = fonte->prox;
        while (rapido) {
            rapido = rapido->prox;
            if (rapido) {
                lento = lento->prox;
                rapido = rapido->prox;
            }
        }
        *frente = fonte;
        *tras = lento->prox;
        lento->prox = NULL;
    }
}

void mergeSort(Jogador** cabecaRef) {
    Jogador* cabeca = *cabecaRef;
    if (!cabeca || !cabeca->prox) return;

    Jogador* a;
    Jogador* b;
    dividirLista(cabeca, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *cabecaRef = merge(a, b);
}

void ordenarLista(ListaDescritor* lista) {
    mergeSort(&lista->inicio);

    Jogador* atual = lista->inicio;
    while (atual && atual->prox != NULL) {
        atual = atual->prox;
    }
    lista->fim = atual;

    printf("Ranking ordenado!\n");
    salvarJogadores(lista);
}

void salvarJogadores(ListaDescritor* lista) {
    FILE* f = fopen("jogadores.dat", "wb");
    if (f == NULL) {
        printf("Erro ao salvar os jogadores.\n");
        return;
    }

    Jogador* atual = lista->inicio;
    while (atual) {
        fwrite(&(atual->id), sizeof(int), 1, f);
        fwrite(atual->nome, sizeof(char), MAX_NOME, f);
        fwrite(&(atual->pontuacao), sizeof(int), 1, f);
        atual = atual->prox;
    }
    fclose(f);
}

void carregarJogadores(ListaDescritor* lista) {
    FILE* f = fopen("jogadores.dat", "rb");
    if (f == NULL) return;

    int id;
    char nome[MAX_NOME];
    int pontuacao;

    while (fread(&id, sizeof(int), 1, f) == 1) {
        fread(nome, sizeof(char), MAX_NOME, f);
        fread(&pontuacao, sizeof(int), 1, f);
        inserirJogador(lista, id, nome, pontuacao);
    }
    fclose(f);
}

void excluirTabela(ListaDescritor* lista) {
    char confirmacao;
    printf("\nTem certeza que deseja excluir a tabela? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        liberarLista(lista);
        listaGlobal = criarLista();

        limparPilha();
        limparFila();

        remove("jogadores.dat");
        printf("Tabela excluida com sucesso.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
}

void liberarLista(ListaDescritor* lista) {
    Jogador* atual = lista->inicio;
    while (atual) {
        Jogador* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

void menu() {
    printf("\n==== Sistema de Ranking ====\n");
    printf("1. Inserir jogador\n");
    printf("2. Atualizar pontuacao\n");
    printf("3. Exibir ranking\n");
    printf("4. Ordenar por pontuacao\n");
    printf("5. Excluir tabela\n");
    printf("0. Sair\n");
}

int main() {
    listaGlobal = criarLista();
    carregarJogadores(listaGlobal);

    int opcao, id, pontuacao;
    char nome[MAX_NOME];

    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("ID: "); scanf("%d", &id);
                printf("Nome: "); scanf(" %[^\n]", nome);
                printf("Pontuacao: "); scanf("%d", &pontuacao);
                inserirJogador(listaGlobal, id, nome, pontuacao);
                break;
            case 2:
                printf("ID do jogador: "); scanf("%d", &id);
                printf("Nova pontuacao: "); scanf("%d", &pontuacao);
                atualizarPontuacao(listaGlobal, id, pontuacao);
                break;
            case 3:
                imprimirLista(listaGlobal);
                break;
            case 4:
                ordenarLista(listaGlobal);
                break;
            case 5:
                excluirTabela(listaGlobal);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    salvarJogadores(listaGlobal);
    liberarLista(listaGlobal);
    limparPilha();
    limparFila();

    return 0;
}
