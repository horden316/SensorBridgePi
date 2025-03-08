#include "sensor_dht11.h"
#define TIMEOUT 100

int get_dht11_data(int PIN) {
    unsigned char state = 1;
    unsigned char counter = 0;
    unsigned char data[5] = {0,0,0,0,0};
    unsigned char checksum;
    unsigned char temperature;
    unsigned char humidity;
    
    int timeout = 0;


    // Start signal
    wiringPiSetup();
    pinMode(PIN, OUTPUT);  //SET OUTPUT

    digitalWrite(PIN, LOW);
    delay(20);     //pull down at least 18ms
    digitalWrite(PIN, HIGH);
    delayMicroseconds(35);   //host pull up 20~40us


    // DHT11 response
    pinMode(PIN, INPUT);    //SET INPUT
    while (digitalRead(PIN) && timeout < TIMEOUT) //DHT11 will pull down ~80us
    {
        timeout++;
        delayMicroseconds(1);
    };

    if (timeout >= TIMEOUT)
        return 1;
    else
        timeout = 0;
    
    while (!digitalRead(PIN) && timeout < TIMEOUT) //DHT11 pull down and then pull up ~80us
    {
        timeout++;
        delayMicroseconds(1);
    };

    if (timeout >= TIMEOUT)
        return 1;
    else
        timeout = 0;

    // Read data
    for (int i = 0; i < 5; i++) //read 40 bits data
    {
        for (int j = 0; j < 8; j++) //read 8 bits data
        {
            timeout = 0;
            while (digitalRead(PIN) && timeout < TIMEOUT) //wait for low level
            {
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
    if (checksum == data[4])
    {
        humidity_data = data[0];
        temp_data = data[2];
    }
    else
    {
        return 1;
    }



    //Print data
    printf("Humidity: %d%%\n", humidity);
    printf("Temperature: %d°C\n", temperature);

    
    return 0;
}