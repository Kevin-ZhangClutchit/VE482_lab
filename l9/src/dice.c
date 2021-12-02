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
#include <linux/device.h>
//TODO: Add necessary header files
#include "dice.h"

int dice_major;                /* Major number of dice devices */
int dice_devs = DICE_DEVS;     /* Number of dice devices */
int dice_num = DICE_NUM;       /* Initial number of dice in a device */
int gen_sides = GEN_SIDES;     /* Initial number of sides of `arbitrary` dice game */
struct dice_dev *dice_devices; /* An array of dice device */
struct class *dice_class;      /* Used for class */

static const char dice_name[]="dicedevice";

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
module_param(gen_sides, int, 0);

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
    printk("%s: Find major number dynamically ....",dice_name);
    if (alloc_chrdev_region(&dev,0,dice_devs,dice_name)<0){
        printk(KERN_WARNING "%s: fail to dynamically find major number for register",dice_name);
        return -1;
    }else{
        dice_major=MAJOR(dev);
    }
    //return 0;
    //TODO: Allocate memory for dices
    printk("%s: Allocate memory ....",dice_name);
    dice_devices=kmalloc(dice_devs * sizeof(struct dice_dev), GFP_KERNEL);

    if (dice_devices==NULL){
        printk(KERN_WARNING "%s: fail to allocate memory for devices",dice_name);
        return -3;
    }
    //TODO: create a class, loop through registering cdev and creating device
    // Hint: class_create, cdev_init, cdev_add, device_create
    printk("%s: Create class ...",dice_name);
    dice_class=class_create(THIS_MODULE,"dice_class");
    printk("%s: Create devices ...",dice_name);
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
        }
        device_create(dice_class, NULL, dev_add, NULL, "dice_dev%d",i);
    }
    printk("%s: After for loop ....",dice_name);
    dice_devices[0].dice_type=REGULAR;
    printk("%s: Huo ....",dice_name);
    dice_devices[1].dice_type=BACKGAMMON;
    dice_devices[2].dice_type=GENERIC;
    dice_devices[0].num=dice_num;
    dice_devices[1].num=dice_num;
    dice_devices[2].num=dice_num;
    printk("%s: Initialize succeed!",dice_name);
    printk("Yeah Tiger!\n");
    return 0;
}

static void __exit dice_exit(void) {
    //TODO: release all resources
    // Hint: Pay attention to the order!
    // Hint: device_destroy, cdev_del, class_destroy, kfree, unregister_chrdev_region
    int i;
    dev_t dev;
    dev = MKDEV(dice_major,0);

    printk("%s: Exit Process ...",dice_name);
    printk("%s: Delete devices ...",dice_name);
    for (i = 0; i < dice_devs; ++i) {
        device_destroy(dice_class,MKDEV(dice_major,i));
        cdev_del(&(dice_devices[i].dice_cdev));
    }
    printk("%s: Delete class ...",dice_name);
    class_destroy(dice_class);
    dice_class=NULL;
    printk("%s: Free allocating memory ...",dice_name);
    kfree(dice_devices);

    printk("%s: Unregister the device ...",dice_name);

    unregister_chrdev_region(dev,dice_devs);
    printk("%s: Exit succeeds!",dice_name);
    printk("Gubbai! Kimi no unmei no hito was not me!\n");
}

static int dice_open(struct inode *inode, struct file *filp) {
    //TODO: Find which dice is opened
    // Hint: container_of, filp->private_data
    struct dice_dev *dev = container_of(inode->i_cdev, struct dice_dev, dice_cdev);
    filp->private_data = dev;
    printk("number of dice: %d, type of dice game: %d\n", ((struct dice_dev *)filp->private_data)->num, ((struct dice_dev *)filp->private_data)->dice_type);
    return 0;
}

static int dice_release(struct inode *inode, struct file *filp) {
    //Do nothing here
    //If you allocate any resource in dice_open(), then you must release them here
    printk("Release dice!\n");
    return 0;
}

static ssize_t dice_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
    //TODO: Generate dice patterns, generate random number
    // Attention: handle count and offp carefully
    // Hint: copy_to_user
    struct dice_dev *dev = (struct dice_dev *)filp->private_data;
    int dice_type = dev->dice_type;
    int str_len = 0;
