#ifndef _TMUSICA_H_
#define _TMUSICA_H_
#include "tArtista.h"
#include "tPropriedades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct tMusica tMusica;


//==============================leitura de arquivo====================================
/**
 * @brief Leitura e registro de dados do arquivo passado pelo argv.
 * @param tracks_file ptr FILE* para o arquivo a ser lido.
 * @param pp_Musicas Vetor de structs do tipo tMusica (ponteiro duplo);
 * @param pp_Artistas  Vetor de structs do tipo tArtistas (ponteiro duplo);
 * @return tMusica** Array de structs cadastradas com as informações de cada música lida.
 */
tMusica** Le_Musicas(FILE* tracks_file, tMusica** pp_Musicas, tArtista** pp_Artistas);



//==============================inicializacao de ponteiro==============================
/**
 * @brief Aloca a memória necessária para inicializar o ponteiro de ponteiros.
 * @return tMusica** Array de ponteiros alocado na memória.
 */
tMusica** Inicializa_PonteiroDePonteiroDeMusicas();

/**
 * @brief Registra as informações da música atual para a struct na posição X do array.
 * @param id_musica str com código hash.
 * @param nome str com o nome da música.
 * @param popularidade int com a popularidade medida de 0 a 100.
 * @param duracao duração da música em milisegundos.
 * @param Nome_artistas lista com o nome dos artistas.
 * @param id_artistas código hash dos artistas.
 * @param data_lancamento data da música.
 * @param pp_Artistas Array de ponteiros.
 * @param posicaoNoArray posicao no array da musica atual.
 * @return tMusica* ponteiro com as informações registradas.
 */
tMusica* Inicializa_PonteiroDeMusica(char id_musica[], char nome[], int popularidade, int duracao, int explicit, char Nome_artistas[], char id_artistas[], char data_lancamento[], tArtista** pp_Artistas, int posicaoNoArray);

/**
 * @brief Procura pela hash do artista da musica atual na base de dados lida no artists.csv
 * @param p_Musica ponteiro que indica a musica cujo hash será o parâmetro de busca.
 * @param pp_Artistas base de dados dos artidas cadastrados.
 * @return tArtista** array de artistas da musica com todas as informações indexadas.
 */
tArtista** Registra_ArtistasDaMusica(tMusica* p_Musica, tArtista** pp_Artistas);
//======================================aux==========================================
/**
 * @brief Retorna um ponteiro com str do nome.
 * @param p_Musica vetor na posição X a ser retornado o nome.
 * @return char* ponteiro para a string
 */
char* Retorna_NomeMusica(tMusica* p_Musica);

/**
 * @brief Reseta as strings com '\0' em todas as posições do array;
 * @param nomeMusica str a ser resetada.
 * @param idMusica str a ser resetada.
 * @param dataDeLancamento str a ser resetada.
 * @param idAgrupado str a ser resetada.
 */
void Reseta_Informacoes(char* nomeMusica, char* idMusica, char* dataDeLancamento, char* idAgrupado);

/**
 * @brief Recebe uma string com os nomes separados por '|'. Por meio da strtok() há o retorno de um array das palavras separadas por '|'.
 * @param str string a ser separada.
 * @param p_musica ponteiro para a posição.
 * @return char** array de palavras.
 */
char** RetornaLista_ID(char* str, tMusica* p_musica);

/**
 * @brief recebe um valor booleano que informa se ela deve trocar o valor salvo e retorna-lo ou apenar retorna-lo sem alteracoes.
 * @param x valor usado para a alteracao, caso ocorra.
 * @param trocar valor booleano indicando se a função irá registrar o valor ou retornar.
 */
int Acesso_QuantidadeMusicas(int x, int trocar);

/**
 * @brief Dada uma posição do vetor de structs retornar a struct interna referente às propriedades.
 * @param p_musica vetor de structs.
 * @return tPropriedades* struct interna referente às propriedades.
 */
tPropriedades* Retorna_PropriedadesDaMusica(tMusica* p_musica);

/**
 * @brief recebe um valor e armazena no ponteiro de musica
 * @param pMusica ponteiro do tipo musica
 * @param x valor a ser adicionado no ponteiro
 */
void Incrementa_X_Em_qtd_PresencaEmPlaylist(tMusica* pMusica, int x);

/**
 * @brief retorna o ID da musica passada como parametro
 * @param p_Musica ponteiro do tipo musica
 * @return char* id musica.
 */
char* Retorna_ID_Musica(tMusica* p_Musica);

/**
 * @brief incrementa em X o valor de presencas em playlists armazenado no tipo tMusica
 * @param pMusica ponteiro do tipo tMusica
 * @param x valor a ser incrementado
 */
void Incrementa_X_Em_qtd_PresencaMusicaEmPlaylist(tMusica* pMusica, int x);

/**
 * @brief Retorna o maior numero de ocorrencias de musicas em uma playlist (necessario para relatorio de musicas).
 * @param pp_Musicas base de musicas.
 * @return int maior numero de ocorrencias de musicas em uma playlist.
 */
