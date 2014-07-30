#include "mapas.h"

// Cria os pares de cor que podem ser utilizados na Ncurses
// Ex: COLOR_PAIR(COLOR_BLUE)
void inicializaCores(void) {
    int i;
    int cores[] = { COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE };
    for( i = 0; i < sizeof(cores) / sizeof(*cores); i++ )
        init_pair(cores[i], COLOR_WHITE, cores[i]);
    /*
    COLOR_BLACK   0
    COLOR_RED     1
    COLOR_GREEN   2
    COLOR_YELLOW  3
    COLOR_BLUE    4
    COLOR_MAGENTA 5
    COLOR_CYAN    6
    COLOR_WHITE   7
    */
}


// Usada para exibir na tela os mapas disponíveis, listando um diretório path
// Para posicionar o texto, recebe uma tela e coordenadas x e y
void mapasDisponiveis(WINDOW * tela, int y, int x, char path[]) {
    DIR *mapas;
    struct dirent *mapa;
    mapas = opendir (path);
    int i = 0;

    if (mapas != NULL) {
        while ((mapa = readdir (mapas)) )
            if (mapa->d_name[0] != '.') {
                mvwprintw(tela, y+i, x, "%s", mapa->d_name);
                i++;
            }
        closedir (mapas);
    } else
        perror ("Erro ao carregar lista de mapas!");
}


// Dado um arquivo (com o cursor posicionado no início do mapa), carrega o mapa
// para a tela
void carregaMapa (FILE * arquivo, WINDOW *tela, MOTO *jogador, MOTO *inimigo) {

    int i = 1, j; // utilizados como coordenadas
    char linha[LARGURA_MAPA+4]; // tamanho válido tanto para EOL de linux quanto Windows

    while((fgets(linha, sizeof(linha), arquivo)) != NULL) {
        for(j = 1; j <= LARGURA_MAPA; j++) {
            char c = linha[j-1];
            switch(c) {
            case '0': // espaço em branco
                break;
            case '1': // obstáculo deixado pelo jogador
                mvwaddch(tela, i, j, ' ' | COLOR_PAIR(jogador->cor));
                break;
            case '2': // obstáculo deixado pelo inimigo
                mvwaddch(tela, i, j, ' ' | COLOR_PAIR(inimigo->cor));
                break;
            case '3': // obstáculo
                mvwaddch(tela, i, j, ' ' | COLOR_PAIR(COLOR_YELLOW));
                break;
            case 'I':
                mvwaddch(tela, i, j, 'I');
                inimigo->c.y = i;
                inimigo->c.x = j;
                break;
            case 'J':
                mvwaddch(tela, i, j, 'J');
                jogador->c.y = i;
                jogador->c.x = j;
                break;
            }
        }
        i++;
    }
}
