SRC = src
PATH_DEST = ./
INCLUDE = include
PAR = -Wall
OBJ = ces.o file.o main.o rom.o
Debug:main

Clean:
	rm -f *.o
	rm -f ces

main: $(OBJ)
	gcc -o $(PATH_DEST)ces $(OBJ) $(PAR)
	rm -f *.o

ces.o:$(SRC)/ces.c
	gcc -o ces.o -c $(SRC)/ces.c -I$(INCLUDE) $(PAR)

file.o:$(SRC)/file.c
	gcc -o file.o -c $(SRC)/file.c -I$(INCLUDE) $(PAR)

main.o:$(SRC)/main.c
	gcc -o main.o -c $(SRC)/main.c -I$(INCLUDE) $(PAR)

rom.o:$(SRC)/rom.c
	gcc -o rom.o -c $(SRC)/rom.c -I$(INCLUDE) $(PAR)
