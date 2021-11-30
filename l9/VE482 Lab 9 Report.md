# VE482 Lab 9 Report

Lan Wang  519370910084

Kaiwen Zhang  519370910188

## Tasks

- **What needs to be returned by read and write file operations for a character device? [1]** 

  * `read` : if error or exception happens, return a value signal `invalid`; "else 0 to mark the end of the file in the case of read;else the number of bytes transferred"
  * `write`: if error or exception happens, return a value signal `invalid`; "else 0 to mean that no byte has been written and that no error has occurred;else the number of bytes transferred"

- **How are exactly those major and minor numbers working? You vaguely remember that you can display them using `ls -l /dev`. [2]**

  * Major number:  "used to associate the device with driver. The devices of the same major number share the same driver."
  * Minor number: "used for the driver specified by the major number to differentiate among different devices should be handled by it."

- **Knowing the major number and minor numbers of a device, how to add a character device to `/dev`?[3]**

  ```c
  //First
  void cdev_init (	struct cdev * cdev,
   	const struct file_operations * fops);
  //where
  //cdev: the structure to initialize
  //fops: the file_operations for this device
  
  int cdev_add (	struct cdev * p,
   	dev_t dev,
   	unsigned count);
  // where
  // p: the cdev structure for the device
  // dev: the first device number for which this device is responsible
  // count: the number of consecutive minor numbers corresponding to this device
  ```

  

- **Where are the following terms located in linux source code?**
  **– `module_init`**: [**include/linux/module.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/module.h#L88)
  **– `module_exit`**: [**include/linux/module.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/module.h#L100)
  **– `printk`**: [**include/linux/printk.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/printk.h#L450)
  **– `container_of`**: [**include/linux/kernel.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/kernel.h#L493)
  **– `dev_t`**: [**include/linux/types.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/types.h#L16)
  **– `MAJOR`**: [**include/linux/kdev_t.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/kdev_t.h#L10)
  **– `MINOR`**: [**include/linux/kdev_t.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/kdev_t.h#L11)
  **– `MKDEV`**: [**include/linux/kdev_t.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/kdev_t.h#L12)
  **– `alloc_chrdev_region`**: [**fs/char_dev.c**](https://elixir.bootlin.com/linux/latest/source/fs/char_dev.c#L236)
  **– `module_param`**: [**include/linux/moduleparam.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/moduleparam.h#L126)
  **– `cdev_init`**: [**fs/char_dev.c**](https://elixir.bootlin.com/linux/latest/source/fs/char_dev.c#L651)
  **– `cdev_add`**: [**fs/char_dev.c**](https://elixir.bootlin.com/linux/latest/source/fs/char_dev.c#L479)
  **– `cdev_del`**: [**fs/char_dev.c**](https://elixir.bootlin.com/linux/latest/source/fs/char_dev.c#L594)
  **– `THIS_MODULE`**: [**include/linux/export.h**](https://elixir.bootlin.com/linux/latest/source/include/linux/export.h#L17)

- **How to generate random numbers when working inside the Linux kernel? You think that a while back you read something about getting the current time.**

  [**drivers/char/random.c**](https://elixir.bootlin.com/linux/v4.3/source/drivers/char/random.c#L1253)

  ```c
  void get_random_bytes(void *buf, int nbytes);
  ```

- **How to define and specify module options?**

  Just use `module_param`:

  ```c
  // in code of module
  static int para = 0;
  // the variable to alter, and exposed parameter name; the type of the parameter; visibility in sysfs
  module_param(para, int, S_IRUGO);
  
  // when install: sudo insmod name.ko para=10
  ```

  

## Reference

[1] [Character device drivers — The Linux Kernel documentation (linux-kernel-labs.github.io)](https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html)

[2] [Major and Minor Numbers - Linux Device Drivers, Second Edition [Book] (oreilly.com)](https://www.oreilly.com/library/view/linux-device-drivers/0596000081/ch03s02.html)

[3] [cdev_add (kernel.org)](https://www.kernel.org/doc/htmldocs/kernel-api/API-cdev-add.html) [cdev_init (kernel.org)](https://www.kernel.org/doc/htmldocs/kernel-api/API-cdev-init.html)

