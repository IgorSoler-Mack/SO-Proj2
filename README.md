# SO-Proj2 - Concorrencia

### Grupo:
Igor Soler Cavalcanti - 42013550

Paloma de Sousa Bezerra - 32094264

Rafael Miranda Ferreira - 42080932

# Utilização

Como compilar o código no WSL: `gcc -o main  main.c -lpthread`

Como executar o codigo compilado: `./main`

# Funcionamento

Este sistema de transação realiza n transações de R$1,00 até que a quantia necessaria seja transferida.

Cada transação é feita por uma thread diferente, utilizando a lib pthread.

Este sistema foi feito desta forma para maximizar a concorrência e simular um sistema com diversas transferencias simultâneas em uma mesma conta.

Para que a concorrencia não gere nenhuma transação errada, a zona critica (Momento em que as threads interagem com a conta de algum usuario) é limitada a apenas 1 thread por vez. Isso é feito utilizando Mutex. O Mutex é uma trava que permite que apenas 1 thread passe determinado ponto do código por vez, utilizando a função `pthread_mutex_lock()`. Ao atingir o `pthread_mutex_unlock()` repectivo, o mutex lock é destravado e uma proxima thread pode acessar a area.
