#include <stdint.h>
#include <stdio.h>
#include "device.h"
#include "../kmod/chardev.h"

#define ARRAY_SIZE(array)   (sizeof(array)/sizeof(array[0]))

#define CHAR_DEVICE     "/dev/nunchuk"

static uint8_t buffer[4];

void dump_bytes(uint8_t* array, size_t length)
{
    size_t i = 0;
    
    for(; i < length; i++)
    {
        printf("%c ", array[i]); 
    }
    
    printf("\n");
}


int32_t main(void)
{
    int32_t fd = open_device(CHAR_DEVICE);
    
    if (fd == RET_ERR)
    {
        return RET_ERR;
    }
    
    if (read_device(fd, buffer, 4) == RET_ERR)
    {
        return RET_ERR;
    }

    while(1){
		printf("x axis value: %d\n", buffer[0]);
    printf("y axis value: %d\n", buffer[1]);
    if(buffer[2]){
		printf("c pressed\n");
	}else{
		printf("c not pressed\n");
	}
    if(buffer[3]){
		printf("z pressed\n");
	}else{
		printf("z not pressed\n");
	}
    
    if (close_device(fd) == RET_ERR)
    {
        return RET_ERR;
    }
	}
    
    return RET_OK;
}
