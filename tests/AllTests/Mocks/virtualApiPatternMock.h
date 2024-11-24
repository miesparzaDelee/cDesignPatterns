#ifndef VIRTUAL_API_PATTERN_MOCK_H
#define VIRTUAL_API_PATTERN_MOCK_H

 #include "virtualApiPattern_API.h"

/* Mock implementation for the write function */
int mock_write(const struct commVirtualApi** handle, const uint8_t* data, size_t size);

/* Mock implementation for the read function */
int mock_read(const struct commVirtualApi** handle, uint8_t* data, size_t size);

#endif // VIRTUAL_API_PATTERN_MOCK_H
