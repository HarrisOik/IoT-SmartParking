const mongoose = require('mongoose');

// ticket schema for RFID cards

const TicketSchema = new mongoose.Schema({
    ticket: {
        type: String,
        required: [true, 'must provide RFID'],
        trim: true,
        unique: true,
    },
})

module.exports = mongoose.model('Ticket',TicketSchema)