/*TRABALHO PRÁTICO 3 - GRUPO 2
Alunos: Cauan Matias de Oliveira - Mat(2025200002) e Daniel Valinho de Souza - Mat(2025200009)
*/

#include <stdio.h>
#include <stdlib.h>
#define TAM 3
#define HIST 5

// Estrutura para guardar uma partida finalizada
typedef struct {
    char tab[TAM][TAM]; // estado final do tabuleiro
    char res;           // resultado: X, O ou E
} Partida;

// Histórico das últimas partidas
Partida hist[HIST];
int qtd = 0;

// ===== Funções do Tabuleiro =====
// Preenche o tabuleiro com espaços vazios
void limpar(char t[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) 
        for (int j = 0; j < TAM; j++) 
            t[i][j] = ' ';
}

// Mostra o tabuleiro na tela
void mostrar(char t[TAM][TAM]) {
    printf("\n   1   2   3\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", i+1);
        for (int j = 0; j < TAM; j++) {
            printf(" %c ", t[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  ---+---+---\n");
    }
}

// Verifica se o tabuleiro está cheio
int cheio(char t[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (t[i][j] == ' ')
                return 0;
    return 1;
}

// Verifica se existe um vencedor 
char vencedor(char t[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        if (t[i][0] != ' ' && t[i][0] == t[i][1] && t[i][1] == t[i][2])
            return t[i][0];
        if (t[0][i] != ' ' && t[0][i] == t[1][i] && t[1][i] == t[2][i])
            return t[0][i];
    }
    if (t[0][0] != ' ' && t[0][0] == t[1][1] && t[1][1] == t[2][2])
        return t[0][0];
    if (t[0][2] != ' ' && t[0][2] == t[1][1] && t[1][1] == t[2][0])
        return t[0][2];
    
    return ' ';
}

// ------- INTELIGÊNCIA DO COMPUTADOR -------

// Algoritmo Minimax para avaliar jogadas
int minimax(char t[TAM][TAM], int prof, int max) {
    char v = vencedor(t);

    if (v == 'O') return 10 - prof;
    if (v == 'X') return prof - 10;
    if (cheio(t)) return 0;
    
    int melhor = max ? -1000 : 1000;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (t[i][j] == ' ') {
                t[i][j] = max ? 'O' : 'X';
                int val = minimax(t, prof+1, !max);
                t[i][j] = ' ';

                if (max && val > melhor) melhor = val;
                if (!max && val < melhor) melhor = val;
            }
        }
    }
    return melhor;
}

// Escolhe a melhor jogada possível para o computador 
void jogadaPC(char t[TAM][TAM]) {
    int melhor = -1000, li = 0, co = 0;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (t[i][j] == ' ') {
                t[i][j] = 'O';
                int val = minimax(t, 0, 0);
                t[i][j] = ' ';
                if (val > melhor) {
                    melhor = val;
                    li = i;
                    co = j;
                }
            }
        }
    }
    t[li][co] = 'O';
}

// ------- HISTÓRICO -------
// Salva a partida no histórico
void salvar(char t[TAM][TAM], char r) {
    if (qtd < HIST) {
        hist[qtd].res = r;
        for (int i = 0; i < TAM; i++) 
            for (int j = 0; j < TAM; j++)
                hist[qtd].tab[i][j] = t[i][j];
        qtd++;
    } else {
        for (int i = 1; i < HIST; i++) 
            hist[i - 1] = hist[i];

        hist[HIST - 1].res = r;
        for (int i = 0; i < TAM; i++)
            for (int j = 0; j < TAM; j++)
                hist[HIST - 1].tab[i][j] = t[i][j];    
    }
}

// Mostra todas as partidas armazenadas
void mostrarHist() {
    printf("\n=== HISTÓRICO ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nPartida %d - ", i + 1);
        if (hist[i].res == 'O') printf("O Computador Venceu\n");
        else if (hist[i].res == 'X') printf("O Jogador Venceu\n");
        else printf("Empate\n");
        mostrar(hist[i].tab);
    }
}
// ------ FUNÇÃO PRINCIPAL ------

int main() {
    char tab[TAM][TAM];
    int l, c, humano;
    char resp;

    // Define quem começa o jogo
    printf("Quem começa? (1-Jogador 2-Computador): ");
    scanf("%d", &humano);
    humano = (humano == 1);

    // Laço para jogar várias partidas
    do {
        limpar(tab);

        while (1) {
            mostrar(tab);

            if (humano) {
                printf("Linha e coluna (1 a 3): ");
                scanf("%d %d", &l, &c);
                l--; c--;
                // avalia se a jogada desejada é válida
                if (l < 0 || l > 2 || c < 0 || c > 2) {
                    printf("Jogada inválida: fora do tabuleiro.\n");
                    continue;
                }
                if (tab[l][c] != ' ') {
                    printf("Jogada inválida: posição ocupada.\n");
                    continue;
                }
                tab[l][c] = 'X';
            } else {
                jogadaPC(tab);
            }

            char v = vencedor(tab);
            if (v != ' ') {
                mostrar(tab);
                printf(v == 'O' ? "Computador venceu!\n" : "Jogador venceu!\n");
                salvar(tab, v);
                break;
            }

            if (cheio(tab)) {
                mostrar(tab);
                printf("Empate!\n");
                salvar(tab, 'E');
                break;
            }

            humano = !humano;
        }
        //pergunta ao usuario se deseja começar uma nova partida
        printf("Jogar novamente? (s/n): ");
        scanf(" %c", &resp);

    } while (resp == 's' || resp == 'S');

    mostrarHist();
    return 0;
}