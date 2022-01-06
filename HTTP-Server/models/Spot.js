const mongoose = require('mongoose');

// db schema for parking spots

const SpotSchema = new mongoose.Schema({
    name: {
        type: String,
        required: [true, 'must provide name'],
        trim: true,
        maxlength: [5, 'name cannot exceed 5 characters'],
        unique: true,
    },
    status: {
        type: Boolean,
        default: false,
    },
})

module.exports = mongoose.model('Spot',SpotSchema)