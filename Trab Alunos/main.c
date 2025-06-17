#include <stdio.h>      // Entrada e saída
#include <stdlib.h>     // Alocação dinâmica
#include "aluno.h"      // Interface da biblioteca

int main() {
    Aluno* lista = NULL;      // Ponteiro para a lista de alunos
    int totalAlunos = 0;      // Contador de alunos cadastrados
    int opcao, matricula;     // Variáveis para menu e busca

    // Menu principal
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Buscar por matricula\n");
        printf("3. Listar alunos\n");
        printf("4. Excluir aluno\n");
        printf("5. Sair e salvar\n");
        printf("Opcao: ");
        scanf("%d", &opcao); // Lê a opção do usuário

        switch (opcao) {
            case 1:
                lista = cadastrarAluno(lista, &totalAlunos); // Chama a função para cadastrar
                break;
            case 2:
                printf("Digite a matricula: ");
                scanf("%d", &matricula);
                buscarAluno(lista, totalAlunos, matricula); // Chama a função de busca
                break;
            case 3:
                listarAlunos(lista, totalAlunos); // Exibe todos os alunos
                break;
            case 4:
                printf("Digite a matricula a excluir: ");
                scanf("%d", &matricula);
                lista = excluirAluno(lista, &totalAlunos, matricula); // Remove aluno
                break;
            case 5:
                salvarAlunos(lista, totalAlunos, "alunos.txt"); // Salva no arquivo
                break;
            default:
                printf("Opcaoo invalida.\n");
        }
    } while (opcao != 5); // Encerra quando a opção for 5

    free(lista); // Libera a memória alocada
    return 0;
}
