#include "tPlaylist.h"

struct tPlaylist{
    int indice;
    char nome[50];
    int qtdMusica;
    tMusica** Lista_musicas;
};


//----------inicializacao de ponteiro--------------
tPlaylist** Inicializa_PonteiroDePonteiroDePlaylist(){
    tPlaylist  **pp_ListaPlaylist = NULL;
    pp_ListaPlaylist = (tPlaylist**)malloc(sizeof(tPlaylist*)); 
    return pp_ListaPlaylist;
}

tPlaylist* Inicializa_PonteiroDePlaylist(char nome[], int indice){
    tPlaylist* p_Playlist = NULL;
    p_Playlist = (tPlaylist*) malloc(sizeof(struct tPlaylist));
    p_Playlist->Lista_musicas = (tMusica**)malloc(sizeof(tMusica*));
    strcpy(p_Playlist->nome, nome);
    p_Playlist->indice = indice;
    p_Playlist->qtdMusica = 0;
    //Cria_ArquivoPlaylist(nome, p_Playlist);
    return p_Playlist;
}

void Cria_ArquivoPlaylist(char nome[], tPlaylist* p_Playlist){
    char path[70];
    Reseta_String(path);
    strcat(path, "mkdir Playlists/");
    system(path);
    
    Reseta_String(path);
    strcat(path, "touch Playlists/");
    strcat(path, nome);
    system(path);
}



tPlaylist* Adiciona_MusicaPlaylist(int indice, tPlaylist* p_Playlist, tMusica** pp_Musica, tArtista **pp_Artistas){
    int posicao = p_Playlist->qtdMusica;
    p_Playlist->Lista_musicas[posicao] = Inicializa_PonteiroDeMusicaSemParamentros();
    p_Playlist->Lista_musicas[posicao] = pp_Musica[indice];
    Incrementa_X_Em_qtd_PresencaMusicaEmPlaylist(pp_Musica[indice], 1);
    Incrementa_X_EmTodosOsArtistasDaMusica(pp_Musica[indice]);
    
    p_Playlist->qtdMusica++;
    return p_Playlist;
}

tPlaylist* Realoca_Memoria_PonteiroDeMusica(tPlaylist* p_Playlist){
    int multiplicador = p_Playlist->qtdMusica + 1;
    p_Playlist->Lista_musicas = realloc(p_Playlist->Lista_musicas, multiplicador*sizeof(tMusica*));

    return p_Playlist;
}   

// ----------- auxiliares -----------

void Reseta_String(char *nome){
    int i;
    for(i=0; i<strlen(nome);i++){
        nome[i] = '\0';
    }
}

//------------- Impressao -----------

void Imprime_ListarUmaPlaylist(tPlaylist *p_Playlist){
    printf("===========================================================================\n");
    printf("Nome Da Playlist: %s\n", p_Playlist->nome);
    ImprimeTodasAsMusicasDaPlaylist(p_Playlist->Lista_musicas, p_Playlist->qtdMusica);
    printf("===========================================================================\n");
}

void Imprime_ListarPlaylists(tPlaylist** pp_ListaPlaylist, int qtd_playlists){
    int i;
    printf("===========================================================================\n\n");
    for(i=0; i<qtd_playlists;i++){
        printf("Nome: %s\n", pp_ListaPlaylist[i]->nome);
        printf("Indice: %d\n", pp_ListaPlaylist[i]->indice);
        printf("Quantidade de musicas: %d\n\n", pp_ListaPlaylist[i]->qtdMusica);
    }
    printf("===========================================================================\n");
}