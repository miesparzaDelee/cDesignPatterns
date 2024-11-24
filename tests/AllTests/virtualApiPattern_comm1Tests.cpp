#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {
    #include "virtualApiPattern_comm1.h"
}

TEST_GROUP(VirtualApiPattern_Comm1)
{
    comm1 myComm;

    void setup()
    {
        /* Initialize the comm1 object */
        comm1_init(&myComm);
    }

    void teardown()
    {
        /* Clear mock expectations */
        mock().clear();
    }
};

TEST(VirtualApiPattern_Comm1, Init)
{
    /* Verify initialization */
    CHECK_EQUAL(0, myComm.status);
    CHECK_EQUAL(0, myComm.write_count);
    CHECK_EQUAL(0, myComm.read_count);
}

TEST(VirtualApiPattern_Comm1, Write)
{
    /* Test data */
    const uint8_t write_data[] = "Hello, comm1!";
    size_t write_size = sizeof(write_data);

    /* Perform write */
    int result = comm_write(&myComm.base, write_data, write_size);

    /* Validate results */
    CHECK_EQUAL(write_size, result);
    CHECK_EQUAL(1, myComm.write_count);
    STRCMP_EQUAL((const char*)write_data, (const char*)myComm.buffer);
}

TEST(VirtualApiPattern_Comm1, Read)
{
    /* Simulate a prior write operation */
    const char* test_message = "Test read buffer";
    memcpy(myComm.buffer, test_message, strlen(test_message) + 1);

    /* Buffer to store the read data */
    uint8_t read_data[50];
    memset(read_data, 0, sizeof(read_data));

    /* Perform read */
    int result = comm_read(&myComm.base, read_data, strlen(test_message));

    /* Validate results */
    CHECK_EQUAL(strlen(test_message), result);
    CHECK_EQUAL(1, myComm.read_count);
    STRCMP_EQUAL(test_message, (const char*)read_data);
}

TEST(VirtualApiPattern_Comm1, WriteInvalidData)
{
    /* Test with NULL data */
    int result = comm_write(&myComm.base, NULL, 10);
    CHECK_EQUAL(-1, result);
    CHECK_EQUAL(0, myComm.write_count);
}

TEST(VirtualApiPattern_Comm1, ReadInvalidBuffer)
{
    /* Test with NULL buffer */
    int result = comm_read(&myComm.base, NULL, 10);
    CHECK_EQUAL(-1, result);
    CHECK_EQUAL(0, myComm.read_count);
}

