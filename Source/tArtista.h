#ifndef _TARTISTA_H_
#define _TARTISTA_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tArtista tArtista;

//===========================inicializacao de ponteiro===========================
/**
 * @brief Aloca memória para o ponteiro de ponteiro (lista de artistas do tipo tArtistas).
 * @return tArtista** endereço de memória (já alocada) inicial do ponteiro (posição 0). 
 */
tArtista** Inicializa_PonteiroDePonteiroDeArtistas();

/**
 * @brief  Aloca a memória necessária para uma struct tArtista e já preenche o item da posição X do tipo com as devidas informações.
 * @param id código hash referente à codificação do nome do artista.
 * @param seguidores número de seguidores do artista.
 * @param nome nome do artista não codificado.
 * @param popularidade índice de popularidade do artista (0 a 100).
 * @return tArtista* endereço de memória (já alocada e preenchida) inicial do ponteiro.
 */
tArtista* Inicializa_PonteiroDeArtistas(char id[], float seguidores, char nome[], char todos_generos[], int popularidade);
//===========================leitura de arquivos===========================

/**
 * @brief le cada linha do arquivo de entrada separando cada informacao em variaveis locais em loop, inicializando um ponteiro de artista e armazenando esses valores nesse, depois salva o novo artista alocado em um array de artistas e continua o loop.
 * @param artista_file ponteiro do tipo FILE que contém o arquivo a ser lido.
 * @param pp_Artistas Ponteiro duplo (vetor de ponteiros) do tipo tArtista.
 * @return tArtista** Vetor de ponteiros já preenchido (e alocado dinâmiacamente) com os artistas do arquivo.
 */
tArtista** Le_Artistas(FILE* artista_file, tArtista** pp_Artistas);
//===========================auxilaires====================================
/**
 * @brief Retorna o hash do ponteiro dado.
 * @param p_Artista endereço de memória que o ponteiro aponta.
 * @return char* str com id.
 */
char* Retorna_Id(tArtista* p_Artista);

/**
 * @brief recebe uma str separada por '|' e a divide em stgs diferentes, genero a genero
 * @param str strg generica com '|' 
 * @param artista ponteiro do artista referente a strg
 * @return char** 
 */
char** Retorna_ListaDeGeneros(char* str, tArtista* artista);

/**
 * @brief varre as strgs nome e genero colocando '\0' em todas as posicoes
 * @param nome vetor de caracteres a serem resetados em forma de string (todo o vetor será preenchido com '\0').
 * @param genero vetor de caracteres a serem resetados em forma de string (todo o vetor será preenchido com '\0').
 */
void Reseta_NomeGenero(char* nome, char* genero);

/**
 * @brief recebe um valor booleano que informa se ela deve trocar o valor salvo e retorna-lo ou apenar retorna-lo sem alteracoes.
 * @param x valor usado para a alteracao, caso ocorra.
 * @param trocar valor booleano indicando se a função irá registrar o valor ou retornar.
 */
int Acesso_QuantidadeArtistas(int x, int trocar);

/**
 * @brief aumenta em x a quantidade de presencas de um artista
 * @param pArtista ponteiro do tipo tArtista
 * @param x valor a ser adicionado
 */
void Incrementa_X_Em_qtd_PresencaArtistaEmPlaylist(tArtista *pArtista, int x);

/**
 * @brief varre todos os artistas e retorna o maior numero de presencas
 * @param pp_Artistas array de artistas
 * @return maior numero de presencas
 */
int MaiorNumeroDePresencas_Artistas(tArtista** pp_Artistas);

//============================impressao=============================
/**
 * @brief  imprime os dados armazenados no ponteiro artista
 * @param artista ponteiro para o artista da posição atual do vetor de artistas.
 */
void Imprime_Artista(tArtista *artista);

/**
 * @brief Imprime a str dentro do tipo tArtistas
 * @param pp_Artistas vetor de structs
 * @param qtdArtistas tamanho do vetor
 */
void Imprime_NomeDosArtistas(tArtista **pp_Artistas, int qtdArtistas);

/**
 * @brief gera relatorio contendo os artistas cujas músicas estão em playlists também ordenados pelo número de vezes que suas músicas foram adicionadas em playlists.
 * @param RelatorioArtista arquivo aberto para escrita
 * @param pp_Artistas array de artistas
 */
void ImprimeRelatorioArtistaNoArquivo(FILE * RelatorioArtista, tArtista** pp_Artistas);

//============liberacao de artistas=============
/**
 * @brief varre todos os artistas liberando-os
 * @param pp_Artistas array de artistas
 */
void LiberaTodosOsArtistas(tArtista** pp_Artistas);

/**
 * @brief libera um unico artista
 * @param pArtista ponteiro de artista
 */
void LiberaArtista(tArtista *pArtista);



#endif