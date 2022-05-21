#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>

// 64kB stack
#define FIBER_STACK 1024 * 64
struct c
{
    int saldo;
};

typedef struct c conta;
conta from, to;
int valor;

// The child thread will execute this function
void *transferencia(void *arg)
{
    int tid = *((int *) arg);
    free(arg);

    if (from.saldo >= valor)
    { 
        from.saldo -= valor;
        to.saldo += valor;
        printf("Thread %i realizou uma trasnferência! c1: %d; c2: %d\n", tid, from.saldo, to.saldo);
    }
    else 
    {
        printf("Thread %i possuia saldo insuficiente para transferencia! c1: %d; c2: %d\n", tid, from.saldo, to.saldo);
    }

    //printf("Thread %i executou!, c1: %d; c2: %d\n", tid, from.saldo, to.saldo);
}


int main()
{
    void *stack;
    pid_t pid;
    int i;

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
    printf("Transferindo 10 para a conta c2\n");
    valor = 1;
    int numThreads = 120;
    pthread_t tid[numThreads];
    for (i = 0; i < numThreads; i++)
    {
        int *arg = malloc(sizeof(*arg));
        if ( arg == NULL ) {
            fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
            exit(EXIT_FAILURE);
        }
        *arg = i;
        pthread_create(&tid[i], NULL, transferencia, arg);
        if (pid == -1)
        {
           perror("clone");
           exit(2);
        }
    }
    int* ptr;
    for (i=0; i < numThreads; i++){
        pthread_join(tid[i], (void**)&ptr); 
    }

    //pthread_exit(NULL);
    printf("Transferências concluídas e memória liberada.\n");
    
    return 0;
}
