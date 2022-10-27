#include "tMusica.h"
#include "tArtista.h"
#include "tPropriedades.h"

struct tMusica{
    char id_musicas[25]; //hash alfanumerico
    char *nome;
    int popularidade;
    float duracao_ms;
    int explicit; //uso booleano.
    tArtista **artistas;
    char **id_artistas;
    char *data_lancamento;
    tPropriedades *propriedades;
};

void teste(){
}
