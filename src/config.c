#include "config.h"

int read_config(const char* filename, Config* config) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("開啟設定檔失敗");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // 忽略註解行與空行
        if (line[0] == '#' || line[0] == '\n')
            continue;
        
        // 移除行尾的換行字元
        line[strcspn(line, "\n")] = '\0';
        
        // 尋找 '=' 字元作為分隔符號
        char* delimiter = strchr(line, '=');
        if (delimiter == NULL)
            continue;
        
        // 將字串分割成 key 與 value
        *delimiter = '\0';
        char* key = line;
        char* value = delimiter + 1;

        // 去除 key 與 value 左側的空白
        while (*key == ' ' || *key == '\t') key++;
        while (*value == ' ' || *value == '\t') value++;

        // 儲存對應的設定值
        if (strcmp(key, "username") == 0) {
            strncpy(config->username, value, sizeof(config->username) - 1);
            config->username[sizeof(config->username) - 1] = '\0';
        } else if (strcmp(key, "password") == 0) {
            strncpy(config->password, value, sizeof(config->password) - 1);
            config->password[sizeof(config->password) - 1] = '\0';
        } else if (strcmp(key, "broker_address") == 0) {
            strncpy(config->broker_address, value, sizeof(config->broker_address) - 1);
            config->broker_address[sizeof(config->broker_address) - 1] = '\0';
        }
    }
    
    fclose(file);
    return 0;
}