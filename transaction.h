#ifndef TRANSACTION_H_
#define TRANSACTION_H_
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

#define MBUFSIZE 1024
#define MAXCHAR 500


typedef struct mailbox {

	int name;
	int deleted;
	
}__attribute__((packed)) MAILBOX;

char path[50];
DIR * dirp;
FILE * fp;
static int flg = 0;
static int temp = 0;
MAILBOX * mails;

/**
 * @function read_line
 * @brief read a line from terminal
 * @param line Command line
 */
void read_line(char * line);

/**
 * @function mess_count
 * @brief calculate the number of messages exist in a directory and the size of directory in bytes
 * @param results An array with the file_count at the possition 0 and the size at the position 1.
 */
 void mess_count(int * results);

/**
 * @function count_size
 * @brief open the directory and call the mess_count
 * @param result An array with the file_count at the possition 0 and the size at the position 1.
 */
 void count_size(int * results);

/**
 * @function findfileSize
 * @brief count the size of specific file
 * @param f_n[] the path for the file.
 */
 long findfileSize(char f_n[]);

/**
 * @function checkDelet
 * @brief Check for specific message if is deleted
 * @param n Message name.
 * @return if the n message is deleted or not 
 */
int checkDelet(int n);

/**
 * @function initialize
 * @brief set all the messages not deleted at the begining
 */
void initialize();

/**
 * @function STAT
 * @brief find the number of the messages exists in a mailbox and the size in octets
 * @param res The answer of the function which return in the client.
 */
void STAT(char *res);

/**
 * @function LIST
 * @brief with no parametres find the message number and the size in octets and print all the 
 * messages one by one with the size of each one or with parameter print the specific message if
 * exist with the it's size in octets
 * @param n -1 for no parameter or the name of the message
 * @param res The answer of the function which return in the client.
 */
void LIST(int n, char *res);

/**
 * @function RETR
 * @brief print the entire message if exist
 * @param n the name of the message
 * @param res The answer of the function which return in the client.
 */
void RETR (char * n, char *res);

/**
 * @function DELE
 * @brief set a message as deleted if the message exist
 * @param n the name of the message
 * @param res The answer of the function which return in the client.
 */
void DELE (int n, char * res);

/**
 * @function RSET
 * @brief set all the deleted message not deleted and return them in the mailbox
 * @param res The answer of the function which return in the client.
 */
void RSET (char * res);



void UQUIT(char *res);

#endif