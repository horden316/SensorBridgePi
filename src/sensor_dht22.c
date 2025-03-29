#include "sensor_dht22.h"
#define TIMEOUT 100

sensor_result get_dht22_data(int PIN) {
    unsigned char state = 1;
    unsigned char data[5] = {0,0,0,0,0};
    unsigned char checksum;
    float temperature;
    float humidity;
    
    int timeout = 0;

    sensor_result result;


    // Start signal
    wiringPiSetup();
    pinMode(PIN, OUTPUT);  //SET OUTPUT

    digitalWrite(PIN, LOW);
    delay(10); // DHT22要求至少拉低1ms
    digitalWrite(PIN, HIGH);
    delayMicroseconds(30); // 拉高20~40us


    // DHT22 response
    pinMode(PIN, INPUT);    //SET INPUT
    while (digitalRead(PIN) && timeout < TIMEOUT) //DHT22 will pull down ~80us
    {
        timeout++;
        delayMicroseconds(1);
    }

    if (timeout >= TIMEOUT){
        result.get_status = 1;
        return result;
    }
    else{
        timeout = 0;
    }
    
    while (!digitalRead(PIN) && timeout < TIMEOUT) //DHT22 pull down and then pull up ~80us
    {
        timeout++;
        delayMicroseconds(1);
    }

    if (timeout >= TIMEOUT) {
        printf("DHT22 might not be connected\n");
        result.get_status = 2;
        return result;
    } else {
        timeout = 0;
    }

    // Read data
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            timeout = 0;
            while (digitalRead(PIN) && timeout < TIMEOUT) {
                timeout++;
                delayMicroseconds(1);
            }
            timeout = 0;
            while (!digitalRead(PIN) && timeout < TIMEOUT) //wait for high level
            {
                timeout++;
                delayMicroseconds(1);
            }
            delayMicroseconds(40); //wait for 40us
            if (digitalRead(PIN))
                state = 1;
            else
                state = 0;
            data[i] = (data[i] << 1) | state;
        }
    }

    // Checksum
    checksum = data[0] + data[1] + data[2] + data[3];
    if (checksum == data[4]) {
        humidity = data[0] + data[1] * 0.1; // 濕度解析
        temperature = data[2] + data[3] * 0.1; // 溫度解析
    } else {
        printf("Checksum error\n");
        result.get_status = 3;
        return result;
    }

    result.type = SENSOR_TYPE_TEMPERATURE_HUMIDITY;
    result.value.temphum.temperature = temperature;
    result.value.temphum.humidity = humidity;
    result.timestamp = time(NULL);
    result.get_status = 0;

    return result;
}
