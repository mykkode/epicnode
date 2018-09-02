//
// Created by mykkode on 16.06.2018.
//

#include <stdio.h>
#define PATH_MAX 1

int main(){
    FILE *fp;
    int status;
    char path[PATH_MAX];


    fp = popen("diff a b", "r");
    if(fp==NULL){
        printf("PIPE ERROR");
    }


    if (fgets(path, PATH_MAX, fp) != NULL)
        printf("%s", path);

    pclose(fp);
}
