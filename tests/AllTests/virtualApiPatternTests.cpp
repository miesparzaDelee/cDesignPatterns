#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {
#include "virtualApiPattern.h"
#include "virtualApiPattern_API.h"
}

#include "virtualApiPatternMock.h"

TEST_GROUP(VirtualApiPattern)
{
    struct commVirtualApi api;       /* Virtual API instance */
    struct commVirtualApi* apiPtr;  /* Pointer to the virtual API instance */
    struct commVirtualApi** apiHandle; /* Double-pointer handle */
    abstractComm comm;              /* Abstract communication object */

    uint8_t buffer[10];             /* Buffer for testing */

    void setup() {
        /* Initialize the virtual API with mock functions */
        api.write = mock_write;
        api.read = mock_read;

        /* Set up pointers */
        apiPtr = &api;
        apiHandle = &apiPtr;

        /* Initialize the abstract communication object */
        comm_init(&comm, apiHandle);
    }

    void teardown() {
        mock().clear();
    }
};

TEST(VirtualApiPattern, InitWithValidApi)
{
    /* Validate that the handle and status are set correctly */
    CHECK(comm.handle == apiHandle);
    CHECK_EQUAL(0, comm.status);
}

TEST(VirtualApiPattern, InitWithNullApi)
{
    /* Initialize with NULL API */
    comm_init(&comm, NULL);

    /* Validate that the status indicates an error */
    CHECK_EQUAL(255, comm.status);
    CHECK(comm.handle == NULL);
}

TEST(VirtualApiPattern, WriteDelegatesToVirtualApi)
{
    /* Mock expectation */
    mock().expectOneCall("write")
        .withPointerParameter("handle", apiHandle) // Explicit pointer comparison
        .withPointerParameter("data", buffer) // Explicit pointer comparison
        .withParameter("size", sizeof(buffer))
        .andReturnValue(5); /* Mock return value */

  /* Call comm_write */
    int result = comm_write(&comm, buffer, sizeof(buffer));

    /* Verify result */
    CHECK_EQUAL(5, result);

    /* Validate expectations */
    mock().checkExpectations();
}

TEST(VirtualApiPattern, ReadDelegatesToVirtualApi)
{
    mock().expectOneCall("read")
        .withPointerParameter("handle", apiHandle) // Explicit pointer comparison
        .withPointerParameter("data", buffer) // Explicit pointer comparison
        .withParameter("size", sizeof(buffer))
        .andReturnValue(7); /* Mock return value */

    int result = comm_read(&comm, buffer, sizeof(buffer));
    CHECK_EQUAL(7, result);
    mock().checkExpectations();
}

TEST(VirtualApiPattern, WriteFailsForUninitializedHandle)
{
    /* Simulate an uninitialized comm object */
    abstractComm uninitializedComm;
    uninitializedComm.handle = NULL;
    uninitializedComm.status = 0;

    int result = comm_write(&uninitializedComm, buffer, sizeof(buffer));
    CHECK_EQUAL(-1, result);
}

TEST(VirtualApiPattern, ReadFailsForUninitializedHandle)
{
    /* Simulate an uninitialized comm object */
    abstractComm uninitializedComm;
    uninitializedComm.handle = NULL;
    uninitializedComm.status = 0;

    int result = comm_read(&uninitializedComm, buffer, sizeof(buffer));
    CHECK_EQUAL(-1, result);
}
