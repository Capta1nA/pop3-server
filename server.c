#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include "threadpool.h"
#include "workqueue.h"
#include "config.h"

#define SERVER_PORT 9000
#define BACKLOG 1
#define BUFSIZE 4096
#define THREADPOOL_SIZE 4

//pthread_mutex_t smutex = PTHREAD_MUTEX_INITIALIZER;

int main(){


    struct sockaddr_in address;
    int serverFd;
    int csocket;
    int opt = 1;
    int addr_size = sizeof(address);

    //Initialize the threadpool
    Threadpool *tpool = create_threadpool(THREADPOOL_SIZE, 50);

    if((serverFd = socket(AF_INET, SOCK_STREAM,0)) == 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }
        // Forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR,&opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);
       
    // Forcefully attaching socket to the port 8080
    if (bind(serverFd,(struct sockaddr *)&address, sizeof(address))<0){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if(listen(serverFd, BACKLOG) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1){

        if((csocket = accept(serverFd, (struct sockaddr *)&address,(socklen_t*)&addr_size))<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }

        int *pclient = malloc(sizeof(int));
        *pclient = csocket;
        pthread_mutex_lock(&mutex);
        enqueue(pclient);
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);


        //Check the command the client sent
        //handleConnection(csocket);
    }


}