#ifndef MAPAS_H
#define MAPAS_H

#include <sys/types.h>
#include <dirent.h>
#include <ncurses.h>
#include "motos.h"

#define ALTURA_MAPA 22
#define LARGURA_MAPA 50
#define MARGEM_LATERAL 0
#define MARGEM_SUPERIOR 3
#define MAPAS_PATH "mapas/"

void inicializaCores(void);
void mapasDisponiveis(WINDOW * tela, int y, int x, char path[]);
void carregaMapa (FILE * arquivo, WINDOW *tela, MOTO *jogador, MOTO *inimigo);

#endif
