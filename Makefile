CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99 -fsanitize=address
SRC=./src/
BIN=./bin/

#compilation du code
ftc : ftc.o arbre.o
	$(CC) -o ftc $(BIN)ftc.o $(BIN)arbre.o $(CFLAGS)
ftc.o :
	$(CC) -o $(BIN)ftc.o -c $(SRC)ftc.c $(CFLAGS) 
arbre.o :
	$(CC) -o $(BIN)arbre.o -c $(SRC)arbre.c $(CFLAGS)







#outils 
clean :
	rm -r $(BIN)*.o