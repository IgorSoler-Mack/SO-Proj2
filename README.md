# SO-Proj2 - Concorrencia

### Grupo:
Igor Soler Cavalcanti - 42013550

Paloma de Sousa Bezerra - 32094264

Rafael Miranda Ferreira - 42080932

# Utilização

Como compilar o código no WSL: `gcc -o main  main.c -lpthread`

Como executar o codigo compilado: `./main`

# Explicação

Este sistema de transação realiza n transações de R$1,00 até que a quantia necessaria seja transferida.

Cada transação é feita por uma thread diferente, utilizando a lib pthread.

Este sistema foi feito desta forma para maximizar a concorrência e simular um sistema com diversas transferencias simultâneas em uma mesma conta.

Para que a concorrencia não gere nenhuma transação errada, a zona critica (Momento em que as threads interagem com a conta de algum usuario) é limitada a apenas 1 thread por vez. Isso é feito utilizando Mutex. O Mutex é uma trava que permite que apenas 1 thread passe determinado ponto do código por vez, utilizando a função `pthread_mutex_lock()`. Ao atingir o `pthread_mutex_unlock()` repectivo, o mutex lock é destravado e uma proxima thread pode acessar a area.

# Funcionamento


Código compilando sem erros

![](https://github.com/IgorSoler-Mack/SO-Proj2/blob/2ce5dfc40deae5e04b0818c00b3dc66dc1ff9063/img/compilando.png)

Transferindo 1000 de Conta2 para Conta1


![](https://github.com/IgorSoler-Mack/SO-Proj2/blob/2ce5dfc40deae5e04b0818c00b3dc66dc1ff9063/img/1000%20de%202%20para%201.png)

Resultado desta 1º transação

![](https://github.com/IgorSoler-Mack/SO-Proj2/blob/2ce5dfc40deae5e04b0818c00b3dc66dc1ff9063/img/Resultado.png)

Transferindo 9000 de Conta1 para Conta2

![](https://github.com/IgorSoler-Mack/SO-Proj2/blob/2ce5dfc40deae5e04b0818c00b3dc66dc1ff9063/img/9000%20de%201%20para%202.png)

Resultado desta 2º transação

![](https://github.com/IgorSoler-Mack/SO-Proj2/blob/2ce5dfc40deae5e04b0818c00b3dc66dc1ff9063/img/Resultado2.png)

Transferindo 2001 de Conta1 para Conta2 (Note que esta transação é de um valor maior que o armazenado na Conta1)

![](https://github.com/IgorSoler-Mack/SO-Proj2/blob/2ce5dfc40deae5e04b0818c00b3dc66dc1ff9063/img/2003%20de%201%20para%202.png)

Resultado desta 3º transação

![](https://github.com/IgorSoler-Mack/SO-Proj2/blob/2ce5dfc40deae5e04b0818c00b3dc66dc1ff9063/img/Resultado3.png)
