# include "virtualApiPattern.h" 
# include "virtualApiPattern_API.h"

#include <stddef.h>

void comm_init(hAbstractComm me, hCommVirtualApi api)
{
    if (!api || !(*api)) {
        me->status = -1; /* Error: Invalid arguments */
        me->api = NULL;
        return;
    }
    me->status = 0; /* Reset status */
    me->api = api; /* Assign the virtual API handle */
}

int comm_write(hAbstractComm me, const uint8_t* data, size_t size)
{
	hCommVirtualApi api = me->api;
    if(api)
	    return (*api)->write(api, data, size);
    return -1;
}

int comm_read(hAbstractComm me, uint8_t* data, size_t size)
{
	hCommVirtualApi api = me->api;
    if(api)
	    return (*api)->read(api, data, size);
    return -1;
}