#include "tPropriedades.h"

struct tPropriedades{
    float danceability;
    float energy;
    int key;
    float loudness;
    int mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int time_signature;
    float arrayPropriedades[12];
};

tPropriedades* Insere_PropriedadesNaMusica(float danceabilidade,float  energia,int key, float loudness, int mode, float speechiness, float acousticness, float instrumentalness, float liveness, float valence, float tempo, int time_signature){
    tPropriedades *p_propriedades = NULL;
    p_propriedades = (tPropriedades*)malloc(sizeof(struct tPropriedades));

    p_propriedades->danceability = danceabilidade;
    p_propriedades->energy = energia;
    p_propriedades->key = key;
    p_propriedades->loudness = loudness;
    p_propriedades->mode = mode;
    p_propriedades->speechiness = speechiness; 
    p_propriedades->acousticness = acousticness;
    p_propriedades->instrumentalness = instrumentalness;
    p_propriedades->liveness = liveness;
    p_propriedades->valence = valence;
    p_propriedades->tempo = tempo;
    p_propriedades->time_signature = time_signature;
    
    p_propriedades->arrayPropriedades[0] = (float)danceabilidade;
    p_propriedades->arrayPropriedades[1] = (float)energia;
    p_propriedades->arrayPropriedades[2] = (float)mode;
    p_propriedades->arrayPropriedades[3] = (float)speechiness;
    p_propriedades->arrayPropriedades[4] = (float)acousticness;
    p_propriedades->arrayPropriedades[5] = (float)instrumentalness;
    p_propriedades->arrayPropriedades[6] = (float)liveness;
    p_propriedades->arrayPropriedades[7] = (float)valence;
    return p_propriedades; 
}

void Imprime_PropriedadesDaMusisca(tPropriedades* p_propriedades){
    printf("Propriedades: \nDanceability -> %f\nEnergy -> %f\nKey -> %d\nLoudness -> %f\nMode -> %d\nSpeechiness -> %f\nAcousticiness -> %f\nInstrumentalness -> %f\nLiveness -> %f\nValence -> %f;\nTempo -> %f\nTime_signature -> %d", 
    p_propriedades->danceability, p_propriedades->energy, p_propriedades->key, p_propriedades->loudness, p_propriedades->mode, p_propriedades->speechiness, p_propriedades->acousticness, p_propriedades->instrumentalness, p_propriedades->liveness,
    p_propriedades->valence, p_propriedades->tempo, p_propriedades->time_signature);
}

float RetornaPropriedadeXdaMusica(tPropriedades* propriedades, int indice){
    return propriedades->arrayPropriedades[indice];
}
