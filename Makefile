CC=gcc

CFLAGS=-c -lm -Wall -pedantic
DEPS = $(wildcard SourceCode/*.h)
OBJ = $(wildcard Objects/*.o)
SRC = $(wildcard SourceCode/*.c)
OUT = Objects/
IN = SourceCode/
EXE = exe
ARTIST_FILE = data/artists_2.csv
TRACKS_FILE = data/tracks_2.csv

Compile: $(SRC) $(DEPS)
	$(CC) -o $(OUT)tPropriedades.o $(IN)tPropriedades.c $(CFLAGS)
	$(CC) -o $(OUT)tArtista.o $(IN)tArtista.c $(CFLAGS)
	$(CC) -o $(OUT)tMusica.o $(IN)tMusica.c $(CFLAGS)
	$(CC) -o $(OUT)tPlaylist.o $(IN)tPlaylist.c $(CFLAGS)
	$(CC) -o $(OUT)FuncoesPrincipais.o $(IN)FuncoesPrincipais.c $(CFLAGS)
	$(CC) -o $(OUT)main.o $(IN)main.c $(CFLAGS)

GenExe:
	$(CC) -o $(OUT)$(EXE) $(OBJ) -lm

Execute:
	chmod +777 $(OUT)$(EXE)
	./$(OUT)$(EXE) $(ARTIST_FILE) $(TRACKS_FILE)

CreateFolder:
	mkdir Objects

clear:
	rm -rf Objects
