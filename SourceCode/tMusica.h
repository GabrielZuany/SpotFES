#ifndef _TMUSICA_H_
#define _TMUSICA_H_
#include "tArtista.h"
#include "tPropriedades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tMusica tMusica;


//------------------------leitura de arquivo----------------------------

/**
 * @brief Leitura e registro de dados do arquivo passado pelo argv.
 * 
 * @param tracks_file ptr FILE* para o arquivo a ser lido.
 * @param pp_Musicas Vetor de structs do tipo tMusica (ponteiro duplo);
 * @param pp_Artistas  Vetor de structs do tipo tArtistas (ponteiro duplo);
 * @return tMusica** Array de structs cadastradas com as informações de cada música lida.
 */
tMusica** Le_Musicas(FILE* tracks_file, tMusica** pp_Musicas, tArtista** pp_Artistas);



//-----------------------inicializacao de ponteiro----------------------

/**
 * @brief Aloca a memória necessária para inicializar o ponteiro de ponteiros.
 * 
 * @return tMusica** Array de ponteiros alocado na memória.
 */
tMusica** Inicializa_PonteiroDePonteiroDeMusicas();

/**
 * @brief Registra as informações da música atual para a struct na posição X do array.
 * 
 * @param id_musica str com código hash.
 * @param nome str com o nome da música.
 * @param popularidade int com a popularidade medida de 0 a 100.
 * @param duracao duração da música em milisegundos.
 * @param Nome_artistas lista com o nome dos artistas.
 * @param id_artistas código hash dos artistas.
 * @param data_lancamento data da música.
 * @param pp_Artistas Array de ponteiros.
 * @return tMusica* ponteiro com as informações registradas.
 */
tMusica* Inicializa_PonteiroDeMusica(char id_musica[], char nome[], int popularidade, int duracao, int explicit, char Nome_artistas[], char id_artistas[], char data_lancamento[], tArtista** pp_Artistas);

/**
 * @brief Procura pela hash do artista da musica atual na base de dados lida no artists.csv
 * 
 * @param p_Musica ponteiro que indica a musica cujo hash será o parâmetro de busca.
 * @param pp_Artistas base de dados dos artidas cadastrados.
 * @return tArtista** array de artistas da musica com todas as informações indexadas.
 */
tArtista** Registra_ArtistasDaMusica(tMusica* p_Musica, tArtista** pp_Artistas);


//-------------------------------aux-------------------------------------

/**
 * @brief Imprime as informações relacionadas à música.
 * 
 * @param p_Musica ponteiro para a posicção de memória da struct.
 */
void Imprime_Musica(tMusica* p_Musica);

/**
 * @brief Reseta as strings com '\0' em todas as posições do array;
 * 
 * @param nomeMusica str a ser resetada.
 * @param idMusica str a ser resetada.
 * @param dataDeLancamento str a ser resetada.
 * @param idAgrupado str a ser resetada.
 */
void Reseta_Informacoes(char* nomeMusica, char* idMusica, char* dataDeLancamento, char* idAgrupado);

/**
 * @brief Recebe uma string com os nomes separados por '|'. Por meio da strtok() há o retorno de um array das palavras separadas por '|'.
 * 
 * @param str string a ser separada.
 * @param p_musica ponteiro para a posição.
 * @return char** array de palavras.
 */
char** RetornaLista_ID(char* str, tMusica* p_musica);

#endif