#define MAX_STR 15
#define MAX_TOTAL_STR 10000
    char *str = kmalloc(MAX_TOTAL_STR * sizeof(char), GFP_KERNEL);

    unsigned int rd[100]; // TODO: dynamically adjust the size
    int i;
    int offset = 0;
    dice_num = dev->num;

    printk(KERN_NOTICE "Dice: outputing data\n");

    if (*offp == 0){ // without this, random number will be generated multiple times
    if (dice_type == REGULAR){
        // regular
        static const char DICE_PATTERN[3][6][10] = {
                {"|     |","|     |","|  o  |","| o o |","| o o |","| o o |"},
                {"|  o  |","| o o |","|     |","|     |","|  o  |","| o o |"},
                {"|     |","|     |","| o o |","| o o |","| o o |","| o o |"}
        };
        printk(KERN_NOTICE "Dice: regular dice");
        for(i = 0; i < dice_num; ++i){
            get_random_bytes(&rd[i], sizeof(unsigned int));
            rd[i] = rd[i] % 6; // 0~5
            printk("%u\n",rd[i]);
        }
        printk("Start print!\n");
//        printk("Start 1st!\n");
        for(i = 0; i < dice_num; i++) offset += snprintf(str+offset,MAX_STR,"-------  ");
        offset += snprintf(str+offset,MAX_STR,"\n");
//        printk("Start 2nd!\n");
        for(i = 0; i < dice_num; i++) offset += snprintf(str+offset,MAX_STR,"%s  ",DICE_PATTERN[0][rd[i]]);
        offset += snprintf(str+offset,MAX_STR,"\n");
//        printk("Start 3rd!\n");
        for(i = 0; i < dice_num; i++) offset += snprintf(str+offset,MAX_STR,"%s  ",DICE_PATTERN[1][rd[i]]);
        offset += snprintf(str+offset,MAX_STR,"\n");
//        printk("Start 4th!\n");
        for(i = 0; i < dice_num; i++) offset += snprintf(str+offset,MAX_STR,"%s  ",DICE_PATTERN[2][rd[i]]);
        offset += snprintf(str+offset,MAX_STR,"\n");
//        printk("Start 5th!\n");
        for(i = 0; i < dice_num; i++) offset += snprintf(str+offset,MAX_STR,"-------  ");
        offset += snprintf(str+offset,MAX_STR,"\n");
    } else if (dice_type == BACKGAMMON) {
        // backgammon
        static const char DICE_BACKGAMMON[6][4] = { "2","4","8","16","32","64" };
        printk(KERN_NOTICE "Dice: backgammon~");
        for(i = 0; i < dice_num; i++){
            get_random_bytes(&rd[i], sizeof(unsigned int));
            rd[i] = rd[i] % 6; // 0~5
            printk("%u\n",rd[i]);
        }

        for(i = 0; i < dice_num; i++) offset += snprintf(str+offset,MAX_STR,"%s ",DICE_BACKGAMMON[rd[i]]);
        offset += snprintf(str+offset,MAX_STR,"\n");
    } else if (dice_type == GENERIC) {
        // arbitrary number of sides
        printk(KERN_NOTICE "Dice: generic, from 1 to %d\n", gen_sides);
        for(i = 0; i < dice_num; i++){
            get_random_bytes(&rd[i], sizeof(unsigned int));
            rd[i] = rd[i] % gen_sides; // 0~gen_sides-1
            printk("%u\n",rd[i]);
        }

        for(i = 0; i < dice_num; i++) offset += snprintf(str+offset,MAX_STR,"%u ",rd[i]+1);
        offset += snprintf(str+offset,MAX_STR,"\n");
    }
    }

    /* examing output to user space */
    if (offset<0){
        printk(KERN_NOTICE "Dice: error in snprintf\n");
    }
    str_len = offset;
    if ( *offp >= str_len ) {
        printk(KERN_NOTICE "Dice: Already copied all info\n");
        return 0;
    }
    if ( str_len - *offp < count ){ // the length of string to be copied is less than buffer length
        count = str_len - *offp;
    }
    if ( copy_to_user(buff, str+*offp, count) != 0 ){
        printk(KERN_NOTICE "Dice: copy_to_user error, aborting\n");
        kfree(str);
        return -1;
    }
    *offp += count;
    kfree(str);

    return count;
}
static ssize_t dice_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
    //TODO: Read in number of dice
    // Attention: handle count and offp carefully
    // Hint: copy_from_user
    struct dice_dev *dev = (struct dice_dev *)filp->private_data;
#define MAX_DICE_IN 10
    char input_str[MAX_DICE_IN];
    long int tmp_num = 0;
// retval = __get_user(dice_num, buff);
// if(retval != 0){ // error
//     printk(KERN_NOTICE "Dice: error on getting user's input!\n");
// }
// if(dice_num == '\n') return 1;
// retval = 1; // return number of bytes written
    if (count > MAX_DICE_IN){
        printk(KERN_NOTICE "Dice: too much input");
        return -EINVAL;
    }
    if ( copy_from_user(input_str, buff, count) != 0 ){
        printk(KERN_NOTICE "Dice: copy_from_user error!\n");
        return -EINVAL;
    }
    input_str[count-1] = '\0';
    if (kstrtol(input_str, 10, &tmp_num) != 0){
        printk(KERN_NOTICE "Dice: kstrtol error handling <%s> with count %d!\n", input_str, (int)count);
    }
    dice_num = (int) tmp_num;
    // dice_num = dice_num - '0';
    printk(KERN_NOTICE "Dice: new dice number assigned: %d\n",dice_num);
    // printk("return: %d ", retval);
    dev->num = dice_num;
    // return retval;
    return count;
}
