//
// Created by citrate on 11/23/21.
//
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/export.h>
#include <linux/time64.h>
#include <linux/timekeeping.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/printk.h>
//TODO: Add necessary header files
#include "dice.h"

int dice_major;                /* Major number of dice devices */
int dice_devs = DICE_DEVS;     /* Number of dice devices */
int dice_num = DICE_NUM;       /* Initial number of dice in a device */
int gen_sides = GEN_SIDES;     /* Initial number of sides of `arbitrary` dice game */
struct dice_dev *dice_devices; /* An array of dice device */
struct class *dice_class;      /* Used for class */

static const char dice_name[]="GrandpaDice";

static int __init dice_init(void);
static void __exit dice_exit(void);
static int dice_open(struct inode *inode, struct file *filp);
static int dice_release(struct inode *inode, struct file *filp);
static ssize_t dice_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
static ssize_t dice_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);

MODULE_LICENSE("GPL");
module_init(dice_init);
module_exit(dice_exit);
//TODO: Make gen_sides a module parameter

static struct file_operations fops = {
        .read = dice_read,
        .write = dice_write,
        .open = dice_open,
        .release = dice_release,
};

static int __init dice_init(void) {
    dev_t dev;
    int i;

    
    printk("Grandpa, this is for you! Initialize process triggering...\n");

    dev = MKDEV(dice_major,0);//initialize the driver
    //TODO: Find Major number dynamically
    // Hint: alloc_chrdev_region
    if (alloc_chrdev_region(&dev,0,dice_devs,dice_name)<0){
        printk(KERN_WARNING "%s: fail to dynamically find major number for register",dice_name);
        return -1;
    }else{
        dice_major=MAJOR(dev);
    }
    //TODO: Allocate memory for dices


    //TODO: create a class, loop through registering cdev and creating device
    // Hint: class_create, cdev_init, cdev_add, device_create

    for (i = 0; i < dice_devs; ++i) {
        //TODO: Check whether it should be fixed to DICE_DEVS
        dev_t dev_add=MKDEV(dice_major,i);
        struct cdev* major_dev=&(dice_devices[i].dice_cdev);
        cdev_init(major_dev,&fops);
        (major_dev)->owner=THIS_MODULE;
        (major_dev)->ops=&fops;
        if(cdev_add(major_dev,dev_add,1)<0){
            printk(KERN_WARNING "%s: fail to allocate memory for three dices",dice_name);
            return -2;
        }else{
            continue;
        }
    }
    dice_devices[0].dice_type=REGULAR;
    dice_devices[1].dice_type=BACKGAMMON;
    dice_devices[2].dice_type=GENERIC;
    dice_devices[0].num=dice_num;
    dice_devices[1].num=dice_num;
    dice_devices[2].num=dice_num;
    printk(KERN_NOTICE "%s: Initialize succeed!",dice_name);
    return 0;
}

static void __exit dice_exit(void) {
    //TODO: release all resources
    // Hint: Pay attention to the order!
    // Hint: device_destroy, cdev_del, class_destroy, kfree, unregister_chrdev_region
}

static int dice_open(struct inode *inode, struct file *filp) {
    //TODO: Find which dice is opened
    // Hint: container_of, filp->private_data
    return 0;
}

static int dice_release(struct inode *inode, struct file *filp) {
    //Do nothing here
    //If you allocate any resource in dice_open(), then you must release them here
    return 0;
}

static ssize_t dice_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
    //TODO: Generate dice patterns, generate random number
    // Attention: handle count and offp carefully
    // Hint: copy_to_user
    return 0;
}
static ssize_t dice_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
    //TODO: Read in number of dice
    // Attention: handle count and offp carefully
    // Hint: copy_from_user
    return 0;
}
