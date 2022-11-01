#ifndef _FUNCOESPRINCIPAIS_H_
#define _FUNCOESPRINCIPAIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tMusica.h"
#define VERDADE 1
#define FALSO 0


void ExibeMenu();

void ExecutaOpcaoUsuario(int opcao, tMusica** pp_Musicas);

void BuscarMusicas(tMusica** pp_Musicas);

void ListarMusica(tMusica** pp_Musicas);

FILE* AbreArquivoArtistasCSV(int argc, char **argv);

FILE* AbreArquivoTracksCSV(char *argv[]);


#endif