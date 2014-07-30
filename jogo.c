#include "jogo.h"

// contem configurações inicias do jogo: tela, player...
void iniciaJogo(char escolha) {
    MOTO Jogador, Inimigo;
    PLAYER player1;
    Jogador.icone = 'J';
    Inimigo.icone = 'I';
    player1.tempo = 0;

    WINDOW * tela;
    tela = newwin(ALTURA_MAPA+2, LARGURA_MAPA+2, MARGEM_SUPERIOR, MARGEM_LATERAL);


    switch(escolha) { // vê se é jogo novo ou salvo que o jogador quer iniciar
    case 'n':
        novoJogo(&player1);
        inicializaJogoNovo(tela, &Jogador, &Inimigo);
        break;
    case 's':
        inicializaJogoSalvo(tela, &Jogador, &Inimigo, &player1);
        break;
    }

    Jogo(tela, &player1, &Jogador, &Inimigo);
}


// contem toda parte de movimentação do jogo
void Jogo(WINDOW *tela, PLAYER *player1, MOTO *Jogador, MOTO *Inimigo) {

    int mov;
    time_t horainicio = time(NULL) - player1->tempo, tempopausado = 0; //
    enum direcoes { RIGHT = 1, LEFT, UP, DOWN }; //define as direcoes com 1, 2, 3, 4

    clear();
    menuSuperior();
    refresh();

    while ( (mov = getch()) ) { // x para sair do jogo
        attron(A_BOLD);
        mvprintw(4, 53, "Jogador: %s", player1->nome);//mostra nome do jogador na tela lateral
        mvprintw(5, 53, "Tempo decorrido: %ds", time(NULL) - horainicio);//mostra tempo na lateral
        exibeRankingLateral();
        attroff(A_BOLD);
        // Teclas de 'atalho'
        switch (mov) {
        case 'n':
            iniciaJogo('n');
            break;
        case 'p': // pausa o jogo
            tempopausado = time(NULL);//tempo pausa
            do {
                WINDOW *pausado;
                pausado = newwin(6, 27, 12, 13);
                box(pausado, 0, 0);
                mvwaddstr(pausado, 2, 3, "JOGO PAUSADO");
                mvwaddstr(pausado, 3, 3, "[Tecle P para voltar]");
                wrefresh(pausado);
                mov = getch();
            } while (mov != 'p');
            tempopausado = tempopausado - time(NULL);//tempo recomeca
            horainicio = horainicio - tempopausado;
            tempopausado = 0;
            break;
        case 's': // salva o jogo
            tempopausado = time(NULL);//pausa tempo
            player1->tempo = time(NULL) - horainicio; // associa o tempo ao jogador
            salvaJogo(tela, player1, Inimigo, Jogador);
            tempopausado = tempopausado - time(NULL);
            horainicio = horainicio - tempopausado; // recomeca o tempo
            tempopausado = 0;
            break;
        case 'c': // carrega um jogo
            iniciaJogo('s');
            break;
        case 'x':
            encerraJogo(player1);
            break;
        default:

            decideInimigo(tela, Inimigo);

            if(mov != ERR) { // o getch() retorna ERR em caso de erro ou OK em caso de sucesso
                switch(mov) {
                case KEY_UP:
                    if(Jogador->direcao != DOWN) Jogador->direcao = UP;
                    break;
                case KEY_DOWN:
                    if(Jogador->direcao != UP) Jogador->direcao = DOWN;
                    break;
                case KEY_RIGHT:
                    if(Jogador->direcao != LEFT) Jogador->direcao = RIGHT;
                    break;
                case KEY_LEFT:
                    if(Jogador->direcao != RIGHT) Jogador->direcao = LEFT;
                    break;
                default:
                    break;
                }
            }

            player1->tempo = time(NULL) - horainicio;

            moveJogador(tela, Jogador, player1); //chama a moveJogador pro Jogador
            moveJogador(tela, Inimigo, player1); //chama a moveJogador pro Inimigo

            break;
        }
    }
}


