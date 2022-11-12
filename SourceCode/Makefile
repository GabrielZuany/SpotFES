CC=gcc
CFLAGS=-lm -Wall

DEPS= FuncoesPrincipais.h tArtista.h tMusica.h tPlaylist.h tPropriedades.h

OBJ=FuncoesPrincipais.o tArtista.o tMusica.o tPlaylist.o tPropriedades.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prog: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	echo "Compilado!"

clean:
	rm -rf *.o prog

run:
	./prog

objFolder:
    @ mkdir -p objects