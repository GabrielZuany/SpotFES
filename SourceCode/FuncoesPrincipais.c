#include "FuncoesPrincipais.h"
#define Sair 0
#define Buscar_Musica 1
#define Listar_Uma_Musica 2
#define Criar_Uma_Playlist 3
#define Listar_Playlists 4
#define Listar_Uma_Playlist 5
#define Adicionar_Uma_Musica_Na_Playlist 6
#define Recomendar_Musicas_Parecidas_Com_Uma_Playlist 7
#define Gerar_Relatorio 8


// --------- Interatividade com o Usuário ----------

void ExibeMenu(){
    printf("\nEscolha uma opcao\n0 - Sair\n1 - Buscar musicas\n2 - Listar musica\n3 - Criar playlist\n4 - Listar todas as playlists\n5 - Listar uma playlist\n6 - Adicionar musica na playlist\n7 - Recomendar musica parecida\n8 - Gerar relatorio\n-> ");
}

tPlaylist** ExecutaOpcaoUsuario(int opcao, tMusica** pp_Musicas, tArtista** pp_Artistas,tPlaylist **pp_ListaPlaylist, FILE *RelatorioMusica, FILE *RelatorioArtista){
    static int qtdPlaylist = 0;
    int indiceDaPlaylist = 0;
    int indiceDaMusica = 0;
    int qtd_MusicaParaRecomendar = 0;

    switch (opcao){
    case Sair:
        /* sair */
        break;
        
    case Buscar_Musica:
        BuscarMusicas(pp_Musicas);
        break;

    case Listar_Uma_Musica:
        ListarMusica(pp_Musicas);
        break;

    case Criar_Uma_Playlist:
        pp_ListaPlaylist = realloc(pp_ListaPlaylist, (qtdPlaylist+1) * sizeof(tPlaylist*));
        printf("Nome da playlist: ");
        char nome[50]; //talvez trocar para ponteiro
        Reseta_Str(nome);
        scanf("%[^\n]%*c", nome);
        pp_ListaPlaylist[qtdPlaylist] = Inicializa_PonteiroDePlaylist(nome, qtdPlaylist);
        qtdPlaylist++;
        printf("Playlist criada com sucesso!\n");
        break;

    case Listar_Playlists:
        Imprime_ListarPlaylists(pp_ListaPlaylist, qtdPlaylist);
        break;

    case Listar_Uma_Playlist:
        printf("Indice da playlist: ");
        scanf("%d%*c", &indiceDaPlaylist);
        Imprime_ListarUmaPlaylist(pp_ListaPlaylist[indiceDaPlaylist]);
        break;

    case Adicionar_Uma_Musica_Na_Playlist: 
        printf("Indice da Playlist: ");
        scanf("%d%*c", &indiceDaPlaylist);
        printf("Indice da musica: ");
        scanf("%d%*c", &indiceDaMusica);
        
        pp_ListaPlaylist[indiceDaPlaylist] = Realoca_Memoria_PonteiroDeMusica(pp_ListaPlaylist[indiceDaPlaylist]);
        pp_ListaPlaylist[indiceDaPlaylist] = Adiciona_MusicaPlaylist(indiceDaMusica, pp_ListaPlaylist[indiceDaPlaylist], pp_Musicas, pp_Artistas);
        printf("musica adicionada na playlist %d com sucesso!\n", indiceDaPlaylist);
        break;

    case Recomendar_Musicas_Parecidas_Com_Uma_Playlist: // LEMBRAR DE LIBERAR O ARRAY CRIADO
        printf("Indice da Playlist: ");
        scanf("%d", &indiceDaPlaylist);
        printf("Numero de musicas a serem recomendadas: ");
        scanf("%d", &qtd_MusicaParaRecomendar);
        RecomendaMusicasParecidasComUmaPlaylist(pp_ListaPlaylist[indiceDaPlaylist], pp_Musicas, qtd_MusicaParaRecomendar);
        break;

    case Gerar_Relatorio:
        ImprimeRelatorioMusicaNoArquivo(RelatorioMusica, pp_Musicas);
        ImprimeRelatorioArtistaNoArquivo(RelatorioArtista, pp_Artistas);
        printf("Relatorio impresso com sucesso!\n");
        break;

    default: printf("Opcao nao listada\n");
        break;
    }
    return pp_ListaPlaylist;
}


// ----------- operacoes------------------
void BuscarMusicas(tMusica** pp_Musicas){// operacao numero 1
    char texto[300];
    scanf("%[^\n]", texto);
    scanf("%*c");
    int qtd = Acesso_QuantidadeMusicas(0, FALSO);
    int encontrei = 0;

    for(int i = 0; i<qtd; i++){

        if(strstr(Retorna_NomeMusica(pp_Musicas[i]), texto )){
            Imprime_Funcao_BuscarMusica(pp_Musicas[i]);
            encontrei = 1;
        }
    }
    if(encontrei == 0){
        printf("Nao encontrei nenhuma musica na base de dados\n");
    }
}

void ListarMusica(tMusica** pp_Musicas){// operacao numero 2
    int qtd = Acesso_QuantidadeMusicas(0, FALSO);
    int indice;

    printf("Indice: ");
    scanf("%d", &indice);
    scanf("%*c");
    Imprime_ListarUmaMusica(pp_Musicas[indice]);
    
    printf("\nDeseja executar a musica? S/N -> ");
    char op;
    scanf("%c", &op);
    scanf("%*c");

    if(op == 'S' || op =='s'){
        char command[70];
        Reseta_Str(command);
        strcat(command, "firefox https://open.spotify.com/track/");
        strcat(command, Retorna_ID_Musica(pp_Musicas[indice]));
        printf("%s\n", command);
        //system(command); // executar a musica abrindo o firefox.
    }
}


// ----- auxiliares para operacoes---------
void Reseta_Str(char* str){
    int i;
    for(i = 0; i < strlen(str); i++){
        str[i] ='\0';
    }
    str[i+1] = '\0';
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