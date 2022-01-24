# Quick Start Manual

## Project setup

You will need to setup the proper API IP address as well as the wifi connection credentials you will use on the sensors. To do this, you will need to change the following code:
```
// WiFi connection credentials 

const char* ssid = "your_id";
const char* password = "your_pass";

// API connection paths

char Url[60] ="http://{SERVER_ADDRESS}:3000/api/v1/tickets/"; // For the RFID sensor

http.begin(client,"http://{SERVER_ADDRESS}:3000/api/v1/spots"); // For POST request (init) for parking sensor 
http.begin(client,"http://{SERVER_ADDRESS}:3000/api/v1/spots/A4"); // For PATCH request (update) for parking sensor
```
After setting the proper paths and credentials, you can push and compile the code to the arduino. As this is mainly for development, there are terminal logs for actions that occur.

>**NOTICE:** Make sure the API is up and running with a proper database connection established, otherwise all the requests and sensors sent will fail. Note that the front-end (web application) is not needed for the sensors to work, although it provides a nice visual representation of data.
