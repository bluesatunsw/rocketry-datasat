// In-memory representation of all data pushed to SD card
#pragma once

#define BUFFER_ENTRIES 100

typedef struct {
    // Primary accelerometer readings
    uint64_t thrust_accel;
    
    // Analog reads
    uint16_t thermA;
    uint16_t thermB;
    uint16_t thermC;
    uint16_t thermD;
    uint16_t baro;
    
    // RTC
    uint32_t rtc_time;

    // IMU readings
    uint16_t imu_gyro_x;    // Gyroscope measurements
    uint16_t imu_gyro_y;
    uint16_t imu_gyro_z;
    uint16_t imu_accel_x;   // Accelerometer measurements
    uint16_t imu_accel_y;
    uint16_t imu_accel_z;
    uint16_t imu_mag_x;     // Magnetometer measurements
    uint16_t imu_mag_y;
    uint16_t imu_mag_z;

} buffer_entry_t;

// Compacted struct to save memory, in case SD card fails.
typedef struct {
    // Primary accelerometer readings
    uint64_t thrust_accel;
    
    // RTC
    uint32_t rtc_time;
    
    // Analog reads
    uint16_t thermA;

    // IMU readings
    uint16_t imu_gyro_x;    // Gyroscope measurements
    uint16_t imu_gyro_y;
    uint16_t imu_gyro_z;
    uint16_t imu_accel_x;   // Accelerometer measurements
    uint16_t imu_accel_y;
    uint16_t imu_accel_z;
} compact_buffer_entry_t;