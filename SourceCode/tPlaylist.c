#include "tPlaylist.h"
#define QTD_PROPRIEDADES_ANALISE 8
#define FALSO 0
struct tPlaylist{
    int indice;
    char nome[50];
    int qtdMusica;
    tMusica** Lista_musicas;
};


//========================inicializacao de ponteiro========================
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
    return p_Playlist;
}

char* Cria_ArquivoPlaylist_RetornandoCaminho(char nome[]){
    char* path = calloc(sizeof(char), 70);
    char* command = calloc(sizeof(char), 70);

    strcat(command, "mkdir ");
    strcat(path, "../Playlists/");
    strcat(command, path);
    system(command);

    free(command);// resetar o ponteiro.
    command = calloc(sizeof(char), 70);

    strcat(command, "touch ");
    strcat(path, "../Playlists/");
    strcat(path, nome);
    strcat(path, ".bat");
    strcat(command, path);
    
    system(command);
    free(command);
    return path;
}

void Armazena_Playlist_em_ArquivoBinario(tPlaylist* playlist, char*filepath){
    FILE* file = fopen(filepath, "ab"); // nao sobrescreve. Caso o usuario queira adicionar mais musicas.
    fwrite(playlist, sizeof(playlist), 1, file);
    fclose(file);
}

tPlaylist* Adiciona_MusicaPlaylist(int indice, tPlaylist* p_Playlist, tMusica** pp_Musica, tArtista **pp_Artistas){
    int posicao = p_Playlist->qtdMusica;
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

//========================auxiliares========================

void Reseta_String(char *nome){
    int i;
    for(i=0; i<strlen(nome);i++){
        nome[i] = '\0';
    }
}

void RecomendaMusicasParecidasComUmaPlaylist(tPlaylist* pPlaylist, tMusica **pp_Musicas,int qtd_MusicaParaRecomendar){
    float *p_PropriedadesMusicaIdeal;
    p_PropriedadesMusicaIdeal = CalculaArrayPropriedadesMusicaIdeal(pPlaylist);
    ImprimeXMusicasMaisProximas(pp_Musicas, p_PropriedadesMusicaIdeal, qtd_MusicaParaRecomendar);
    free(p_PropriedadesMusicaIdeal);
}

float* CalculaArrayPropriedadesMusicaIdeal(tPlaylist *pPlaylist){
    int iMusicas = 0, iPropriedades, j = 0, qtd_musicas = pPlaylist->qtdMusica;
    float *p_PropriedadesMusicaIdeal = (float*)malloc(sizeof(float)*QTD_PROPRIEDADES_ANALISE);
    float mediaPropriedades = 0;
    
    for(iPropriedades = 0; iPropriedades < QTD_PROPRIEDADES_ANALISE; iPropriedades++){
        for(iMusicas = 0; iMusicas < qtd_musicas; iMusicas++){
            
           mediaPropriedades = mediaPropriedades + RetornaPropriedadeXdaMusica_ViaMusica(pPlaylist->Lista_musicas[iMusicas], iPropriedades);  
        }
        
        mediaPropriedades = mediaPropriedades/(float)qtd_musicas;
        p_PropriedadesMusicaIdeal[iPropriedades] = mediaPropriedades;
        mediaPropriedades = 0;  
    }
    return p_PropriedadesMusicaIdeal;
}

//========================Impressao========================

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


//===========================liberacao de playlist========================

int Acesso_QuantidadePlaylists(int qtdPlaylist, int trocar){
    static int x;
    if (trocar){
        x = qtdPlaylist;
    }
    return x;
}

void LiberaTodasAsPlaylist(tPlaylist** pp_playlist){
    int qtd_playlists = Acesso_QuantidadePlaylists(0, FALSO);
    int i;

    for(i=0; i<qtd_playlists; i++){
        free(pp_playlist[i]->Lista_musicas);
        free(pp_playlist[i]);
    }
    free(pp_playlist);
}
