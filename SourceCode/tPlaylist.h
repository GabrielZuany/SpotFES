#ifndef _TPLAYLIST_H_
#define _TPLAYLIST_H_
#include <stdio.h>
#include "tMusica.h"

typedef struct tPlaylist tPlaylist;

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

/**
 * @brief envia ao terminal comandos para criar uma pasta "Playlists/" e criar arquivos de playlists dado seus nomes.
 * @param nome nome da playlist.
 * @param p_Playlist playlist[pos_atual].
 */
void Cria_ArquivoPlaylist(char nome[], tPlaylist* p_Playlist);

/**
 * @brief Solicita o índice de uma música e de uma playlist e adiciona a música a playlist
 * @param indice indice da playlist desejada.
 * @param p_Playlist playlist atual.
 * @param pp_Musica base de musicas.
 * @return tPlaylist* playlist atualizada após a inserção da musica.
 */
tPlaylist* Adiciona_MusicaPlaylist(int indice, tPlaylist* p_Playlist, tMusica** pp_Musica);

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

/**
 * @brief Reseta a string referente ao nome, setando todas as posições para '\0'.
 * @param nome string a ser resetada.
 */
void Reseta_String(char *nome);

#endif