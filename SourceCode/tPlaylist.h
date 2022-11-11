#ifndef _TPLAYLIST_H_
#define _TPLAYLIST_H_
#include <stdio.h>
#include "tMusica.h"

typedef struct tPlaylist tPlaylist;


//============================= Alocação de Memória ==================
/**
 * @brief Aloca memoria para o ponteiro de ponteiro (lista de artistas do tipo tArtistas). 
 * @return tPlaylist** array de ponteiros de artista
 */
tPlaylist** Inicializa_PonteiroDePonteiroDePlaylist();

/**
 * @brief aloca memoria para um unico ponteiro de artista
 * @param nome nome do artista
 * @param indice indice do artista
 * @return tPlaylist* ponteiro do artista
 */
tPlaylist* Inicializa_PonteiroDePlaylist(char nome[], int indice);

/**
 * @brief realoca mamoria para armazenar mais musicas
 * @param p_Playlist 
 * @return tPlaylist* 
 */
tPlaylist* Realoca_Memoria_PonteiroDeMusica(tPlaylist* p_Playlist);


tPlaylist *LeUmaPlaylistBinario(FILE *file, tMusica** pp_musicas);

tPlaylist** Le_Playlists_ArqBinario(tPlaylist **pp_ListaPlaylist, tMusica **pp_Musicas, FILE * file);

void Armazena_Playlist_em_ArquivoBinario(tPlaylist* playlist, FILE* file);


void LiberaTodasAsPlaylist(tPlaylist** pp_playlist);

void Registra_Playlists_ArqBinario(tPlaylist** pp_ListaPlaylist, FILE *file);

//============================= aux ==================

/**
 * @brief recebe um valor booleano que informa se ela deve trocar o valor salvo e retorna-lo ou apenar retorna-lo sem alteracoes.
 * @param x valor usado para a alteracao, caso ocorra.
 * @param bool valor booleano indicando se a função irá registrar o valor ou retornar VERDADE  para registrar FALSO para retornar.
 */
int Acesso_QuantidadePlaylists(int qtdPlaylist, int bool);

/**
 * @brief Solicita o índice de uma música e de uma playlist e adiciona a música a playlist
 * @param indice indice da playlist desejada.
 * @param p_Playlist playlist atual.
 * @param pp_Musica base de musicas.
 * @param pp_Artistas base de artistas.
 * @return tPlaylist* playlist atualizada após a inserção da musica.
 */
tPlaylist* Adiciona_MusicaPlaylist(int indice, tPlaylist* p_Playlist, tMusica** pp_Musica, tArtista** pp_Artistas);

/**
 * @brief Reseta a string referente ao nome, setando todas as posições para '\0'.
 * @param nome string a ser resetada.
 */
void Reseta_String(char *nome);

/**
 * @brief Recomenda as N musicas mais parecidas com a pseudomusica que representa a playlist.
 * @param pPlaylist playlist desejada.
 * @param pp_Musicas base de musicas registradas.
 * @param qtd_MusicaParaRecomendar quantidade de musicas a serem recomendadas.
 */
void RecomendaMusicasParecidasComUmaPlaylist(tPlaylist* pPlaylist, tMusica **pp_Musicas,int qtd_MusicaParaRecomendar);

/**
 * @brief Calcula uma pseudomusica cuja cada caracteristica é a media do valor de cada propriedade.
 * @param pPlaylist playlist a ser analisada.
 * @return float* vetor com todas as prorpiedades calculadas.
 */
float* CalculaArrayPropriedadesMusicaIdeal(tPlaylist *pPlaylist);


//============================= impressao ==============================================
/**
 * @brief Solicita que o usuário digite o índice da playlist e apresenta na tela o nome da playlist e os títulos das músicas que ela possui.
 * @param p_Playlist playlist selecionada.
 */
void Imprime_ListarUmaPlaylist(tPlaylist *p_Playlist);

/**
 * @brief Exibe os dados de todas as playlists, uma por linha. Para cada playlist, deve ser exibido o índice da playlist no array, o nome da playlist e o número de músicas que ela possui.
 * @param pp_ListaPlaylist todas as playlists.
 * @param qtd_playlists numero total de playlists.
 */
void Imprime_ListarPlaylists(tPlaylist** pp_ListaPlaylist, int qtd_playlists);


#endif