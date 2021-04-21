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
#include <sys/types.h>
#include <sys/stat.h>
#include "mailbox.h"
INCLUDE "update.h"
char path[50]="/home/pi/epl421_ex4/";
int messages=47;
char newPath[100];
int temp = 0;
DIR * dirp;

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

void QUIT(){
	dirp = opendir(path); 
	struct dirent *entry;
    snprintf("newPath",sizeof(newPath),"%s%s",newPath,mails->name);
	if (dirp == NULL){
		perror("Cannot open directory");
		exit(EXIT_FAILURE);
	}
	int i = 0;
	while ((entry = readdir(dirp)) != NULL) {
		
		if (entry->d_type == DT_REG) { /* If the entry is a regular file */
			if (mails[i].deleted==1){
				remove(path);

        	i++;
    	}
 	
	}
	
}


}
int main (int argc,char * argv){
		char line[15];
		char *res;
		res = (char *)malloc (65536 * sizeof(char));
		strcpy(res, "");
		read_line(line);
		else if (strcmp(newString, "QUIT") == 0) {
		char * newString;
		newString = strtok(line, " \n");
		if (newString)
		QUIT();
	
}
