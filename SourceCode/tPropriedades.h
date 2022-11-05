#ifndef _TPROPRIEDADES_H_
#define _TPROPRIEDADES_H_
#include <stdio.h>
#include <stdlib.h>


typedef struct tPropriedades tPropriedades;

/**
 * @brief Registra na struct os parâmetros lidos no arquivo.
 * 
 * @param danceabilidade 
 * @param energia 
 * @param key 
 * @param loudness 
 * @param mode 
 * @param speechiness 
 * @param acousticness 
 * @param instrumentalness 
 * @param liveness 
 * @param valence 
 * @param tempo 
 * @param time_signature 
 * @return tPropriedades* Ponteiro para a struct devidamente alocada e e escrita com os dados passados.
 */
tPropriedades* Insere_PropriedadesNaMusica(float danceabilidade,float  energia,int key, float loudness, int mode, float speechiness, float acousticness, float instrumentalness, float liveness, float valence, float tempo, int time_signature);


/**
 * @brief Imprime as propriedades da música.
 * 
 * @param p_propriedades struct com as informações a serem impressas.
 */
void Imprime_PropriedadesDaMusisca(tPropriedades* p_propriedades);


float RetornaPropriedadeXdaMusica(tPropriedades* propriedades, int indice);

#endif