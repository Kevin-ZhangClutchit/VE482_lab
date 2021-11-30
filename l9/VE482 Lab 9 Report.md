# VE482 Lab 9 Report

Lan Wang  519370910084

Kaiwen Zhang  519370910188

## Tasks

- **What needs to be returned by read and write file operations for a character device?**

  

- **How are exactly those major and minor numbers working? You vaguely remember that you can display them using `ls -l /dev`.**

  

- **Knowing the major number and minor numbers of a device, how to add a character device to `/dev`?**

  

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

  

