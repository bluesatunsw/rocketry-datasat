// Accelorometer and IMU functions
// Matt Rossouw (omeh-a)
// 08/22

#include "accel.h"

void launchWait(void) {
    // Wait until accelerometer registers launch
    while (1) {
        if (/*TODO*/) {
            break;
        }
    }
}

void accelRead(buffer_entry_t *entry) {
    entry->thust_accel = /*TODO*/;
}

void accelReadCompact(compact_buffer_entry_t *entry) {
    entry->thust_accel = /*TODO*/;
}