char* Cria_ArquivoPlaylist_RetornandoCaminho(char nome[]){
    char* path = calloc(sizeof(char), 90);
    char* command = calloc(sizeof(char), 70);

    strcat(command, "mkdir ");
    strcat(path, "../Playlists/");
    strcat(command, path);
    system(command);

    free(command);// resetar o ponteiro.
    command = calloc(sizeof(char), 70);

    strcat(command, "touch ");
    strcat(path, "../Playlists/");
    strcat(path, nome);
    strcat(path, ".bin");
    strcat(command, path);
    
    system(command);
    free(command);
    return path;
}



    //-------------------- tentando ler ----------------
    /*
    write(&(playlist->indice), sizeof(int), 1, file);
    fwrite(&(playlist->qtdMusica), sizeof(int), 1, file);
    char nome[50];
    strcpy(nome, playlist->nome);
    fwrite(nome, sizeof(char), 50, file);
    //fputs(playlist->nome, file);
    fwrite((playlist->Lista_musicas), sizeof(playlist->Lista_musicas), 1, file);

    file = fopen(filepath, "rb");
    tMusica** lista = malloc(sizeof(playlist->Lista_musicas));
    int indice, qtdMusica;
    char nome[50] = "";
    Reseta_String(nome);

    fread(&indice, sizeof(int), 1, file);
    fread(&qtdMusica, sizeof(int), 1, file);
    fread(nome, sizeof(char), strlen(playlist->nome), file); // tamanho maximo do nome = 50
    //fread(nome, sizeof(char), 50, file); // tamanho maximo do nome = 50

    fread(lista, sizeof(playlist->Lista_musicas), 1, file);


    printf("REGISTRANDO E RESGATANDO BINARIO\n");
    printf("======= INDICE %d ==========\n", indice);
    printf("======= QTD musica: %d =====\n", qtdMusica);
    printf("======= Nome: %s ====\n", nome);

    Imprime_Funcao_BuscarMusica(lista[0]);

    free(lista);
    fclose(file);
    */

    tPlaylist *LeUmaPlaylistBinario(FILE *file, tMusica **pp_Musicas){
    tPlaylist *pPlaylist = malloc(sizeof(struct tPlaylist));
    int qtd_musica = 0, indice = 0, i = 0;
    char nome[50], temp;
    
    
    fread(&indice, sizeof(int), 1, file);
    printf("%d ", indice);
    fread(&qtd_musica, sizeof(int), 1, file);
    printf("%d ", qtd_musica);
    
    i = 0;
    do{
        fread(&temp, sizeof(char),1, file);
        nome[i] = temp;
        printf("%c", nome[i]);
        i++;

    }while(temp!='\0');
    //nome[i] = '\0';
    
    printf("NOME %s ", nome);
    
    int *indiceMusica = malloc(sizeof(int) * qtd_musica);
    fread(indiceMusica, sizeof(int), qtd_musica, file);
    
    pPlaylist->Lista_musicas = malloc(sizeof(tMusica*) * qtd_musica);

    for(i = 0; i < qtd_musica; i++){
        pPlaylist->Lista_musicas[i] = Acesso_MusicaDeIndiceX(pp_Musicas ,indiceMusica[i]);
    }

    pPlaylist->indice = indice;
    pPlaylist->qtdMusica = qtd_musica;
    strcpy(pPlaylist->nome, nome);
    return pPlaylist;
}
