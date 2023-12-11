#include "IMUSimulator.h"

void setParameters(IMURegisters& imuRegisters);

void handleSimulationOption(SocketClient& socketClient) {

    IMURegisters imuRegisters;

    setParameters(imuRegisters);

    socketClient.sendRegisters(imuRegisters);

    std::cout << "\n================================== Plan your simulation ==================================\n";
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

    std::cout << "Simulate a gyroscope:\n";
    for (int i = 0; i < changesNumber; i++) {
        std::cout << "X" << i + 1 << " = ";
        std::cin >> imuData[i].gx;
        std::cout << "Y" << i + 1 << " = ";
        std::cin >> imuData[i].gy;
        std::cout << "Z" << i + 1 << " = ";
        std::cin >> imuData[i].gz;
        std::cout << "---------------------------------------------------------------------------------\n";
    }

    int showSIMvalues;
    std::cout << "Do you want to display simulated values. Type 1\n";
    std::cin >> showSIMvalues;

    int dataCount = 0;
    for (int i = 0; i < changesNumber; i++) { // SENDING SIMULATION data
        if (showSIMvalues == 1) {
            for (int j = 0; j < samplesNumber; j++) {
                std::cout << "Accelerometer: (" << imuData[i].ax << ", " << imuData[i].ay << ", " << imuData[i].az << ")\n";
                std::cout << "Gyroscope:     (" << imuData[i].gx << ", " << imuData[i].gy << ", " << imuData[i].gz << ")\n";
                std::cout << "---------------------------------------------------------------------------------\n";
            }
        }

        for (int j = 0; j < samplesNumber; j++) {
            socketClient.sendData(imuData[i]);
            dataCount++;
        }
    }
    socketClient.sendEND();
    
    std::cout << "Number of simulated values: " << dataCount << " in " 
    << std::setprecision(2) << dataCount * (1.0 / imuRegisters.samplingRate) << "s\n";
}

void setParameters(IMURegisters& imuRegisters) {
    int userInput;

    int tabSamplingRate[] = {ag_25Hz, ag_50Hz, ag_100Hz, ag_200Hz, ag_400Hz, ag_800Hz, ag_1600Hz};
    int tabAccelerometerRange[] = {a_2g, a_4g, a_8g, a_16g};
    int tabGyroscopeRange[] = {g_250dps, g_500dps, g_1000dps, g_2000dps};

    while (1) { // Selection for SamplingRate
        std::cout << "Choose  Sampling Rate:\n";
        std::cout << "0 - 25Hz\n";
        std::cout << "1 - 50Hz\n";
        std::cout << "2 - 100Hz\n";
        std::cout << "3 - 200Hz\n";
        std::cout << "4 - 400Hz\n";
        std::cout << "5 - 800Hz\n";
        std::cout << "6 - 1600Hz\n";
        std::cout << "Enter the number: ";
        std::cin >> userInput;

        if (userInput >= 0 && userInput <= 6) {
            imuRegisters.samplingRate = tabSamplingRate[userInput];
            break;
        } else {
            std::cout << "Entered value is invalid. Try again.\n";
        }
    }

    while (1) { // Selection for AccelerometerRange
        std::cout << "\nChoose Accelerometer Range:\n";
        std::cout << "0 - 2g\n";
        std::cout << "1 - 4g\n";
        std::cout << "2 - 8g\n";
        std::cout << "3 - 16g\n";
        std::cout << "Enter the number: ";
        std::cin >> userInput;

        if (userInput >= 0 && userInput <= 3) {
            imuRegisters.accelerometerRange = tabAccelerometerRange[userInput];
            break;
        } else {
            std::cout << "Entered value is invalid. Try again.\n";
        }
    }

    while (1) { // Selection for GyroscopeRange
        std::cout << "\nChoose Gyroscope Range:\n";
        std::cout << "0 - 250dps\n";
        std::cout << "1 - 500dps\n";
        std::cout << "2 - 1000dps\n";
        std::cout << "3 - 2000dps\n";
        std::cout << "Enter the number: ";
        std::cin >> userInput;

        // Check if the entered value is valid for GyroscopeRange
        if (userInput >= 0 && userInput <= 3) {
            imuRegisters.gyroscopeRange = tabGyroscopeRange[userInput];
            break;
        } else {
            std::cout << "Entered value is invalid. Try again.\n";
        }
    }

    std::cout << "\n---------------------------------------------------------------------------------\n";
    std::cout << "Sampling rate:                   " << imuRegisters.samplingRate        << " Hz"   << "\n";
    std::cout << "Accelerometer measurement range: " << imuRegisters.accelerometerRange  << " g"    << "\n";
    std::cout << "Gyroscope measurement range:     " << imuRegisters.gyroscopeRange      << " dps"  << "\n";
    std::cout << "---------------------------------------------------------------------------------\n";
}