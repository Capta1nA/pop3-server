typedef struct user {

	 char path[60];
    char username[50];
	
}__attribute__((packed)) USERS;

char *USER (char * answer,char *username);
char *PASS (char * password,char * answer,char *username);