# include "virtualApiPattern.h" 
# include "virtualApiPattern_API.h"

#include <stddef.h>

void comm_init(hAbstractComm me, hCommVirtualApi api)
{
    if (!api || !(*api)) {
        me->status = -1; /* Error: Invalid arguments */
        me->handle = NULL;
        return;
    }
    me->status = 0; /* Reset status */
    me->handle = api; /* Assign the virtual API handle */
}

int comm_write(hAbstractComm me, const uint8_t* data, size_t size)
{
	hCommVirtualApi handle = me->handle;
    if(handle)
	    return (*handle)->write(handle, data, size);
    return -1;
}

int comm_read(hAbstractComm me, uint8_t* data, size_t size)
{
	hCommVirtualApi handle = me->handle;
    if(handle)
	    return (*handle)->read(handle, data, size);
    return -1;
}