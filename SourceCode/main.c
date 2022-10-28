#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tMusica.h"

int main(int argc, char *argv[]){
    //                                              abertura de arquivos
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        exit(0);
    }
    FILE* artista_file = fopen(argv[1], "r");
    if (!(artista_file)){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n%s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    FILE* tracks_file = fopen(argv[2], "r");
    if(!tracks_file){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n%s\n", argv[1]);
        fclose(artista_file);
        exit(EXIT_FAILURE);
    }

    tArtista **pp_Artistas = NULL;
    pp_Artistas = Inicializa_PonteiroDePonteiroDeArtistas();
    pp_Artistas = Le_Artistas(artista_file,pp_Artistas);

    printf("\nfim do app\n");
    //fclose(tracks_file);
    //fclose(artista_file);
    return 0;
}
