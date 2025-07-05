# JordanOS
A simple OS written in C that is named after the most powerful person that I know.

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
- On Linux run:
```
make
```
- On Windows run:
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
- For Windows, all prerequisites are required to be installed on WSL. Then can be ran with the `wslmake.bat` file.
- It's possible to pass arguments to `wslmake.bat` just like how it's done with `make`. For example, `make clean` can be ran like `wslmake clean`.
