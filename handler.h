#ifndef HANDLER_H_
#define HANDLER_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void *handleConnection(void *client_socket);

#endif