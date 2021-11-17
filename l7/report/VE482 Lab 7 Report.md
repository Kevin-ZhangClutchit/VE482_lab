# VE482 Lab 7 Report

Lan Wang  519370910084

Kaiwen Zhang  519370910188

## Dadfs

### What is a kernel module, and how does it different from a regular library?



### How to compile a kernel module?



### Write and test all the commands that are only hinted in the README file.

1. compile: `make`

   ![image-20211118012856314](.\image-20211118012856314.png)

2. create a small virtual disk (to be formated in dadfs): `dd bs=4096 count=100 if=/dev/zero of=disk`

   ![image-20211118013111123](.\image-20211118013111123.png)

3. create a small virtual disk (to be used as dadfs' journal): `dd bs=1M count=10 if=/dev/zero of=journal`

   ![image-20211118013129048](.\image-20211118013129048.png)

4. initialise the journal: `mke2fs -b 4096 -O journal_dev journal`

   ![image-20211118013154537](.\image-20211118013154537.png)

5. format the disk: `./mkfs-dadfs disk`

   ![image-20211118013249654](.\image-20211118013249654.png)

6. load dadfs module: `insmod dadfs.ko`

   ![image-20211118013310584](.\image-20211118013310584.png)

7. mount disk: `losetup`, `mount` (loop,journal_path)

   ![image-20211118013327472](.\image-20211118013327472.png)

   ![image-20211118013351282](.\image-20211118013351282.png)

8. play with dad filesystem: `mkdir`, `mv`, `cp`, `cat`, `rm`, `ls`, `cd`, `touch`, etc.

   ![image-20211118013410166](.\image-20211118013410166.png)

9. check the logs: /var/log, `dmesg`

   ![image-20211118013429313](.\image-20211118013429313.png)

10. umount disk: `losetup`, `umount`

    ![image-20211118013622122](.\image-20211118013622122.png)

    ![image-20211118013637349](.\image-20211118013637349.png)

11. unload module: `rmmod`

    ![image-20211118013652557](.\image-20211118013652557.png)

### How are mutex defined and used? How good is this approach?



### How is information shared between the kernel and user spaces?



### Document your changes.