#ifndef MOTOS_MOVE_H
#define MOTOS_MOVE_H

#include <ncurses.h>
#include <stdlib.h>
#include "jogo.h"
#include "player.h"
#include "mapas.h"
#include "motos.h"
#include "ranking.h"
#include "mtwist.h" // biblioteca usada para random

int geraRandom(void);
int varx(int direcao);
int vary(int direcao);
int* opcoes(int direcao);
int motoEmpate(WINDOW *tela, int x, int y);
int motoColisao(WINDOW *tela, int x, int y);
void moveJogador(WINDOW *tela, MOTO *jogador, PLAYER *player);
void motoPerde(char quemcolidiu, PLAYER *player);
void decideInimigo(WINDOW *tela, MOTO *Inimigo);

#endif /* MOTOS_MOVE_H */
