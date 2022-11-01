#include "FuncoesPrincipais.h"


// --------- Interatividade com o Usuário ----------

void ExibeMenu(){
    printf("\nEscolha uma opcao\n0 - Sair\n1 - Buscar musicas\n2 - Listar musica\n3 - Criar playlist\n4 - Listar todas as playlists\n5 - Listar uma playlist\n6 - Adicionar musica na playlist\n7 - Recomendar musica parecida\n8 - Gerar relatorio\n-> ");
}

void ExecutaOpcaoUsuario(int opcao, tMusica** pp_Musicas){

    switch (opcao) 
    {
    case 0:
        /* sair */
        break;
    case 1:
        BuscarMusicas(pp_Musicas);
        break;
    case 2:
        ListarMusica(pp_Musicas);
        break;
    case 3:
        //CriarPlaylist();
        break;
    case 4:
        //ListarTodasAsPlaylist();
        break;
    case 5:
        //ListarUmaPlaylist();
        break;
    case 6:
        //AdicionarMusicaNaPlaylist();
        break;
    case 7:
        //RecomendarMusicaParecida();
        break;
    case 8:
        //GerarRelatorio();
        break;
    default: printf("Opcao nao listada\n");
        break;
    }
}

void BuscarMusicas(tMusica** pp_Musicas){
    char texto[50];
    scanf("%*c");
    scanf("%s", texto);
    int qtd = Acesso_QuantidadeMusicas(0, FALSO);
    int encontrei = 0;

    for(int i = 0; i<qtd; i++){

        if(strstr(Retorna_NomeMusica(pp_Musicas[i]), texto )){
            Imprime_Musica(pp_Musicas[i]);
            encontrei = 1;
        }
    }
    if(encontrei == 0){
        printf("Não encontrei nenhuma musica na base de dados\n");
    }
}

void ListarMusica(tMusica** pp_Musicas){
    int qtd = Acesso_QuantidadeMusicas(0, FALSO);
    int indice;

    scanf("%d", &indice);
    scanf("%*c");
    tPropriedades* propriedades = Retorna_PropriedadesDaMusica(pp_Musicas[indice]);
    Imprime_PropriedadesDaMusisca(propriedades);

    printf("\nDeseja executar a musica? S/N -> ");
    char op;
    scanf("%c", &op);
    scanf("%*c");
    if(op == 'S' || op =='s'){
        //executa
    }
}



// ----------- arquivos main --------------
FILE* AbreArquivoArtistasCSV(int argc, char **argv){
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        exit(0);
    }
    FILE* artista_file = fopen(argv[1], "r");
    if (!(artista_file)){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n%s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    return artista_file;
}

FILE* AbreArquivoTracksCSV(char *argv[]){
    FILE* tracks_file = fopen(argv[2], "r");
    if(!tracks_file){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n%s\n", argv[1]);
        fclose(tracks_file);
        exit(EXIT_FAILURE);
    }
    return tracks_file;
}