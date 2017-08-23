#ifndef DEVICE_C
#define DEVICE_C

#include <stdint.h>

#define RET_OK          0
#define RET_ERR         -1

int32_t open_device(const char* device);
int32_t read_device(int32_t fd, uint8_t *data, int32_t length);
int32_t write_device(int32_t fd, uint8_t *data, int32_t length);
int32_t close_device(int32_t fd);

#endif
