const express = require('express')
const router = express.Router();

const {getAllSpots,createSpot,updateSpot,deleteSpot,} = require('../controllers/spots')

// routes for all functions regarding spots

router.route('/').get(getAllSpots).post(createSpot)
router.route('/:name').patch(updateSpot).delete(deleteSpot)


module.exports = router