# SensorBridgePi
A modular C-based project for collecting data from various sensors on Orange Pi Zero 3

## Project Structure

```
project_root/
├── include/              # Public headers (API definitions)
│   ├── hal.h             # Hardware abstraction layer interface
│   ├── sensor.h          # Sensor interface definitions
│   ├── mqtt.h            # MQTT communication interface
│   ├── app.h             # Application layer interface
│   ├── utils.h           # Utilities and logging interface
│   └── config.h          
├── src/                  # Implementation code
│   ├── hal.c             # Hardware abstraction layer implementation
│   ├── sensor_temp.c     # Temperature/humidity sensor driver
│   ├── sensor_pir.c      # PIR sensor driver implementation
│   ├── mqtt.c            # MQTT communication module
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

