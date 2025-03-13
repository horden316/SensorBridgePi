#include "sensor_sht3x.h"

// 計算 CRC8 (多項式 0x31, 初始值 0xFF)
uint8_t crc8(const uint8_t *data, int len) {
    uint8_t crc = 0xFF;
    for (int i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc <<= 1;
        }
    }
    return crc;
}

sensor_result get_sht3x_data(char *i2c_device, int addr) {
    int file;

    sensor_result result;
    
    // 開啟 I2C 裝置
    if ((file = open(i2c_device, O_RDWR)) < 0) {
        perror("開啟 I2C 裝置失敗");
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        perror("設定 I2C 位址失敗");
        close(file);
        exit(1);
    }
    
    // 發送測量命令 (高精度模式)
    uint8_t cmd[2] = {0x24, 0x00};
    if (write(file, cmd, 2) != 2) {
        perror("寫入命令失敗");
        close(file);
        exit(1);
    }
    
    // 延遲等待量測完成 (建議至少 50ms)
    usleep(50000);
    
    // 讀取 6 個位元組的資料
    uint8_t data[6];
    if (read(file, data, 6) != 6) {
        perror("讀取數據失敗");
        close(file);
        exit(1);
    }
    
    // 驗證溫度數據 CRC
    if (crc8(data, 2) != data[2]) {
        fprintf(stderr, "溫度數據 CRC 檢查失敗\n");
        close(file);
        exit(1);
    }
    
    // 驗證濕度數據 CRC
    if (crc8(&data[3], 2) != data[5]) {
        fprintf(stderr, "濕度數據 CRC 檢查失敗\n");
        close(file);
        exit(1);
    }
    
    // 將兩個位元組組合成原始數據
    uint16_t tempRaw = (data[0] << 8) | data[1];
    uint16_t humRaw  = (data[3] << 8) | data[4];
    
    // 計算實際溫度與濕度
    float temperature = -45 + 175 * ((float)tempRaw / 65535.0);
    float humidity    = 100 * ((float)humRaw / 65535.0);
    
    //printf("溫度: %.2f °C\n", temperature);
    //printf("濕度: %.2f %%\n", humidity);
    result.type = SENSOR_TYPE_TEMPERATURE_HUMIDITY;
    result.value.temphum.temperature = temperature;
    result.value.temphum.humidity = humidity;
    result.timestamp = time(NULL);
    result.get_status = 0;
    
    close(file);
    return result;
}
