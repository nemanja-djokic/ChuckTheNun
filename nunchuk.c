/* INCLUDES */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>

#include "nunchuk.h"

/* DEFINES */
#define RET_SUCCESS             0
#define RET_ERR                 -1
#define DEVICE_NAME             "nunchuk"
#define NUNCHUK_I2C_ADDRESS     0x52
#define NUNCHUK_I2C_BUS         1

/* PROTOTYPES */
static int init_nunchuk_module(void);
static void deinit_nunchuk_module(void);

static ssize_t nunchuk_read(struct file *, char *, size_t, loff_t *);
static int nunchuk_open(struct inode *, struct file *);
static int nunchuk_release(struct inode *, struct file *);

/* GLOBALS */
static int major_number;
static int opened;
static struct i2c_client* nunchuk_client;

static struct file_operations fops = {
    .read = nunchuk_read,
    .open = nunchuk_open,
    .release = nunchuk_release,
};

static int nunchuk_handshake(void)
{
    unsigned char first_pair[] = { 0xF0, 0x55};
    unsigned char second_pair[] = { 0xFB, 0x00};

    i2c_master_send(nunchuk_client, first_pair, sizeof(first_pair));
    udelay(1);
    i2c_master_send(nunchuk_client, second_pair, sizeof(second_pair));
    
    return RET_SUCCESS;
}

static int nunchuk_read_registers(struct i2c_client *client, u8 *buf,
								  int buf_size)
{
	unsigned char buff_to_send[] = { 0x00 };
	i2c_master_send(nunchuk_client, buff_to_send, 1);
	mdelay(10);
	i2c_master_recv(nunchuk_client, buf, buf_size);
	return RET_SUCCESS;
}


/* FUNCTIONS */
static int init_nunchuk_module(void)
{
    struct i2c_adapter* bus_adapter;
    
    major_number = register_chrdev(0, DEVICE_NAME, &fops);

    if (major_number < 0)
    {
      printk(KERN_ALERT "Registering char device failed with %d\n", 
            major_number);
      
      return major_number;
    }
    
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major_number);
     
    bus_adapter = i2c_get_adapter(NUNCHUK_I2C_BUS);
    
    if (bus_adapter == NULL)
    {
        return -ENODEV;
    }
    
    nunchuk_client = i2c_new_dummy(bus_adapter, NUNCHUK_I2C_ADDRESS);
    
    if (nunchuk_client == NULL)
    {
        return -ENODEV;
    }
    
    if (nunchuk_handshake() == RET_ERR)
    {
        return RET_ERR;
    }

    return RET_SUCCESS;
}

static void deinit_nunchuk_module(void)
{
    i2c_unregister_device(nunchuk_client);
    
    unregister_chrdev(major_number, DEVICE_NAME);
}

static int nunchuk_open(struct inode *inode, struct file *file)
{
    if (opened)
    {
        return -EBUSY;
    }

    opened++;
    
    try_module_get(THIS_MODULE);

    return RET_SUCCESS;
}

static int nunchuk_release(struct inode *inode, struct file *file)
{
    opened--;

    module_put(THIS_MODULE);

    return RET_SUCCESS;
}

static ssize_t nunchuk_read(struct file *filp, char *buffer, size_t length, 
                           loff_t * offset)
{
	unsigned char read_buffer[6];
	if(nunchuk_read_registers(nunchuk_client, read_buffer, 6) == RET_SUCCESS){
		int i = 0;
		unsigned char modified_buffer[4];
		modified_buffer[0] = read_buffer[0];
		modified_buffer[1] = read_buffer[1];
		modified_buffer[2] = (read_buffer[5] & 0x2);
		modified_buffer[3] = (read_buffer[5] & 0x1);
		for(i = 0; i<4; i++){
			put_user(modified_buffer[i], buffer+i);
			printk("put %c in buffer", read_buffer[i]);
		}
		return 4;
	}else{
		return 0;
	}
}

module_init(init_nunchuk_module);
module_exit(deinit_nunchuk_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nemanja Djokic <djokic_nemanja@hotmail.com>");
MODULE_DESCRIPTION("This is a simple nunchuk controller driver.");