// Encerra o jogo e, antes disso, exibe uma mensagem de finalização de acordo com a entrada recebida
void theEnd(char quemcolidiu, PLAYER *player) {

    clear();

    switch(quemcolidiu) {
    // Fonte usada: slant    - http://www.network-science.de/ascii/
    case 'I': // Inimigo colidiu, ou seja, Jogador ganhou
        // exibe Você Ganhou
        printw("\n\n\n\n\n\n\n\n\n\n         _    __                   _    __                           __\n");
        printw("        | |  / /___  ________     | |  / /__  ____  ________  __  __/ /\n");
        printw("        | | / / __ \\/ ___/ _ \\    | | / / _ \\/ __ \\/ ___/ _ \\/ / / / / \n");
        printw("        | |/ / /_/ / /__/  __/    | |/ /  __/ / / / /__/  __/ /_/ /_/  \n");
        printw("        |___/\\____/\\___/\\___/     |___/\\___/_/ /_/\\___/\\___/\\__,_(_)   \n");
        printw("                                                                              \n");
        printw("                                                                              \n");
        printw("TEMPO DE JOGO: %ds                                                   \n", player->tempo);

        break;
    case 'J': // Jogador colidiu, ou seja, Inimigo ganhou
        // exibe Você Perdeu
        printw("\n\n\n\n\n\n\n\n\n\n         _    __                   ____                __           __\n");
        printw("        | |  / /___  ________     / __ \\___  _________/ /__  __  __/ /\n");
        printw("        | | / / __ \\/ ___/ _ \\   / /_/ / _ \\/ ___/ __  / _ \\/ / / / / \n");
        printw("        | |/ / /_/ / /__/  __/  / ____/  __/ /  / /_/ /  __/ /_/ /_/  \n");
        printw("        |___/\\____/\\___/\\___/  /_/    \\___/_/   \\__,_/\\___/\\__,_(_)   \n");
        printw("                                                                              \n");
        printw("                                                                              \n");
        printw("TEMPO DE JOGO: %ds                                                   \n", player->tempo);
        break;
    case 'e': //  houve empate
        // exibe Empate
        printw("\n\n\n\n\n\n\n\n\n\n            ______                      __       __\n");
        printw("           / ____/___ ___  ____  ____ _/ /____  / /\n");
        printw("          / __/ / __ `__ \\/ __ \\/ __ `/ __/ _ \\/ / \n");
        printw("         / /___/ / / / / / /_/ / /_/ / /_/  __/_/  \n");
        printw("        /_____/_/ /_/ /_/ .___/\\__,_/\\__/\\___(_)   \n");
        printw("                       /_/                         \n");
        printw("                                                                              \n");
        printw("                                                                              \n");
        printw("TEMPO DE JOGO: %ds                                                   \n", player->tempo);
        break;
    case 'x': // sair/encerrar jogo
        // exibe Jogo Encerrado
        printw("\n\n\n\n\n\n\n\n\n\n        __                                                              __    \n");
        printw("       / /___  ____ _____     ___  ____  ________  ______________ _____/ /___ \n");
        printw("  __  / / __ \\/ __ `/ __ \\   / _ \\/ __ \\/ ___/ _ \\/ ___/ ___/ __ `/ __  / __ \\\n");
        printw(" / /_/ / /_/ / /_/ / /_/ /  /  __/ / / / /__/  __/ /  / /  / /_/ / /_/ / /_/ /\n");
        printw(" \\____/\\____/\\__, /\\____/   \\___/_/ /_/\\___/\\___/_/  /_/   \\__,_/\\__,_/\\____/ \n");
        printw("            /____/                                                            \n");
        printw("                                                                              \n");
        printw("                                                                              \n");
        printw("TEMPO DE JOGO: %ds                                                   \n", player->tempo);
        break;

    case 'q':
        endwin();
        exit(0);
        break;
    }
    refresh();
    sleep(2);
    clear();
    menuInicial();
}


// Inicia um novo jogo. Para isso, pede o nome do usuário
void novoJogo(PLAYER *player) {

    char nome[40];

    WINDOW *novoJ;
    novoJ = newwin(5, 46, 4, 15);
    box(novoJ, 0, 0);

    do {
        mvwprintw(novoJ, 2, 2, "Digite seu nome:");
        echo(); //exibe input na tela
        mvwgetstr(novoJ, 2, 20, nome); // coloca o nome recebido na variavel nome
        timeout(-1);//congela o jogo
        wrefresh(novoJ);
    } while (strcmp(nome, "") == 0);
    timeout(DELAY);//descongela o jogo
    noecho();// oculta input da tela

    strcpy(player->nome, nome); //associa o conteudo de nome com o jogador

}

