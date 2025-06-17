#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define PENSANDO 0
#define FAMINTO  1
#define COMENDO  2

int NumeroDeFilosofos;
int tempoComendo, tempoPensando;

// Mutex global (similar ao sem_t mutex)
HANDLE mutex;

// Um semáforo por filósofo
HANDLE sem_fil[100];

// Estado de cada filósofo
int estado[100];

// Thread handle por filósofo
HANDLE threads[100];

// Prototipação de funções
DWORD WINAPI filosofo(LPVOID param);
void mostrar();
void pegarGarfo(int i);
void devolverGarfo(int i);
void intencao(int i);
void pensar();
void comer();
int calcularEsquerda(int i);
int calcularDireita(int i);
int calcularTempoMedio(int tempo);
void iniciar();
void esperarThreads();

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    printf("Informe o numero de filosofos: ");
    scanf("%d", &NumeroDeFilosofos);

    printf("Informe o tempo medio que cada filosofo gastara comendo (em milissegundos): ");
    scanf("%d", &tempoComendo);

    printf("Informe o tempo mdio que cada filosofo gastara pensando (em milissegundos): ");
    scanf("%d", &tempoPensando);

    iniciar();          // Inicializa os semáforos e estados
    esperarThreads();   // Aguarda as threads rodarem (infinito)

    return 0;
}

// Função que inicializa os semáforos e cria threads
void iniciar() {
    // Inicia o mutex principal
    mutex = CreateMutex(NULL, FALSE, NULL);

    // Inicializa o estado dos filósofos
    for (int i = 0; i < NumeroDeFilosofos; i++) {
        estado[i] = PENSANDO;
        sem_fil[i] = CreateSemaphore(NULL, 0, 1, NULL); // Inicializa com 0
    }

    mostrar(); // Mostra estados iniciais

    // Cria uma thread para cada filósofo
    for (int i = 0; i < NumeroDeFilosofos; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        threads[i] = CreateThread(NULL, 0, filosofo, id, 0, NULL);
    }
}

// Aguarda as threads (mas nunca termina pois são laços infinitos)
void esperarThreads() {
    WaitForMultipleObjects(NumeroDeFilosofos, threads, TRUE, INFINITE);
}

// Thread de cada filósofo
DWORD WINAPI filosofo(LPVOID param) {
    int i = *(int*)param;
    free(param);

    while (1) {
        pensar();
        pegarGarfo(i);
        comer();
        devolverGarfo(i);
    }
    return 0;
}

// Mostra o estado atual dos filósofos
void mostrar() {
    for (int i = 0; i < NumeroDeFilosofos; i++) {
        if (estado[i] == PENSANDO)
            printf("Filosofo %d esta pensando...\n", i + 1);
        else if (estado[i] == FAMINTO)
            printf("Filosofo %d esta com fome...\n", i + 1);
        else if (estado[i] == COMENDO)
            printf("Filosofo %d esta comendo!\n", i + 1);
    }
    printf("\n");
}

// Calcula o índice do filósofo à esquerda
int calcularEsquerda(int i) {
    return (i + NumeroDeFilosofos - 1) % NumeroDeFilosofos;
}

// Calcula o índice do filósofo à direita
int calcularDireita(int i) {
    return (i + 1) % NumeroDeFilosofos;
}

// Gera tempo aleatório baseado na entrada (em ms)
int calcularTempoMedio(int tempo) {
    return rand() % (tempo + 1);
}

// Simula tempo pensando
void pensar() {
    Sleep(calcularTempoMedio(tempoPensando));
}

// Simula tempo comendo
void comer() {
    Sleep(calcularTempoMedio(tempoComendo));
}

// Tenta pegar os garfos
void pegarGarfo(int i) {
    WaitForSingleObject(mutex, INFINITE); // Trava região crítica
    estado[i] = FAMINTO;
    mostrar();
    intencao(i);
    ReleaseMutex(mutex);                 // Libera região crítica
    WaitForSingleObject(sem_fil[i], INFINITE); // Espera até poder comer
}

// Devolve os garfos
void devolverGarfo(int i) {
    int esq = calcularEsquerda(i);
    int dir = calcularDireita(i);

    WaitForSingleObject(mutex, INFINITE);
    estado[i] = PENSANDO;
    mostrar();
    intencao(esq); // Verifica se vizinhos podem comer
    intencao(dir);
    ReleaseMutex(mutex);
}

// Verifica se filósofo pode comer
void intencao(int i) {
    int esq = calcularEsquerda(i);
    int dir = calcularDireita(i);

    if (estado[i] == FAMINTO &&
        estado[esq] != COMENDO &&
        estado[dir] != COMENDO) {

        estado[i] = COMENDO;
        mostrar();
        ReleaseSemaphore(sem_fil[i], 1, NULL); // Libera para comer
    }
}
