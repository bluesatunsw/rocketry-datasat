// Function definitions for writing to ESP onboard storage
// Matt Rossouw (omeh-a)
// 08/22

#pragma once

#include "buffer.h"

/**
 * @brief Initialise the onboard storage.
 * 
 * @return int Non-zero on failure.
 */
int flashwrite_init(void);

/**
 * @brief Write to the onboard flash memory. Should only be used on SD card failure, and 
 * consequently only accepts compact buffer entries
 * 
 * @param entry Compact buffer entry. 
 * @return int Non-zero on failure.
 */
int flashwrite(compact_buffer_entry_t *data);