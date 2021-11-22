# IoT-SmartParking
## About:
This is a group project developed for the Internet of Things (IoT) course of University of West Attica (UniWA).

This project expands on a pre-existing idea of automatically tracked parking spots that notify users of availability into a completely autonomous system used in private parkings (i.e. shopping mall parking).

The goal for the project is to be "endlessly" expandable while utilizing cheap and long-lasting sensors.

## Hardware Requirements:

### Requirements for Parking Node (Wireless):
- 1 HY-SRF05 Ultrasonic Distance Sensor
- 1 ESP8266 Wi-Fi MCU

<b>Approximate Node Price ≈ 6-8€</b>

### Requirements for Gate System (Wireless):
- 1 RFID Reader
- 1 ESP8266 Wi-Fi MCU

<b>Approximate Node Price ≈ 10-12€</b>

### Requirements for Middleware:
- 1 Raspberry Pi

<b>Approximate Price ≈ 20-25€</b>

## Architecture:
![architecture](https://user-images.githubusercontent.com/79098484/142884899-d7bde8e8-cf9e-4332-8891-2aa61237e9db.jpg)
### Endeictive Use-Case:
1. User registers RFID card/tag on the system via the web application
2. User can check the web application for all available parking spots in the system
3. User arrives at a gate node with a vehicle and scans the card/tag on the RFID reader[^1]
4. After the system verifies that the card/tag is valid/registered, it allows the user to enter the parking space[^1]
5. User parks the vehicle on any available parking spot in the system
6. System detects the vehicle and automatically updates the web application 

[^1]: The system does NOT NEED to have a GATE SYSTEM. It can also operate simply as a tracker for available parking spots.
