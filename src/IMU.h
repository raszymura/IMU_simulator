#pragma once

#include <cstdint>

struct IMUData {
    double ax, ay, az;  // Accelerometer data
    double gx, gy, gz;  // Gyroscope data
};

struct IMURegisters {
    int samplingRate;        // Sampling rate in Hz (ODR)
    int accelerometerRange;  // Accelerometer measurement range in g
    int gyroscopeRange;      // Gyroscope measurement range in dps
};

//---------------------------------------------------------------------
// Not used yet
struct RAW_IMUData { // 16 bits = 2 bytes
    int16_t ax, ay, az;  // Raw accelerometer data
    int16_t gx, gy, gz;  // Raw gyroscope data
};

//---------------------------------------------------------------------
enum SamplingRate { // Accelerometer and Gyroscope
    ag_25Hz = 25,
    ag_50Hz = 50,
    ag_100Hz = 100,
    ag_200Hz = 200,
    ag_400Hz = 400,
    ag_800Hz = 800,
    ag_1600Hz = 1600
};

enum AccelerometerRange { // Sensitivity Scale Factor
    a_2g = 2,           // 16,384  LSB/g 
    a_4g = 4,           // 8,192  LSB/g 
    a_8g = 8,           // 4,096  LSB/g 
    a_16g = 16          // 2,048  LSB/g 
}; // ± 2/4/8/16

enum GyroscopeRange {
    g_250dps = 250,     // 131  LSB/dps
    g_500dps = 500,     // 65.5 LSB/dps
    g_1000dps = 1000,   // 32.8 LSB/dps
    g_2000dps = 2000    // 16.4 LSB/dps
}; // ± 250/500/1000/2000

/************************** From ICM-42670-P Datasheet ***************************************************
# Output Data Rate (ODR) - (aka “sampling rate”) is the rate at which a sensor obtains new measurements,
or samples. ODR is measured in number of samples per second (Hz).

# Full Scale Range (FSR) - is associated with the range of values that can be measured for a given sensor and allows 
the application developer to trade-off measurement precision for larger ranges of detection. 
The full-scale range of the gyro sensor may be digitally programmed to:
±250, ±500, ±1000, ±2000 degrees per second (dps).
The full-scale range of the accelerometers sensor may be adjusted to:
±2g, ±4g, ±8g and ±16g.

# SENSOR DATA REGISTERS 
The sensor data registers contain the latest gyroscope, accelerometer, and temperature measurement data. They 
are read-only registers and are accessed via the serial interface. Data from these registers may be read any time,
but the simulator will only use FIFO register for reading.

# I2C
The ICM-42670-P always operates as a slave device when communicating to the system processor, which thus acts 
as the master. The maximum bus speed is 1 MHz.

Selected registers:
______________________REGISTER MAP____________________________
--------------------USER BANK 0 REGISTER MAP--------------------
# GYRO_CONFIG0
GYRO_UI_FS_SEL  Full scale select for gyroscope UI interface output
                00: ±2000 dps
                01: ±1000 dps
                10: ±500 dps
                11: ±250 dps

GYRO_ODR        Gyroscope ODR selection for UI interface output
                0101: 1.6k Hz
                0110: 800 Hz
                0111: 400 Hz
                1000: 200 Hz
                1001: 100 Hz
                1010: 50 Hz
                1011: 25 Hz
                1100: 12.5 Hz

# ACCEL_CONFIG0
ACCEL_UI_FS_SEL Full scale select for accelerometer UI interface output
                00: ±16g 
                01: ±8g
                10: ±4g
                11: ±2g

ACCEL_ODR       Gyroscope ODR selection for UI interface output
                0101: 1.6 kHz
                0110: 800 Hz
                0111: 400 Hz
                1000: 200 Hz
                1001: 100 Hz
                1010: 50 Hz
                1011: 25 Hz

--------------------USER BANK MREG1, MREG2, MREG3 REGISTER MAP----------------
I do not reproduce this
*/