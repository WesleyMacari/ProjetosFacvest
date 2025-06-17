#include <stdio.h>        // Biblioteca padrão para entrada e saída (printf)
#include <stdlib.h>       // Biblioteca para funções como rand()
#include <windows.h>      // Biblioteca necessária para threads e semáforos no Windows

#define N 5 // Define o número de filósofos e garfos

// Cria um vetor de semáforos (um para cada garfo)
HANDLE garfos[N];

// Função que representa o comportamento de cada filósofo
DWORD WINAPI filosofo(LPVOID num) {
    int id = *(int*)num;  // Converte o argumento recebido em um número inteiro (ID do filósofo)

    while (1) {  // Loop infinito: o filósofo vive pensando e comendo
        // Fase de pensamento
        printf("Filósofo %d está pensando.\n", id);
        Sleep(rand() % 3000); // Dorme de 0 a 2999 milissegundos (0-3 segundos)

        // Para evitar deadlock, filósofos pares pegam os garfos em uma ordem,
        // enquanto os ímpares pegam na ordem inversa
        if (id % 2 == 0) {
            // Filósofo par pega primeiro o garfo à esquerda
            WaitForSingleObject(garfos[id], INFINITE);               // Espera o garfo da esquerda
            WaitForSingleObject(garfos[(id + 1) % N], INFINITE);     // Depois o da direita
        } else {
            // Filósofo ímpar pega primeiro o garfo à direita
            WaitForSingleObject(garfos[(id + 1) % N], INFINITE);     // Espera o garfo da direita
            WaitForSingleObject(garfos[id], INFINITE);               // Depois o da esquerda
        }

        // Fase de comer
        printf("Filósofo %d está comendo.\n", id);
        Sleep((rand() % 2000) + 1000); // Dorme entre 1 a 3 segundos (simulando refeição)

        // Após comer, libera os dois garfos (semáforos)
        ReleaseSemaphore(garfos[id], 1, NULL);                    // Libera o garfo da esquerda
        ReleaseSemaphore(garfos[(id + 1) % N], 1, NULL);          // Libera o garfo da direita

        printf("Filósofo %d largou os garfos.\n", id);
    }

    return 0; // Nunca chega aqui porque o loop é infinito
}

int main() {
    HANDLE threads[N];  // Vetor que armazena os "handles" das threads dos filósofos
    int ids[N];         // Vetor que armazena os IDs de cada filósofo

    // Inicializa cada semáforo (representando um garfo)
    for (int i = 0; i < N; i++) {
        garfos[i] = CreateSemaphore(
            NULL,   // Segurança padrão
            1,      // Valor inicial do semáforo (1 = disponível)
            1,      // Valor máximo do semáforo
            NULL    // Sem nome (semáforo local)
        );
    }

    // Cria as threads para os filósofos
    for (int i = 0; i < N; i++) {
        ids[i] = i; // Define o ID do filósofo

        threads[i] = CreateThread(
            NULL,              // Atributos padrão de segurança
            0,                 // Tamanho padrão da pilha
            filosofo,          // Função que a thread vai executar
            &ids[i],           // Argumento passado para a função (ID do filósofo)
            0,                 // Começa imediatamente
            NULL               // Ignora o ID da thread retornado
        );
    }

    // Aguarda todas as threads terminarem (nunca acontece, pois elas são infinitas)
    WaitForMultipleObjects(N, threads, TRUE, INFINITE);

    // Libera os semáforos (nunca será executado aqui, mas é boa prática deixar)
    for (int i = 0; i < N; i++) {
        CloseHandle(garfos[i]);
    }

    return 0; // Fim do programa (teoricamente, nunca alcançado)
}
