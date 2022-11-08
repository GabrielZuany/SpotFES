#include "FuncoesPrincipais.h"

#define FALSO 0
#define VERDADE 1

int main(int argc, char *argv[]){
    // abertura de arquivos
    FILE* artista_file = AbreArquivoArtistasCSV(argc, argv);
    FILE* tracks_file = AbreArquivoTracksCSV(argv);

    //Criar pasta com arquivos para relatorio.
    system("mkdir ../Relatorio");
    system("touch ../Relatorio/Musica.txt");
    system("touch ../Relatorio/Artista.txt");
    FILE* RelatorioMusica = fopen("../Relatorio/Musica.txt", "w");
    FILE* RelatorioArtista = fopen("../Relatorio/Artista.txt", "w");


    // inicializacao de ponteiros
    tArtista **pp_Artistas = NULL;
    pp_Artistas = Inicializa_PonteiroDePonteiroDeArtistas();
    pp_Artistas = Le_Artistas(artista_file,pp_Artistas);
    

    tMusica **pp_Musicas = NULL;
    pp_Musicas = Inicializa_PonteiroDePonteiroDeMusicas();
    pp_Musicas = Le_Musicas(tracks_file, pp_Musicas, pp_Artistas);


    tPlaylist **pp_ListaPlaylist = NULL;
    pp_ListaPlaylist = Inicializa_PonteiroDePonteiroDePlaylist();


    int opcao = 0;
    
    do{
        ExibeMenu();
        scanf("%d",&opcao);
        scanf("%*c");
        pp_ListaPlaylist = ExecutaOpcaoUsuario(opcao, pp_Musicas, pp_Artistas, pp_ListaPlaylist, RelatorioMusica, RelatorioArtista);
    }while(opcao != 0);

    LiberaTodosOsArtistas(pp_Artistas);
    LiberaTodasAsMusicas(pp_Musicas);
    LiberaTodasAsPlaylist(pp_ListaPlaylist);

    fclose(RelatorioMusica);
    fclose(RelatorioArtista);
    fclose(tracks_file);
    fclose(artista_file);


    return 0;
}

