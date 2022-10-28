
#include "tArtista.h"
#define multiplicador_malloc 1

struct tArtista{
    char id[25]; //hash alfanumerico
    float seguidores;
    char **generos; //lista de generos
    char nome[1000];
    int popularidade;
};




//-----------------------inicializacao de ponteiro----------------------
tArtista** Inicializa_PonteiroDePonteiroDeArtistas(){
    tArtista **pp_Artistas = NULL;
    pp_Artistas = (tArtista**)malloc(multiplicador_malloc * sizeof(tArtista*));
    return pp_Artistas;
}

tArtista* Inicializa_PonteirDeArtistas(char id[], float seguidores, char nome[], int popularidade){
    int tamanhoNome = 0;

    tArtista *p_Artista = NULL;
    p_Artista = (tArtista *)malloc(1 * sizeof(tArtista));
    
    strcpy(p_Artista->id, id);
    strcpy(p_Artista->nome, nome);
    p_Artista->seguidores = seguidores;
    p_Artista->popularidade = popularidade;
    return p_Artista;
}

//--------------------leitura de arquivos--------------------------------
//---------artistas
tArtista** Le_Artistas(FILE* artista_file, tArtista** pp_Artistas){
    tArtista *p_Artista = NULL;
    static int i = 0;
    char todos_generos[1000], nome[1000], id[25];
    float seguidores = 0;
    int popularidade = 0;
    
    Reseta_NomeGenero(nome, todos_generos);

    while(i<64703){
        int x = 0;
        pp_Artistas = (tArtista**)realloc(pp_Artistas, (i+1) * sizeof(tArtista*));

        x = fscanf(artista_file,"%[^;];%f;%[^;];%[^;];%d\n", id, &seguidores, todos_generos, nome, &popularidade);
        p_Artista = Inicializa_PonteirDeArtistas(id, seguidores, nome, popularidade);
        p_Artista->generos = Retorna_ListaDeGeneros(todos_generos);

        pp_Artistas[i] = p_Artista;
        
        Imprime_Artista(pp_Artistas[i]);
        printf("\n");
        i++;
        
        Reseta_NomeGenero(nome, todos_generos);
        
    }
    
    

    return pp_Artistas;
}

void Reseta_NomeGenero(char* nome, char* genero){
    int i = 0;
    for(i=0; i<strlen(nome); i++){
        nome[i] ='\0';
    }
    for(i=0; i<strlen(genero); i++){
        genero[i] = '\0';
    }
}

char** Retorna_ListaDeGeneros(char* str){
    char* genero;
    char** ListaDeGeneros = (char**)malloc(sizeof(char)*(strlen(str)+1));
    int i = 0;

    genero = strtok (str,"|");
    
    while (genero != NULL){
        ListaDeGeneros[i] = genero;
        i++;
        genero = strtok (NULL,"|");
    }
    
    return ListaDeGeneros;
}


void Imprime_Artista(tArtista *artista){
    printf("Id: %s Seguidores: %.1f Nome: %s Popularidade: %d", artista->id, artista->seguidores, artista->nome, artista->popularidade);
}