int MaiorNumeroDePresencas_Musicas(tMusica** pp_Musicas);

/**
 * @brief varre todos os artistas icrementando a quantidade de presenca.
 * @param pMusica ponteiro da musica na posicao do vetor de musicas.
 */
void Incrementa_X_EmTodosOsArtistasDaMusica(tMusica *pMusica);

/**
 * @brief Reseta a variavel 'int acessada' para 0 de todas as musicas no ponteiro de ponteiro de tMusica.
 * 
 * @param pp_Musicas vetor de structs tMusica.
 * @param qtdMusicas quantidade de musicas a serem resetadas.
 */
void ResetaMusicasAcessadas(tMusica** pp_Musicas, int qtdMusicas);

/**
 * @brief Dada uma musica, acessa e retorna o valor de determinada propriedade da musica.
 * 
 * @param pMusica musica a qual a propriedade será acessada.
 * @param indicePropriedade indice da propriedade a ser acessada.
 * @return float valor numérico contido na posição do array de propriedades.
 */
float RetornaPropriedadeXdaMusica_ViaMusica(tMusica* pMusica, int indicePropriedade);

/**
 * @brief calcula e retorna o indice da posição do menor valor entre um A e um B.
 * @param distanciaEuclidiana vetor de valores em ponto flutuante.
 * @param i posição no array.
 * @param qtd_Musicas quantidade de vezes que será comparada.
 * @return int indice da posição do menor.
 */
int MenorEntreAeB(double distanciaEuclidiana[], int i, int qtd_Musicas);

/**
 * @brief Ordena o vetor de todas as distancias euclidianas calculadas.
 * @param distanciaEuclidiana array com todos os valores.
 * @param qtd_Musicas quantidade de valores.
 */
void OrdenaVetorDouble(double* distanciaEuclidiana, int qtd_Musicas);

/**
 * @brief Calucla a distancia euclidiana entre duas musicas raiz{(somatorio de: [(x-y)^2]/n)}.
 * @param propriedades_MusicaAtual propriedade da musica X.
 * @param p_PropriedadesMusicaIdeal prppriedade da musica Y.
 * @param qtd_propriedades quantidade de propriedades.
 * @return double valor da distancia euclidiana.
 */
double Calcula_DistanciaEuclidiana(float* propriedades_MusicaAtual, float* p_PropriedadesMusicaIdeal, int qtd_propriedades);

/**
 * @brief Dada uma musica, acessa e retorna o valor de determinada propriedade da musica.
 * @param pMusica musica a qual a propriedade será acessada.
 * @param indicePropriedade indice da propriedade a ser acessada.
 * @return float valor numérico contido na posição do array de propriedades.
 */
float AcessoProPriedadeXDaMusica(tMusica* pMusica, int indicePropriedade);



//====================================impressao======================================
/**
 * @brief Imprime todos os artistas da musica atual.
 * @param p_Musica musica atual.
 */
void Imprime_Artistas_da_Musica(tMusica* p_Musica);

/**
 * @brief contendo as músicas que foram adicionadas em playlists ordenadas de forma decrescente pelo número de playlists às quais elas foram adicionadas.
 * @param RelatorioMusica arquivo aberto para escrita.
 * @param pp_Musicas base de musicas.
 */
void ImprimeRelatorioMusicaNoArquivo(FILE * RelatorioMusica, tMusica **pp_Musicas);

/**
 * @brief Imprime as informações relacionadas à música.
 * @param p_Musica ponteiro para a posicção de memória da struct.
 */
void Imprime_Musica_Recomendada(tMusica* p_Musica);

/**
 * @brief Imprime atributos da musica
 * @param pMusica ponteiro para struct musica
 */
void Imprime_Funcao_BuscarMusica(tMusica *pMusica);

/**
 * @brief imprime todos os atributos de uma musica
 * @param p_Musica ponteiro para struct musica
 */
void Imprime_ListarUmaMusica(tMusica* p_Musica);

/**
 * @param ppMusica array de ponteiros de musica 
 * @param qtdMusicas quantidade total de musicas alocadas
 */
void ImprimeTodasAsMusicasDaPlaylist(tMusica **ppMusica, int qtdMusicas);

/**
 * @brief Calcula as muscias mais proximas em termos das distancias euclidianas e já imprime na stdout.
 * @param pp_Musicas base de muscias a serem comparadas.
 * @param p_PropriedadesMusicaIdeal a média dos valores das propriedades baseada nas musicas da playlist.
 * @param x quantidade de musicas que serão recomendadas.
 */
void ImprimeXMusicasMaisProximas(tMusica **pp_Musicas, float *p_PropriedadesMusicaIdeal, int x);


//==========================liberacao de musicas=====================
/**
 * @brief varre as musicas liberando-as
 * @param pp_musica array de musicas
 */
void LiberaTodasAsMusicas(tMusica** pp_musica);

/**
 * @brief libera uma unica musica
 * @param musica ponteiro de musica
 */
void LiberaMusica(tMusica* musica);

#endif