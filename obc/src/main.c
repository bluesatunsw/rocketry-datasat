// Bluesat22 primary microcontroller Rocketry collab 10,000ft test flight
// Matt Rossouw (omeh-a) Priyanta Islam ()
// 08/22

#include "main.h"

// Buffers stored as byte fields to avoid heap operations. This may or may not work.
static char sd_buffer[BUFFER_SIZE * sizeof(buffer_entry_t)];
static char flash_buffer[BUFFER_SIZE * sizeof(buffer_entry_t)];

unsigned int buffer_index = 0;
unsigned int failure_buffer_index = 0;

int main(char *argv[], int argc) {
    
    // Initialise buffers - set each entry to 0
    for (int i = 0; i < BUFFER_SIZE * sizeof(buffer_entry_t); i++) {
        sd_buffer[i] = 0;
    }
    for (int i = 0; i < BUFFER_SIZE * sizeof(compact_buffer_entry_t); i++) {
        flash_buffer[i] = 0;
    }

    // Perform device initialisation
    deviceInit();

    // Initialise onboard flash
    flashwrite_init();

    // Initialise SD card
    sdcard_init();
    
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
        buffer_entry_t *entry = (buffer_entry_t*)&sd_buffer[buffer_index * sizeof(buffer_entry_t)];        

        // Read RTC
        //TODO
        
        // Read accelerometer
        accelRead(entry);

        // Read IMU

        // Read analog inputs
        //TODO


        // write to SD card
        int err = writeSD();
        if (err) goto sd_fatal;
    }

    return;

sd_fatal:
    // If the SD card is misbehaving, immediately terminate communication to
    // protect stored data. Poll sensors at a much slower rate and utilise backup
    // storage onboard ESP
    
    // Don't touch the previously bufferred data.
    while (1) {
        // TODO: wait for 1 second using ESP32 RTOS

        // Get pointer to buffer entry
        compact_buffer_entry_t *entry = (compact_buffer_entry_t*)&flash_buffer[failure_buffer_index * sizeof(compact_buffer_entry_t)];

        // Read RTC
        //TODO

        // Read accelerometer
        compact_accelRead(entry);

        // Read IMU
        //TODO

        // Commit to flash
        flashwrite(entry);
        
    }
    

    return;
}

void deviceInit() {

}