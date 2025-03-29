#include "config.h"

char* read_file(const char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("無法開啟檔案");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);

    char *buffer = (char*)malloc(filesize + 1);
    if (buffer == NULL) {
        fclose(fp);
        return NULL;
    }
    fread(buffer, 1, filesize, fp);
    buffer[filesize] = '\0';
    fclose(fp);
    return buffer;
}

int read_config_json(const char* filename, Config* config) {
    char *json_data = read_file(filename);
    if (json_data == NULL) {
        return -1;
    }

    cJSON *json = cJSON_Parse(json_data);
    free(json_data);
    if (json == NULL) {
        printf("解析 JSON 失敗！\n");
        return -1;
    }

    cJSON *username = cJSON_GetObjectItemCaseSensitive(json, "username");
    cJSON *password = cJSON_GetObjectItemCaseSensitive(json, "password");
    cJSON *broker_address = cJSON_GetObjectItemCaseSensitive(json, "broker_address");
    cJSON *temperature_humidity_sensor = cJSON_GetObjectItemCaseSensitive(json, "temperature_humidity_sensor");
    cJSON *humidity_compensation = cJSON_GetObjectItemCaseSensitive(json, "humidity_compensation");

    if (cJSON_IsString(username) && (username->valuestring != NULL)) {
        strncpy(config->username, username->valuestring, sizeof(config->username) - 1);
        config->username[sizeof(config->username) - 1] = '\0';
    } else {
        printf("無法取得 username\n");
        cJSON_Delete(json);
        return -1;
    }

    if (cJSON_IsString(password) && (password->valuestring != NULL)) {
        strncpy(config->password, password->valuestring, sizeof(config->password) - 1);
        config->password[sizeof(config->password) - 1] = '\0';
    } else {
        printf("無法取得 password\n");
        cJSON_Delete(json);
        return -1;
    }

    if (cJSON_IsString(broker_address) && (broker_address->valuestring != NULL)) {
        strncpy(config->broker_address, broker_address->valuestring, sizeof(config->broker_address) - 1);
        config->broker_address[sizeof(config->broker_address) - 1] = '\0';
    } else {
        printf("無法取得 broker_address\n");
        cJSON_Delete(json);
        return -1;
    }

    if (cJSON_IsString(temperature_humidity_sensor) && (temperature_humidity_sensor->valuestring != NULL)) {
        strncpy(config->temperature_humidity_sensor, temperature_humidity_sensor->valuestring, sizeof(config->temperature_humidity_sensor) - 1);
        config->temperature_humidity_sensor[sizeof(config->temperature_humidity_sensor) - 1] = '\0';
    } else {
        printf("無法取得 temperature_humidity_sensor\n");
        cJSON_Delete(json);
        return -1;
    }

    if (cJSON_IsNumber(humidity_compensation)) {
        config->humidity_compensation = humidity_compensation->valueint;
    } else {
        printf("無法取得 humidity_compensation\n");
        cJSON_Delete(json);
        return -1;
    }

    cJSON_Delete(json);
    return 0;
}