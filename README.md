
# IoT-Based Automatic Transformer Health & Thermal Monitoring System with Smart Fault Isolation

## Project Overview

This project presents an ESP32-based intelligent transformer monitoring and protection system capable of continuously monitoring transformer health parameters in real time. The system measures winding temperature, oil temperature, load current, and oil level to detect abnormal operating conditions before catastrophic failures occur.

Traditional transformer protection systems operate only after faults occur. In contrast, this project adopts a preventive maintenance approach by continuously analyzing transformer health and automatically isolating the transformer whenever unsafe conditions are detected.

The system uses low-cost IoT hardware and cloud telemetry to provide an affordable alternative to industrial monitoring systems.

---

## Objectives

* Monitor transformer oil temperature.
* Monitor winding temperature.
* Measure transformer load current.
* Detect oil leakage using oil-level sensing.
* Provide real-time IoT telemetry.
* Trigger automatic fault isolation during abnormal conditions.
* Generate local alerts using a buzzer and LEDs.

---

## Features

* Real-time transformer health monitoring.
* Thermal analysis using DS18B20 sensors.
* Current sensing using ACS712.
* Oil-level monitoring using HC-SR04.
* Automatic relay tripping.
* Audible fault alerts.
* Wi-Fi-based remote monitoring.
* Expandable IoT dashboard support.

---

## Hardware Components

* ESP32 Development Board
* DS18B20 Waterproof Temperature Sensors
* ACS712 Current Sensor (20A)
* HC-SR04 Ultrasonic Sensor
* 1-Channel Relay Module
* Active Buzzer
* LEDs and resistors
* 12V Step-Down Transformer
* Breadboard and jumper wires

---

## Working Principle

The ESP32 continuously collects data from temperature, current, and oil-level sensors.

The measured values are compared against predefined safety limits:

* Temperature greater than 85°C
* Load current exceeding the rated limit
* Oil level below the threshold value

When any of these conditions are violated, the ESP32:

1. Trips the relay.
2. Activates the buzzer.
3. Turns on the fault indicator.
4. Sends status information to the IoT dashboard.

Under normal conditions, the relay remains active and the system continues monitoring.

---

## System Workflow

1. Sensor data acquisition.
2. Signal processing and filtering.
3. Threshold comparison.
4. Fault detection.
5. Relay tripping.
6. Alarm generation.
7. Cloud telemetry update.

---

## Folder Structure

```text
iot-transformer-fault-isolation-system/

├── README.md
├── COMPONENTS.md
├── CONNECTIONS.md
├── firmware/
├── docs/
├── dashboard/
└── assets/
```

---

## Future Improvements

* Historical data logging.
* Machine learning-based fault prediction.
* GSM alerts.
* Web dashboard integration.
* Power factor monitoring.
* Transformer efficiency analysis.

---

## Technologies Used

* ESP32
* Arduino IDE
* Embedded C++
* IoT
* Wi-Fi
* Blynk
* Electrical Protection Systems

---

## Status

Project under development.

---

## Author

Anendra Narayan Dixit

B.Tech Electrical Engineering

Central University of Karnataka
