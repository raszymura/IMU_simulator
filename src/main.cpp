/**
 * This project was written as a recruitment task for Embevity.
 * @author Rafal Szymura
 * Date: December 2023
 */

#include <iostream>
#include <fstream>
#include <iomanip> // For std::setprecision

#include "ReadCSV.h"
#include "IMU.h"
// #include "IMUSimulator.h"
#include "SocketClient.h"

int main(){
    std::cout << "\n************** Welcome to IMU simulator! **************\n";

    std::cout << "Open FREE-FALL_detector.exe, when done press enter" << '\n';
    getchar();

    SocketClient socketClient("127.0.0.1", "12345"); // Localhost (Loopback address), port

    while(1) {
        IMUData imuData;
        IMURegisters imuRegisters;

        std::string inputOption;
        std::cout << "Do you want to read data from a file (f) or simulate values (s)? \tExit (e)\n";
        std::cin >> inputOption;

        switch (inputOption[0]) {
        case 'f': { // FILE---------------------------------------------------------------------------------------------
            // Relative path of saved logs
            const std::string filename = "../data/2023-01-16-15-33-09-imu.csv";
            ReadCSV reader(filename);
            
            imuRegisters.samplingRate = 50;      // Sampling rate in Hz
            imuRegisters.accelerometerRange = 2; // Accelerometer measurement range in g
            imuRegisters.gyroscopeRange = 250;   // Gyroscope measurement range in dps

            std::cout << std::fixed << std::setprecision(15);
            while (reader.readData(imuData)) {
                std::cout << "Accelerometer: (" << imuData.ax << ", " << imuData.ay << ", " << imuData.az << ")\n";
                std::cout << "Gyroscope:     (" << imuData.gx << ", " << imuData.gy << ", " << imuData.gz << ")\n";
                std::cout << "---------------------------------------------------------------------------------\n";

                socketClient.sendData(imuData);
            }

            //socketClient.sendData(imuData);

            std::cout << "Done.\n";
            //socketClient.sendRegisters(imuRegisters);
            
            std::cout << "---------------------------------------------------------------------------------\n";
            std::cout << "Sampling rate:                   " << imuRegisters.samplingRate        << " Hz"   << "\n";
            std::cout << "Accelerometer measurement range: " << imuRegisters.accelerometerRange  << " g"    << "\n";
            std::cout << "Gyroscope measurement range:     " << imuRegisters.gyroscopeRange      << " dps"  << "\n";
            std::cout << "---------------------------------------------------------------------------------\n";

            break;
        }
        case 's': { // SIMULATION---------------------------------------------------------------------------------------------
            /*
            std::cout << "Enter Accelerometer data (ax ay az): ";
            std::cin >> imuData.ax >> imuData.ay >> imuData.az;

            std::cout << "Enter Gyroscope data (gx gy gz): ";
            std::cin >> imuData.gx >> imuData.gy >> imuData.gz;

            std::cout << "Entered data:\n";
            std::cout << "Accelerometer: (" << imuData.ax << ", " << imuData.ay << ", " << imuData.az << ")\n";
            std::cout << "Gyroscope: (" << imuData.gx << ", " << imuData.gy << ", " << imuData.gz << ")\n";
            */
           break;
        }
        case 'e': { // EXIT---------------------------------------------------------------------------------------------
            std::cout << "Exiting the program. Goodbye!\n";
            return 0;
        }
        default: {  // OTHER---------------------------------------------------------------------------------------------
            std::cerr << "Invalid option. Please enter 'f' or 's'." << std::endl;
        }
        }
    }

    return 0;
}