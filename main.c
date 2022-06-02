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
conta *from, *to; // Ponteiros usados nas transacoes
int valor; // Valor transferido por thread em cada transacao
pthread_mutex_t mutex; // Mutex usado para tratar a concorrencia
int terminou = 0; // Flag usada no While do Menu

// Funcao que cada thread ira executar
void *transferencia(void *arg)
{
    int tid = *((int *) arg); // Pega o Thread ID
    free(arg); // Libera memoria usada pelos arguments da funcao

    // A thread passa apenas se o mutex nao estiver travado
    // Trava o mutex imediatamente depois de passar
    pthread_mutex_lock(&mutex); 
    if (from->saldo >= valor){  // A transacao ocorre apenas se a conta "from" tiver saldo
        from->saldo -= valor;   // O valor e removido da conta "from"
        to->saldo += valor;     // e transferido para a conta "to"
        printf("Thread %i realizou uma trasnferência! Conta1: %d; Conta2: %d\n", tid, from->saldo, to->saldo);
    }
    else {
        printf("Thread %i Saldo insuficiente Conta1: %d; Conta2: %d\n", tid, from->saldo, to->saldo);
    }
    pthread_mutex_unlock(&mutex); // Libera o mutex, assim permitindo que outra thread entre

}

// Programa Principal
int main()
{
    pid_t pid;
    int i;  
    
    // Todas as contas começam com saldo 10000
    c1.saldo = 10000; // Saldo Inicial da conta2
    c2.saldo = 10000; // Saldo Inicial da conta1
    valor = 1; // Valor a ser transferido por cada thread
    int numThreads; // Limite maximo de Threads
    int conta_selecionada; 

    pthread_mutex_init(&mutex, NULL); // Inicializa o Mutex
    
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

        // Seleciona qual conta recebe e qual transfere
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

        // Cria todas as threads necessarias
        for (i = 0; i < numThreads; i++)
        {
            int *arg = malloc(sizeof(*arg));
            if ( arg == NULL ) {
                fprintf(stderr, "Não foi possível alocar memória para o arg\n");
                exit(EXIT_FAILURE);
            }
            *arg = i;
            pthread_create(&tid[i], NULL, transferencia, arg);
            if (pid == -1)
            {
                printf("Erro ao criar a thread!");
                exit(2);
            }
        }

        int* ptr;
        // Espera cada thread finalizar
        for (i=0; i < numThreads; i++){
            pthread_join(tid[i], (void**)&ptr); //Aguarda que todas as threads finalizem antes de continuar
        }
        printf("\nTransferências concluídas e memória liberada.\n\n");
    }
    pthread_mutex_destroy(&mutex); // Destroi o Mutex
    return 0;
}
