#ifndef VIRTUAL_API_PATTERN_COMM1_H
#define VIRTUAL_API_PATTERN_COMM1_H

#include "virtualApiPattern.h"

/** @file virtualApiPattern_comm1.h
 *  @brief Specific implementation of the virtual API pattern for `comm1`.
 *
 *  This header defines the `comm1` communication object, an implementation of the
 *  virtual API pattern. The `comm1` object extends the `abstractComm` structure,
 *  providing additional functionality such as data buffering and operation counters.
 */

 /**
  * @brief Represents the `comm1` communication object.
  *
  * This structure extends the `abstractComm` base structure, adding fields specific to
  * the `comm1` implementation. It includes an internal buffer for storing data and counters
  * to track the number of write and read operations. The `api` field provides the virtual
  * API implementation for the `comm1` object.
  */
typedef struct
{
    abstractComm base;       /**< Base abstract communication object. */
    struct commVirtualApi* api; /**< Pointer to the virtual API instance for `comm1`. */
    uint32_t status;         /**< Additional status field specific to `comm1`. */
    uint32_t write_count;    /**< Counter for the number of write operations. */
    uint32_t read_count;     /**< Counter for the number of read operations. */
    uint8_t buffer[100];     /**< Internal buffer to store data. */
} comm1;

/**
 * @brief Initializes the `comm1` communication object.
 *
 * This function sets up the `comm1` object, associating it with its virtual API
 * functions for `write` and `read` operations. The function also initializes the
 * object's internal fields, such as counters and the buffer.
 *
 * @param me Pointer to the `comm1` communication object.
 */
void comm1_init(comm1* me);

#endif // VIRTUAL_API_PATTERN_COMM1_H
