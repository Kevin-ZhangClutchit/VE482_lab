# VE482 Lab 8 Report

## 2 Memory in Minix 3

### 2.1 Memory management at kernel level

- What does `vm` stands for? (Hint: in this context the answer is not virtual machine)
- Find the page table definition and search what fields each entry contain?
  What basic functions are used to handle virtual memory?
- Find all the places where the `vm` used inside the kernel, Why does it appear in so many different places?
- How is memory allocated within the kernel? Why are not `malloc` and `calloc` used?
- While allocating memory, how does the functions in kernel space switch back and fro between user and kernel spaces? How is that boundary crossed? How good or bad it is to put `vm` in userspace?
- How are pagefaults handled?

### 2.2 Mum’s Really Unfair!

- What algorithm is used by default in Minix 3 to handle pagefault? Find its implementation and study it closely.
- Use the top command to keep track of your used memory and cache, then run `time grep -r "mum" /usr/src`. Run the command again. What do you notice?
- Adjust the implementation of LRU into MRU and recompile the kernel.
- Use the top command to keep track of your used memory and cache, then run `time grep -r "mum" /usr/src`. Run the command again. What do you notice?
- Discuss the different behaviours of LRU and MRU as well as the consequences