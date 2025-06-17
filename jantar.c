#include <stdio.h>        // Biblioteca padr�o para entrada e sa�da (printf)
#include <stdlib.h>       // Biblioteca para fun��es como rand()
#include <windows.h>      // Biblioteca necess�ria para threads e sem�foros no Windows

#define N 5 // Define o n�mero de fil�sofos e garfos

// Cria um vetor de sem�foros (um para cada garfo)
HANDLE garfos[N];

// Fun��o que representa o comportamento de cada fil�sofo
DWORD WINAPI filosofo(LPVOID num) {
    int id = *(int*)num;  // Converte o argumento recebido em um n�mero inteiro (ID do fil�sofo)

    while (1) {  // Loop infinito: o fil�sofo vive pensando e comendo
        // Fase de pensamento
        printf("Fil�sofo %d est� pensando.\n", id);
        Sleep(rand() % 3000); // Dorme de 0 a 2999 milissegundos (0-3 segundos)

        // Para evitar deadlock, fil�sofos pares pegam os garfos em uma ordem,
        // enquanto os �mpares pegam na ordem inversa
        if (id % 2 == 0) {
            // Fil�sofo par pega primeiro o garfo � esquerda
            WaitForSingleObject(garfos[id], INFINITE);               // Espera o garfo da esquerda
            WaitForSingleObject(garfos[(id + 1) % N], INFINITE);     // Depois o da direita
        } else {
            // Fil�sofo �mpar pega primeiro o garfo � direita
            WaitForSingleObject(garfos[(id + 1) % N], INFINITE);     // Espera o garfo da direita
            WaitForSingleObject(garfos[id], INFINITE);               // Depois o da esquerda
        }

        // Fase de comer
        printf("Fil�sofo %d est� comendo.\n", id);
        Sleep((rand() % 2000) + 1000); // Dorme entre 1 a 3 segundos (simulando refei��o)

        // Ap�s comer, libera os dois garfos (sem�foros)
        ReleaseSemaphore(garfos[id], 1, NULL);                    // Libera o garfo da esquerda
        ReleaseSemaphore(garfos[(id + 1) % N], 1, NULL);          // Libera o garfo da direita

        printf("Fil�sofo %d largou os garfos.\n", id);
    }

    return 0; // Nunca chega aqui porque o loop � infinito
}

int main() {
    HANDLE threads[N];  // Vetor que armazena os "handles" das threads dos fil�sofos
    int ids[N];         // Vetor que armazena os IDs de cada fil�sofo

    // Inicializa cada sem�foro (representando um garfo)
    for (int i = 0; i < N; i++) {
        garfos[i] = CreateSemaphore(
            NULL,   // Seguran�a padr�o
            1,      // Valor inicial do sem�foro (1 = dispon�vel)
            1,      // Valor m�ximo do sem�foro
            NULL    // Sem nome (sem�foro local)
        );
    }

    // Cria as threads para os fil�sofos
    for (int i = 0; i < N; i++) {
        ids[i] = i; // Define o ID do fil�sofo

        threads[i] = CreateThread(
            NULL,              // Atributos padr�o de seguran�a
            0,                 // Tamanho padr�o da pilha
            filosofo,          // Fun��o que a thread vai executar
            &ids[i],           // Argumento passado para a fun��o (ID do fil�sofo)
            0,                 // Come�a imediatamente
            NULL               // Ignora o ID da thread retornado
        );
    }

    // Aguarda todas as threads terminarem (nunca acontece, pois elas s�o infinitas)
    WaitForMultipleObjects(N, threads, TRUE, INFINITE);

    // Libera os sem�foros (nunca ser� executado aqui, mas � boa pr�tica deixar)
    for (int i = 0; i < N; i++) {
        CloseHandle(garfos[i]);
    }

    return 0; // Fim do programa (teoricamente, nunca alcan�ado)
}
