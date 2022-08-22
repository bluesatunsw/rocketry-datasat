// SD card write function
// Priyanta Islam, Matt Rossouw
// 22/08/12

#include "sd_write.h"

static const char *TAG = "datasat";

#define MOUNT_POINT "/sdcard"
#define SPI_DMA_CHAN  SPI_DMA_CH_AUTO

static FILE *logfile;

int sd_init(int MISO, int MOSI, int CLK, int CS) {
    esp_err_t ret;
    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_card_t *card;
    const char mount_point[] = MOUNT_POINT;
    
    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = MOSI,
        .miso_io_num = MISO,
        .sclk_io_num = CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ret = spi_bus_initialize(host.slot, &bus_cfg, SPI_DMA_CHAN);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize bus.");
        return 1;
    }

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = CS;
    slot_config.host_id = host.slot;

    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    //Check for error
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. ");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). ", esp_err_to_name(ret));
        }
        return 1;
    }

    // Card has been initialized, print its properties
    //sdmmc_card_print_info(stdout, card);

    // create a file.
    logfile = fopen(MOUNT_POINT"/hello.txt", "a+");
    if (logfile == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return 1;
    }


}


/**
 * Write to SD card over SPI
 * Takes MISO, MOSI, CLK and CS signals as params
 */
int sd_write(buffer_entry_t *data) {
    // Package data into a string
    uint64_t buf[6];
    buf[0] = data->thrust_accel;
    buf[1] = data->thermA << 48 | data->thermB << 32 | data->thermC << 16 | data->thermD;
    buf[3] = data->rtc_time << 32 | data->imu_gyro_x << 16 | data->imu_gyro_y;
    buf[4] = data->imu_gyro_z << 48 | data->imu_accel_x << 32 | data->imu_accel_y << 16 | data->imu_accel_z;
    buf[5] = data->imu_mag_x << 48 | data->imu_mag_y << 32 | data->imu_mag_z << 16 | 0x0;
    
    // This is maybe a very hacky way to do this, but it is midnight and I don't have better thoughts in me.

    return fprintf(logfile, "%s", (char *)&buf);
}

