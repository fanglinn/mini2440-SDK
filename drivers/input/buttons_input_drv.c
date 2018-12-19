/**
*  File     :  buttons_input_drv.c
*
*  create   :    Oct 24, 2018
*   Note(s) :    buttons drv from input-subsystem
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

#include <linux/input.h>
#include <linux/device.h>    /* class_create() , ...  */

static  struct input_dev *buttons_dev;

static int major;

static struct class *buttonsdrv_class;
static struct class_device *buttonsdrv_class_dev;

struct pin_desc 
{
	int irq;
	char *name;
	unsigned int pin;
	unsigned int key_value;
};

static struct pin_desc pins[] = 
{
	{IRQ_EINT8   , "K1",  S3C2410_GPG0 , 0x01},
	{IRQ_EINT11  , "K2",  S3C2410_GPG3 , 0x02},
	{IRQ_EINT13  , "K3",  S3C2410_GPG5 , 0x03},
	{IRQ_EINT14  , "K4",  S3C2410_GPG6 , 0x04},
	{IRQ_EINT15  , "K5",  S3C2410_GPG7 , 0x05},
	{IRQ_EINT19  , "K6",  S3C2410_GPG11, 0x06}
};


static int buttons_drv_open(struct inode * inode, struct file * file)
{
	return 0;
}

static ssize_t buttons_drv_read(struct file * file, char __user * userbuf, size_t count, loff_t * off)
{
	return 0;
}

static struct file_operations buttons_drv_fops = 
{
	.owner      = THIS_MODULE,
	.open       = buttons_drv_open,
	.read       = buttons_drv_read
};

static int buttons_drv_init(void)
{
	major = register_chrdev(0, "buttons_drv", &buttons_drv_fops);

	buttonsdrv_class = class_create(NULL, "buttons_class");
	// /dev/buttons
	buttonsdrv_class_dev = class_device_create(buttonsdrv_class, NULL, MKDEV(major, 0), NULL, "buttons");

	
	
	buttons_dev = input_allocate_device();
	if (!buttons_dev)
		return -ENOMEM;

	buttons_dev->name = "buttons";
	//buttons_dev->evbit = EV_KEY;
	//buttons_dev->keybit = KEY_L;      // 'l'
	//buttons_dev->keybit = KEY_S;      // 's'
	//buttons_dev->keybit = KEY_ENTER;  // '\n'
	set_bit(EV_KEY, buttons_dev->evbit);
	set_bit(EV_REP, buttons_dev->evbit);

	set_bit(KEY_L, buttons_dev->keybit);
	set_bit(KEY_S, buttons_dev->keybit);
	set_bit(KEY_ENTER, buttons_dev->keybit);
	set_bit(KEY_LEFTSHIFT, buttons_dev->keybit);
	
	input_register_device(buttons_dev);

	
	return 0;
}

static void buttons_drv_exit(void)
{
	// free input-device
	input_unregister_device(buttons_dev);
	input_free_device(buttons_dev);

	// free class
	class_device_unregister(buttonsdrv_class_dev);	
	class_destroy(buttonsdrv_class);

	
	unregister_chrdev(major, "buttons_drv");
}


module_init(buttons_drv_init);
module_exit(buttons_drv_exit);
MODULE_LICENSE("GPL");

