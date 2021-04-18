#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <ftw.h>
#include "MailBox.h"
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define MAXCHAR 500


void read_line(char *);
int checkDelet(int);
void STAT(char *res);
void LIST(int n, char *res);
void RETR (char * n, char *res);
void DELE (int n, char * res);
void RSET (char * res);


char username[10];
char path[50];
DIR * dirp;
FILE * fp;
static int flg = 0;
int temp = 0;
MAILBOX * mails;

void read_line(char* line) //read line
{
	char buf[BUFSIZE];
	int c;
	
	if ((c = read(STDIN_FILENO, buf, sizeof(buf))) == -1) //read from terminal and save in a buffer
	{
		perror("read"); //error if can't read 
		exit(EXIT_FAILURE);
	}

	buf[c] = '\0'; //put null in the end

	strcpy(line, buf);

}

void mess_count(int * results) {

	struct dirent *entry;
	struct stat buf;
	char folder[50];
	int size = 0;
	int file_count = 0;
	int j = 0;

	while ((entry = readdir(dirp)) != NULL) {
		
    	if (entry->d_type == DT_REG) { /* If the entry is a regular file */
		switch(flg) {
			case 0: 
				file_count++;
				break;
			case 1:
			 		if(mails[checkDelet(atoi(entry->d_name))].deleted == 0){
        				file_count++;
        				strcpy(folder, path);
        				strcat(folder, "/");
        				strcat(folder, entry->d_name);
        				stat(folder,&buf);
        				size+=buf.st_size;
			 		}

        		break;
			}
    	}
	}

	results[0] = file_count;
	results[1] = size;

}

void count_size(int *results) {

	dirp = opendir(path); /* There should be error handling after this */

	if (dirp == NULL){
		perror("Cannot open directory");
		exit(EXIT_FAILURE);
	}
	
	mess_count(results);

	closedir(dirp);
	
}

long findfileSize(char f_n[]) {

   FILE* fp = fopen(f_n, "r"); // opening a file in read mode
   
   if (fp == NULL) { // checking whether the file exists or not 
      printf("File Not Found!\n");
      return -1;
   }
   
   fseek(fp, 0, SEEK_END);
   long res = ftell(fp); //counting the size of the file
   fseek(fp, 0, SEEK_SET);
   fclose(fp); //closing the file
   return res;
}

int checkDelet(int n) {

	int j = 0;

	for(j = 0; j < temp; j++){
		// printf("%d %d\n",j, mails[j].name);
		if (mails[j].name == n)
			break;
	}

	return j;
}

void initialize() {

	int results[2];
	
	count_size(results);
	temp = (results[0]);

	mails = malloc (temp * sizeof(MAILBOX));

	dirp = opendir(path); /* There should be error handling after this */
	struct dirent *entry;

	if (dirp == NULL){
		perror("Cannot open directory");
		exit(EXIT_FAILURE);
	}

	int i = 0;

	while ((entry = readdir(dirp)) != NULL) {
		
		if (entry->d_type == DT_REG) { /* If the entry is a regular file */
			
        	mails[i].name = atoi(entry->d_name);
        	mails[i].deleted = 0;

        	i++;
    	}
	}

	// for (int i = 0; i < temp; i++)
	// 	printf("%d %d\n", mails[i].name, mails[i].deleted);
	mails[i].deleted = 1;

	flg = 1;

}

void STAT(char * res) {

	char fc[10];
	char tot[10];
	int results[2];
	
	strcpy(res, "S: +OK " );
	
	count_size(results);

	sprintf(fc, "%d", results[0]);
	sprintf(tot, "%d", results[1]);

	if (results[0] > 0) {
		strcat(res, fc);
		strcat(res, " ");
		strcat(res, tot);
		strcat(res, "\n");
	}
	else {
		strcat(res, "\n");
	}

}

