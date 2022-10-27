#include "tArtista.h"

struct tArtista{
    char id[25]; //hash alfanumerico
    int seguidores;
    char **generos; //lista de generos
    char *nome;
    int popularidade;
};
