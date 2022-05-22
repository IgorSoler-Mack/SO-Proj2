#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>

struct c
{
    int saldo;
};

typedef struct c conta;
conta from, to;
int valor;
pthread_mutex_t mutex;

// The child thread will execute this function
void *transferencia(void *arg)
{
    int tid = *((int *) arg);
    free(arg);

    pthread_mutex_lock(&mutex);
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
    pthread_mutex_unlock(&mutex);
}


int main()
{
    void *stack;
    pid_t pid;
    int i;  
    
    // Todas as contas começam com saldo 100
    from.saldo = 10000;
    to.saldo = 10000;
    valor = 1;
    int numThreads = 10000;
    pthread_t tid[numThreads];
    pthread_mutex_init(&mutex, NULL);

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

    pthread_mutex_destroy(&mutex);
    printf("Transferências concluídas e memória liberada.\n");
    
    return 0;
}
