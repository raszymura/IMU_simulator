#include "IMUcsv.h"


void handleFileOption(SocketClient& socketClient) {
    IMUData imuData;
    IMURegisters imuRegisters;

    // Relative path of saved logs
    const std::string filename = "../data/2023-01-16-15-33-09-imu.csv";
    ReadCSV reader(filename);

    // IMU settings for saved logs
    imuRegisters.samplingRate = ag_50Hz;        // Sampling rate in [Hz]
    imuRegisters.accelerometerRange = a_2g;     // Accelerometer measurement range in [g]
    imuRegisters.gyroscopeRange = g_250dps;     // Gyroscope measurement range in [dps]

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
