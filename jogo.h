#ifndef JOGO_H
#define JOGO_H

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "motos.h"
#include "interface.h"
#include "menu.h"
#include "moto_move.h"
#include "player.h"
#include "ranking.h"

#define SAVEGAME_PATH "savegames/"

void Jogo(WINDOW *tela, PLAYER *player1, MOTO *Jogador, MOTO *Inimigo);
void theEnd(char quemcolidiu, PLAYER *player);
void novoJogo(PLAYER *player);
void pedeMapa(char mapa[], char escolha);
void inicializaJogoNovo(WINDOW *tela, MOTO *jogador, MOTO *inimigo);
void inicializaJogoSalvo(WINDOW *tela, MOTO *jogador, MOTO *inimigo, PLAYER *player);
void iniciaJogo(char escolha);
void encerraJogo(PLAYER *player);
int arquivoExiste(char caminho[]);
void salvaJogo(WINDOW *tela, PLAYER *player, MOTO *inimigo, MOTO *jogador);

#endif
