/* SD card and FAT filesystem example.
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "sdwrite.h"
#include <stdio.h>
#include <string.h>

extern "C" {
  void app_main();
}

// SPI Pin Mapping
#define PIN_NUM_MISO 6
#define PIN_NUM_MOSI 4
#define PIN_NUM_CLK  5
#define PIN_NUM_CS   1

void app_main(void)
{
    int err = sd_write(PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);

    if(err) {
        ESP_LOGI("datasat", "Error!");
    } else {
        ESP_LOGI("datasat", "Success!");
    }
}
