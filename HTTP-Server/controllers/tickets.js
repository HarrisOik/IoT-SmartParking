const Ticket = require('../models/Ticket')

// returns specific ticket. used by sensors

const getTicket = async (req,res) => {
    try {
        const {ticket:ticketNAME} = req.params;
        const ticket = await Ticket.findOne({ticket:ticketNAME})
        if (!ticket) {
            return res.status(404).json({ msg: `No ticket with ID: ${ticketNAME}` })
        }
        res.status(200).json({ ticket })
    } catch (error) {
        res.status(500).json({ msg: error })
    }
}

// creates a new ticket. used by front end

const createTicket = async (req,res) => {
    try {
        const ticket = await Ticket.create(req.body)
        res.status(201).json({ ticket })    
    } catch (error) {
        res.status(500).json({ msg: error })    
    }
}

module.exports = {
    getTicket,
    createTicket,
}