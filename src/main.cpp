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

    // If app is open separately (not via FF detector)
    //std::cout << "Open FREE-FALL_detector.exe, when done press enter" << '\n'; 
    //getchar();

    SocketClient socketClient("127.0.0.1", "12345"); // Localhost (Loopback address), port
    std::cout << "Port: 1234" << '\n';

    while(1) {
        int inputOption;
        std::cout << "Do you want to read data from a file (1) or simulate values (2)? \tExit (3)\n";
        std::cin >> inputOption;

        switch (inputOption) {
        case 1: { // READ FILE----------------------------------------------------
            handleFileOption(socketClient);

            getchar();
            std::cout << "\nPress enter to exit.";
            getchar();
            return 0;
        }
        case 2: { // SIMULATION---------------------------------------------------          
            handleSimulationOption(socketClient);

            getchar();
            std::cout << "\nPress enter to exit.";
            getchar();
            return 0;
        }
        case 3: { // EXIT---------------------------------------------------------
            std::cout << "Exiting the program. Goodbye!\n";
            return 0;
        }
        default: {  // OTHER--------------------------------------------------------
            std::cerr << "Invalid option. Please enter (1) or (2)." << std::endl;
        }
        }
    }

    return 0;
}