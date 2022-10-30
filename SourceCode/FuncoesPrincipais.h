#ifndef _FUNCOESPRINCIPAIS_H_
#define _FUNCOESPRINCIPAIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tMusica.h"


void ExibeMenu();

void ExecutaOpcaoUsuario(int opcao);

FILE* AbreArquivoArtistasCSV(int argc, char **argv);

FILE* AbreArquivoTracksCSV(char *argv[]);


#endif