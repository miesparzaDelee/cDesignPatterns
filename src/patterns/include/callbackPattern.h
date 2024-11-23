#ifndef CALLBACK_PATTERN_H
#define CALLBACK_PATTERN_H

#include <stdint.h>

// Callback holder/triggerer (Object being observed)

struct callbackOwner_t
{
	uint32_t variable;
	uint32_t flags;
	struct ownerCallback* callback;
	// struct ownerCallback[MAX_CALLBACKS] callbacks;
};

typedef struct callbackOwner_t* hCallbackOwner;

struct ownerCallback
{
	void (*cb)(struct ownerCallback* cb);
};

void cbOwner_Init(hCallbackOwner me);

void cbOwner_AddCallback(hCallbackOwner me, struct ownerCallback * cb);

void cbOwner_RemoveCallback(hCallbackOwner me, struct ownerCallback* cb);

void cbOwner_TriggerCB(hCallbackOwner me);

// Callback receiver object (observer object)

struct callBackReceiver_t
{
	uint32_t flags;
	uint32_t callback_count;
	hCallbackOwner instance;
	struct ownerCallback callback;	
};

typedef struct callBackReceiver_t* hCallBackReceiver;

void cbRec_Init(hCallBackReceiver me, hCallbackOwner initializedInstance);

#endif // !CALLBACK_PATTERN_H
