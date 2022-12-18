CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99 -fsanitize=address
SRC=./src/
BIN=./bin/

#compilation du code
ftc : ftc.o arbre.o check.o MegaMimes.o liste.o 
	$(CC) -o ftc $(BIN)ftc.o $(BIN)arbre.o  $(BIN)check.o $(BIN)liste.o $(BIN)MegaMimes.o $(CFLAGS)
ftc.o :
	$(CC) -o $(BIN)ftc.o -c $(SRC)ftc.c $(CFLAGS) 
arbre.o :
	$(CC) -o $(BIN)arbre.o -c $(SRC)arbre.c $(CFLAGS)
check.o :
	$(CC) -o $(BIN)check.o -c $(SRC)check.c $(CFLAGS)
MegaMimes.o :
	$(CC) -o $(BIN)MegaMimes.o -c $(SRC)MegaMimes.c $(CFLAGS)
liste.o :
	$(CC) -o $(BIN)liste.o -c $(SRC)liste.c $(CFLAGS)


#outils 
clean :
	rm -r $(BIN)*.o
