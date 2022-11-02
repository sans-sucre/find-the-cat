CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99
SRC=./src/
BIN=./bin/

#compilation du code
ftc : ftc_test.o arbre.o
	$(CC) -o ftc $(BIN)ftc_test.o $(BIN)arbre.o $(CFLAGS)
ftc_test.o :
	$(CC) -o $(BIN)ftc_test.o -c $(SRC)ftc_test.c $(CFLAGS) 
arbre.o :
	$(CC) -o $(BIN)arbre.o -c $(SRC)arbre.c $(CFLAGS)







#outils 
clean :
	rm -r $(BIN)*.o