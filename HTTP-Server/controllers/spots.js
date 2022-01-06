const Spot = require('../models/Spot')

// returns all spots found on the db as json. used by front end

const getAllSpots = async (req,res) => {
    try {
        const spots = await Spot.find({})
        res.status(200).json({ spots })
    } catch (error) {
        res.status(500).json({ msg: error }) 
    }
}

// creates a new parking spot on the db. used by sensors

const createSpot = async (req,res) => {
    try {
        const spot = await Spot.create(req.body)
        res.status(201).json({ spot })    
    } catch (error) {
        res.status(500).json({ msg: error })    
    }
}

// updates a parking spot on the db. used by sensors

const updateSpot = async (req,res) => {
    try {
        const {name:spotNAME} = req.params;
        const spot = await Spot.findOneAndUpdate({name:spotNAME},req.body,{
            new:true,
            runValidators: true,
        })
        if (!spot) {
            return res.status(404).json({ msg: `No spot with name: ${spotNAME}` })
        }
        res.status(200).json({ spot })
    } catch (error) {
        res.status(500).json({ msg: error })
    }
}

// deletes a parking spot. used by admins

const deleteSpot = async (req,res) => {
    try {
        const {name:spotNAME} = req.params;
        const spot = await Spot.findOneAndDelete({name:spotNAME});
        if (!spot) {
            return res.status(404).json({ msg: `No spot with name: ${spotNAME}` })
        }
        res.status(200).json({ spot })
    } catch (error) {
        res.status(500).json({ msg: error })
    }
}

module.exports = {
    getAllSpots,
    createSpot,
    updateSpot,
    deleteSpot,
}