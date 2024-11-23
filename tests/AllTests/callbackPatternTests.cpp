#include "CppUTest/TestHarness.h"

extern "C" {
#include "callBackPattern.h"
    // other references
}

TEST_GROUP(callbackPattern)
{
    void setup()
    {
        // Run before every test.
    }
    void teardown()
    {
        // Run after every test.
    }
};


TEST(callbackPattern, Init_Owner)
{
    
}

TEST(callbackPattern, Init_Receiver)
{

}

TEST(callbackPattern, Callback_Triggered)
{
    struct callbackOwner_t owner;
    hCallbackOwner hOwner = &owner;
    cbOwner_Init(hOwner);

    struct callBackReceiver_t receiver;
    hCallBackReceiver hRecevier = &receiver;
    cbRec_Init(hRecevier, hOwner);

    cbOwner_TriggerCB(hOwner);

    LONGS_EQUAL(1, hRecevier->callback_count);
}