// Pede o nome de um mapa para o usuario e cria o "caminho" para abrir ele
void pedeMapa(char mapa[], char escolha) {

    char mapa_recebido[40], caminho[80], path[40];

    WINDOW *mapa_pedir;
    mapa_pedir = newwin(20, 46, 4, 15);

    strcpy(mapa_recebido,"");

    switch(escolha) {
    case 'n': // jogo novo
        strcpy(path, MAPAS_PATH);
        break;
    case 'c': // jogo salvo
        strcpy(path, SAVEGAME_PATH);
        break;
    }

    do {
        strcpy(caminho, path); // copia o caminho "mapas" para a variavel caminho
        wclear(mapa_pedir);
        box(mapa_pedir, 0, 0);
        if (strcmp(mapa_recebido, "") == 0)
            mvwprintw(mapa_pedir, 2, 2,"Digite o mapa:");
        else
            mvwprintw(mapa_pedir, 2, 2,"Não existe. Digite outro:");
        mvwprintw(mapa_pedir, 4, 2, "MAPAS DISPONIVEIS:");
        mapasDisponiveis(mapa_pedir, 5, 2, path);
        echo();//exibe input na tela
        mvwgetstr(mapa_pedir, 2, 28, mapa_recebido);
        timeout(-1);//congela o jogo
        wrefresh(mapa_pedir);
        timeout(DELAY);//descongela o jogo
        strcat(caminho, mapa_recebido);
    } while (strcmp(mapa_recebido, "") == 0 || !arquivoExiste(caminho));

    strcpy(mapa, mapa_recebido);
    noecho();// oculta input da tela
}


// Encerra o jogo por vontade do usuário
void encerraJogo(PLAYER *player) {
    char tecla;

    do {
        WINDOW *janela;
        janela = newwin(7, 24, 12, 14);
        box(janela, 0, 0);
        mvwaddstr(janela, 2, 3, "Deseja mesmo sair?");
        mvwaddstr(janela, 4, 3, "[S]im   [V]oltar");
        wrefresh(janela);//da refresh na janela
    } while ( (tecla = getch()) && (tecla != 's' && tecla != 'v') );

    if (tecla == 's')
        theEnd('x', player);

}





// Carrega um novo jogo. Busca mapas e inicializa variáveis necessárias.
void inicializaJogoNovo(WINDOW *tela, MOTO *jogador, MOTO *inimigo) {
    FILE *arquivo;

    char linha[51], mapa_rec[80], caminho[80];

    pedeMapa(mapa_rec, 'n');

    strcpy(caminho, MAPAS_PATH);

    strcat(caminho, mapa_rec);

    jogador->cor = COLOR_CYAN;
    inimigo->cor = COLOR_RED;

    if( (arquivo = fopen(caminho, "r")) == NULL)
        printf("Erro ao carregar mapa!");
    else {
        fgets(linha, sizeof(linha), arquivo);
        jogador->direcao =  atoi(strtok(linha,";")); //associa a primeira direcao para o jogador
        inimigo->direcao = atoi(strtok(NULL,";")); //associa a segunda direcao para o inimigo
        carregaMapa (arquivo, tela, jogador, inimigo);

        fclose(arquivo);
    }

}

// Carrega um jogo salvo
void inicializaJogoSalvo(WINDOW *tela, MOTO *jogador, MOTO *inimigo, PLAYER *player) {
    FILE *arquivo;

    char linha[51], mapa_rec[80], caminho[80];

    pedeMapa(mapa_rec, 'c');

    strcpy(caminho, SAVEGAME_PATH);

    strcat(caminho, mapa_rec);

    jogador->cor = COLOR_CYAN;
    inimigo->cor = COLOR_RED;

    if( (arquivo = fopen(caminho, "r")) == NULL)
        printf("Erro ao carregar mapa!");
    else {
        fgets(linha, sizeof(linha), arquivo);
        strcpy(player->nome, strtok(linha,";"));//da primeira linha do arq, pega o nome e coloca no jog
        player->tempo = atoi(strtok(NULL,";"));//pega o segundo item, e coloca no tempo do jog
        jogador->direcao =  atoi(strtok(NULL,";"));//separa o terceiro item e coloca na direcao do jog
        inimigo->direcao = atoi(strtok(NULL,";"));//separa o quarto item e coloca na direcao do inim
        carregaMapa (arquivo, tela, jogador, inimigo);

        fclose(arquivo);
    }

}

