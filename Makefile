CC=gcc

CFLAGS=-c -lm -Wall -pedantic
DEPS = $(wildcard Headers/*.h)
OBJ = $(wildcard Objects/*.o)
SRC = $(wildcard Source/*.c)
OUT = Objects/
IN = Source/
EXE = exe

all: CreateFolder Compile GenExe

Compile: $(SRC) $(DEPS)
	@$(CC) -o $(OUT)tPropriedades.o $(IN)tPropriedades.c $(CFLAGS)
	@$(CC) -o $(OUT)tArtista.o $(IN)tArtista.c $(CFLAGS)
	@$(CC) -o $(OUT)tMusica.o $(IN)tMusica.c $(CFLAGS)
	@$(CC) -o $(OUT)tPlaylist.o $(IN)tPlaylist.c $(CFLAGS)
	@$(CC) -o $(OUT)FuncoesPrincipais.o $(IN)FuncoesPrincipais.c $(CFLAGS)
	@$(CC) -o $(OUT)main.o $(IN)main.c $(CFLAGS)
	@echo compilado objetos!

GenExe:
	@$(CC) -o $(IN)$(EXE) $(OBJ) -lm
	@echo compilado executavel!

CreateFolder:
	@mkdir -p Objects

clear:
	@rm -rf Objects && rm $(IN)exe
