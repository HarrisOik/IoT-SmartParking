const mongoose = require('mongoose');

// takes mongodb connection URL for DB connection.

const connectDB = (url) => {
    return mongoose.connect(url)
}

module.exports = connectDB