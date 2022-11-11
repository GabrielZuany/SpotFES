#include "tMusica.h"
#define multiplicador_malloc 1
#define FALSO 0
#define VERDADE 1
#define QTD_PROPRIEDADES_ANALISE 8

struct tMusica{
    char data_lancamento[11];
    char id_musicas[25]; //hash alfanumerico
    char **id_artistas;
    char *nome;
    int popularidade;
    int duracao_ms;
    int explicit; //uso booleano
    int qtd_artistas_registrados_na_musica;
    int qtd_artistas_na_musica;
    int qtd_PresencaEmPlaylist;
    int posicaoNoArray;
    int acessada;
    double DistanciaRelativaEntreDuasMusicas;
    tArtista **artistas;
    tPropriedades* propriedades;
};

//-----------------------inicializacao de ponteiro----------------------
tMusica** Inicializa_PonteiroDePonteiroDeMusicas(){
    tMusica **pp_Musica = NULL;
    pp_Musica = (tMusica**)malloc(multiplicador_malloc * sizeof(tMusica*));
    return pp_Musica;
}

tMusica* Inicializa_PonteiroDeMusica(char id_musica[], char nome[], int popularidade, int duracao, int explicit, char Nome_artistas[], char id_artistas[], char data_lancamento[], tArtista** pp_Artistas, int posicaoNoArray){
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
    p_Musica->posicaoNoArray = posicaoNoArray;
    p_Musica->id_artistas = RetornaLista_ID(id_artistas, p_Musica);
    p_Musica->artistas = Registra_ArtistasDaMusica(p_Musica, pp_Artistas);
    p_Musica->qtd_PresencaEmPlaylist = 0;
    p_Musica->DistanciaRelativaEntreDuasMusicas = (double)0;
    p_Musica->acessada = 0;
    return p_Musica;
}


//--------------------leitura de arquivos--------------------------------
tMusica** Le_Musicas(FILE* tracks_file, tMusica** pp_Musicas, tArtista** pp_Artistas){
    tMusica* p_Musica = NULL;
    int i = 0;
    tArtista **artistas;
 
    //primeiro scanf
    char idMusica[25], nomeMusica[1000], nomeArtistas[10000], idArtistas_AGRUPADO[10000], dataDeLancamento[11];
    int popularidade = 0, tempo_ms = 0, explicit = 0; 
    //segundo sacnf
    float danceabilidade = 0.0, energia = 0.0, loudness = 0.0, speechiness = 0.0, acousticness = 0.0, instrumentalness = 0.0, liveness = 0.0, valence = 0.0, tempo = 0.0;
    int key = 0, mode = 0, time_signature = 0;

    
    while(fscanf(tracks_file,"%[^;];%[^;];%d;%d;%d;%[^;];%[^;];%[^;];",idMusica, nomeMusica, &popularidade, &tempo_ms, &explicit, nomeArtistas, idArtistas_AGRUPADO, dataDeLancamento) == 8){
        fscanf(tracks_file,"%f;%f;%d;%f;%d;%f;%f;%f;%f;%f;%f;%d\n", &danceabilidade, &energia, &key, &loudness, &mode, &speechiness, &acousticness, &instrumentalness, &liveness, &valence, &tempo, &time_signature);

        pp_Musicas = (tMusica**)realloc(pp_Musicas, ((i+1) * sizeof(tMusica*)));
        p_Musica = Inicializa_PonteiroDeMusica(idMusica, nomeMusica, popularidade, tempo_ms, explicit, nomeArtistas, idArtistas_AGRUPADO, dataDeLancamento, pp_Artistas, i);

        p_Musica->propriedades = Insere_PropriedadesNaMusica(danceabilidade, energia, key, loudness, mode, speechiness, acousticness, instrumentalness, liveness, valence, tempo, time_signature);
        pp_Musicas[i] = p_Musica;
        
        //Imprime_Musica(pp_Musicas[i]);
        i++;    
        Reseta_Informacoes(nomeMusica, idMusica, dataDeLancamento, idArtistas_AGRUPADO);
    }

    Acesso_QuantidadeMusicas(i, VERDADE);

    return pp_Musicas;
}


//-----------------------auxiliares--------------------------
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
    tArtista** artistas_da_musica = (tArtista**)malloc(sizeof(tArtista*));

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

int Acesso_QuantidadeMusicas(int x, int trocar){
    static int qtdMusicas = 0;
    if (trocar){
        qtdMusicas = x;
    }
    return qtdMusicas;
}

char** RetornaLista_ID(char* str, tMusica* p_musica){
    char* id;
    char** ListaDeArtistas = (char**)malloc(sizeof(char*) * (strlen(str)+1));
    int i = 0;
    id = strtok (str,"|");

    while (id != NULL){
        ListaDeArtistas[i] = id;
        i++;
        id = strtok (NULL,"|");
    }
    p_musica->qtd_artistas_na_musica = i;
    free(id);
    return ListaDeArtistas;
}

