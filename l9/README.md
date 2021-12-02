# README

This lab is about a dice written as a kernel module.

## Requirements

Test and meant to work on `Ubuntu 20.04` with kernel version `Linux version 5.11.0-41-generic (buildd@lgw01-amd64-005)  `

## Build

```shell
cd src/
make
```

On my computer, following information will be printed:

```shell
make -C /lib/modules/5.11.0-41-generic/build M=/home/kevin-zhang/VE482_lab/l9/src modules
make[1]: Entering directory '/usr/src/linux-headers-5.11.0-41-generic'
  CC [M]  /home/kevin-zhang/VE482_lab/l9/src/dice.o
  LD [M]  /home/kevin-zhang/VE482_lab/l9/src/dicedevice.o
  MODPOST /home/kevin-zhang/VE482_lab/l9/src/Module.symvers
  CC [M]  /home/kevin-zhang/VE482_lab/l9/src/dicedevice.mod.o
  LD [M]  /home/kevin-zhang/VE482_lab/l9/src/dicedevice.ko
  BTF [M] /home/kevin-zhang/VE482_lab/l9/src/dicedevice.ko
Skipping BTF generation for /home/kevin-zhang/VE482_lab/l9/src/dicedevice.ko due to unavailability of vmlinux
make[1]: Leaving directory '/usr/src/linux-headers-5.11.0-41-generic'

```

## Usage

### Install

```shell
sudo insmod dicedevice.ko
```

If succeed, following information will be printed in the `dmesg` result.

```text
[ 2214.583825] Grandpa, this is for you! Initialize process triggering...
[ 2214.583829] dicedevice: Find major number dynamically ....
[ 2214.583831] dicedevice: Allocate memory ....
[ 2214.583832] dicedevice: Create class ...
[ 2214.583976] dicedevice: Create devices ...
[ 2214.591135] dicedevice: After for loop ....
[ 2214.591138] dicedevice: Huo ....
[ 2214.591138] dicedevice: Initialize succeed!
[ 2214.591139] Yeah Tiger!
```

### Use

Now , under folder `/dev`, you can see three new devices:

* `dice_dev0`: the regular dice whose result will be printed in ASCII image.
* `dice_dev1`: the backgammon dice
* `dice_dev2`: a dice whose range is specified by the `input` during the `insmod` (with default 20).

You can just type `sudo cat /dev/dice_dev<0-2>` to play the dice for one time.

To specify the number of dices, you should first enter the `root` mode and then:

```shell
echo <number> > /proc/dice_dev<0-2>
```

### Remove

To remove the module, you can just type:

```shell
sudo rmmod dicedevice
```

If succeed, following information will be printed in the `dmesg` result.

```text
[ 2541.495888] dicedevice: Exit Process ...
[ 2541.495891] dicedevice: Delete devices ...
[ 2541.499152] dicedevice: Delete class ...
[ 2541.499163] dicedevice: Free allocating memory ...
[ 2541.499164] dicedevice: Unregister the device ...
[ 2541.499165] dicedevice: Exit succeeds!
[ 2541.499166] Gubbai! Kimi no unmei no hito was not me!
```

