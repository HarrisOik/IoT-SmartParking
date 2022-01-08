# HTTP Server Documentation

---

## Introduction:
This document contains in full detail the functionality and operation of the HTTP server for the IoT-SmartParking project. Within this document you will find:
- [Dependencies](#dependencies)
- [How to Set Up The dotenv File](#setting-up-the-dotenv-file)
- [MongoDB Schemas](#mongodb-schemas)
- [Parking Spot HTTP Routes](#parking-spot-http-routes)
- [Parking Ticket (RFID) HTTP Routes](#parking-ticket-http-routes)
- [Parking Spot HTTP Controllers](#parking-spot-http-controllers)
- [Parking Ticket (RFID) HTTP Controllers](#parking-ticket-http-controllers)
- [Status Codes](#status-codes)

---

## Dependencies
### General Dependencies
The application requires the following dependencies to be installed in order to work. Those dependencies are:
- express
- mongoose
- dotenv
Express.js is used in order to utilise features like the express.Router. Also a very important tool is the JSON middleware (express.json) that express has.

>**NOTICE:** You must use Express v4.16.0 and onwards for this application to work as express.json does not exist in older versions.

Mongoose.js is used for the creation of schemas for our different objects (parking spots and tickets) as well as the connection and handling of MongoDB.
dotenv is used for setting up an environment variable. We will use this to add our connection URL to a file ignored by git.

>**IMPORTANT:** You must set up the .env file in order for the application to connect to the database. Without DB connection the application does not run. More on this later on.

### Development Dependencies
The only development dependency that was used is nodemon.js. This is not necessary as it is only used for automatically restarting the server when the files are changed.
If you wish to run the server in development mode use ```npm dev```

---

### Setting Up The dotenv File
The first and most important step for running this application after installing all the dependencies is to set up the dotenv file. The following steps explain the process:
1. Navigate inside the HTTP Server folder.
2. Create a file name ```.env```
3. Inside the file add the following variable -> ```MONGO_URI={your_atlas_connection_url}```
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

## Parking Spot HTTP Routes
The following table contains all the different routes that are related with the parking spots along with their results when they are executed. The {{URL}} variable is ```network_ip:3000```

| Route                          | Method      | Description                                                                       |
| ------------------------------ | ----------- | --------------------------------------------------------------------------------- |
| {{URL}}/api/v1/spots/          | GET         | Returns all parking spot entries from the database                                |
| {{URL}}/api/v1/spots/          | POST        | Creates a new parking spot                                                        |
| {{URL}}/api/v1/spots/:name     | PATCH       | Updates an existing parking spot matching the name given in the url (:name)       |
| {{URL}}/api/v1/spots/:name     | DELETE      | Deletes an existing parking spot matching the name given in the url (:name)       |

---

## Parking Ticket HTTP Routes
The following table contains all the different routes that are related with the parking tickets along with their results when they are executed. The {{URL}} variable is ```network_ip:3000```

| Route                            | Method      | Description                                                                         |
| -------------------------------- | ----------- | ----------------------------------------------------------------------------------- |
| {{URL}}/api/v1/tickets/          | POST        | Creates a new parking ticket                                                        |
| {{URL}}/api/v1/tickets/:ticket   | GET         | Returns an existing parking ticket matching the ticket given in the url (:ticket)   |

---

## Parking Spot HTTP Controllers
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

```
- spots/ POST request
```
URL:
spots/
BODY:
{
    "name":"A1",
    "status":false
}
```
- spots/ POST response
```
BODY:

```
- spots/:name PATCH request
```
URL:
spots/{parking_spot_name}
BODY:
{
    "status":true
}
```
- spots/:name PATCH response
```
BODY:

```
- spots/:name DELETE request
```
URL:
spots/{parking_spot_name}
BODY:
null
```
- spots/:name DELETE response
```
BODY:

```

---

## Parking Ticket HTTP Controllers
Now we will see the format the **requests** and **responses** for the parking tickets for the proper operation of the HTTP server.
- tickets/ POST request
```
URL:
tickets/
BODY:
{
    "ticket": "12345abcd6789"
}
```
- tickets/ POST response
```
BODY:

```
- tickets/:ticket GET request
```
URL:
tickets/12345abcd6789
BODY:
null
```
- tickets/:ticket GET response
```
BODY:

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