char* Retorna_NomeMusica(tMusica* p_Musica){
    return p_Musica->nome;
}

tPropriedades* Retorna_PropriedadesDaMusica(tMusica* p_musica){
    return p_musica->propriedades;
}

char* Retorna_ID_Musica(tMusica* p_Musica){
    return p_Musica->id_musicas;
}

void Incrementa_X_Em_qtd_PresencaMusicaEmPlaylist(tMusica* pMusica, int x){
    pMusica->qtd_PresencaEmPlaylist += x;
}

void Incrementa_X_EmTodosOsArtistasDaMusica(tMusica *pMusica){
    int i = 0, qtdArtistasRegistrados = pMusica->qtd_artistas_registrados_na_musica;
    for(i = 0; i < qtdArtistasRegistrados; i++){
        Incrementa_X_Em_qtd_PresencaArtistaEmPlaylist(pMusica->artistas[i], 1);
    }
}

float AcessoProPriedadeXDaMusica(tMusica* pMusica, int indicePropriedade){
    float x = RetornaPropriedadeXdaMusica(pMusica->propriedades, indicePropriedade);
    return x;
}

void ImprimeXMusicasMaisProximas(tMusica **pp_Musicas, float *p_PropriedadesMusicaIdeal, int qtd_MelhoresMusicas){
    int iMusicas = 0, iPropriedades = 0, posicao = 1, indiceAtualMelhores = 0, aux_encerrarLoop = 0;
    int qtd_Musicas = Acesso_QuantidadeMusicas(0, FALSO);
    float propriedades_MusicaAtual[QTD_PROPRIEDADES_ANALISE];
    double DistanciaEuclidianaDeTodasAsMusicas[qtd_Musicas];


    for(iMusicas = 0; iMusicas < qtd_Musicas; iMusicas++){
        for(iPropriedades = 0; iPropriedades < QTD_PROPRIEDADES_ANALISE; iPropriedades++){
            propriedades_MusicaAtual[iPropriedades] = RetornaPropriedadeXdaMusica(pp_Musicas[iMusicas]->propriedades, iPropriedades);
        } 
        pp_Musicas[iMusicas]->DistanciaRelativaEntreDuasMusicas = Calcula_DistanciaEuclidiana(propriedades_MusicaAtual , p_PropriedadesMusicaIdeal, QTD_PROPRIEDADES_ANALISE);
        DistanciaEuclidianaDeTodasAsMusicas[iMusicas] = pp_Musicas[iMusicas]->DistanciaRelativaEntreDuasMusicas;
    }
    OrdenaVetorDouble(DistanciaEuclidianaDeTodasAsMusicas, qtd_Musicas);

    while (indiceAtualMelhores < qtd_MelhoresMusicas){

        for(iMusicas = 0; iMusicas < qtd_Musicas; iMusicas++){

            if( (pp_Musicas[iMusicas]->DistanciaRelativaEntreDuasMusicas == DistanciaEuclidianaDeTodasAsMusicas[indiceAtualMelhores]) && (pp_Musicas[iMusicas]->acessada == 0) ){

                pp_Musicas[iMusicas]->acessada = 1;
                printf("Musica no rank %d de aproximidade: ", posicao);
                Imprime_Musica_Recomendada(pp_Musicas[iMusicas]);
                printf("\nDistancia entre a playlist e a musica: %lf\n", pp_Musicas[iMusicas]->DistanciaRelativaEntreDuasMusicas);
                printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");
                posicao++;
                indiceAtualMelhores++;
                break;
            
            }
        }
    }
    ResetaMusicasAcessadas(pp_Musicas, qtd_Musicas);
}

void ResetaMusicasAcessadas(tMusica** pp_Musicas, int qtdMusicas){
    int i=0;
    for(; i<qtdMusicas; i++){
        pp_Musicas[i]->acessada = 0;
    }
}

int MenorEntreAeB(double distanciaEuclidiana[], int a, int qtd_Musicas){
    int indiceMenor = a;
    double menor = distanciaEuclidiana[a];
    a++;
    for(a; a < qtd_Musicas; a++){
        if (distanciaEuclidiana[a] < menor){
            menor = distanciaEuclidiana[a];
            indiceMenor = a;
        }
    }
    return indiceMenor;
}

void OrdenaVetorDouble(double* distanciaEuclidiana, int qtd_Musicas){
    int i = 0, j, indiceMenor = 0; 
    double aux = 0;

    for(i = 0; i < qtd_Musicas; i++){
        indiceMenor = MenorEntreAeB(distanciaEuclidiana, i+1, qtd_Musicas); 
        if(distanciaEuclidiana[i] > distanciaEuclidiana[indiceMenor]){
            aux = distanciaEuclidiana[i];
            distanciaEuclidiana[i] = distanciaEuclidiana[indiceMenor];
            distanciaEuclidiana[indiceMenor] = aux;
        }
    }
}

