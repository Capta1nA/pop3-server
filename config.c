#include "config.h"


Config *readConfig(const char *filename){

    FILE *fp;
    char temp[2048];
    char buffer[2048];

    fp = fopen(filename,"r");

    if(fp == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    Config *conf = (Config *)malloc(sizeof(Config));

    if(conf == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while(fscanf(fp,"%s",buffer) != EOF){

        if(strncmp(buffer,"MAX_THREADS",11) == 0){
            strncpy(temp,buffer+12, strlen(buffer)-10);

            conf->nthreads = atoi(temp);
        
        }
        else if(strncmp(buffer,"SERVER_PORT",11) == 0){
            strncpy(temp,buffer+12, strlen(buffer)-10);
            
            conf->port = atoi(temp);
        } 
        else if(strncmp(buffer,"SERVER_BCKLG",12) == 0){
            strncpy(temp,buffer+13, strlen(buffer)-11);
            
            conf->serverBacklog = atoi(temp);
        }          

    }


    return conf;
}