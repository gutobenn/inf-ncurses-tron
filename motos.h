#ifndef MOTOS_H
#define MOTOS_H

typedef struct {
    int x;
    int y;
} COORDENADA;

typedef struct {
    COORDENADA c;
    int direcao;
    int cor;
    char icone;
} MOTO;


#endif /* MOTOS_H */