double Calcula_DistanciaEuclidiana(float* propriedades_MusicaAtual, float* p_PropriedadesMusicaIdeal, int qtd_propriedades){
    int i;
    double distancia_euclidiana = 0;

    for(i=0; i<qtd_propriedades; i++){
        distancia_euclidiana+= pow( (propriedades_MusicaAtual[i] - p_PropriedadesMusicaIdeal[i]) , 2);
    }
    distancia_euclidiana = sqrt(distancia_euclidiana);

    return distancia_euclidiana;
}

float RetornaPropriedadeXdaMusica_ViaMusica(tMusica* pMusica, int indicePropriedade){
    float x = 0;
    x = RetornaPropriedadeXdaMusica(pMusica->propriedades, indicePropriedade);
    return x;
}


//============================impressao========================================
void Imprime_Funcao_BuscarMusica(tMusica *pMusica){
    printf("Musica: %s\n", pMusica->nome);
    printf("Indice: %d      ID: %s     \n", pMusica->posicaoNoArray, pMusica->id_musicas);
    printf("Nome dos Artistas: ");
    Imprime_NomeDosArtistas(pMusica->artistas, pMusica->qtd_artistas_registrados_na_musica);
    printf("\n");
    printf("--------------------------------------------\n");
}

void Imprime_ListarUmaMusica(tMusica* p_Musica){
    printf("--------------------------------------------\n");
    Imprime_Artistas_da_Musica(p_Musica);
    Imprime_PropriedadesDaMusisca(p_Musica->propriedades);
    printf("\n");
    printf("--------------------------------------------\n");
}

void ImprimeTodasAsMusicasDaPlaylist(tMusica **ppMusica, int qtdMusicas){
    int i;
    for(i = 0; i < qtdMusicas; i++){
        printf("Posicao Na Playlist: %d Musica: %s\n", i, ppMusica[i]->nome);
    }
    if (qtdMusicas == 0){
        printf("Nenhuma musica regristrada!\n");
    }
}

void Imprime_Artistas_da_Musica(tMusica* p_Musica){
    int i;
    int qtdArtistas = p_Musica->qtd_artistas_registrados_na_musica;

    for(i=0; i<qtdArtistas; i++){
        Imprime_Artista(p_Musica->artistas[i]);
        printf("\n");
    }
}

void Imprime_Musica_Recomendada(tMusica* p_Musica){
    printf("PosicaoArray: %d | ID: %s | Nome: %s" ,p_Musica->posicaoNoArray, p_Musica->id_musicas, p_Musica->nome);
}

void ImprimeRelatorioMusicaNoArquivo(FILE * RelatorioMusica, tMusica **pp_Musicas){
    int qtdPresencas = 0, iLinha = 0, iColuna = 0, qtdMusicas = 0;
    qtdPresencas = MaiorNumeroDePresencas_Musicas(pp_Musicas);
    qtdMusicas = Acesso_QuantidadeMusicas(0, FALSO);
    int Acessou = 0, jaImprimiuAlgo = 0;

    for (iLinha = qtdPresencas; iLinha > 0; iLinha--){
        
        for(iColuna = 0; iColuna < qtdMusicas; iColuna++){
            
            if (pp_Musicas[iColuna]->qtd_PresencaEmPlaylist == iLinha){
                if (!Acessou){
                    if(jaImprimiuAlgo){
                        fprintf(RelatorioMusica,"\n");
                    }
                    fprintf(RelatorioMusica,"Musicas com %d presencas em playlists:\n", iLinha);
                    Acessou = 1;
                    jaImprimiuAlgo = 1;
                }
                
                fprintf(RelatorioMusica, "Nome: %s\n", pp_Musicas[iColuna]->nome);
            }
        }
        Acessou = 0;
    }
}

int MaiorNumeroDePresencas_Musicas(tMusica** pp_Musicas){
    int MaiorQtdPresenca = 0, i;
    int qtdMusicas = Acesso_QuantidadeMusicas(0, FALSO);    

    for(i=0; i<qtdMusicas; i++){
        if(pp_Musicas[i] -> qtd_PresencaEmPlaylist > MaiorQtdPresenca){
            MaiorQtdPresenca = pp_Musicas[i] -> qtd_PresencaEmPlaylist;
        }
    }

    return MaiorQtdPresenca;
}


//======================== Liberação de memória ===========================

void LiberaTodasAsMusicas(tMusica** pp_musica){
    int qtd = Acesso_QuantidadeMusicas(0, FALSO);
    int i = 0;
    for(i=0; i<qtd; i++){
        LiberaMusica(pp_musica[i]);
        free(pp_musica[i]);
    }
    free(pp_musica);
}

void LiberaMusica(tMusica* musica){
    free(musica->propriedades);
    free(musica->nome);
    free(musica->artistas);
    free(musica->id_artistas);
}


tMusica* Acesso_MusicaDeIndiceX(tMusica** pp_Musicas , int indiceMusica){
    return pp_Musicas[indiceMusica];
}

int Acesso_IndiceNoArrayMusicaX(tMusica** pp_Musicas , int indice){
    return pp_Musicas[indice]->posicaoNoArray;
}
