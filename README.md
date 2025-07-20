# JordanOS
A simple OS written in C made in order to understand operating system development.

## About
JordanOS is an operating system that compiles into an ISO which can be ran with an emulator or burned into a USB in order to view it on real hardware. It was built on the x86 architecture and uses x86 assembly and C for low level hardware access. The main challenge was creating the building process since there's a lot of things to consider such as assembly files, C files, and creating the setup needed for GRUB to work on the system. In the future this OS will be having most of the basic features that will make this a "real" OS. These future features can be founded within the "Features" section.

# Features
- [x] Linux support and Window support (in the form of WSL).
- [x] GRUB bootloader.
- [x] VGA driver.
- [x] Rewrite GRUB's GDT.
- [x] Write an IDT.
- [x] IRQ and ISR support.
- [x] Keyboard driver.
- [x] Basic PIT functionality.
- [ ] Basic shell with:
  - [x] `help` command.
  - [x] `clear` command.
  - [x] `uptime` command.
  - [ ] Other simple commands.
- [ ] Basic memory management functions.
  - [x] Paging.
  - [ ] Memory allocation with jos_malloc.
- [ ] FAT12 file system.
- [ ] Audio support.
 
## Prerequisites
JordanOS is only available natively on Linux; however, it's possible to build JordanOS in Windows using WSL 2. Therefore, if on Windows these dependencies must be installed in WSL 2.
- GCC i386 cross compiler.
- NASM.
- grub.
  - grub-file.
  - grub-mkrescue.
  - xorriso.
- binutils.
- qemu (Optional, but JordanOS provides `qemu.bat` and `qemu.sh` to use QEMU easily for emulation.)

## Building
1. Clone the repository by opening a terminal and running:
```
git clone https://github.com/BJL156/JordanOS
```
2. Enter the project directory using:
```
cd JordanOS
```
3. Build the project.
- On Linux:
```
make
```
- On Windows:
```
wslmake
```
4. Running the ISO in an emulator.
- If QEMU is installed, the repository provides `qemu.bat` or `qemu.sh`.
- On Linux:
```
bash qemu.sh
```
- On Windows:
```
qemu
```
- For another emulator, point to `build/JordanOS.iso`.

## Notes
- The Makefile was designed for Linux.
- For Windows, all prerequisites are required to be installed on WSL. Then can be ran with `wslmake.bat`.
- It's possible to pass arguments to `wslmake.bat` just like how it's done with `make`. For example, `make clean` can be ran like `wslmake clean`.

## Credits
- [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page)
- [OSDever by Brandon Friesen](https://www.osdever.net/bkerndev/index.php)
