#include "handler.h"
#include "user.h"
#include "MailBox.h"
#include "threadpool.h"

#define BUFSIZE 2048
#define MAX_BUF_SIZE 64 * 1024


void *handleConnection(void *client_socket){
    int csocket = *((int *)client_socket);
    free(client_socket);

    char readBuffer[BUFSIZE];
    char writeBuffer[BUFSIZE];
    char mailBuffer[MAX_BUF_SIZE];

    char username[100];
    char password[100];
    char state[100];
    char greetings[100];
    char ltemp[512];



    size_t bread;
    int msize = 0;

    strcpy(state,"AUTHORIZATION");

    

    strcpy(greetings, "+ OK POP3 server ready\n");
    write(csocket,greetings, strlen(greetings));

    while(1){

        while((bread = read(csocket, readBuffer+msize, sizeof(readBuffer)-msize)) > 0){
            msize += bread;

            if(msize > BUFSIZE-1 || readBuffer[msize-1] == '\n'){
                break;
            }

        }

        readBuffer[msize-1] = 0;
        
        if(memcmp(readBuffer,"QUIT",4) == 0){

            if(strcmp(state,"AUTHORIZATION") == 0){
                strcpy(writeBuffer, "+OK user POP3 server signing off\n");
                write(csocket, writeBuffer,strlen(writeBuffer));
                break;
            }

        }

        if(memcmp(readBuffer,"USER",4) == 0){

            if(strcmp(state,"AUTHORIZATION") == 0){
                memcpy(username,readBuffer+5,strlen(readBuffer) - 6);
                USER(writeBuffer, username);
                write(csocket, writeBuffer,strlen(writeBuffer));
                memset(writeBuffer,'\0',sizeof(writeBuffer));
            }

        }
        else if(memcmp(readBuffer,"PASS",4) == 0){

            if(strcmp(state,"AUTHORIZATION") == 0){
                memcpy(password,readBuffer+5,strlen(readBuffer) - 6);
                PASS(password, writeBuffer,username);
                write(csocket, writeBuffer,strlen(writeBuffer));
                memset(writeBuffer,'\0',sizeof(writeBuffer));

                strcpy(state,"TRANSACTION");

                strcpy(path,"mails/");
                strcat(path,username);
                initialize();

                
            }
        }
        else if(memcmp(readBuffer, "STAT",4) == 0 && strlen(readBuffer) == 5){
            if(strcmp(state,"TRANSACTION") == 0){
                STAT(writeBuffer);
                write(csocket, writeBuffer,strlen(writeBuffer));
            }

        }
        else if(memcmp(readBuffer, "LIST",4) == 0 && strlen(readBuffer) == 5){
            if(strcmp(state,"TRANSACTION") == 0){
                LIST(-1, writeBuffer);
                write(csocket, writeBuffer,strlen(writeBuffer));
            }

        }
        else if(memcmp(readBuffer, "LIST",4) == 0){
            if(strcmp(state,"TRANSACTION") == 0){
                memcpy(ltemp,readBuffer+5,strlen(readBuffer) - 6);
                
                LIST(atoi(ltemp), writeBuffer);
                strcpy(path,"mails/");
                strcat(path,username);
                write(csocket, writeBuffer,strlen(writeBuffer));
                memset(ltemp,'\0',sizeof(ltemp));
            }
        }

        else if(memcmp(readBuffer, "RETR",4) == 0){
            if(strcmp(state,"TRANSACTION") == 0){
                memcpy(ltemp,readBuffer+5,strlen(readBuffer) - 6);
                
                RETR(ltemp,mailBuffer);
                strcpy(path,"mails/");
                strcat(path,username);
                write(csocket, mailBuffer,strlen(mailBuffer));
                memset(ltemp,'\0',sizeof(ltemp));
            }
        }

        else if(memcmp(readBuffer, "DELE",4) == 0){
            if(strcmp(state,"TRANSACTION") == 0){
                memcpy(ltemp,readBuffer+5,strlen(readBuffer) - 6);
                
                DELE(atoi(ltemp),writeBuffer);
                strcpy(path,"mails/");
                strcat(path,username);
                write(csocket, writeBuffer,strlen(writeBuffer));
                memset(ltemp,'\0',sizeof(ltemp));
            }
        }
        else if(memcmp(readBuffer, "NOOP",4) == 0){
            if(strcmp(state,"TRANSACTION") == 0){
                strcpy(writeBuffer, "+OK\n");
                write(csocket, writeBuffer,strlen(writeBuffer));
            }  
        }
        else if(memcmp(readBuffer, "RSET",4) == 0){
            if(strcmp(state,"TRANSACTION") == 0){
                RSET(writeBuffer);
                strcpy(path,"mails/");
                strcat(path,username);
                write(csocket, writeBuffer,strlen(writeBuffer));
                
            }
        }
        else if(memcmp(readBuffer,"QUIT",4) == 0){
            if(strcmp(state,"TRANSACTION") == 0){
                // strcpy(writeBuffer, "+OK user POP3 server signing off\n");
                // write(csocket, writeBuffer,strlen(writeBuffer));
                // break;
                strcpy(state,"UPDATE");
            }

        }

        msize = 0;
        memset(readBuffer,'\0',sizeof(readBuffer));
        memset(writeBuffer,'\0',sizeof(writeBuffer));
        memset(mailBuffer,'\0',sizeof(mailBuffer));
        memset(ltemp,'\0',sizeof(ltemp));

    }

    activeThreads--;
    return NULL;

}