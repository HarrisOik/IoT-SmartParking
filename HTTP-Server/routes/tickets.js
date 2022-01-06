const express = require('express')
const router = express.Router();

const {getTicket,createTicket} = require('../controllers/tickets')

// routes for all functions regarding tickets

router.route('/').post(createTicket)
router.route('/:ticket').get(getTicket)


module.exports = router