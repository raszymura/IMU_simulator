#include "ReadCSV.h"

ReadCSV::ReadCSV(const std::string& filename) : firstLine(true) {
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

ReadCSV::~ReadCSV() {
    if (file.is_open()) {
        file.close();
    }
}

bool ReadCSV::readData(IMUData& CSV_imuData) {
    if (std::getline(file, line)) {

        if (firstLine) { // Condition to skip the first line (header)
            firstLine = false;
            return readData(CSV_imuData); // Recursive call
        }

        std::istringstream iss(line);
        char comma;

        iss >> CSV_imuData.ax >> comma
            >> CSV_imuData.ay >> comma
            >> CSV_imuData.az >> comma
            >> CSV_imuData.gx >> comma
            >> CSV_imuData.gy >> comma
            >> CSV_imuData.gz;

        return true;
    }
    return false;
}
