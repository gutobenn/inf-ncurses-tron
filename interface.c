#include "interface.h"

// ajusta tela e realiza configuracoes iniciais da ncurses
void init(void) {

    system("resize -s 27 82 >> /dev/null"); // redimensiona o terminal

    /* http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html#using */
    initscr();
    start_color();
    inicializaCores();
    curs_set(0); // oculta cursor
    noecho(); // para de exibir caracteres assim que digitados
    cbreak(); // um caractere por vez
    timeout(DELAY); // tempo de refresh
    keypad(stdscr, TRUE); // ativa teclas 'especiais' (direcionais inclusive)

}

