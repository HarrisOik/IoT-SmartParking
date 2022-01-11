const express = require('express');
const cors = require('cors')
const app = express();
const spots = require('./routes/spots')
const tickets = require('./routes/tickets')
const connectDB = require('./db/connect')
require('dotenv').config()

// middleware
// app.use(express.static('./public')) for serving front end
app.use(cors())                 // middleware for allowing foreign URLs
app.use(express.json());        // middleware for json handling

// routes
app.use('/api/v1/spots', spots)         // routes for spots
app.use('/api/v1/tickets', tickets)     // routes for tickets

const port = 3000

// waits for mongodb connection before starting, prevents starting with no connection

const start = async () => {
    try {
        await connectDB(process.env.MONGO_URI)
        app.listen(port, console.log(`Server is listening on port ${port}... `))
    } catch (error) {
        console.log(error)       
    }
}

start()