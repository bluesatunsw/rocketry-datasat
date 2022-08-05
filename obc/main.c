// Bluesat22 primary microcontroller Rocketry collab 10,000ft test flight

// #includes
#include <stdio.h>

// #defines


// structs / enums
enum error_t{

}

typedef struct {

} Sensor_data_t;


// forward definitions
int init_setup(void);
int low_power_mode(void);
int scan_sensors(void);
int monitor_check(void);
void check_err(void);
int write_sd_card(void);
int write_sensor_data(void);
int main_loop(void);
int end_procedure(void);

// global variables
Sensor_data_t data;

int main(void) {
    int err = 0;

    err = init_setup();
    check_err(err);

    err = init_calibration();
    check_err(err);

    err = low_power_mode();
    check_err(err);

    err = main_loop();
    check_err(err);

    err = end_procedure();
    check_err(err);

    return 0;
}

/*  @brief setup communication with and configure peripherals
 *  @return 
*/
int init_setup(void) {
    // TODO
}

/*  @brief wait in low power mode until device 
 *  @return 
*/
int low_power_mode(void) {
    // TODO
}

/*  @brief read data packets from all sensors
 *  @return 
*/
int scan_sensors(void) {
    // TODO
}

/*  @brief communicate with other microcontrollers on board to track functioning progress
 *  @return 
*/
int monitor_check(void) {
    // TODO
}

/*  @brief checks for errors and if detected minimises data lost
*/
void check_err(void) {
    // TODO
}

/*  @brief write to sensor data to sd card
 *  @return 
*/
int write_sensor_data(void) {
    // TODO
}

/*  @brief write to sd card
 *  @return 
*/
int write_sd_card(void) {
    // TODO
}

/*  @brief main loop of sensing, communicating and data logging
 *  @return 
*/
int main_loop(void) {
    // TODO
    while (1) {
        // scan sensors
        err = scan_sensors();

        // communicate with other microcontroller
        err = monitor_check();
        check_err();

        // write to SD card
        write_sd_card();
    }
}


/*  @brief make the microcontroller no longer write to the sd card if it is accidentally reset 
    before the card runs out. 
 *  @return 
*/
int end_procedure(void) {
    // TODO
}

