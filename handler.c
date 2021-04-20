#include "handler.h"
#define BUFSIZE 2048

void *handleConnection(void *client_socket){
    int csocket = *((int *)client_socket);
    free(client_socket);

    char buffer[BUFSIZE];
    size_t bread;
    int msize = 0;

    while(1){

        while((bread = read(csocket, buffer+msize, sizeof(buffer)-msize)) > 0){
            msize += bread;

            if(msize > BUFSIZE-1 || buffer[msize-1] == '\n'){
                break;
            }

        }
        buffer[msize-1] = 0;
        // printf("REQUEST %s\n", buffer);
        // fflush(stdout);

        msize = 0;
        memset(buffer,'\0',sizeof(buffer));

    }
    return NULL;

}