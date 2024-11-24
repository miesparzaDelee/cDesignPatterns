#ifndef VIRTUAL_API_PATTERN_H
#define VIRTUAL_API_PATTERN_H

#include <stdint.h>

/** @file virtualApiPattern.h
 *  @brief Defines an abstract communication interface using a virtual API pattern.
 *
 *  This header provides an abstraction layer for communication interfaces.
 *  The `abstractComm` structure serves as a wrapper for a virtual API, allowing
 *  polymorphic access to communication operations such as `write` and `read`.
 */

 /**
  * @brief Represents a handle to a virtual API instance.
  *
  * The `hCommVirtualApi` handle is a double pointer to a `commVirtualApi` structure,
  * which defines the virtual API functions.
  */
struct commVirtualApi;
typedef struct commVirtualApi** hCommVirtualApi;

/**
 * @brief Abstract communication object.
 *
 * The `abstractComm` structure provides a wrapper for the virtual API handle.
 * It includes a status field to monitor the state of the communication object.
 */
typedef struct
{
    uint8_t status;               /**< Status of the communication object. */
    hCommVirtualApi handle;       /**< Handle to the virtual API instance. */
} abstractComm;

typedef abstractComm* hAbstractComm;

/**
 * @brief Initializes the abstract communication object.
 *
 * Sets the virtual API handle for the communication object and initializes its status.
 *
 * @param me Pointer to the abstract communication object.
 * @param api Handle to the virtual API instance.
 */
void comm_init(hAbstractComm me, hCommVirtualApi api);

/**
 * @brief Writes data using the virtual API.
 *
 * Delegates the write operation to the virtual API's `write` function.
 *
 * @param me Pointer to the abstract communication object.
 * @param data Pointer to the data buffer to write.
 * @param size Number of bytes to write.
 * @return Number of bytes written, or -1 if the operation fails.
 */
int comm_write(hAbstractComm me, const uint8_t* data, size_t size);

/**
 * @brief Reads data using the virtual API.
 *
 * Delegates the read operation to the virtual API's `read` function.
 *
 * @param me Pointer to the abstract communication object.
 * @param data Pointer to the buffer to store read data.
 * @param size Maximum number of bytes to read.
 * @return Number of bytes read, or -1 if the operation fails.
 */
int comm_read(hAbstractComm me, uint8_t* data, size_t size);

#endif // VIRTUAL_API_PATTERN_H
