#ifndef _FUNCOESPRINCIPAIS_H_
#define _FUNCOESPRINCIPAIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tPlaylist.h"
#define VERDADE 1
#define FALSO 0

/**
 * @brief Abre o arquivo de artistas para leitura e armazenamento nas structs.
 * @param argc entradas do terminal referentes ao caminho do arquivo.
 * @param argv entradas do terminal referentes ao caminho do arquivo.
 * @return FILE* O arquivo aberto para a leitura.
 */
FILE* AbreArquivoArtistasCSV(int argc, char **argv);

/**
 * @brief Abre o arquivo de musicas para leitura e armazenamento nas structs.
 * @param argc entradas do terminal referentes ao caminho do arquivo.
 * @param argv entradas do terminal referentes ao caminho do arquivo.
 * @return FILE* O arquivo aberto para a leitura.
 */
FILE* AbreArquivoTracksCSV(char *argv[]);

/**
 * @brief Exibe menu de opcoes.
 */
void ExibeMenu();

/**
 * @brief Executa a função selecionada pelo usuário.
 * @param opcao opção desejada (int).
 * @param pp_Musicas Base de dados de musicas.
 * @param pp_ListaPlaylist array de tipos tPlaylist.
 * @return tPlaylist** Playlists atualizadas.
 */
tPlaylist** ExecutaOpcaoUsuario(int opcao, tMusica** pp_Musicas, tArtista** pp_Artistas, tPlaylist **pp_ListaPlaylist, FILE *RelatorioMusica, FILE *RelatorioArtista);

/**
 * @brief Solicita que o usuário digite um texto e exibe na tela todas as músicas que possuem aquele texto no título.
 * @param pp_Musicas base de dados de musicas.
 */
void BuscarMusicas(tMusica** pp_Musicas);

/**
 * @brief Solicita que o usuário digite o índice de uma música no vetor e exibe na tela todos os atributos da música e dos artistas que a produziram.
 * @param pp_Musicas base de dados de musicas.
 */
void ListarMusica(tMusica** pp_Musicas);

/**
 * @brief Reseta a string dada setando todas as posições do array com '\0'.
 * @param str string a ser resetada.
 */
void Reseta_Str(char* str);




#endif