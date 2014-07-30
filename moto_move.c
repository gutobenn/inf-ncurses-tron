#include "moto_move.h"

enum direcoes { RIGHT = 1, LEFT, UP, DOWN };

//retorna um numero aleatorio de 0 a 10
int geraRandom(void) {
    return mt_seed() % 10;
}

//Varia o valor de X dependendo da direcao escolhida
int varx(int direcao) {
    int x = 0;
    switch(direcao) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    }
    return x;
}

//Varia o valor de Y dependendo da direcao escolhida
int vary(int direcao) {
    int y = 0;
    switch(direcao) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    return y;
}

// Dada uma direção, retorna as possíveis opções de nova direção, considerando um movimento de 90º.
int* opcoes(int direcao) {
    int * opc = malloc(sizeof(int) * 2);

    switch(direcao) {
    case UP:
    case DOWN:
        opc[0] = RIGHT;
        opc[1] = LEFT;
        break;
    case RIGHT:
    case LEFT:
        opc[0] = DOWN;
        opc[1] = UP;
        break;
    }

    return opc;
}

// retorna se há colisão em x,y
int motoColisao(WINDOW *tela, int x, int y) {
    return (x <= 0
            || y <= 0
            || y > ALTURA_MAPA
            || x > LARGURA_MAPA
            || mvwinch(tela, y, x) == (' ' | COLOR_PAIR(COLOR_CYAN))
            || mvwinch(tela, y, x) == (' ' | COLOR_PAIR(COLOR_RED))
            || mvwinch(tela, y, x) == ('J' | COLOR_PAIR(COLOR_CYAN))
            || mvwinch(tela, y, x) == ('I' | COLOR_PAIR(COLOR_RED))
            || mvwinch(tela, y, x) == (' ' | COLOR_PAIR(COLOR_YELLOW)) );
}

// retorna se há empate (colisão entre motos)
int motoEmpate(WINDOW *tela, int x, int y) {
    return (mvwinch(tela, y, x) == ('J' | COLOR_PAIR(COLOR_CYAN))
            || mvwinch(tela, y, x) == ('I' | COLOR_PAIR(COLOR_RED)) );
}


void moveJogador(WINDOW *tela, MOTO *jogador, PLAYER *player) {

    mvwaddch(tela, jogador->c.y, jogador->c.x, ' ' | COLOR_PAIR(jogador->cor) ); // muda ponto anterior de 'J' para '1'

    switch (jogador->direcao) { //dependendo da direcao escolhida, altera a coordenada do jogador
    case UP:
        jogador->c.y--;
        break;
    case DOWN:
        jogador->c.y++;
        break;
    case RIGHT:
        jogador->c.x++;
        break;
    case LEFT:
        jogador->c.x--;
        break;
    default:
        break;
    }

    if (motoColisao (tela, jogador->c.x, jogador->c.y) ) { //se acontecer colisao
        if (motoEmpate (tela, jogador->c.x, jogador->c.y)) // e se acontecer empate
            theEnd('e', player); // mostra empate na tela
        else
            motoPerde (jogador->icone, player);//senao o jogador perde
    }


    mvwaddch(tela, jogador->c.y, jogador->c.x, jogador->icone | COLOR_PAIR(jogador->cor));

    box(tela, 0 , 0);
    wrefresh(tela);

}

// decide que direção a moto inimiga deve seguir. 80% das vezes ela continua na mesma direção
void decideInimigo(WINDOW *tela, MOTO *Inimigo) {

    int k, r;

    k = geraRandom();
    r = geraRandom();

    // se k = 8 ou k = 9, ou seja, 20% das vezes restante, decide uma nova direção
    if ( k == 8 )
        Inimigo->direcao = opcoes(Inimigo->direcao)[0];
    else if ( k == 9 )
        Inimigo->direcao = opcoes(Inimigo->direcao)[1];


    if (motoColisao(tela,(Inimigo->c.x)+varx(Inimigo->direcao),(Inimigo->c.y)+vary(Inimigo->direcao))) {
        if (motoColisao(tela,(Inimigo->c.x)+varx(opcoes(Inimigo->direcao)[0]),(Inimigo->c.y)+vary(opcoes(Inimigo->direcao)[0])))
            Inimigo->direcao = opcoes(Inimigo->direcao)[1];
        else if (motoColisao(tela,(Inimigo->c.x)+varx(opcoes(Inimigo->direcao)[1]),(Inimigo->c.y)+vary(opcoes(Inimigo->direcao)[1])))
            Inimigo->direcao = opcoes(Inimigo->direcao)[0];
        else if(r <= 4)
            Inimigo->direcao = opcoes(Inimigo->direcao)[0];
        else
            Inimigo->direcao = opcoes(Inimigo->direcao)[1];
    }

}


// Ação disparada pela moto que colidiu. Chama o fim do jogo, passando por parâmetro o vencedor.
void motoPerde(char quemcolidiu, PLAYER *player) {
    switch(quemcolidiu) {
    case 'J':
        theEnd('J', player);
        break;
    case 'I':
        insereRanking(player);
        theEnd('I', player);
        break;
    }
}
