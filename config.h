#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    int nthreads;
    int queueSize;
    int serverBacklog;
}Config;

Config *readConfig(const char *filename);

#endif