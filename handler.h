#ifndef HANDLER_H_
#define HANDLER_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * @function handleConnection
 * @brief A function for handling each socker of a client. This function
 * is been called by threads every time a client connects to the server
 * @param client_socket The socker file descriptor of the client
 */
void *handleConnection(void *client_socket);

#endif