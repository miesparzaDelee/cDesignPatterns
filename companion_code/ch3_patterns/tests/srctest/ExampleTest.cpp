#include "CppUTest/TestHarness.h"

extern "C" {
/*
 * You can add your c-only include files here
 */
}

TEST_GROUP(MyModule){ 
    void setup(){
        // add init 
    }

    void teardown(){
        // add deinit
    } 
};

TEST(MyModule, test1)
{
    /*
     * Instantiate you class or call the function you want to test
     */
}
