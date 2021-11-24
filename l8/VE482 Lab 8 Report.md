# VE482 Lab 8 Report

## 2 Memory in Minix 3

### 2.1 Memory management at kernel level

- **What does `vm` stands for? (Hint: in this context the answer is not virtual machine)**

  Virtual Memory

- **Find the page table definition and search what fields each entry contain? What basic functions are used to handle virtual memory?**

  Page table is defined in `servers/vm/pt.h`:

  ```c
  /* A pagetable. */
  typedef struct {
  	/* Directory entries in VM addr space - root of page table.  */
  	u32_t *pt_dir;		/* page aligned (ARCH_VM_DIR_ENTRIES) */
  	u32_t pt_dir_phys;	/* physical address of pt_dir */
  
  	/* Pointers to page tables in VM address space. */
  	u32_t *pt_pt[ARCH_VM_DIR_ENTRIES];
  
  	/* When looking for a hole in virtual address space, start
  	 * looking here. This is in linear addresses, i.e.,
  	 * not as the process sees it but the position in the page
  	 * page table. This is just a hint.
  	 */
  	u32_t pt_virtop;
  } pt_t;
  ```

  To see the functions used to handle VM, we can check the main function of VM. Some basic functions are listed below:

  ```c
  /* Initialize system so that all processes are runnable */
  void init_vm(void);
  
  /* Register init callbacks. */
  void sef_setcb_init_restart(sef_cb_init_t cb);
  void sef_setcb_signal_handler(sef_cb_signal_handler_t cb);
  
  /* Let SEF perform startup. */
  void sef_startup();
  
  /* Check status */
  int sef_receive_status(endpoint_t src, message *m_ptr, int *status_ptr);
  int vm_isokendpt(endpoint_t endpoint, int *proc);
  static int vm_acl_ok(endpoint_t caller, int call);
  
  /* Map all the services in the boot image and return a result which is used to send reply message */
  static int do_rs_init(message *m);
  
  /* Handle pagefault */
  void do_pagefaults(message *m);
  void pt_clearmapcache(void);
  ```

- **Find all the places where the `vm` used inside the kernel, Why does it appear in so many different places?**

  

- **How is memory allocated within the kernel? Why are not `malloc` and `calloc` used?**

  By using `kmalloc()` or `vmalloc()` (allocate virtual memory).

  `malloc()` and `calloc()` are defined in user-space, so they cannot be used in kernel space (kernel can only use functions defined in kernel space). 

- **While allocating memory, how does the functions in kernel space switch back and fro between user and kernel spaces? How is that boundary crossed? How good or bad it is to put `vm` in userspace?**

  

- **How are pagefaults handled?** [[1]](https://elixir.ortiz.sh/minix/v3.2.1/source/servers/vm/main.c#L74) [[2]](https://elixir.ortiz.sh/minix/v3.2.1/source/servers/vm/pagefaults.c#L51) [[3]](https://elixir.ortiz.sh/minix/v3.2.1/source/kernel/system/do_vmctl.c#L19)

  Kernel sends the pagefault message through `pagefault()`. When VM receives the message in its `main()` function, it will call `do_pagefaults()` to handle it:

  ```c
  ...
  if(msg.m_type == RS_INIT && msg.m_source == RS_PROC_NR) {
      result = do_rs_init(&msg);
  } else if (msg.m_type == VM_PAGEFAULT) {
      if (!IPC_STATUS_FLAGS_TEST(rcv_sts, IPC_FLG_MSG_FROM_KERNEL)) {
          printf("VM: process %d faked VM_PAGEFAULT "
  					"message!\n", msg.m_source);
      }
      do_pagefaults(&msg);
      pt_clearmapcache();
      ...
  ```

  In `do_pagefaults()`, it checks whether the address is valid. If the process is writing, it will also check whether the memory is writable. After that, it sends signal back to kernel through `sys_vmctl()`.

  After kernel receives this signal, it calls `do_vmctl()` to handle it. It checks `VMCTL_CLEAR_PAGEFAULT` to ensure that the pagefault is already handled:

  ```c
  ...
  switch(m_ptr->SVMCTL_PARAM) {
  	case VMCTL_CLEAR_PAGEFAULT:
  		assert(RTS_ISSET(p,RTS_PAGEFAULT));
  		RTS_UNSET(p, RTS_PAGEFAULT);
  		return OK;
      ...
  ```

### 2.2 Mum’s Really Unfair!

- **What algorithm is used by default in Minix 3 to handle pagefault? Find its implementation and study it closely.**
- **Use the top command to keep track of your used memory and cache, then run `time grep -r "mum" /usr/src`. Run the command again. What do you notice?**
- **Adjust the implementation of LRU into MRU and recompile the kernel.**
- **Use the top command to keep track of your used memory and cache, then run `time grep -r "mum" /usr/src`. Run the command again. What do you notice?**
- **Discuss the different behaviours of LRU and MRU as well as the consequences**