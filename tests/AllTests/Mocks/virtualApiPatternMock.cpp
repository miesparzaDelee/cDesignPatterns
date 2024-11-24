#include "virtualApiPatternMock.h"
#include "CppUTestExt/MockSupport.h"

/* Mock implementation of the write function */
int mock_write(const struct commVirtualApi** handle, const uint8_t* data, size_t size) {
    mock().actualCall("write")
        .withPointerParameter("handle", (void*)handle) // Use pointer parameter for handle
        .withPointerParameter("data", (void*)data) // Use pointer parameter for data
        .withParameter("size", size);
    return mock().returnIntValueOrDefault(0);
}

/* Mock implementation of the read function */
int mock_read(const struct commVirtualApi** handle, uint8_t* data, size_t size) {
    mock().actualCall("read")
        .withPointerParameter("handle", (void*)handle) // Use pointer parameter for handle
        .withPointerParameter("data", (void*)data) // Use pointer parameter for data
        .withParameter("size", size);
    return mock().returnIntValueOrDefault(0);
}
