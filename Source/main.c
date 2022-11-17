#include "../Headers/FuncoesPrincipais.h"
#include <math.h>
#define FALSO 0
#define VERDADE 1
#define RESET_COLOR "\033[0m"

int main(int argc, char *argv[]){    
    // abertura de arquivos
    FILE* artista_file = AbreArquivoArtistasCSV(argc, argv);
    FILE* tracks_file = AbreArquivoTracksCSV(argv);
    
    SystemCreateFoldersCommands();
    
    FILE* RelatorioMusica = fopen("../Relatorio/Musica.txt", "w");
    FILE* RelatorioArtista = fopen("../Relatorio/Artista.txt", "w"); 

    ImprimeTitulo();

    // inicializacao de ponteiros
    tArtista **pp_Artistas = NULL;
    pp_Artistas = Inicializa_PonteiroDePonteiroDeArtistas();
    pp_Artistas = Le_Artistas(artista_file,pp_Artistas);
    
    tMusica **pp_Musicas = NULL;
    pp_Musicas = Inicializa_PonteiroDePonteiroDeMusicas();
    pp_Musicas = Le_Musicas(tracks_file, pp_Musicas, pp_Artistas);

    tPlaylist **pp_ListaPlaylist = NULL;
    FILE* fPlaylists_Cadastradas = fopen("../Playlists/playlists_cadastradas.bin", "rb");

    if(fPlaylists_Cadastradas == NULL){
        system("touch ../Playlists/playlists_cadastradas.bin");
        Acesso_QuantidadePlaylists(0, VERDADE);
        pp_ListaPlaylist = Inicializa_PonteiroDePonteiroDePlaylist(1);
    }
    else{
        Le_Quantidade_Playlists_ArqBinario(fPlaylists_Cadastradas);
        pp_ListaPlaylist = Inicializa_PonteiroDePonteiroDePlaylist(Acesso_QuantidadePlaylists(0, FALSO));
        pp_ListaPlaylist = Le_Playlists_ArqBinario(pp_ListaPlaylist, pp_Musicas, pp_Artistas, fPlaylists_Cadastradas);
        fclose(fPlaylists_Cadastradas);
    }

    int opcao = 0;    
    do{
        ExibeMenu();
        scanf("%d",&opcao);
        scanf("%*c");
        pp_ListaPlaylist = ExecutaOpcaoUsuario(opcao, pp_Musicas, pp_Artistas, pp_ListaPlaylist, RelatorioMusica, RelatorioArtista);
    }while(opcao != 0);
    
    fPlaylists_Cadastradas = fopen("../Playlists/playlists_cadastradas.bin", "wb");
    Registra_Playlists_ArqBinario(pp_ListaPlaylist, fPlaylists_Cadastradas);
    
    LiberaTodosOsArtistas(pp_Artistas);
    LiberaTodasAsMusicas(pp_Musicas);
    LiberaTodasAsPlaylist(pp_ListaPlaylist);

    fclose(fPlaylists_Cadastradas);
    CloseFiles(RelatorioMusica, RelatorioArtista, tracks_file, artista_file);

    printf("Programa finalizado!\n" RESET_COLOR);
    return 0;
}

