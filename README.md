# Trabalho final: Tron
#### Para Linux

## COMPILANDO
**Para compilar e executar**

```clear && make && ./Tron```

**Para apagar os arquivos gerados na compilação**

```make clean```

**Para identar o código:**

```astyle --style=google *.c *.h```


### IDEIAS POSTERIORES:
- Poderia ter vários niveis de dificuldade, é só mudar a velocidade do DELAY
- Permitir ao jogador escolher cor e ícone. ai teria que arrumar a bool motoColisao()
- Som
- Criar executável para resetar ranking
- Gerar uma struct estática para salvar as opções da int* opcoes(int direcao); e não ter que fazertodo processamento a cada vez
- Carregar o conteúdo dos rankings e salvá-los em algum lugar estático para não precisar abrir o arquivo a cada volta do loop
- Criar funções para manipulação da interface. Ex: criar box que peça algum input


----

### Boas referências sobre a biblioteca ncurses:
- http://publib.boulder.ibm.com/infocenter/aix/v7r1/index.jsp?topic=%2Fcom.ibm.aix.basetechref%2Fdoc%2Fbasetrf2%2Fgetch.htm
- https://stackoverflow.com/questions/3065116/get-the-text-in-the-display-with-ncurses
- http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO
- http://www.faqs.org/docs/Linux-HOWTO/NCURSES-Programming-HOWTO.html
- http://linux.die.net/man/3/timeout
