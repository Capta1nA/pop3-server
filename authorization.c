#include <stdio.h>
#include <string.h>
#include<fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "authorization.h"

USERS * contact;
char userr[50];
int cnt=0;
    
void splitCommand (char * buf,int character,char new[][character]){
	contact= malloc (100*sizeof(contact));
	int i,line,col;
	col=0;line=0;
		for (i=0;i<character;i++){
			if(buf[i]==' ' || buf[i]=='\n'){
			new[line][col]='\0';
			line++;
			col=0;
			}
			else {
				new[line][col]=buf[i];
				col++;
				}
	
	}			

}

void USER (char * answer,char *username) {
	contact= malloc (100*sizeof(contact));
	strcpy(contact[cnt].username,username);
	strcpy(contact[cnt].path,"mails/");
	strcat(contact[cnt].path,contact[cnt].username);
	DIR * dir =opendir(contact[cnt].path);
	if(dir){
		closedir(dir); //to directory yparxei 
		strcat(answer,"+OK ");strcat(answer,contact[cnt].username);strcat(answer," is a valid mailbox\n");
	}
	else if (ENOENT == errno ){ //to directory den iparxei 
		strcat(answer,"-ERR never heard of mailbox ");
		strcat(answer,contact[cnt].username);
		strcat(answer,"\n");
	 }
	else { // i opendir() exei apotixei gia kapoio logo
		strcat(answer,"-ERR never heard of mailbox ");
		strcat(answer,contact[cnt].username);
		strcat(answer,"\n");
	}
}

void PASS (char * password,char * answer,char *username) {
   contact= malloc (100*sizeof(contact));
   strcpy(contact[cnt].username,username);
  int flag=0;
  FILE *fp = fopen("mails/password", "r");
      if(fp == NULL) {
          perror("Unable to open file!");
          exit(1);
    }
    char *line = NULL;
    size_t len = 0;
    char str[100];
     while(getline(&line, &len, fp) != -1) {
		 strcpy(str, line); //get the first token 
		 strtok(str, " "); 
		  char * ptr = strtok(NULL, " \n");     //SECOND TOKEN
		  
		 if (strcmp(str,contact[cnt].username) == 0 && strcmp(ptr,password) == 0){
				strcat(answer,"+OK maildrop locked and ready\n"); flag=1;
				break;
            }
		}
       if (flag==0){
		   	strcat(answer,("-ERR invalid password\n"));

	   }
 
 
     fclose(fp);
     free(line);     
 
}


void QUIT (){
	contact= malloc (100*sizeof(contact));
	char str1[100];
	strcpy(str1,"/home/pi/epl421_ex4/");
        strcat(str1,userr);
	struct stat buf;
	DIR *dptr;
	struct dirent *sdir;
	int size=0;
	char str[100];
	dptr=opendir(str1);
	//int i ;
	char prefix[100] = "";
	char newPath[40];
        int count=0; int fd1;
	while((sdir=readdir(dptr)))
{
   if(sdir->d_type==4)
    {
        if(sdir->d_name[0]!='.')
        {
           stat(sdir->d_name,&buf);

        }
    }
    else
    {
        strcpy(str,str1);
        strcat(str,"/");
        strcat(str,sdir->d_name);
        stat(str,&buf);
        printf("%s",str);
        size=buf.st_size;
        fd1=open(str, O_WRONLY|O_CREAT | O_APPEND , 7777);
        if (fd1<0) { perror("r1");exit(1);}
        snprintf(newPath,sizeof(newPath),"%s%s%d",str1,"/",count);count++;
        if (rename(str,newPath)==0){
			printf("sdf");}
        else{printf("prob");
			}
        snprintf(prefix, sizeof(prefix), "\n %s: %d ","Size", size);
        printf("%d",size);   
	write(fd1,prefix,sizeof(prefix));
	
	     close(fd1);
    }
  }
	
	
}
#ifdef DEBUG
int main (int argc , char *argv){
		int continuee=0; //simenei pws den exei valei akoma tin entoli USER
		char buf[100];
		char *answer;	char buf2[100];
		answer = (char *)malloc (2096 * sizeof(char));
		char *answer2;	
		answer2 = (char *)malloc (2096 * sizeof(char));
		char *correct;
		correct = (char *)malloc (2096 * sizeof(char));
		char str[100];		
		 char character;	
		if (((character = read(STDIN_FILENO, buf, sizeof(buf))) == -1)){
				perror("error");
				exit(EXIT_FAILURE);
		}
	        buf[character]='\0';
			        char new[character][character];

	        splitCommand(buf,character,new);		
		 if (strcmp(new[0],"USER") ==0){
		 USER (answer,new[1]);
		 printf("%s \n",answer);

		 strcat(correct,"+OK ");strcat(correct,new[1]);strcat(correct," is a valid mailbox");
		if (strcmp(answer,correct)==0){
		 continuee=1; //mporei na proxorisei sto password
	         }
		 if (continuee != 1 ){
			exit(EXIT_FAILURE);
		 }
		 
	
		 if (((character = read(STDIN_FILENO, buf2, sizeof(buf2))) == -1) ){
				perror("error");
				exit(0);
		}
		strcpy(str, buf2); //get the first token 
		strtok(str, " ");
	        }
                 if  (strcmp(str ,"PASS ") && continuee==1){
		 char * ptr = strtok(buf2, " ");     //SECOND TOKEN
                 PASS(strtok(NULL, " "),answer2,new[1]); 
	         printf("%s \n",answer2);
		}
			if (strcmp(answer2,"+OK maildrop locked and ready")==0){
				continuee=2; //mporei na ektelesei tin quit
			}


		if (((character = read(STDIN_FILENO, buf, sizeof(buf))) == -1)){
				perror("error");
				exit(EXIT_FAILURE);
			}        
		 buf[character]='\0'; 
	     splitCommand(buf,character,new);		
		 if (strcmp(new[0],"QUIT") ==0 && continuee==2){		
			strcpy(userr,new[1]);			
			QUIT();
		}
	cnt++;
return 0 ;

}
#endif