//verifica a existencia de um arquivo, retornando 1 para sim e 0 para nao
int arquivoExiste(char caminho[]) {
    FILE *fp = fopen(caminho,"r");

    if (fp)
        return 1;

    return 0;
}


// Salva o jogo
void salvaJogo(WINDOW *tela, PLAYER *player, MOTO *inimigo, MOTO *jogador) {
    WINDOW* telasalvajogo;
    telasalvajogo = newwin(5, 44, 12, 4);
    char tecla, str[80], caminho[80];
    strcpy(str,"");

    do {
        wclear(telasalvajogo);
        box(telasalvajogo, 0, 0);
        strcpy(caminho, SAVEGAME_PATH); // copia o caminho "savegames" para a variavel caminho
        mvwprintw(telasalvajogo, 2, 2, "                                         ");// apaga todos caracteres da linha caso tenha ficado algum resquicio
        if (strcmp(str, "") == 0)
            mvwprintw(telasalvajogo, 2, 2,"Nome para o arquivo:  ");
        else
            mvwprintw(telasalvajogo, 2, 2,"Já existe! Novo nome: ");
        echo(); // so precisa se quiser exibir direto, sem posicionar na window e sem o mvprintw
        mvwgetstr(telasalvajogo, 2, 24, str);//associa a string recebida na variavel str
        timeout(-1);//congela o jogo
        wrefresh(telasalvajogo);
        timeout(DELAY);//descongela o jogo
        strcat(caminho, str); // concatena o nome dado pelo usuario ao caminho
    } while (strcmp(str, "") == 0 || arquivoExiste(caminho));

    noecho();// oculta input da tela

    FILE *arq_salva;

    if ((arq_salva = fopen(caminho, "w")) == NULL) {
        printf("Erro ao criar o arquivo\n\n");
    } else {
        fprintf(arq_salva, "%s;%d;%d;%d\n", player->nome, player->tempo, jogador->direcao, inimigo->direcao);

        char charac = '0';
        int i, j;
        for(i = 1; i <= ALTURA_MAPA; i++) {
            for(j = 1; j <= LARGURA_MAPA; j++) {

                if (mvwinch(tela, i, j) == (' ' | COLOR_PAIR(jogador->cor))) {
                    charac = '1';//verifica se e' a cor do jogador e estiver ' ' e coloca 1
                } else if (mvwinch(tela, i, j) == (' ' | COLOR_PAIR(inimigo->cor))) {
                    charac = '2';//verifica se e' a cor do inimigo e estiver ' ' e coloca 2
                } else if (mvwinch(tela, i, j) == (' ' | COLOR_PAIR(COLOR_YELLOW))) {
                    charac = '3';//verifica se e' a cor de obstaculo e estiver ' ' e coloca 3
                } else if (mvwinch(tela, i, j) == ('J' | COLOR_PAIR(jogador->cor))) {
                    charac = 'J';//verifica se e' a cor do jogador e estiver 'J' e coloca J
                } else if (mvwinch(tela, i, j) == ('I' | COLOR_PAIR(inimigo->cor))) {
                    charac = 'I';//verifica se e' a cor do jogador e estiver 'I' e coloca I
                } else {
                    charac = '0'; //senao coloca 0
                }

                fputc(charac, arq_salva);
            }

            fputc('\n', arq_salva);
        }

        fclose(arq_salva);


        do {
            mvwprintw(telasalvajogo, 2, 2, "                                         ");// apaga todos caracteres da linha caso tenha ficado algum resquicio
            mvwprintw(telasalvajogo, 2, 2,"Jogo salvo! [V]oltar   [S]air");
            wrefresh(telasalvajogo);
        } while ( (tecla = getch()) && (tecla != 's' && tecla != 'v') );

        if (tecla == 's')
            theEnd('x', player);

    }
}
