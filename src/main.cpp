/**
 * This project was written as a recruitment task for Embevity.
 * @author Rafal Szymura
 * Date: December 2023
 */

#include <iostream>
#include <fstream>
#include <iomanip>

#include "ReadCSV.h"
#include "IMU.h"
#include "IMUSimulator.h"
#include "SocketClient.h"

void handleFileOption(SocketClient& socketClient);
void handleSimulationOption(SocketClient& socketClient);


int main(){
    std::cout << "\n************** Welcome to IMU simulator! **************\n";

    std::cout << "Open FREE-FALL_detector.exe, when done press enter" << '\n';
    getchar();

    SocketClient socketClient("127.0.0.1", "12345"); // Localhost (Loopback address), port
    std::cout << "Port: 1234" << '\n';

    while(1) {
        std::string inputOption;
        std::cout << "Do you want to read data from a file (f) or simulate values (s)? \tExit (e)\n";
        std::cin >> inputOption;

        switch (inputOption[0]) {
        case 'f': { // READ FILE----------------------------------------------------
            handleFileOption(socketClient);
            return 0;
        }
        case 's': { // SIMULATION---------------------------------------------------          
            handleSimulationOption(socketClient);
            return 0;
        }
        case 'e': { // EXIT---------------------------------------------------------
            std::cout << "Exiting the program. Goodbye!\n";
            return 0;
        }
        default: {  // OTHER--------------------------------------------------------
            std::cerr << "Invalid option. Please enter 'f' or 's'." << std::endl;
        }
        }
    }

    return 0;
}

void handleFileOption(SocketClient& socketClient) {
    IMUData imuData;
    IMURegisters imuRegisters;

    // Relative path of saved logs
    const std::string filename = "../data/2023-01-16-15-33-09-imu.csv"; // Path to the .csv file with IMU logs
    ReadCSV reader(filename);

    // IMU settings for saved logs
    imuRegisters.samplingRate = 50;      // Sampling rate in [Hz]
    imuRegisters.accelerometerRange = 2; // Accelerometer measurement range in [g]
    imuRegisters.gyroscopeRange = 250;   // Gyroscope measurement range in [dps]

    socketClient.sendRegisters(imuRegisters);

    std::cout << "---------------------------------------------------------------------------------\n";
    std::cout << "Sampling rate:                   " << imuRegisters.samplingRate        << " Hz"   << "\n";
    std::cout << "Accelerometer measurement range: " << imuRegisters.accelerometerRange  << " g"    << "\n";
    std::cout << "Gyroscope measurement range:     " << imuRegisters.gyroscopeRange      << " dps"  << "\n";
    std::cout << "---------------------------------------------------------------------------------\n";

    int showCSV;
    std::cout << "Do you want to display this data? Type 1\n";
    std::cin >> showCSV; 

    std::cout << std::fixed << std::setprecision(15);
    int dataCount = 0;
    while (reader.readData(imuData)) {
        if (showCSV == 1) {
            std::cout << "Accelerometer: (" << imuData.ax << ", " << imuData.ay << ", " << imuData.az << ")\n";
            std::cout << "Gyroscope:     (" << imuData.gx << ", " << imuData.gy << ", " << imuData.gz << ")\n";
            std::cout << "---------------------------------------------------------------------------------\n";
        }

        socketClient.sendData(imuData);
        dataCount++;
    }
    socketClient.sendEND();

    std::cout << "Number of simulated values: " << dataCount << " in " 
    << std::setprecision(2) << dataCount * (1.0 / imuRegisters.samplingRate) << "s\n";

    std::cout << "Done.\n";
}

void handleSimulationOption(SocketClient& socketClient) {

    IMURegisters imuRegisters;

    std::cout << "Enter Sampling rate: ";
    std::cin >> imuRegisters.samplingRate;
    std::cout << "Enter Accelerometer measurement range: ";
    std::cin >> imuRegisters.accelerometerRange;
    std::cout << "Gyroscope measurement range: ";
    std::cin >> imuRegisters.gyroscopeRange;

    socketClient.sendRegisters(imuRegisters);

    std::cout << "================================== Plan your simulation ==================================\n";
    std::cout << "How many value changes you want?\n";
    int changesNumber;
    std::cin >> changesNumber;
    std::cout << "How many samples per value?\n";
    int samplesNumber;
    std::cin >> samplesNumber;

    IMUData imuData[changesNumber];

    for (int i = 0; i < changesNumber; i++) {
        std::cout << "Accelerometer:\n";
        std::cout << "X" << i + 1 << " = ";
        std::cin >> imuData[i].ax;
        std::cout << "Y" << i + 1 << " = ";
        std::cin >> imuData[i].ay;
        std::cout << "Z" << i + 1 << " = ";
        std::cin >> imuData[i].az;
        std::cout << "---------------------------------------------------------------------------------\n";
    }

    std::cout << "If you also want to simulate a gyroscope, enter 1: ";
    int gyroscopeON;
    std::cin >> gyroscopeON;
    if (gyroscopeON == 1) {
        for (int i = 0; i < changesNumber; i++) {
            std::cout << "Gyroscope:\n";
            std::cout << "X" << i + 1 << " = ";
            std::cin >> imuData[i].gx;
            std::cout << "Y" << i + 1 << " = ";
            std::cin >> imuData[i].gy;
            std::cout << "Z" << i + 1 << " = ";
            std::cin >> imuData[i].gz;
            std::cout << "---------------------------------------------------------------------------------\n";
        }
    }

    int showSIMvalues;
    std::cout << "Do you want to display simulated values. Type 1\n";
    std::cin >> showSIMvalues;

    int dataCount = 0;
    for (int i = 0; i < changesNumber; i++) { // SENDING SIMULATION data
        if (showSIMvalues == 1) {
            std::cout << "Accelerometer: (" << imuData[i].ax << ", " << imuData[i].ay << ", " << imuData[i].az << ")\n";
            if (gyroscopeON == 1) {
                std::cout << "Gyroscope:     (" << imuData[i].gx << ", " << imuData[i].gy << ", " << imuData[i].gz << ")\n";
            }
            std::cout << "---------------------------------------------------------------------------------\n";
        }

        for (int j = 0; j < samplesNumber; j++) {
            socketClient.sendData(imuData[i]);
            dataCount++;
        }
    }
    socketClient.sendEND();
    
    std::cout << "Number of simulated values: " << dataCount << " in " 
    << std::setprecision(2) << dataCount * (1.0 / imuRegisters.samplingRate) << "s\n";

    std::cout << "Done.\n";
}

