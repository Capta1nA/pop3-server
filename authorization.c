#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
void splitCommand (char * buf,int character,char new[][character]);
char *USER (char * username,char * answer) ;
char *PASS (char * password,char * username,char * answer) ;
void QUIT ();

	char path[60];
    char username[50];
    
void splitCommand (char * buf,int character,char new[][character]){
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

char *USER (char * username,char * answer) {
	strcpy(path,"/home/pi/epl421_ex4/");
	strcat(path,username);
	DIR * dir =opendir(path);
	if(dir){
		closedir(dir); //to directory yparxei 
		strcat(answer,"+OK ");strcat(answer,username);strcat(answer," is a valid mailbox");
	}
	else if (ENOENT == errno ){ //to directory den iparxei 
		strcat(answer,"-ERR never heard of mailbox ");
		strcat(answer,username);
	 }
	else { // i opendir() exei apotixei gia kapoio logo
		strcat(answer,"-ERR never heard of mailbox ");
		strcat(answer,username);	}
}

char *PASS (char * password,char * username,char * answer) {
  FILE *fp = fopen("/home/pi/epl421_ex4/password", "r");
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
		 if (strcmp(str,username)==0){
			 char * ptr = strtok(line, " ");     //SECOND TOKEN
			  }
			if ((strcmp(strtok(NULL, " "),password))== 0 ) {
				strcat(answer,"+OK maildrop locked and ready"); 
            }
            else { 
				strcat(answer,("-ERR invalid password"));
			
       }
 
 
     fclose(fp);
     free(line);     
 
}
}

void QUIT (){
	struct stat buf;
	DIR *dptr;
	struct dirent *sdir;
	int size=0;
	char str[100];
	dptr=opendir(path);
	int i ;            char output[42];
int count=0;
	while(sdir=readdir(dptr))

{
   if(sdir->d_type==4)
    {
        if(sdir->d_name[0]!='.')
        {
		   printf("%s",sdir->d_name);
           stat(sdir->d_name,&buf);
           size=buf.st_size; printf("%s",str);
     FILE* fp = fopen("/home/pi/epl421_ex4/InformationFile", "a"); 
        fprintf(fp, "File number %d , Size %d"); 
        printf("%s\n", output); 
   

        }
    }
    else
    {
        strcpy(str,path);
        strcat(str,"/");
        strcat(str,sdir->d_name);
        stat(str,&buf);
        FILE* fp = fopen(str, "a"); 
        fprintf(fp, "File number %d , Size %d"); 
        printf("%s\n", output); 
   
   
           fprintf(fp, "%s\n", size);  
        
    }
  }
	
	
}
int main (int argc , char *argv){
		int continuee=0; //simenei pws den exei valei akoma tin entoli USER
		char buf[100];char *answer;	char buf2[100];
		answer = (char *)malloc (2096 * sizeof(char));
		char *answer2;	
		answer2 = (char *)malloc (2096 * sizeof(char));
		char *correct;
		correct = (char *)malloc (2096 * sizeof(char));
		char str[100];		

		int character;
		
		if (((character = read(STDIN_FILENO, buf, sizeof(buf))) == -1)){
				perror("error");
				exit(EXIT_FAILURE);
			}
	     buf[character]='\0';
	     char new[character][character];
	     splitCommand(buf,character,new);		
		 if (strcmp(new[0],"USER") ==0){
		 USER (new[1],answer);
		 printf("%s \n",answer);
		 strcat(correct,"+OK ");strcat(correct,new[1]);strcat(correct," is a valid mailbox");

		 if (strcmp(answer,correct)==0){
		 continuee=1; //mporei na proxorisei sto password
		 }
	        }
		 if (continuee != 1 ){
				exit(EXIT_FAILURE);
		 }
		 if (((character = read(STDIN_FILENO, buf2, sizeof(buf2))) == -1)){
				perror("error");
				exit(0);
			}
			strcpy(str, buf2); //get the first token 
			strtok(str, " ");
            if  (strcmp(str ,"PASS ")){
				 char * ptr = strtok(buf2, " ");     //SECOND TOKEN
                 PASS(strtok(NULL, " "),new[1],answer2); 
				printf("%s \n",answer2);
}
		if (((character = read(STDIN_FILENO, buf, sizeof(buf))) == -1)){
				perror("error");
				exit(EXIT_FAILURE);
			}        
		 buf[character]='\0';
	     splitCommand(buf,character,new);		
		 if (strcmp(new[0],"QUIT") ==0){		
			strcpy(username,new[1]);		
			QUIT();
			}	
return 0 ;
}

	
