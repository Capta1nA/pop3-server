#ifndef AUTHORIZATION_H_
#define AUTHORIZATION_H_
typedef struct user {

	 char path[60];
    char username[50];
	
}__attribute__((packed)) USERS;

void USER (char * answer,char *username);
void PASS (char * password,char * answer,char *username);
void QUIT ();
void splitCommand (char * buf,int character,char new[][character]);

#endif