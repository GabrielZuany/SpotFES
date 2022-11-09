#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Inicializa_Str(char* str){
    for(int i=0; i<strlen(str); i++){
        str[i] = '\0';
    }
}

int main(){
    char command[100], path[100];
    int i, x;
    Inicializa_Str(command);
    Inicializa_Str(path);
    system("mkdir files");

    FILE* f = NULL;

    for(i=0; i<10; i++){
        x = i+100;

        strcat(command, "touch ");

        char index[2] = {'\0', '\0'};
        index[0] = i+'0';
        strcat(path, "files/file");
        strcat(path, index);
        strcat(path, ".bat");

        strcat(command, path);
        system(command);

        f = fopen(path, "wb");

        fwrite(&x, sizeof(x), 1, f);

        Inicializa_Str(command);
        Inicializa_Str(path);

        fclose(f);
    }

    return 0;
}
