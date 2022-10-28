#ifndef _TARTISTA_H_
#define _TARTISTA_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tArtista tArtista;

//-----------------------inicializacao de ponteiro----------------------
tArtista** Inicializa_PonteiroDePonteiroDeArtistas();
tArtista* Inicializa_PonteirDeArtistas(char id[], float seguidores, char nome[], int popularidade);

//--------------------leitura de arquivos--------------------------------
//---------artistas
tArtista** Le_Artistas(FILE* artista_file, tArtista** pp_Artistas);
char** Retorna_ListaDeGeneros(char* str);


void Reseta_NomeGenero(char* nome, char* genero);




void Imprime_Artista(tArtista *artista);
#endif