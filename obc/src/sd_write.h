// Function declarations for accessing SD card.


#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "sdmmc_cmd.h"
#include "sdkconfig.h"
#include "buffer.h"

/**
 * @brief Mount and prepare the SD card and logfile for use.
 * 
 * @return int Non-zero on failure.
 */
int sd_init(int MISO, int MOSI, int CLK, int CS);

/**
 * Write to SD card over SPI
 */
int sd_write(buffer_entry_t *data); 