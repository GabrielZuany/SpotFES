#include "tArtista.h"

struct tArtista{
    char *id; //hash alfanumerico
    int seguidores;
    char **generos; //lista de generos
    char *nome;
    int popularidade;
};