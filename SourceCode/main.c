#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tMusica.h"
#define FALSO 0
#define VERDADE 1

FILE* AbreArquivoArtistasCSV(int argc, char **argv);
FILE* AbreArquivoTracksCSV(char *argv[]);


int main(int argc, char *argv[]){
    //                                                abertura de arquivos
    FILE* artista_file = AbreArquivoArtistasCSV(argc, argv);
    FILE* tracks_file = AbreArquivoTracksCSV(argv);

    //                                                inicializacao de ponteiros
    tArtista **pp_Artistas = NULL;
    pp_Artistas = Inicializa_PonteiroDePonteiroDeArtistas();
    pp_Artistas = Le_Artistas(artista_file,pp_Artistas);
    tMusica **pp_Musicas = NULL;
    pp_Musicas = Inicializa_PonteiroDePonteiroDeMusicas();
    pp_Musicas = Le_Musicas(tracks_file, pp_Musicas, pp_Artistas);



    fclose(tracks_file);
    fclose(artista_file);
    return 0;
}


FILE* AbreArquivoArtistasCSV(int argc, char **argv){
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        exit(0);
    }
    FILE* artista_file = fopen(argv[1], "r");
    if (!(artista_file)){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n%s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    return artista_file;
}

FILE* AbreArquivoTracksCSV(char *argv[]){
    FILE* tracks_file = fopen(argv[2], "r");
    if(!tracks_file){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n%s\n", argv[1]);
        fclose(tracks_file);
        exit(EXIT_FAILURE);
    }
    return tracks_file;
}