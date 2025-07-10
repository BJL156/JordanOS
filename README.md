# JordanOS
A simple OS written in C made in order to understand operating system development.

## About
JordanOS is an operating system that compiles into an ISO which can be ran with an emulator or burned into a USB in order to view it on real hardware. It was built on the x86 architecture and uses x86 assembly and C for low level hardware access. The main challenge was creating the building process since there's a lot of things to consider such as assembly files, C files, and creating the setup needed for GRUB to work on the system. In the future this OS will be having most of the basic features that will make this a "real" OS. These future features can be founded within the "Features" section.

# Features
- [x] Linux support and Window support (in the form of WSL).
- [x] GRUB bootloader
- [x] VGA driver
- [x] Rewrite GRUB's GDT.
- [x] Write an IDT.
- [x] IRQ and ISR support.
- [x] Keyboard driver
- [ ] Basic shell with:
  - [ ] `help` command.
  - [ ] `clear` command.
  - [ ] `uptime` command.
- [ ] Basic memory management functions.
 
## Prerequisites
If on Windows these dependencies must be installed in WSL.
- GCC cross compiler
- NASM
- grub-file
- grub-mkrescue
- xorriso

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

# Credits
- [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page)
- [OSDever by Brandon Friesen](https://www.osdever.net/bkerndev/index.php)
