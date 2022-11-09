CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99 
SRC=./src/
BIN=./bin/

#compilation du code
ftc : ftc.o arbre.o liste.o
	$(CC) -o ftc $(BIN)ftc.o $(BIN)arbre.o $(BIN)liste.o $(CFLAGS)
ftc.o :
	$(CC) -o $(BIN)ftc.o -c $(SRC)ftc.c $(CFLAGS) 
arbre.o :
	$(CC) -o $(BIN)arbre.o -c $(SRC)arbre.c $(CFLAGS)
liste.o :
	$(CC) -o $(BIN)liste.o -c $(SRC)liste.c $(CFLAGS)





#outils 
clean :
	rm -r $(BIN)*.o
