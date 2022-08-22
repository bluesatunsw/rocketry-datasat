// Function definitions for main
// Matt Rossouw (omeh-a)
// 08/22
#pragma once
#include "buffer.h"
#include "pins.h"
#include "accel.h"
#include "sd_write.h"
#include "flashwrite.h"

// ESP includes
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include <stdio.h>

int main(char *argv[], int argc);

int mainLoop(id);