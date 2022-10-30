#include "FuncoesPrincipais.h"

#define FALSO 0
#define VERDADE 1

int main(int argc, char *argv[]){
    // abertura de arquivos
    FILE* artista_file = AbreArquivoArtistasCSV(argc, argv);
    FILE* tracks_file = AbreArquivoTracksCSV(argv);

    // inicializacao de ponteiros
    tArtista **pp_Artistas = NULL;
    pp_Artistas = Inicializa_PonteiroDePonteiroDeArtistas();
    pp_Artistas = Le_Artistas(artista_file,pp_Artistas);
    tMusica **pp_Musicas = NULL;
    pp_Musicas = Inicializa_PonteiroDePonteiroDeMusicas();
    pp_Musicas = Le_Musicas(tracks_file, pp_Musicas, pp_Artistas);

    int opcao = 0;
    
    do{
        ExibeMenu();
        scanf("%d",&opcao);
        ExecutaOpcaoUsuario(opcao);
    }while(opcao != 0);

    fclose(tracks_file);
    fclose(artista_file);
    return 0;
}

