#include "virtualApiPattern_comm1.h"

#include "common.h"
#include "virtualApiPattern_API.h"

#include <string.h>
#include <stdio.h>

/* Forward declarations of the virtual API functions */
static int comm1_write(hCommVirtualApi api, const uint8_t* data, size_t size);
static int comm1_read(hCommVirtualApi api, uint8_t* data, size_t size);

/* Virtual API instance for `comm1` */
static struct commVirtualApi comm1_api = {
    .write = comm1_write,
    .read = comm1_read,
};


/* Initializes the `comm1` object */
void comm1_init(comm1* me)
{
    me->api = &comm1_api;
    /* Initialize the base abstract communication object */
    comm_init(&me->base, (hCommVirtualApi)&me->api); 

    /* Set additional `comm1`-specific fields */
    me->status = 0; /* Reset status */
    me->write_count = 0;
    me->read_count = 0;
    memset(me->buffer, 0, sizeof(me->buffer));
}

static int comm1_write(hCommVirtualApi handle, const uint8_t* data, size_t size)
{
    /* Correctly calculate the `comm1` object using the dereferenced pointer */
    comm1* me = CONTAINER_OF(handle, comm1, api);

    if (data == NULL || size == 0) {
        return -1; /* Invalid arguments */
    }

    /* Simulate writing data */
    size_t to_copy = size < sizeof(me->buffer) ? size : sizeof(me->buffer);
    memcpy(me->buffer, data, to_copy);
    me->write_count++;

    return (int)to_copy;
}


/* Implementation of the `read` function for `comm1` */
static int comm1_read(hCommVirtualApi handle, uint8_t* data, size_t size)
{
    comm1* me = CONTAINER_OF(handle, comm1, api);
    if (data == NULL || size == 0) {
        return -1; /* Invalid arguments */
    }

    /* Simulate reading data by copying from `comm1`'s buffer */
    size_t to_copy = size < sizeof(me->buffer) ? size : sizeof(me->buffer);
    memcpy(data, me->buffer, to_copy);
    me->read_count++;

    return (int)to_copy; /* Return the number of bytes "read" */
}
