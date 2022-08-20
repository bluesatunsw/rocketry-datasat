// Bluesat22 primary microcontroller Rocketry collab 10,000ft test flight
// Matt Rossouw (omeh-a) Priyanta Islam ()
// 08/22

#include <stdio.h>
#include "main.h"
#include "buffer.h"
#include "pins.h"
#include "accel.h"

static char buffer[BUFFER_SIZE * sizeof(buffer_entry_t)]
static char failure_buffer[10*BUFFER_SIZE * sizeof(buffer_entry_t)]

unsigned int buffer_index = 0;
unsigned int failure_buffer_index = 0;

int main(char *argv[], int argc) {
    
    // Initialise buffers
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = (buffer_entry_t)0x0;
    }
    for (int i = 0; i < 10*BUFFER_SIZE; i++) {
        failure_buffer[i] = (buffer_entry_t)0x0;
    }

    // Perform device initialisation
    deviceInit();

    // Wait until accelerometer registers launch
    launchWait();

    // Start data collection
    mainLoop();

    return 0;
}

/*  @brief main loop of sensing, communicating and data logging
 *  @return 
*/
void mainLoop(void) {
    while (1) {
        

        // write to SD card
        int err = writeSD();
        if (err) goto sd_fatal;
    }

    return;

sd_fatal:
    // If the SD card is misbehaving, immediately terminate communication to
    // protect stored data. Poll sensors at a much slower rate and utilise backup
    // memory buffer to store data.
    
    // Don't touch the previously bufferred data.
    while (1) {
        // TODO: wait for 1 second using ESP32 RTOS

        // 
    }
    

    return;
}

void deviceInit() {

}