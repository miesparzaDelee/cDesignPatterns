#include "callbackPattern.h"

#include <string.h>
#include "common.h"

#define CB_HOLDER_INIT_FLAG 0x1

void cbOwner_Init(hCallbackOwner me)
{
	memset(me, 0, sizeof(*me));
	me->flags |= CB_HOLDER_INIT_FLAG;
}

void cbOwner_AddCallback(hCallbackOwner me, struct ownerCallback* cb)
{
	me->callback = cb;
}

void cbOwner_RemoveCallback(hCallbackOwner me, struct ownerCallback* cb)
{
	me->callback = NULL;
}

void cbOwner_TriggerCB(hCallbackOwner me)
{
	if (me->callback)
	{
		me->callback->cb(me->callback);
	}
}

// CB Receiver code
#define CB_RECEIVER_INIT_FLAG 0x1

static void CbReceiver_onHoldersEvent(struct ownerCallback * cb)
{
	 hCallBackReceiver me = CONTAINER_OF(cb, struct callBackReceiver_t, callback);
	 me->callback_count++;
}

void cbRec_Init(hCallBackReceiver me, hCallbackOwner initializedInstance)
{
	memset(me, 0, sizeof(*me));
	me->flags |= CB_RECEIVER_INIT_FLAG;
	me->instance = initializedInstance;
	me->callback.cb = CbReceiver_onHoldersEvent;
	cbOwner_AddCallback(initializedInstance, &me->callback);
}