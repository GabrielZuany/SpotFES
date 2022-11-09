#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


int main(){
    FILE* f = NULL;
    int x;

    char filename[50];
    char pos[2] = {'\0', '\0'};
    for(int i=0; i<50; i++){
        filename[i] = '\0';
    }
    

    int file_count = 0;
    DIR * dirp;
    struct dirent * entry;
    dirp = opendir("files"); /* There should be error handling after this */
    while ((entry = readdir(dirp)) != NULL) {
        file_count++;
    }
    closedir(dirp);
    printf("=== %d ====\n", file_count-2);

    for(int i=0; i<file_count-2; i++){
        strcat(filename, "files/file");
        pos[0] = i+'0';
        strcat(filename, pos);
        strcat(filename, ".bat");

        f = fopen(filename, "rb");
        fread(&x, sizeof(int), 1, f);
        printf("FILE %d: x=%d\n", i, x);

        for(int i=0; i<50; i++){
            filename[i] = '\0';
        }
        pos[0] = '\0';
        fclose(f);
    }
    

    //fclose(f);

    return 0;
}