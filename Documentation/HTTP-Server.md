# HTTP Server Documentation

---

## Introduction:
This document contains in full detail the functionality and operation of the HTTP server for the IoT-SmartParking project. Within this document you will find:
- [Dependencies](#dependencies)
- [How to Set Up The dotenv File](#setting-up-the-dotenv-file)
- [MongoDB Schemas](#mongodb-schemas)
- [Parking Spot API](#parking-spot-api)
- [Parking Ticket (RFID) API](#parking-ticket-api)
- [Parking Spot API Controllers](#parking-spot-api-controllers)
- [Parking Ticket (RFID) API Controllers](#parking-ticket-api-controllers)
- [Status Codes](#status-codes)

---

## Dependencies
### General Dependencies
The application requires the following dependencies to be installed in order to work. Those dependencies are:
- express.js
- mongoose.js
- dotenv

Express.js is used in order to utilise features like the express.Router. Also a very important tool is the JSON middleware (express.json) that express has.

>**NOTICE:** You must use Express v4.16.0 and onwards for this application to work as express.json does not exist in older versions.

Mongoose.js is used for the creation of schemas for our different objects (parking spots and tickets) as well as the connection and handling of MongoDB.

dotenv is used for setting up an environment variable. We will use this to add our connection URL to a file ignored by git.

>**IMPORTANT:** You must set up the .env file in order for the application to connect to the database[^1]. Without DB connection the application does not run. 

### Development Dependencies
The only development dependency that was used is nodemon.js. This is not necessary as it is only used for automatically restarting the server when the files are changed.
If you wish to run the server in development mode use ```npm run dev```

---

### Setting Up The dotenv File
The first and most important step for running this application after installing all the dependencies is to set up the dotenv file[^1]. The following steps explain the process:
1. Navigate inside the HTTP Server folder.
2. Create a file named ```.env```
3. Inside the file add the following variable -> ```MONGO_URI={your_mongo_connection_url}```
4. Save the file and run the server (assuming the dotenv dependency is installed the server should run and connect automatically to your database)

>**NOTE:** For this project we used MongoDB Atlas Database. It provides an application connection URL.

---

## MongoDB Schemas
The application utilises 2 different schemas. The Spot schema and the Ticket schema. 

The Spot schema has 2 attributes, name and status. 
- The name attribute is **required** and it is a string of maximum length of 5 characters. It must be **unique**.
- The status attribute is a boolean and it defaults to **false**. **True** indicates that the spot is taken, **False** indicates that the spot is free.

The Ticket schema has a single attribute, ticket.
- The ticket attribute is **required** and it is a string. It must be **unique**.

The schemas prevent any useless attributes to be added to the database by ignoring them while enforcing proper data structure for compatibility with the web application.

---

## Parking Spot API
The following table contains all the different routes that are related with the parking spots along with their results when they are executed. The {{URL}} variable is ```network_ip:3000```

| Route                          | Method      | Description                                                                       |
| ------------------------------ | ----------- | --------------------------------------------------------------------------------- |
| {{URL}}/api/v1/spots/          | GET         | Returns all parking spot entries from the database                                |
| {{URL}}/api/v1/spots/          | POST        | Creates a new parking spot                                                        |
| {{URL}}/api/v1/spots/:name     | PATCH       | Updates an existing parking spot matching the name given in the URL (:name)       |
| {{URL}}/api/v1/spots/:name     | DELETE      | Deletes an existing parking spot matching the name given in the URL (:name)       |

---

## Parking Ticket API
The following table contains all the different routes that are related with the parking tickets along with their results when they are executed. The {{URL}} variable is ```network_ip:3000```

| Route                            | Method      | Description                                                                         |
| -------------------------------- | ----------- | ----------------------------------------------------------------------------------- |
| {{URL}}/api/v1/tickets/          | POST        | Creates a new parking ticket                                                        |
| {{URL}}/api/v1/tickets/:ticket   | GET         | Returns an existing parking ticket matching the ticket given in the URL (:ticket)   |

---

## Parking Spot API Controllers
Now we will see the format the **requests** and **responses** for the parking spots for the proper operation of the HTTP server.
- spots/ GET request
```
URL:
spots/
BODY:
null
```
- spots/ GET response
```
BODY:
{
    "spots": [
        {
            "_id": "61d5d2d192c2b7203e299bed",
            "name": "A1",
            "status": false,
            "__v": 0
        },
        {
            "_id": "61d5d3d092c2b7203e299bef",
            "name": "A2",
            "status": true,
            "__v": 0
        },
       .
       .
       .
    ]
}
```
- spots/ POST request
```
URL:
spots/
BODY:
{
    "name":"B3",
    "status":true
}
```
- spots/ POST response
```
BODY:
{
    "spot": {
        "name": "B3",
        "status": true,
        "_id": "61dc3c603d90a5cb036125dc",
        "__v": 0
    }
}
```
- spots/:name PATCH request
```
URL:
spots/B3
BODY:
{
    "status":false
}
```
- spots/:name PATCH response
```
BODY:
{
    "spot": {
        "_id": "61dc3c603d90a5cb036125dc",
        "name": "B3",
        "status": false,
        "__v": 0
    }
}
```
- spots/:name DELETE request
```
URL:
spots/B3
BODY:
null
```
- spots/:name DELETE response
```
BODY:
{
    "spot": {
        "_id": "61dc3c603d90a5cb036125dc",
        "name": "B3",
        "status": false,
        "__v": 0
    }
}
```

---

## Parking Ticket API Controllers
Now we will see the format the **requests** and **responses** for the parking tickets for the proper operation of the HTTP server.
- tickets/ POST request
```
URL:
tickets/
BODY:
{
    "ticket": "12345abcd67890"
}
```
- tickets/ POST response
```
BODY:
{
    "ticket": {
        "ticket": "12345abcd67890",
        "_id": "61dc3d323d90a5cb036125e0",
        "__v": 0
    }
}
```
- tickets/:ticket GET request
```
URL:
tickets/12345abcd67890
BODY:
null
```
- tickets/:ticket GET response
```
BODY:
{
    "ticket": {
        "_id": "61dc3d323d90a5cb036125e0",
        "ticket": "12345abcd67890",
        "__v": 0
    }
}
```

---

## Status Codes
The following table shows the different status codes that a user can receive for each route.
| Route                            | Method      | On Success | On Failure | On Error |
| -------------------------------- | ----------- | ---------- | ---------- | -------- |
| {{URL}}/api/v1/spots/            | GET         | 200        | null       | 500      |
| {{URL}}/api/v1/spots/            | POST        | 201        | null       | 500      |
| {{URL}}/api/v1/spots/:name       | PATCH       | 200        | 404        | 500      |
| {{URL}}/api/v1/spots/:name       | DELETE      | 200        | 404        | 500      |
| {{URL}}/api/v1/tickets/          | POST        | 201        | null       | 500      |
| {{URL}}/api/v1/tickets/:ticket   | GET         | 200        | 404        | 500      |

[^1]: You can hard-code the URL inside of the app.js replacing the MONGO_URI variable, although it is not recommended.
