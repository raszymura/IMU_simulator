#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "IMU.h"

class ReadCSV{
private:
    std::ifstream file;
    std::string line;
    bool firstLine; // Flag to skip the first line

public:
    ReadCSV(const std::string &filename);
    ~ReadCSV();
    bool readData(IMUData &imuData);
};

/*
The data in the .csv file is stored as follows:

ax, ay, az, gx, gy, gz
-0.8137455366679891,-0.043336283455916016,-0.5445722830896939,0.18311105685598317,-0.5035554063539537,0.5493331705679495
-0.815576647236549,-0.041383098849452196,-0.5449385052034059,0.22888882106997893,-0.5035554063539537,0.5951109347819452
-0.8149662770470291,-0.04199346903897214,-0.5445722830896939,0.27466658528397475,-0.6256294442579424,0.5493331705679495
-0.815576647236549,-0.043214209418012024,-0.5439619129001739,0.24414807580797754,-0.6103701895199438,0.5340739158299509
-0.8149662770470291,-0.04248176519058809,-0.5440839869380779,0.25940733054597614,-0.5798516800439466,0.5951109347819452
-0.814233832819605,-0.04113895077364421,-0.5410321359904782,0.25940733054597614,-0.640888698995941,0.5188146610919523
...and so on...

The first line shows the header.
The next lines are 6 recording data separated by a comma.

Saved logs have >15 decimal digits,
so I will use the signed double type to represent them in the code.
--------------------------------------------------------------------------------
The data was saved with:
- sampling rate: 50Hz
- accelerometer measurement range: 2.0g
- gyroscope measurement range: 250dps (Degrees per Second)
*/