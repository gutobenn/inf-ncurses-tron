#ifndef RANKING_H
#define RANKING_H

#include <ncurses.h>
#include <string.h>
#include "player.h"

#define ARQ_RANKING "db/ranking.bin"

void resetaRanking(void);
void exibeRanking(void);
void exibeRankingLateral(void);
void insereRanking(PLAYER *player);

#endif /* RANKING_H */
