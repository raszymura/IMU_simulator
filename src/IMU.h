#pragma once

/*
class IMU {
  public:
    ICM42670P(TwoWire &i2c,bool address_lsb);
    
    int begin();
    int startAccel(uint16_t odr, uint16_t fsr);
    int startGyro(uint16_t odr, uint16_t fsr);
    int getDataFromRegisters(inv_imu_sensor_event_t* evt);
    int enableFifoInterrupt(uint8_t intpin, ICM42670P_irq_handler handler, uint8_t fifo_watermark);
    int getDataFromFifo(ICM42670P_sensor_event_cb event_cb);
    bool isAccelDataValid(inv_imu_sensor_event_t *evt);
    bool isGyroDataValid(inv_imu_sensor_event_t *evt);

    uint8_t i2c_address;
    TwoWire *i2c;
  protected:
    struct inv_imu_device icm_driver;
    bool use_spi;
    ACCEL_CONFIG0_ODR_t accel_freq_to_param(uint16_t accel_freq_hz);
    GYRO_CONFIG0_ODR_t gyro_freq_to_param(uint16_t gyro_freq_hz);
    ACCEL_CONFIG0_FS_SEL_t accel_fsr_g_to_param(uint16_t accel_fsr_g);
    GYRO_CONFIG0_FS_SEL_t gyro_fsr_dps_to_param(uint16_t gyro_fsr_dps);
};
*/
struct IMUData {  
    double ax, ay, az;  // Accelerometer data
    double gx, gy, gz;  // Gyroscope data
};

struct IMURegisters {
    int samplingRate;        // Sampling rate in Hz
    int accelerometerRange;  // Accelerometer measurement range in g
    int gyroscopeRange;      // Gyroscope measurement range in dps
};