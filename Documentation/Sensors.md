# Hardware Information

---

## About

We utilized two different "groups" of sensors for the project. The parking sensors are responsible for sending and updating the status to the database through the API. The RFID sensors are responsible for scanning and verifying the RFID card by sending a GET request to the database through the API. In this document you will find a more in depth guide of the changes someone will need to do in order to use the sensors properly, as well as how the sensors actually work.

## How to Setup

1. The easiest way to setup and run the sensors is through the Arduino IDE. You can easily edit the neccssary code and push the changes to the sensors.

2. The first step is to change the WiFi credentials so the sensors have internet connectivity. Note that if you do not have IP enabled sensors this code will not work, but it can be altered to send the data through other means (e.g. NRF or Wired) to a middleware which will then push the data to the database through an API (e.g. with an RPi). The changes happen at these two variables:
```
const char* ssid = "your_id";
const char* password = "your_pass";
```
The WiFi SSID is the WiFi's name and the PASSWORD is the WiFi's password. Once you change those two variables, the sensors should have internet connectivity. The variables are identical in both sensors.

3. The second step is to change the API address. This depends on the network address the API is running on. Once you identified the address, you need to change the following locations at the code:

**RFID Sensor Code**
```
char Url[60] ="http://{SERVER_ADDRESS}:3000/api/v1/tickets/"; // For the RFID sensor
```
**Parking Sensor Code**
```
http.begin(client,"http://{SERVER_ADDRESS}:3000/api/v1/spots"); // For POST request (init) for parking sensor 
http.begin(client,"http://{SERVER_ADDRESS}:3000/api/v1/spots/A4"); // For PATCH request (update) for parking sensor
```
You will need to replace the {SERVER_ADDRESS} variable with the network address the API is running on.

4. After the changes, pushing and compiling the code on the sensors should make the sensors work.

## How it Works

### RFID Sensor

The functionality of the RFID sensor is very simple.
1. The user places the card near the sensor.
2. The sensor reads the card and translates the bytes into a string.
3. The sensor adds the string at the end of the request URL (e.g. http://{SERVER_ADDRESS}:3000/api/v1/tickets/{STRING}).
4. The sensor sends a GET request to the API asking for the existance of the card on the database.
5. Depending on the database response (200 or 404) the sensor acts accordingly.

>**NOTE:** At the moment, the sensor only prints if the card was found or not in the database on the terminal.

### Parking Sensor

The functionality of the Parking sensor is slightly more complex.
1. On activation, the sensor sends a post request through the API to add itself to the database (each sensor has a unique name).
2. The sensor now is continuously scanning for a car (with the help of a distance threshold)
3. When a car is found (the sensor detects a number below the threshold), the sensor sends a PATCH request to the API which will update the database entry (based on the sensor name)
4. When a car leaves (the sensor detects a number above the threshold), the sensor sends a PATCH request to the API which will update the database entry (based on the sensor name)
5. This loop continues until the sensors turn off.

>**IMPORTANT:** Depending on the quality of the sensors, distance sensors can have significant jitter. This will cause unecessary PATCH requests to be sent to the API which can result in issues and lag in a very big network. Although the sensors will return to their true status (if a spot is taken or not), it is wise to use high quality distance sensors to avoid issues like this.
