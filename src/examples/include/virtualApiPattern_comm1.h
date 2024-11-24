#ifndef VIRTUAL_API_PATTERN_COMM1_H
#define VIRTUAL_API_PATTERN_COMM1_H

#include "virtualApiPattern.h"

/** @file virtualApiPattern_comm1.h
 *  @brief Specific implementation of the virtual API pattern for `comm1`.
 */

 /**
  * @brief Represents the `comm1` communication object.
  *
  * This structure extends the `abstractComm` structure and includes additional
  * fields specific to the `comm1` implementation, such as a buffer and counters.
  */
typedef struct
{
    abstractComm base;       /**< Base abstract communication object. */
    struct commVirtualApi* api;
    uint32_t status;         /**< Additional status field specific to `comm1`. */
    uint32_t write_count;    /**< Counter for the number of write operations. */
    uint32_t read_count;     /**< Counter for the number of read operations. */
    uint8_t buffer[100];     /**< Internal buffer to store data. */
} comm1;

/**
 * @brief Initializes the `comm1` communication object.
 *
 * Sets up the `comm1` object and registers its virtual API functions.
 *
 * @param me Pointer to the `comm1` communication object.
 */
void comm1_init(comm1* me);

#endif // VIRTUAL_API_PATTERN_COMM1_H