void LIST(int n, char *res) {
	
	char fc[10];
	char tot[10];
	int results[2];
	strcpy(res, "S: +OK " );
	
	int file_count = 0;
	
	dirp = opendir(path); /* There should be error handling after this */

	if (dirp == NULL){
		perror("Cannot open directory");
		exit(EXIT_FAILURE);
	}


	if (n == (-1)) {
		
		count_size(results);

		sprintf(fc, "%d", results[0]);
		sprintf(tot, "%d", results[1]);

		if (results[0] > 0) {

			strcat(res, fc);
			strcat(res, " (");
			strcat(res, tot);
			strcat(res, " octets)\n");
		
			dirp = opendir (path);
			if (dirp == NULL) {
            	printf ("Cannot open directory '%s'\n", path);
            	exit(EXIT_FAILURE);
        	}

        	struct dirent **entry;
        	int n;
        	int i = 0;

       		n = scandir(path, &entry, NULL, alphasort);
        	if (n < 0)
        		perror("scandir");
        	else {

        		while (i<n) {

        			char filepath[50];
        			strcpy(filepath, path);
    
    	   			if(entry[i]->d_type == DT_REG && mails[checkDelet(atoi(entry[i]->d_name))].deleted == 0	){
        				strcat(filepath, "/");
        				strcat(filepath, entry[i]->d_name);
        		
    					long fp_size = findfileSize(filepath);
    					//printf("%d\n", fp_size);
    					sprintf(fc, "%ld", fp_size);

        				strcat(res, "S: ");
        				strcat(res, entry[i] -> d_name);
        				strcat(res, " ");
        				strcat(res, fc);
        				strcat(res, "\n");
        			}
        		++i;
           
        		}
   			}

		closedir(dirp);
		}
		else {
			strcat(res, "\n");
		}

	}

	else {

		count_size(results);

		sprintf(fc, "%d", results[0]);
		sprintf(tot, "%d", n);

		strcat(path, "/");
		strcat(path, tot);

		fp = fopen(path, "r");
	
		if (!fp || mails[checkDelet(n)].deleted != 0) {
			strcpy(res, "-ERR no such message, only ");
			strcat(res, fc);
			strcat(res, " message in mailbox\n");
		}
		else {

			strcat(res, tot);
			strcat(res, " ");

			long fp_size = findfileSize(path);
    			//printf("%d\n", fp_size);

    		sprintf(fc, "%ld", fp_size);

    		strcat(res, fc);
    		strcat(res, "\n");

    		fclose(fp);

		}

	}
}

void RETR (char *n, char *res) {

	strcpy(res, "S: +OK " );
	strcat(path, "/");
	strcat(path, n);
	char line[MAXCHAR];
	char c[10];

	//printf("%d %d\n",checkDelet(atoi(n)), mails[checkDelet(atoi(n))].deleted);
	fp = fopen(path, "r");

	if (!fp || mails[checkDelet(atoi(n))].deleted != 0) {
		strcpy(res, "-ERR no such message\n");
	}
	else {

		long fp_size = findfileSize(path);
    	sprintf(c, "%ld", fp_size);

		strcat(res, c);
		strcat(res, " octets\n");
		strcat(res, "S: ");
		
		int flag = 0;
		while ((fgets(line, MAXCHAR, fp)) != NULL){
	
			if(strcmp(line, "\r\n") == 0 && !flag)
			 	flag = 1;
			 if (flag){
			 	strcat(res, line);
			 }
		}


		strcat(res, "\nS:.\n");
		fclose(fp);
	}

}

void DELE (int n, char * res) {

	if (mails[checkDelet(n)].deleted == 0) {
		strcpy(res, "+ OK message ");
		char fc[10];
		sprintf(fc, "%d", n);
		mails[checkDelet(n)].deleted = 1;
		strcat(res, fc);
		strcat(res, " deleted\n");
	}

	//if (mails[checkDelet(n)].deleted != 0) {
	else {
		strcpy(res, "-ERR no such message\n");
	}
}

void RSET (char * res) {

	int i; 
	for (i = 0; i < temp; i++)
		mails[i].deleted = 0;

	char fc[10];
	char tot[10];
	int results[2];
	
	strcpy(res, "S: +OK maildrop has " ); //node
	
	count_size(results);

	sprintf(fc, "%d", results[0]);
	sprintf(tot, "%d", results[1]);

	strcat(res, fc);
	strcat(res, " messages (");
	strcat(res, tot);
	strcat(res, " octets)\n");

}

int main(int argc, char *argv[]) {

	strcpy(username, argv[1]);
	strcpy(path,"as4-supplementary/");
	strcat(path, username);

	char line[15];
	char *res;
	res = (char *)malloc (65536 * sizeof(char));
	strcpy(res, "S: +OK ");

	flg = 0;
	initialize();

	while (1) {

		strcpy(path,"as4-supplementary/");
		strcat(path, username);
		strcpy(res, "");
		read_line(line);
		
		char * newString;
		newString = strtok(line, " \n");

		while(newString != NULL) {

			
			if (strcmp(newString, "STAT") == 0){
				newString = strtok(NULL, " \n");
				if (newString == NULL)
					STAT(res);
			}

			else if (strcmp(newString, "LIST") == 0){
				newString= strtok(NULL, " \n");

				if (newString == NULL){

					LIST((-1), res);
				}
				else {

					LIST(atoi(newString), res);
				}
			}

			else if (strcmp(newString, "RETR") == 0){

				newString= strtok(NULL, " \n");
				RETR(newString, res);
			}

			else if (strcmp(newString, "DELE") == 0){

				newString= strtok(NULL, " \n");
				if (newString != NULL)
					DELE(atoi(newString), res);

			}

			else if (strcmp(newString, "NOOP") == 0){
				newString = strtok(NULL, " \n");
				if (newString == NULL)
					strcpy(res, "S: +OK\n");
			}

			else if (strcmp(newString, "RSET") == 0) {
				newString = strtok(NULL, " \n");
				if (newString == NULL)
					RSET(res);
			}


			newString= strtok(NULL, " \n");

		}
		printf("%s", res);
	}

}