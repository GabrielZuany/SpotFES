#include "tArtista.h"
#define multiplicador_malloc 1
#define VERDADE 1
#define FALSO 0

struct tArtista{
    char id[25]; //hash alfanumerico
    float seguidores;
    char **generos; //lista de generos
    char *nome;
    int popularidade;
    int qtd_generos;
};

//-----------------------inicializacao de ponteiro----------------------

tArtista** Inicializa_PonteiroDePonteiroDeArtistas(){
    tArtista **pp_Artistas = NULL;
    pp_Artistas = (tArtista**)malloc(multiplicador_malloc * sizeof(tArtista*));
    return pp_Artistas;
}
tArtista* Inicializa_PonteiroDeArtistas(char id[], float seguidores, char nome[], int popularidade){
    int tamanhoNome = 0;

    tArtista *p_Artista = NULL;
    p_Artista = (tArtista *)malloc(1 * sizeof(tArtista));
    
    strcpy(p_Artista->id, id);
    tamanhoNome = strlen(nome);
    p_Artista->nome = (char*)malloc((tamanhoNome+1) * sizeof(char));
    strcpy(p_Artista->nome, nome);

    p_Artista->seguidores = seguidores;
    p_Artista->popularidade = popularidade;
    p_Artista->qtd_generos = 0;
    return p_Artista;
}


//--------------------leitura de arquivos--------------------------------
tArtista** Le_Artistas(FILE* artista_file, tArtista** pp_Artistas){
    tArtista *p_Artista = NULL;
    int i = 0;
    char todos_generos[1000], nome[1000], id[25];
    float seguidores = 0;
    int popularidade = 0;
    
    Reseta_NomeGenero(nome, todos_generos);

    while(fscanf(artista_file,"%[^;];%f;%[^;];%[^;];%d\n", id, &seguidores, todos_generos, nome, &popularidade)==5){
        pp_Artistas = (tArtista**)realloc(pp_Artistas, (i+1) * sizeof(tArtista*));
        
        p_Artista = Inicializa_PonteiroDeArtistas(id, seguidores, nome, popularidade);
        p_Artista->generos = Retorna_ListaDeGeneros(todos_generos, p_Artista);

        pp_Artistas[i] = p_Artista;
        
        //Imprime_Artista(p_Artista);
        //printf("\n");
        i++;
        
        Reseta_NomeGenero(nome, todos_generos);
    }

    int aux = 0;
    aux = Acesso_QuantidadeArtistas(i, VERDADE); // guarda a quantidade de artistas na função p/ retornar depois.
    
    return pp_Artistas;
}

//--------------------------auxiliares--------------------------------

char* Retorna_Id(tArtista* p_Artista){
    return p_Artista->id;
}


void Reseta_NomeGenero(char* nome, char* genero){
    int i = 0;
    for(i=0; i<(strlen(nome)+1); i++){
        nome[i] ='\0';
    }
    for(i=0; i<(strlen(genero)+1); i++){
        genero[i] = '\0';
    }
}

char** Retorna_ListaDeGeneros(char* str, tArtista* artista){
    char* genero;
    char** ListaDeGeneros = (char**)malloc(sizeof(char)*(strlen(str)+1));
    int i = 0;

    genero = strtok (str,"|");
    
    while (genero != NULL){
        ListaDeGeneros[i] = genero;
        i++;
        genero = strtok (NULL,"|");
    }

    artista->qtd_generos = i;
    return ListaDeGeneros;
}

int Acesso_QuantidadeArtistas(int x, int trocar){
    static int qtdArtistas = 0;
    if (trocar){
        qtdArtistas = x;
    }
    return qtdArtistas;
}

//--------------------------impressao--------------------------------

void Imprime_Artista(tArtista *artista){
    printf("Id: %s Seguidores: %.1f ", artista->id, artista->seguidores);
    printf("Generos: ");
    
    int i = 0;
    for(i=0; i<(artista->qtd_generos); i++){
        printf("%s | ", artista->generos[i]);
    }

    printf("Nome: %s Popularidade: %d\n", artista->nome, artista->popularidade);
}

void ImprimeNomeDosArtistas(tArtista **pp_Artistas, int qtdArtistasRegistrados){
    int i = 0;
    for (i = 0; i < qtdArtistasRegistrados; i++){
        printf("%s ", pp_Artistas[i]->nome);
    }
}

