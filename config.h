#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    int nthreads;
    int port;
    int serverBacklog;
}Config;


/**
 * @function readConfig
 * @brief It read the file where the configuration of mail server is stored
 * then parse it to the Config structure and return it
 * @param filename The config filename
 * @return A pointer to a Config struct
 */
Config *readConfig(const char *filename);

#endif