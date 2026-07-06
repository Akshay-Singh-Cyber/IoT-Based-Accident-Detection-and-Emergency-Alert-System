# IoT-Based Accident Detection and Emergency Alert System

> A smart IoT-based vehicle safety system that automatically detects road accidents using motion sensors and instantly shares the accident location with emergency contacts via Telegram.

![ESP32](https://img.shields.io/badge/ESP32-NodeMCU-red)
![IoT](https://img.shields.io/badge/IoT-Embedded-blue)
![GPS](https://img.shields.io/badge/GPS-Ublox%207M-green)
![MPU9250](https://img.shields.io/badge/Sensor-MPU9250-orange)
![Language](https://img.shields.io/badge/Language-Arduino%20C++-yellow)

---

## Overview

Road accidents often result in delayed emergency response because victims may be unconscious or unable to communicate their location. This project presents a low-cost IoT-based accident detection system capable of automatically identifying collisions and notifying emergency contacts with the vehicle's real-time GPS location.

The system continuously monitors vehicle acceleration using an MPU-9250 inertial measurement unit. When the measured acceleration exceeds a predefined threshold, the ESP32 retrieves GPS coordinates from the Ublox 7M GPS module and sends an emergency alert through the Telegram Bot API, including a clickable Google Maps location.

---

## Features

- Automatic accident detection
- Real-time GPS location tracking
- Instant Telegram notification
- Google Maps location sharing
- ESP32-based embedded implementation
- Low-cost IoT architecture
- Lightweight and portable design

---

## Hardware Components

| Component | Purpose |
|-----------|---------|
| ESP32 NodeMCU | Main controller |
| MPU-9250 | 9-axis motion sensing |
| Ublox 7M GPS Module | GPS location tracking |
| Buzzer | Local emergency alert |
| Wi-Fi | Internet connectivity |

---

## Software Stack

- Arduino IDE
- Arduino C++
- TinyGPS++
- MPU9250 Library
- WiFi Library
- HTTPClient Library
- Telegram Bot API

---

## System Architecture

> *(Insert architecture image here later)*

```
MPU-9250
     │
     ▼
 ESP32 NodeMCU
     │
 ┌───┴────┐
 │        │
 ▼        ▼
GPS     Buzzer
 │
 ▼
Telegram Bot
 │
 ▼
Emergency Contact
```

---

## Working Principle

1. ESP32 continuously reads acceleration values from the MPU-9250.
2. The resultant acceleration (G-force) is calculated.
3. If the G-force exceeds the accident threshold, an accident is detected.
4. ESP32 obtains the current GPS coordinates.
5. A Telegram alert containing a Google Maps link is sent to emergency contacts.
6. The buzzer is activated to alert nearby people.

---

## Project Structure

```text
iot-accident-detection-system
│
├── firmware/
│   └── accident_detection.ino
│
├── circuit/
│
├── images/
│
├── results/
│
└── docs/
```

---

## Results

✔ Accident detection based on acceleration threshold

✔ GPS location acquisition

✔ Real-time Telegram notification

✔ Google Maps integration

✔ Functional hardware prototype

---

## Future Improvements

- GSM/LTE fallback communication
- Cloud dashboard
- Mobile application
- Machine Learning-based accident detection
- Battery backup
- Vehicle health monitoring

---

## My Contributions

- ESP32 firmware development
- Telegram Bot integration
- Real-time emergency communication
- Sensor integration and debugging
- Prototype testing and validation
- Technical documentation

---

## Acknowledgements

Project completed under the guidance of **Dr. Dev Narayan Yadav**

Department of Computer Science and Engineering

National Institute of Technology Rourkela

---

## License

This repository is intended for educational and research purposes.
