#include "tArtista.h"
#define multiplicador_malloc 1
#define VERDADE 1
#define FALSO 0

struct tArtista{
    char id[25]; //hash alfanumerico
    float seguidores;
    char generos[1000]; //lista de generos
    char *nome;
    int popularidade;
    int qtd_generos;
    int qtd_PresencaEmPlaylist;
}; 

//===========================inicializacao de ponteiro===========================
tArtista** Inicializa_PonteiroDePonteiroDeArtistas(){
    tArtista **pp_Artistas = NULL;
    pp_Artistas = (tArtista**)malloc(multiplicador_malloc * sizeof(tArtista*));
    return pp_Artistas;
}
tArtista* Inicializa_PonteiroDeArtistas(char id[], float seguidores, char nome[], char todos_generos[], int popularidade){
    int tamanhoNome = 0, tamanhoGeneros = 0;

    tArtista *p_Artista = NULL;
    p_Artista = (tArtista *)malloc(1 * sizeof(tArtista));
    

    tamanhoNome = strlen(nome);
    tamanhoGeneros = strlen(todos_generos);
    p_Artista->nome = (char*)malloc((tamanhoNome+1) * sizeof(char));
    p_Artista->nome = (char*)malloc((tamanhoGeneros+1) * sizeof(char));
    strcpy(p_Artista->nome, nome);
    strcpy(p_Artista->generos, todos_generos);


    strcpy(p_Artista->id, id);
    p_Artista->seguidores = seguidores;
    p_Artista->popularidade = popularidade;
    p_Artista->qtd_generos = 0;
    p_Artista->qtd_PresencaEmPlaylist = 0;
    return p_Artista;
}
tArtista* Inicializa_PonteiroDeArtistas_SemParametros(){
    tArtista *pArtista = NULL;
    pArtista = (tArtista*)malloc(sizeof(struct tArtista));
    return pArtista;
}
//===========================leitura de arquivos=================================
tArtista** Le_Artistas(FILE* artista_file, tArtista** pp_Artistas){
    tArtista *p_Artista = NULL;
    int i = 0;
    char todos_generos[1000], nome[1000], id[25];
    float seguidores = 0;
    int popularidade = 0;
    
    Reseta_NomeGenero(nome, todos_generos);

    while(fscanf(artista_file,"%[^;];%f;%[^;];%[^;];%d\n", id, &seguidores, todos_generos, nome, &popularidade)==5){
        pp_Artistas = (tArtista**)realloc(pp_Artistas, (i+1) * sizeof(tArtista*));
        
        p_Artista = Inicializa_PonteiroDeArtistas(id, seguidores, nome, todos_generos,popularidade);
        //p_Artista->generos = Retorna_ListaDeGeneros(todos_generos, p_Artista);
        
        pp_Artistas[i] = p_Artista;

        i++;
        Reseta_NomeGenero(nome, todos_generos);
    }

    int aux = 0;
    aux = Acesso_QuantidadeArtistas(i, VERDADE); // guarda a quantidade de artistas na funcao p/ retornar depois.
    
    return pp_Artistas;
}
//===========================auxiliares==========================================
char* Retorna_Id(tArtista* artista){
    return artista->id;
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
void Incrementa_X_Em_qtd_PresencaArtistaEmPlaylist(tArtista *pArtista, int x){
    pArtista->qtd_PresencaEmPlaylist+= 1;
}
int MaiorNumeroDePresencas_Artistas(tArtista** pp_Artistas){
    int MaiorQtdPresenca = 0, i;
    int qtdMusicas = Acesso_QuantidadeArtistas(0, FALSO);    

    for(i=0; i<qtdMusicas; i++){
        if(pp_Artistas[i] ->qtd_PresencaEmPlaylist > MaiorQtdPresenca){
            MaiorQtdPresenca = pp_Artistas[i] -> qtd_PresencaEmPlaylist;
        }
    }

    return MaiorQtdPresenca;
}
//===========================impressao==========================================
void Imprime_Artista(tArtista *artista){
    printf("Nome: %s\nId: %s\nSeguidores: %.1f\nPopularidade: %d\nGeneros: %s", artista->nome, artista->id, artista->seguidores, artista->popularidade, artista->generos);
    printf("\n-----------------------------------------");
}
void Imprime_NomeDosArtistas(tArtista **pp_Artistas, int qtdArtistasRegistrados){
    int i = 0;
    for (i = 0; i < qtdArtistasRegistrados; i++){
        printf("%s ", pp_Artistas[i]->nome);
    }
}
void ImprimeRelatorioArtistaNoArquivo(FILE * RelatorioArtista, tArtista **pp_Artistas){
    int qtdPresencas = 0, iLinha = 0, iColuna = 0, qtdMusicas = 0;
    qtdPresencas = MaiorNumeroDePresencas_Artistas(pp_Artistas);
    qtdMusicas = Acesso_QuantidadeArtistas(0, FALSO);
    int Acessou = 0, jaImprimiuAlgo = 0;

    for (iLinha = qtdPresencas; iLinha > 0; iLinha--){

        for(iColuna = 0; iColuna < qtdMusicas; iColuna++){

            if (pp_Artistas[iColuna]->qtd_PresencaEmPlaylist == iLinha){
                if (!Acessou){
                    if(jaImprimiuAlgo){
                        fprintf(RelatorioArtista,"\n");
                    }
                    fprintf(RelatorioArtista,"Artistas com %d presencas em playlists:\n", iLinha);
                    Acessou = 1;
                    jaImprimiuAlgo = 1;
                }
                
                fprintf(RelatorioArtista, "Nome: %s\n", pp_Artistas[iColuna]->nome);
            }
        }
        Acessou = 0;
    }
}

