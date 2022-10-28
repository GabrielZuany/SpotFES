#include "tMusica.h"
#define multiplicador_malloc 1
#define FALSO 0
#define VERDADE 1

struct tMusica{
    char id_musicas[25]; //hash alfanumerico
    char *nome;
    int popularidade;
    int duracao_ms;
    int explicit; //uso booleano
    tArtista **artistas;
    char **id_artistas;
    char data_lancamento[11];
    tPropriedades* propriedades;
    int qtd_artistas_registrados_na_musica;
    int qtd_artistas_na_musica;
};

//-----------------------inicializacao de ponteiro----------------------
tMusica** Inicializa_PonteiroDePonteiroDeMusicas(){
    tMusica **pp_Musica = NULL;
    pp_Musica = (tMusica**)malloc(multiplicador_malloc * sizeof(tMusica*));
    return pp_Musica;
}

tMusica* Inicializa_PonteiroDeMusica(char id_musica[], char nome[], int popularidade, int duracao, int explicit, char Nome_artistas[], char id_artistas[], char data_lancamento[], tArtista** pp_Artistas){
    int tamanhoNome = 0;
    tMusica* p_Musica = (tMusica*) malloc(sizeof(struct tMusica));

    //alocar memoria para musica->nome
    tamanhoNome = strlen(nome);
    p_Musica->nome = (char*)malloc((tamanhoNome+1) * sizeof(char));
    strcpy(p_Musica->nome, nome);

    strcpy(p_Musica->id_musicas, id_musica);
    strcpy(p_Musica->nome, nome);
    strcpy(p_Musica->data_lancamento, data_lancamento);
    p_Musica->popularidade = popularidade;
    p_Musica->duracao_ms = duracao;
    p_Musica->explicit = explicit;
    p_Musica->id_artistas = RetornaLista_ID(id_artistas, p_Musica);
    p_Musica->artistas = Registra_ArtistasDaMusica(p_Musica, pp_Artistas);
    return p_Musica;
}

//--------------------leitura de arquivos--------------------------------
tMusica** Le_Musicas(FILE* tracks_file, tMusica** pp_Musicas, tArtista** pp_Artistas){
    tMusica* p_Musica = NULL;
    int i = 0;
    tArtista **artistas;
    char **id_artistas;
 
    //primeiro scanf
    char idMusica[25], nomeMusica[1000], nomeArtistas[10000], idArtistas_AGRUPADO[10000], dataDeLancamento[11];
    int popularidade = 0, tempo_ms = 0, explicit = 0; 
    //segundo sacnf
    float danceabilidade = 0.0, energia = 0.0, loudness = 0.0, speechiness = 0.0, acousticness = 0.0, instrumentalness = 0.0, liveness = 0.0, valence = 0.0, tempo = 0.0;
    int key = 0, mode = 0, time_signature = 0;

    
    while(fscanf(tracks_file,"%[^;];%[^;];%d;%d;%d;%[^;];%[^;];%[^;];",idMusica, nomeMusica, &popularidade, &tempo_ms, &explicit, nomeArtistas, idArtistas_AGRUPADO, dataDeLancamento) == 8){
        fscanf(tracks_file,"%f;%f;%d;%f;%d;%f;%f;%f;%f;%f;%f;%d\n", &danceabilidade, &energia, &key, &loudness, &mode, &speechiness, &acousticness, &instrumentalness, &liveness, &valence, &tempo, &time_signature);

        pp_Musicas = (tMusica**)realloc(pp_Musicas, ((i+1) * sizeof(tMusica*)));
        p_Musica = Inicializa_PonteiroDeMusica(idMusica, nomeMusica, popularidade, tempo_ms, explicit, nomeArtistas, idArtistas_AGRUPADO, dataDeLancamento, pp_Artistas);

        p_Musica->propriedades = Insere_PropriedadesNaMusica(danceabilidade, energia, key, loudness, mode, speechiness, acousticness, instrumentalness, liveness, valence, tempo, time_signature);
        pp_Musicas[i] = p_Musica;

        Imprime_Musica(pp_Musicas[i]);
        i++;        
        Reseta_Informacoes(nomeMusica, idMusica, dataDeLancamento, idArtistas_AGRUPADO);
    }

    return pp_Musicas;
}

//-----------------------auxiliares--------------------------

void Imprime_Musica(tMusica* p_Musica){
    printf("%s;%s;%d;%d;%d;%s;",p_Musica->id_musicas, p_Musica->nome, p_Musica->popularidade, p_Musica->duracao_ms, p_Musica->explicit, p_Musica->data_lancamento);
    ImprimeNomeDosArtistas(p_Musica->artistas, p_Musica->qtd_artistas_registrados_na_musica);
    //ImprimePropriedadesDaMusisca(p_Musica->propriedades);
    //printf("   %d     %d ", p_Musica->qtd_artistas_na_musica, p_Musica->qtd_artistas_registrados_na_musica);
    printf("\n");
}

void Reseta_Informacoes(char* nomeMusica, char* idMusica, char* dataDeLancamento, char* idAgrupado){
    int i = 0, j = 0, k = 0, l = 0;
    int len_nome = strlen(nomeMusica), len_idMusica = strlen(idMusica), len_dataDeLancamento = strlen(dataDeLancamento), len_idAgrupado = strlen(idAgrupado);

    for(; i<len_nome, j<len_dataDeLancamento, k<len_idMusica, l<len_idAgrupado; i++, j++, k++, l++){
        nomeMusica[i] = '\0';
        dataDeLancamento[j] = '\0';
        idMusica[k] = '\0';
        idAgrupado[l] = '\0';
    }
}
 
tArtista** Registra_ArtistasDaMusica(tMusica* p_Musica, tArtista** pp_Artistas){
    tArtista** artistas_da_musica = (tArtista**) malloc(sizeof(tArtista*));

    int i, j, quantidadeArtistasRegistrados = 0;

    for(i=0; i < (p_Musica->qtd_artistas_na_musica); i++){  
        
        for(j=0; j<Acesso_QuantidadeArtistas(0, FALSO); j++){
            
            if(strcmp(Retorna_Id(pp_Artistas[j]), p_Musica->id_artistas[i]) == 0){
                artistas_da_musica[quantidadeArtistasRegistrados] = pp_Artistas[j];
                quantidadeArtistasRegistrados++;
                artistas_da_musica = (tArtista**)realloc(artistas_da_musica, (quantidadeArtistasRegistrados+1) * sizeof(tArtista*));
                break;
            }
        }
    }
    p_Musica->qtd_artistas_registrados_na_musica = quantidadeArtistasRegistrados;
    return artistas_da_musica;
}

char** RetornaLista_ID(char* str, tMusica* p_musica){
    char* id;
    char** ListaDeArtistas = (char**)malloc(sizeof(char)*(strlen(str)+1));
    int i = 0;
    id = strtok (str,"|");

    while (id != NULL){
        ListaDeArtistas[i] = id;
        i++;
        id = strtok (NULL,"|");
    }
    p_musica->qtd_artistas_na_musica = i;
    return ListaDeArtistas;
}


