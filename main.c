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

conta c1, c2;     // Contas 
conta *from, *to; // Ponteiro usando nas transacoes
int valor; // Valor transferido por thread em cada transacao
pthread_mutex_t mutex; // Mutex usado para tratar a concorrencia
int terminou = 0; // Flag usada no While do Menu

// Funcao que cada thread ira executar
void *transferencia(void *arg)
{
    int tid = *((int *) arg); // Pega o Thread ID
    free(arg); // Libera memoria usada pelos arguments da funcao

    pthread_mutex_lock(&mutex); // A thread passa apenas se o mutex nao estiver travado
    if (from->saldo >= valor){  // A transacao ocorre apenas se a conta "from" tiver saldo
        from->saldo -= valor;   // O valor e removido da conta "from"
        to->saldo += valor;     // e transferido para a conta "to"
        printf("Thread %i realizou uma trasnferência! Conta1: %d; Conta2: %d\n", tid, from->saldo, to->saldo);
    }
    else {
        printf("Thread %i Saldo insuficiente Conta1: %d; Conta2: %d\n", tid, from->saldo, to->saldo);
    }
    pthread_mutex_unlock(&mutex);

}

// Programa Principal
int main()
{
    pid_t pid;
    int i;  
    
    // Todas as contas começam com saldo 10000
    c1.saldo = 10000;
    c2.saldo = 10000;
    valor = 1; // Valor a ser transferido de uma conta para outra
    int numThreads; // Limite maximo de Threads
    
    pthread_mutex_init(&mutex, NULL);
    int conta_selecionada;

    while(!terminou){
        // Selecao de valor da transferencia
        printf("Saldo:\n");
        printf("Conta1: R$%d.00\n", c1.saldo);
        printf("Conta2: R$%d.00\n", c2.saldo);
        printf("\nQuanto deseja transferir? (int > 0)\n");
        printf("> ");
        scanf("%i", &numThreads);
        pthread_t tid[numThreads];
        // Selecao de transferencia
        printf("\nDeseja fazer a transferencia de que conta (from)? (0, 1 ou 2)\n");
        printf("0 - Sair do Programa\n");
        printf("1 - Conta1\n");
        printf("2 - Conta2\n");
        printf("> ");
        scanf("%i", &conta_selecionada);

        if(conta_selecionada == 0){
            break;
        }
        else if(conta_selecionada == 1){
            from = &c1;
            to = &c2;
        }
        else {
            from = &c2;
            to = &c1;
        }
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
        printf("\nTransferências concluídas e memória liberada.\n\n");
    }
    return 0;
}
