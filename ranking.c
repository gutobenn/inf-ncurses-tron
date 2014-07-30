#include "ranking.h"
/*
Funções de manipulação do ranking, que fica salvo em
db/ranking.bin e contém 5 PLAYER
*/

// Reseta ranking com dados falsos
void resetaRanking(void) {
    FILE *arq;
    PLAYER jogadores[5];
    int i;

    // cria jogadores e insere suas pontuações no vetor
    for (i = 0; i < 5; i++) {
        jogadores[i].tempo = (i+1)*7;
    }

    strcpy(jogadores[0].nome, "Janaina");
    strcpy(jogadores[1].nome, "Arnaldo");
    strcpy(jogadores[2].nome, "Eddie");
    strcpy(jogadores[3].nome, "Clara");
    strcpy(jogadores[4].nome, "Alex");

    // salva no arquivo
    if ((arq = fopen(ARQ_RANKING, "wb")) == NULL) {
        printf("Erro ao criar ranking\n\n");
    } else {
        fwrite(&jogadores, sizeof(PLAYER), 5, arq);
        fclose(arq);
    }
}


// Exibe o ranking no menu inicial do jogo
void exibeRanking(void) {
    char tecla;

    do {
        WINDOW *janela;
        janela = newwin(13, 32, 13, 27);
        box(janela, 0, 0);
        mvwaddstr(janela, 2, 3, "RANKING");

        FILE* arq;
        if ((arq = fopen(ARQ_RANKING, "rb")) == NULL) {
            mvwaddstr(janela, 4, 3, "Erro ao carregar!");
        } else {
            PLAYER jogador;
            int i = 0;
            for(i = 1; i <= 5; i++) {
                fread(&jogador, sizeof(PLAYER), 1, arq);
                mvwprintw(janela, i+3, 3, "%d. %-19s %ds", i, jogador.nome, jogador.tempo );
            }
            mvwaddstr(janela, 10, 5, "[Tecle X para voltar]");

            fclose(arq);
        }
        wrefresh(janela);
    } while ( (tecla = getch()) && tecla != 'x' );

}


// Exibe o ranking na lateral direita do jogo
void exibeRankingLateral(void) {

    mvprintw(7, 53, "RANKING");

    FILE* arq;
    if ((arq = fopen(ARQ_RANKING, "rb")) == NULL) {
        mvprintw(8, 53, "Erro ao carregar");
    } else {
        PLAYER jogador;
        int i = 0;
        for(i = 1; i <= 5; i++) {
            fread(&jogador, sizeof(PLAYER), 1, arq);
            mvprintw(i+7, 53, "%d. %-19s %ds", i, jogador.nome, jogador.tempo );
        }

        fclose(arq);
    }
}

// Insere um player no ranking caso ele tenha ficado entre os 5 melhores jogadores
void insereRanking(PLAYER *player) {
    int i, j, novapos = 0;
    FILE *arq, *arq2;
    PLAYER jogadores[5];

    if ((arq = fopen(ARQ_RANKING, "rb")) == NULL) { // abre arquivo para leitura
        printw("Erro ao carregar ranking");
    } else {
        fread(&jogadores, sizeof(PLAYER), 5, arq); // carrega o vetor 'jogadores' com 5 players
        fclose(arq);

        if ((arq2 = fopen(ARQ_RANKING, "wb")) == NULL) { // cria arquivo para escrita
            printw("Erro ao abrir ranking");
        } else {

            if (player->tempo < jogadores[4].tempo) {
                // se a pontuação do jogador é maior que o último do ranking, ele deve entrar no ranking
                while (player->tempo > jogadores[novapos].tempo) novapos++; // encontra a posição que o jogador deve assumir no ranking

                // reordena o ranking, movendo todos os seguintes uma posição abaixo
                for(j = 4; j > novapos; j--) {
                    jogadores[j].tempo = jogadores[j-1].tempo;
                    strcpy(jogadores[j].nome, jogadores[j-1].nome);
                }
                jogadores[novapos].tempo = player->tempo;
                strcpy(jogadores[novapos].nome, player->nome);

                // exibe uma mensagem de sucesso, parabenizando o jogador por sua conquista
                char tecla;
                do {
                    WINDOW *janela;
                    janela = newwin(15, 45, 7, 3);
                    box(janela, 0, 0);
                    mvwaddstr(janela, 2, 3, "PARABENS!");
                    mvwaddstr(janela, 4, 3, "Você agora faz parte do ranking!");
                    for(i = 0; i < 5; i++) {
                        mvwprintw(janela, i+5, 3, "%d. %-19s %ds", i+1, jogadores[i].nome, jogadores[i].tempo );
                    }
                    mvwaddstr(janela, 11, 3, "[Tecle X para sair]");
                    wrefresh(janela);
                } while ( (tecla = getch()) && tecla != 'x' );
            }

            fwrite(&jogadores, sizeof(PLAYER), 5, arq2);  // salva novo ranking

            fclose(arq2);
        }
    }
}
