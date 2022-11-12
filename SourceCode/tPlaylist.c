#include "tPlaylist.h"
#define QTD_PROPRIEDADES_ANALISE 8
#define FALSO 0
#define VERDADE 1
struct tPlaylist{
    int indice;
    char nome[50];
    int qtdMusica;
    tMusica** Lista_musicas;
};


//========================inicializacao de ponteiro========================
tPlaylist** Inicializa_PonteiroDePonteiroDePlaylist(int x){
    tPlaylist  **pp_ListaPlaylist = NULL;
    pp_ListaPlaylist = (tPlaylist**)malloc(sizeof(tPlaylist*) * x); 
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


//============================binario====================
//======REGISTRO
void Registra_Playlists_ArqBinario(tPlaylist** pp_ListaPlaylist, FILE *file){
    int Qtd_Playlists;
    Qtd_Playlists = Acesso_QuantidadePlaylists(0, FALSO);
    int i = 0;
    
    fwrite(&Qtd_Playlists, sizeof(int), 1, file);
    
    for(i=0; i < Qtd_Playlists; i++){
        Armazena_Playlist_em_ArquivoBinario(pp_ListaPlaylist[i], file);
    }
}


void Armazena_Playlist_em_ArquivoBinario(tPlaylist* playlist, FILE* file){
    int tamanhoNome = 0;
    //indice
    fwrite(&(playlist->indice), sizeof(int), 1, file);
    //qtd musica
    fwrite(&(playlist->qtdMusica), sizeof(int), 1, file);
    //tamahno nome
    tamanhoNome = strlen(playlist->nome);
    fwrite(&tamanhoNome, sizeof(int), 1, file);
    //nome
    fputs(playlist->nome, file);
    int i = 0, indice = 0; 
    for(i = 0; i < (playlist->qtdMusica); i++){
        indice = Acesso_IndiceNoArrayMusicaX(playlist->Lista_musicas, i);
        fwrite(&indice, sizeof(int), 1, file);
    }
}





//=======LEITURA
tPlaylist** Le_Playlists_ArqBinario(tPlaylist **pp_ListaPlaylist, tMusica **pp_Musicas, tArtista **pp_Artistas, FILE * file){
    int indiceDaPlaylist = 0, indice = 0, qtdMusica = 0, tamanhoNome = 0, indiceDaMusica = 0, indiceResetaStg = 0;
    char nome[50];
    for(indiceDaPlaylist = 0; indiceDaPlaylist < Acesso_QuantidadePlaylists(0, FALSO);indiceDaPlaylist++){
        int *indiceMusica = NULL;
        pp_ListaPlaylist[indiceDaPlaylist] = (tPlaylist*) malloc(sizeof(struct tPlaylist));
        //indice
        fread(&indice, sizeof(int), 1, file);
        //qtd musica
        fread(&qtdMusica, sizeof(int), 1, file);
        //tamanho nome
        fread(&tamanhoNome, sizeof(int), 1, file);
        //nome
        for(indiceResetaStg = 0; indiceResetaStg < 50; indiceResetaStg++){
            nome[indiceResetaStg] = '\0';
        }
        fread(nome, sizeof(char), tamanhoNome, file);
        //indicesMusica
        indiceMusica = malloc(sizeof(int) * qtdMusica);
        fread(indiceMusica, sizeof(int), qtdMusica, file); 

        //armazenamento        
        pp_ListaPlaylist[indiceDaPlaylist]->indice = indice;
        pp_ListaPlaylist[indiceDaPlaylist]->qtdMusica = 0;
        strcpy(pp_ListaPlaylist[indiceDaPlaylist]->nome, nome);
        pp_ListaPlaylist[indiceDaPlaylist]->Lista_musicas = (tMusica**)malloc(sizeof(tMusica*) * qtdMusica);

        for(indiceDaMusica = 0; indiceDaMusica < qtdMusica; indiceDaMusica++){
            pp_ListaPlaylist[indiceDaPlaylist] = Adiciona_MusicaPlaylist(indiceMusica[indiceDaMusica], pp_ListaPlaylist[indiceDaPlaylist], pp_Musicas, pp_Artistas);
        }
        free(indiceMusica);
    }
    
    return pp_ListaPlaylist;
}

void Le_Quantidade_Playlists_ArqBinario(FILE* file){
    int qtdPlaylist = 0;
    fread(&qtdPlaylist, sizeof(int), 1, file);
    Acesso_QuantidadePlaylists(qtdPlaylist, VERDADE);
}


// ================fim binario====================
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
    int valorValido = 0;
    if(pPlaylist->qtdMusica <= 0){
        printf("Playlist vazia, nao eh possivel recomendar musicas!\n");
        return;
    }
    if(qtd_MusicaParaRecomendar <= 0){
        while(!valorValido){
            printf("Digite um valor valido: ");
            scanf("%d%*c", &qtd_MusicaParaRecomendar);
            if(qtd_MusicaParaRecomendar > 0){
                valorValido = 1;
            }
        }
        printf("\n");
    }
    float *p_PropriedadesMusicaIdeal;
    p_PropriedadesMusicaIdeal = CalculaArrayPropriedadesMusicaIdeal(pPlaylist);
    ImprimeXMusicasMaisProximas(pp_Musicas, p_PropriedadesMusicaIdeal, qtd_MusicaParaRecomendar);
    free(p_PropriedadesMusicaIdeal);
}

float* CalculaArrayPropriedadesMusicaIdeal(tPlaylist *pPlaylist){
    int iMusicas = 0, iPropriedades, qtd_musicas = pPlaylist->qtdMusica;
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
    int i = 0;

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
