# JordanOS
A simple OS written in C made in order to learn operating system development.

## About
JordanOS is an operating system that builds into an ISO. It can be run within an emulator or put on a USB to be run on real hardware. It was made for the x86 architecture using both C and x86 assembly for direct hardware access.

The hardest part was creating a build system that's simple for users to run because, it has to consider assembly files, C files, setting up GRUB correctly, and creating a way for Windows to interact with the Linux build system.

In the future, JordanOS will have more of the basic features listed below.

# Features
- [x] Runs on Linux and Window (via WSL).
- [x] Uses the GRUB bootloader.
- [x] VGA display driver.
- [x] Custom Global Descriptor Table (GDT).
- [x] Interrupt Descriptor Table (IDT).
- [x] Interrupt Request (IRQ) and Interrupt Service Routine (ISR) support.
- [x] Basic Keyboard driver.
- [x] Basic Programmable Interval Timer (PIT).
- [ ] Basic shell:
  - [x] `help` command.
  - [x] `clear` command.
  - [x] `uptime` command.
  - [ ] More commands coming.
- [ ] Basic memory management.
  - [x] Paging.
  - [ ] Simple memory allocator `jos_malloc`.
- [ ] FAT12 filesystem support.

## Screenshot
<div align="center">
  <img width="1023" height="476" alt="2025-07-20-204402_hyprshot" src="https://github.com/user-attachments/assets/def010a2-03b0-40d0-81f5-2a75190a78c0" />
</div>
JordanOS shell running the `about`, `help`, and `uptime` commands.

## Prerequisites
You can build JordanOS natively on Linux. On Windows, you need to use WSL 2.
- GCC i386 cross compiler.
- NASM.
- grub.
  - grub-file.
  - grub-mkrescue.
  - xorriso.
- binutils.
- qemu (Optional, but JordanOS provides a simple way to use QEMU).

## Building
1. Clone the repository:
```
git clone https://github.com/BJL156/JordanOS
```
2. Enter the project directory:
```
cd JordanOS
```
3. Build:
- On Linux:
```
make
```
- On Windows (don't go into WSL):
```
wslmake
```
4. Run the ISO in an emulator:
- If QEMU is installed, the repository provides `qemu.bat` or `qemu.sh`.
- On Linux:
```
bash qemu.sh
```
- On Windows:
```
qemu
```
- Or open `build/JordanOS.iso` with any emulator you like.

## Notes
- The Makefile is made for Linux.
- For Windows, all prerequisites are required to be installed on WSL. Then can be ran with `wslmake.bat`. This batch file will run the makefile in WSL, so there's no need to go into wsl before running the script.
- You can pass arguments to `wslmake.bat` just like how it's done with `make`. For example, `wslmake clean`.

## Credits
- [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page)
- [OSDever by Brandon Friesen](https://www.osdever.net/bkerndev/index.php)
