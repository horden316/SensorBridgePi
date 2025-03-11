#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cjson/cJSON.h"
#define MAX_LINE_LENGTH 256
typedef struct {
    char username[50];
    char password[50];
    char broker_address[100];
} Config;

char* read_file(const char* filename);
int read_config_json(const char* filename, Config* config);

#endif