/*
== TRON ==
O jogo consiste em um duelo de motos, no qual o cenário tem como obstáculos
as paredes e o rastro das motos. Seu objetivo é fazer o oponente bater antes
que você.

Instruções de compilação e outras informações adicionais estão disponíveis
no arquivo README.md

Autores: Augusto Bennemann e Fabrício Mazzola
*/

#include "interface.h"
#include "jogo.h"

int main() {
    //resetaRanking(); //reseta o ranking

    init(); // carrega configurações iniciais da interface

    menuInicial();

    return 0;
}
