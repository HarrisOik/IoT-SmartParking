# Web Application Information

---

## Introduction:

The Web Application is a very basic interface made with Vue.js. Through the applications users can add their RFID tickets to the database as well as see any available and taken spot in the network. Please refer to the quick start manual to see how to run the application.

>**NOTE:** Due to some issues we encountered with Vue routing, we will use the development server for the operation of the application.

## Pages:

The application has three pages:
1. The main page.
2. The spot availability page.
3. The ticket registration page.

The main page contains a very basic menu for the user to navigate through the application.

The spot availability page, sends a GET request to the API. The GET requests returns a JSON formatted body with all the spots and their data (name, availability etc.). The page showcases the spots (in a card style manner) and it sorts them by name.

The ticket registration page, has a form with a string field. There the user can insert their RFID card ID. Then the application sends a POST request to the API. If the request is successful the user will receieve a success notification.
