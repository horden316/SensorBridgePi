#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 256
typedef struct {
    char username[50];
    char password[50];
    char broker_address[100];
} Config;


#endif