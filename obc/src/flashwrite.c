// Functions for writing to the ESP's onboard storage
// Matt Rossouw (omeh-a)
// 08/22

#include "flashwrite.h"

static FILE *logfile;

int flashwrite_init(void) {
    // TODO: add code to mount SPIFS, open logfile
    return 0;
}


int flashwrite(compact_buffer_entry_t *data) {
    // Package data into a string
    uint64_t buf[4];
    buf[0] = data->thrust_accel;
    buf[1] = data->rtc_time << 32 | data->thermA << 16 | data->imu_gyro_x;
    buf[2] = data->imu_gyro_y << 48 | data->imu_gyro_z << 32 | data->imu_accel_x << 16 | data->imu_accel_y;
    buf[3] = data->imu_accel_z << 48 | 0x0;
    // This is maybe a very hacky way to do this, but it is midnight and I don't have better thoughts in me.

    return fprintf(logfile, "%s", (char *)&buf);
}