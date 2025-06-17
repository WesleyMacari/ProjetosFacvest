#ifndef ALUNO_H // Evita inclus�es m�ltiplas do mesmo cabe�alho
#define ALUNO_H

// Estrutura que representa um aluno
typedef struct {
    char nome[100];   // Nome do aluno
    int idade;        // Idade do aluno
    int matricula;    // N�mero de matr�cula do aluno
} Aluno;

// Declara��o das fun��es utilizadas no programa
Aluno* cadastrarAluno(Aluno* lista, int* totalAlunos);
void listarAlunos(Aluno* lista, int totalAlunos);
int buscarAluno(Aluno* lista, int totalAlunos, int matricula);
Aluno* excluirAluno(Aluno* lista, int* totalAlunos, int matricula);
void salvarAlunos(Aluno* lista, int totalAlunos, const char* arquivo);

#endif

