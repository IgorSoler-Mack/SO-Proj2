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
    printf("Careaio");
    if (from.saldo >= valor)
    { // 2
        from.saldo -= valor;
        to.saldo += valor;
    }
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
}


int main()
{
    void *stack;
    pid_t pid;
    int i;
    // Allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0)
    {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
    printf("Transferindo 10 para a conta c2\n");
    valor = 10;
    pthread_t tid[10];
    for (i = 0; i < 10; i++)
    {
        // Call the clone system call to create the child thread
        pthread_create(&tid[i], NULL, transferencia, &i);
        //printf("Teste");
        if (pid == -1)
        {
           perror("clone");
           exit(2);
        }
        //printf("teste");
    }
    int* ptr;
    for (i=0; i < 10; i++){
        pthread_join(tid[i], (void**)&ptr);
    }

    // Free the stack
    //pthread_exit(NULL);
    free(stack);
    printf("Transferências concluídas e memória liberada.\n");
    
    return 0;
}
