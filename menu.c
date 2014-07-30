#include "menu.h"

// Carrega o Menu Inicial, feito com a biblioteca ncurses-menu
void menuInicial(void) {
    // Opções
    int menu_ret = 1;
    char alts[][100] = {{"Novo Jogo"},
        {"Carregar Jogo"},
        {"Ranking"},
        {"Instruções"},
        {"Sair"},
    };

    do {
        printw("  _____                \n");
        printw(" |_   _| __ ___  _ __  \n");
        printw("   | || '__/ _ \\| '_ \\ \n");
        printw("   | || | | (_) | | | |\n");
        printw("   |_||_|  \\___/|_| |_|\n\n");

        printw(" Bem-vindo ao jogo TRON\n\n");
        printw(" O que voce deseja fazer?\n");

        menu_ret = print_menu (0, 27, 5, 20, "TRON", alts, menu_ret);

        switch(menu_ret) {
        case 1: // novo jogo
            iniciaJogo('n');
            break;
        case 2: // carregar jogo
            iniciaJogo('s');
            break;
        case 3: //ranking
            exibeRanking();
            break;
        case 4: // instrucoes
            exibeInstrucoes();
            break;
        }

        erase();
    } while (menu_ret != 5);


    // Ao fechar o jogo
    printw("\n\n\n\n\n\n\n\n\n\n     _    __      ____          _____                                __\n");
    printw("    | |  / /___  / / /____     / ___/___  ____ ___  ____  ________  / /\n");
    printw("    | | / / __ \\/ / __/ _ \\    \\__ \\/ _ \\/ __ `__ \\/ __ \\/ ___/ _ \\/ / \n");
    printw("    | |/ / /_/ / / /_/  __/   ___/ /  __/ / / / / / /_/ / /  /  __/_/  \n");
    printw("    |___/\\____/_/\\__/\\___/   /____/\\___/_/ /_/ /_/ .___/_/   \\___(_)   \n");
    printw("                                                /_/                    \n");
    refresh();

    sleep(2);
    clear();
    endwin();
    exit(0);

}

// Exibe as instruções de jogo no menu inicial
void exibeInstrucoes(void) {

    char tecla;

    do {
        WINDOW *janela;
        janela = newwin(14, 45, 13, 27);
        box(janela, 0, 0);
        mvwaddstr(janela, 2, 3, "INSTRUCOES");
        mvwaddstr(janela, 4, 3, "O jogo TRON consiste num duelo de motos.");
        mvwaddstr(janela, 5, 3, "O cenario tem como obstaculo as paredes");
        mvwaddstr(janela, 6, 3, "e o rastro das motos.");
        mvwaddstr(janela, 7, 3, "Seu objetivo e fazer o oponente bater");
        mvwaddstr(janela, 8, 3, "antes que voce.");
        mvwaddstr(janela, 9, 3, "Use os direcionais para se mover.");
        mvwaddstr(janela, 10, 3, "Bom jogo e boa sorte =D");
        mvwaddstr(janela, 12, 12, "[Tecle X para voltar]");
        wrefresh(janela);
    } while ( (tecla = getch()) && tecla != 'x' );

}


// Exibe Menu Superior durante o jogo
void menuSuperior(void) {

    printw("| Novo Jogo | Pausar/Continuar | Carregar | Salvar | Sair |\n");
    printw("|    (N)    |       (P)        |   (C)    |   (S)  |  (X) |\n");
    printw(" ----------------------------------------------------------\n");

}

