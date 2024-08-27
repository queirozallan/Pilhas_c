#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Estrutura para um nó da lista encadeada
typedef struct No {
    char dado;
    struct No* proximo;
} No;

// Estrutura para a pilha
typedef struct Pilha {
    No* topo;
} Pilha;

// Função para inicializar a pilha
void inicializar(Pilha* pilha) {
    pilha->topo = NULL;
}

// Função para verificar se a pilha está vazia
bool estaVazia(Pilha* pilha) {
    return pilha->topo == NULL;
}

// Função para empilhar (push) um elemento
void empilhar(Pilha* pilha, char valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

// Função para desempilhar (pop) um elemento
char desempilhar(Pilha* pilha) {
    if (estaVazia(pilha)) {
        printf("Erro: a pilha está vazia\n");
        return '\0';
    }
    No* temp = pilha->topo;
    char valorRemovido = temp->dado;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    return valorRemovido;
}

// Função para consultar o topo da pilha sem remover
char espiarTopo(Pilha* pilha) {
    if (estaVazia(pilha)) {
        printf("Erro: a pilha está vazia\n");
        return '\0';
    }
    return pilha->topo->dado;
}

// Função para verificar se uma palavra ou frase é um palíndromo
bool ePalindromo(char* texto) {
    Pilha pilha;
    inicializar(&pilha);
    
    // Limpa o texto (remove espaços e caracteres não alfanuméricos)
    int tamanho = strlen(texto);
    char textoLimpo[100];
    int j = 0;
    for (int i = 0; i < tamanho; i++) {
        if (isalnum(texto[i])) {
            textoLimpo[j++] = tolower(texto[i]);
        }
    }
    textoLimpo[j] = '\0';

    // Empilha cada caractere
    for (int i = 0; i < j; i++) {
        empilhar(&pilha, textoLimpo[i]);
    }

    // Verifica se é um palíndromo comparando os caracteres empilhados
    for (int i = 0; i < j; i++) {
        if (textoLimpo[i] != desempilhar(&pilha)) {
            return false;
        }
    }

    return true;
}

// Função para converter um número decimal para binário
void converterParaBinario(int numeroDecimal) {
    Pilha pilha;
    inicializar(&pilha);
    
    if (numeroDecimal == 0) {
        printf("0");
        return;
    }

    while (numeroDecimal > 0) {
        int resto = numeroDecimal % 2;
        empilhar(&pilha, resto + '0'); // Armazena o caractere correspondente
        numeroDecimal /= 2;
    }

    // Imprime o número binário
    while (!estaVazia(&pilha)) {
        printf("%c", desempilhar(&pilha));
    }
    printf("\n");
}

// Função para verificar se uma expressão aritmética está balanceada
bool estaBalanceada(char* expressao) {
    Pilha pilha;
    inicializar(&pilha);
    
    for (int i = 0; expressao[i] != '\0'; i++) {
        if (expressao[i] == '(') {
            empilhar(&pilha, '(');
        } else if (expressao[i] == ')') {
            if (estaVazia(&pilha)) {
                return false;
            }
            desempilhar(&pilha);
        }
    }

    return estaVazia(&pilha);
}

// Função principal para testar todas as funcionalidades
int main() {
    // Testes para palíndromo
    printf("Testando palíndromos:\n");
    char texto1[] = "ovo";
    char texto2[] = "subinoonibus";
    char texto3[] = "ana";
    char texto4[] = "palavra";

    printf("%s é palíndromo? %s\n", texto1, ePalindromo(texto1) ? "Sim" : "Não");
    printf("%s é palíndromo? %s\n", texto2, ePalindromo(texto2) ? "Sim" : "Não");
    printf("%s é palíndromo? %s\n", texto3, ePalindromo(texto3) ? "Sim" : "Não");
    printf("%s é palíndromo? %s\n", texto4, ePalindromo(texto4) ? "Sim" : "Não");

    // Testes para conversão decimal para binário
    printf("\nTestando conversão decimal para binário:\n");
    int numeroDecimal = 10;
    printf("Decimal: %d -> Binário: ", numeroDecimal);
    converterParaBinario(numeroDecimal);

    numeroDecimal = 15;
    printf("Decimal: %d -> Binário: ", numeroDecimal);
    converterParaBinario(numeroDecimal);

    numeroDecimal = 0;
    printf("Decimal: %d -> Binário: ", numeroDecimal);
    converterParaBinario(numeroDecimal);

    // Testes para balanceamento de expressões
    printf("\nTestando balanceamento de expressões:\n");
    char expr1[] = "(( ))";
    char expr2[] = "( )( )(( )( ))";
    char expr3[] = "( ) )";
    char expr4[] = ") (";

    printf("%s está balanceada? %s\n", expr1, estaBalanceada(expr1) ? "Sim" : "Não");
    printf("%s está balanceada? %s\n", expr2, estaBalanceada(expr2) ? "Sim" : "Não");
    printf("%s está balanceada? %s\n", expr3, estaBalanceada(expr3) ? "Sim" : "Não");
    printf("%s está balanceada? %s\n", expr4, estaBalanceada(expr4) ? "Sim" : "Não");

    return 0;
}
