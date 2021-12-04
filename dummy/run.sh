#! /bin/bash
if [ $# -eq 0 ]
  then
    echo "Usage ./run.sh [Project BaseDir]"
else
    if [ -d "$1" ]
      then 
        cd $1
        ./tools/poc-dummy-create parking-sensor-A1;
        ./tools/poc-dummy-create parking-sensor-A2;
        ./tools/poc-dummy-create parking-sensor-A3;

        for i in {1..6}; do 
            ./tools/poc-dummy-send parking-sensor-A1 "TAKEN";
            ./tools/poc-dummy-send parking-sensor-A2 "FREE";
            ./tools/poc-dummy-send parking-sensor-A3 "FREE"; 
            sleep 10;
        done
    else
        echo "Directory Not Found!"
    fi
fi