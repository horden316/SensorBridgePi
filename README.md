# SensorBridgePi
A modular C-based project for collecting data from various sensors on Orange Pi Zero 3

## Project Structure

```
project_root/
├── include/              # Public headers (API definitions)
│   ├── sensor.h          # Sensor interface definitions
│   ├── mqtt_connection.h # MQTT communication interface
│   ├── app.h             # Application layer interface
│   ├── utils.h           # Utilities and logging interface
│   └── config.h          
├── src/                  # Implementation code
│   ├── sensor_dht11.c    # Temperature/humidity sensor driver
│   ├── sensor_sht31.c    # Temperature sensor driver
│   ├── sensor_pir.c      # PIR sensor driver implementation
│   ├── mqtt_connection.c # MQTT communication module
│   ├── data_proc.c       # Data processing and formatting
│   ├── app.c             # Main application (main loop, task scheduling)
│   ├── utils.c           # Utilities and logging implementation
│   └── config.c          # Configuration parameters (e.g. pin assignments, MQTT server)
├── Makefile              # Build rules and targets
└── README.md             # Project documentation
```


## Installation
Install libgpiod library
```bash
sudo apt update
sudo apt install libgpiod-dev
```

Install mqtt library
```bash
sudo apt install libpaho-mqtt-dev
```

Insatll gpiod command line tool
```bash
sudo apt install gpiod
```

Install cJSON library
```bash
sudo apt install libcjson-dev
```

Install i2c-tools library
```bash
sudo apt install i2c-tools
```

## Build
```bash
make
```

## Create configuration file
add a file named `sensor_bridge_pi.json` in the project root directory with the following content
```
{
    "username": "admin",
    "password": "mysecretpassword",
    "broker_address": "tcp://localhost:1883"
    "temperature_humidity_sensor": "SHT3x",
    "humidity_compensation": 15
}
```