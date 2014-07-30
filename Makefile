CC = gcc
OUTFILE = Tron

all:
	$(CC) -Wall *.c -o $(OUTFILE) -lncurses

clean:
	rm -rf *.o
	rm -rf $(OUTFILE)
