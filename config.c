#include "config.h"


Config *readConfig(const char *filename){

    FILE *fp;
    char *token;

    char buffer[2048];

    fp = fopen(filename,"r");

    if(fp == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while(fscanf(fp,"%s",buffer) != EOF){
        
        /* get the first token */
        token = strtok(buffer, "=");
        
        /* walk through other tokens */
        while( token != NULL ) {
            printf( "%s\n", token);
            
            token = strtok(NULL, "=");
        }
    }


    return NULL;
}