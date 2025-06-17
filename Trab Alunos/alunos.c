#include <stdio.h>      // Para entrada e saída padrão
#include <stdlib.h>     // Para malloc, realloc, free
#include <string.h>     // Para manipulação de strings
#include "aluno.h"      // Inclui o cabeçalho com as funções e struct

// Função que cadastra um novo aluno
Aluno* cadastrarAluno(Aluno* lista, int* totalAlunos) {
    // Realoca a lista para caber mais um aluno
    lista = realloc(lista, (*totalAlunos + 1) * sizeof(Aluno));

    if (!lista) { // Verifica se a alocação falhou
        printf("Erro ao alocar memoria!\n");
        exit(1); // Encerra o programa com erro
    }

    // Recebe o nome do aluno (com espaço)
    printf("Nome: ");
    scanf(" %[^\n]", lista[*totalAlunos].nome);

    // Recebe a idade
    printf("Idade: ");
    scanf("%d", &lista[*totalAlunos].idade);

    // Recebe a matrícula
    printf("Matrícula: ");
    scanf("%d", &lista[*totalAlunos].matricula);

    // Incrementa o número total de alunos
    (*totalAlunos)++;

    return lista; // Retorna a lista atualizada
}

// Função para listar todos os alunos
void listarAlunos(Aluno* lista, int totalAlunos) {
    printf("\n--- Alunos cadastrados ---\n");
    for (int i = 0; i < totalAlunos; i++) {
        printf("Nome: %s | Idade: %d | Matricula: %d\n",
               lista[i].nome, lista[i].idade, lista[i].matricula);
    }
}

// Função para buscar um aluno pela matrícula
int buscarAluno(Aluno* lista, int totalAlunos, int matricula) {
    for (int i = 0; i < totalAlunos; i++) {
        if (lista[i].matricula == matricula) {
            // Mostra os dados se encontrado
            printf("Encontrado: %s - Idade: %d\n", lista[i].nome, lista[i].idade);
            return i; // Retorna o índice encontrado
        }
    }
    printf("Aluno nao encontrado.\n");
    return -1; // Retorna -1 se não encontrar
}

// Função que remove um aluno da lista
Aluno* excluirAluno(Aluno* lista, int* totalAlunos, int matricula) {
    int indice = buscarAluno(lista, *totalAlunos, matricula);
    if (indice == -1) return lista; // Não encontrado, retorna lista sem mudanças

    // Desloca todos os elementos para a esquerda
    for (int i = indice; i < *totalAlunos - 1; i++) {
        lista[i] = lista[i + 1];
    }

    (*totalAlunos)--; // Diminui o total

    // Redimensiona a memória para o novo tamanho
    lista = realloc(lista, (*totalAlunos) * sizeof(Aluno));
    return lista; // Retorna a nova lista
}

// Função que salva os alunos em um arquivo texto
void salvarAlunos(Aluno* lista, int totalAlunos, const char* arquivo) {
    FILE* f = fopen(arquivo, "w"); // Abre o arquivo para escrita
    if (!f) {
        printf("Erro ao salvar arquivo.\n");
        return;
    }

    // Escreve os dados no formato CSV
    for (int i = 0; i < totalAlunos; i++) {
        fprintf(f, "%s;%d;%d\n", lista[i].nome, lista[i].idade, lista[i].matricula);
    }

    fclose(f); // Fecha o arquivo
    printf("Alunos salvos com sucesso.\n");
}
