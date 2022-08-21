// Accelorometer and IMU function defintions
// Matt Rossouw (omeh-a)
// 08/22
#pragma once

#include "buffer.h"
#define LAUNCH_ACCELERATION_THRESHOLD 2

/**
 * @brief Halt until launch begins.
 * 
 */
void launchWait(void);

/**
 * @brief Read from the accelorometer over SPI and store
 *        the data in the buffer.
 * 
 * @param entry Buffer entry
 */
void accelRead(buffer_entry_t *entry);

/**
 * @brief Same as accelRead, but for the compact buffer.
 * 
 * @param entry 
 */
void accelReadCompact(compact_buffer_entry_t *entry);

/**
 * @brief Read from the IMU over i2c
 * 
 * @param entry 
 */
void imuRead(buffer_entry_t *entry);

/**
 * @brief Same as imuRead, but for the compact buffer.
 * 
 * @param entry 
 */
void imuReadCompact(compact_buffer_entry_t *entry);