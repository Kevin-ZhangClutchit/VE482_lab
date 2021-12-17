# VE482 Lab11 Report

Lan Wang  519370910084

Kaiwen Zhang  519370910188

**What is a filesystem?**

"A filesystem is the methods and data structures that an operating system uses to keep track of files on a disk or partition; that is, the way the files are organized on the disk. The word is also used to refer to a partition or disk that is used to store the files or the type of the filesystem.  Before a partition or disk can be used as a filesystem, it needs to be initialized, and the bookkeeping data structures need to be written to the disk."[1]

**How is the Linux VFS working?**

"In Linux, all files are accessed through the Virtual Filesystem Switch, or VFS. This is a layer of code which implements generic filesystem actions and vectors requests to the correct specific code to handle the request. Two main types of code modules take advantage of the VFS services, device drivers and filesystems. 

The interaction between the VFS and specific filesystem types occurs through two main data structures, the `super_block` structure and the `inode` structure". [2]

**What is FUSE, and how does it interact with the VFS? Can you sketch it quickly to make it clearer?**

FUSE is filesystem in user-space "which lets non-privileged users create their own file systems without editing kernel code".[3]

Interaction[3]: “Request from userspace gets redirected by the Kernel through VFS to FUSE. FUSE then executes the registered handler program and passes it the request. The handler program returns a response back to FUSE which is then redirected to the userspace program that originally made the request.”

Sketch[4]:

![img](file:///C:\Users\LENOVO\Documents\Tencent Files\1542735883\Image\C2C\9A73E36C8F35177E14A994D0C6C43114.png)

## Reference

[1] [Filesystems (tldp.org)](https://tldp.org/LDP/sag/html/filesystems.html)

[2] [A tour of the Linux VFS (tldp.org)](https://tldp.org/LDP/khg/HyperNews/get/fs/vfstour.html)

[3] [Filesystem in Userspace - Wikipedia](https://en.wikipedia.org/wiki/Filesystem_in_Userspace#See_also)

[4] [File:FUSE structure.svg - Wikipedia](https://en.wikipedia.org/wiki/File:FUSE_structure.svg)
