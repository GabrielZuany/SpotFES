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
    system("mkdir ../Playlists");
    
    //Cria pasta com arquivo playlist
    FILE* fPlaylists_Cadastradas = fopen("../Playlists/playlists_cadastradas.bin", "rb");
    if(fPlaylists_Cadastradas == NULL){
        system("touch ../Playlists/playlists_cadastradas.bin");
        Acesso_QuantidadePlaylists(0, VERDADE);
    }

    // inicializacao de ponteiros
    tArtista **pp_Artistas = NULL;
    pp_Artistas = Inicializa_PonteiroDePonteiroDeArtistas();
    pp_Artistas = Le_Artistas(artista_file,pp_Artistas);
    
    tMusica **pp_Musicas = NULL;
    pp_Musicas = Inicializa_PonteiroDePonteiroDeMusicas();
    pp_Musicas = Le_Musicas(tracks_file, pp_Musicas, pp_Artistas);

    tPlaylist **pp_ListaPlaylist = NULL;
    pp_ListaPlaylist = Inicializa_PonteiroDePonteiroDePlaylist();

    //testando
    if(fPlaylists_Cadastradas != NULL){
        pp_ListaPlaylist = Le_Playlists_ArqBinario(pp_ListaPlaylist, pp_Musicas, fPlaylists_Cadastradas);
        fclose(fPlaylists_Cadastradas);
    }

    
    
    //main
    int opcao = 0;


    /*
    printf("\n\n\n==============================================================================================\n");
    do{
        //ExibeMenu();
        scanf("%d",&opcao);
        scanf("%*c");
        pp_ListaPlaylist = ExecutaOpcaoUsuario(opcao, pp_Musicas, pp_Artistas, pp_ListaPlaylist, RelatorioMusica, RelatorioArtista);
    }while(opcao != 0);
    printf("==============================================================================================\n\n\n");
    
    fPlaylists_Cadastradas = fopen("../Playlists/playlists_cadastradas.bin", "wb");
    Registra_Playlists_ArqBinario(pp_ListaPlaylist, fPlaylists_Cadastradas);
    fclose(fPlaylists_Cadastradas);
    LiberaTodasAsPlaylist(pp_ListaPlaylist);
    */


    LiberaTodosOsArtistas(pp_Artistas);
    LiberaTodasAsMusicas(pp_Musicas);

    fclose(RelatorioMusica);
    fclose(RelatorioArtista);
    fclose(tracks_file);
    fclose(artista_file);
    return 0;
}

