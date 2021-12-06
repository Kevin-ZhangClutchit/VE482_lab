# VE482 Lab 10 Report

Lan Wang  519370910084

Kaiwen Zhang  519370910188

## Tasks

### A clean Setup

- **Where to copy the dice module for it to be officially known to the kernel?  ** 

  `/lib/modules/$(uname -r)/kernel/drivers/dice`

- **What command to run in order to generate the `modules.dep` and `map` files?  **

  `depmod`

- **How to ensure the dice module is loaded at boot time, and how to pass it options?  **

  Create & Edit `/etc/modules-load.d/*.conf` & add `dicedevice gen_sides=` to pass parameters.

- **How to create a new `friends` group and add grandpa and his friends to it?  **[1]

  - Create a new `friends` group: `sudo groupadd friends`
  - Add grandpa: `sudo usermod -a -G friends grandpa`
  - Add friends: `sudo usermod -a -G friends friend[i]` where i can be any number

- **What is `udev` and how to define rules such that the group and permissions are automatically setup at device creation?**

  - `udev` "provides a dynamic device directory containing only the files for actually present devices. It creates or removes device node files usually located in the /dev directory, or it renames network interfaces."[2]
  - create a rules file in `/etc/udev/rules.d/*.rules`, set `KERNEL=="DeviceName"` and `MODE=777`.

### A discreet gambling setup  

#### Hacking mum’s computer  

- **How adjust the PATH, ensure its new version is loaded but then forgotten?  **

  

* **What is the exact behaviour of `su` when wrong password is input?  **
  
  
  
* **When using the `read` command how to hide the user input?  **
  
  
  
* **How to send an email from the command line?  **
  
  
#### Automatic setup    

* **What is `systemd`, where are service files stored and how to write one?  **



* **How to get a `systemd` service to autostart?  **



* **What is the difference between running `tmux` from the `systemd` service or from the `gp-2.10` daemon?  **



* **What is `dbus` and how to listen to all the system events from the command line?  **



* **What is `tmux`, when is it especially useful, and how to run a detached session?**



* **What is `tripwire`, what are some alternatives, and why should the configuration files also be
  encrypted and their corresponding plaintext deleted?    **



* **What is `cron` and how to use it in order to run tasks at a specific time?  **



  

  

## Reference

[1] [How to Create Groups in Linux (groupadd Command) | Linuxize](https://linuxize.com/post/how-to-create-groups-in-linux/#:~:text=The general syntax for the groupadd command is,type groupadd followed by the new group name.)

[2] [udev(8) - Linux man page (die.net)](https://linux.die.net/man/8/udev)

