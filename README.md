# Trabalho Pratico 03 - Grupo 2
Este projeto implementa um jogo da velha (3x3) em linguagem C, jogado no terminal, no qual um jogador humano enfrenta o computador.  
O computador utiliza o algoritmo Minimax, tornando-o invencível, ou seja, o jogador humano nunca conseguirá vencer caso o computador jogue de forma ideal.

Além disso, o sistema armazena o histórico das últimas 5 partidas, exibindo ao final do programa o estado final de cada jogo e seu respectivo resultado (vitória do jogador, vitória do computador ou empate).



## Autores

- Cauan Matias de Oliveira 
- Daniel Valinho de Souza 

## Estratégia Utilizada pelo Computador
O computador utiliza o algoritmo **Minimax**, uma técnica clássica de tomada de decisão usada em jogos de turno com informação completa.

A lógica funciona da seguinte forma:
- O computador joga com o símbolo **'O'** e tenta maximizar sua pontuação.
- O jogador humano joga com **'X'** e tenta minimizar a pontuação do computador.
- Cada estado final do jogo recebe uma pontuação:
  - **+10** → vitória do computador  
  - **-10** → vitória do jogador  
  - **0** → empate  

O algoritmo simula todas as jogadas possíveis recursivamente até o final do jogo, escolhendo sempre a jogada que leva ao melhor resultado possível para o computador.  
A profundidade da jogada é considerada para priorizar vitórias mais rápidas e derrotas mais demoradas.


## Instruções de Compilação e Execução 
Para compilar o programa, utilize um compilador C (como o GCC).  
No terminal, execute o seguinte comando:

```bash
gcc "Jogo da Velha V3.c" -o jogo_da_velha

Após a compilação, execute o programa com o comando:

./jogo_da_velha
