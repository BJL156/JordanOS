BUILD_DIR = build
ISO_DIR = $(BUILD_DIR)/iso
SRC_DIR = src

CC = i686-elf-gcc
LD = i686-elf-gcc
NASM = nasm
GRUB_FILE = grub-file

CFLAGS = -ffreestanding -O2 -Wall -Wextra -std=gnu99 -m32
LDFLAGS = -T linker.ld -nostdlib -lgcc

KERNEL_BIN = $(BUILD_DIR)/JordanOS.bin
ISO_IMAGE = $(BUILD_DIR)/JordanOS.iso

C_SOURCES   = $(shell find $(SRC_DIR) -name '*.c')
ASM_SOURCES = $(shell find $(SRC_DIR) -name '*.asm')

C_OBJECTS   = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))
OBJECTS     = $(C_OBJECTS) $(ASM_OBJECTS)

all: $(ISO_IMAGE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	mkdir -p $(dir $@)
	$(NASM) -felf32 $< -o $@

$(KERNEL_BIN): $(OBJECTS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

iso/boot/JordanOS.bin: $(KERNEL_BIN) grub.cfg
	mkdir -p iso/boot/grub
	cp $< $@
	cp grub.cfg iso/boot/grub/grub.cfg

$(ISO_IMAGE): iso/boot/JordanOS.bin
	mkdir -p $(ISO_DIR)
	grub-mkrescue -o $@ iso

verify: $(KERNEL_BIN)
	$(GRUB_FILE) --is-x86-multiboot $< && echo "Multiboot success." || echo "Multiboot failure."

clean:
	rm -rf $(BUILD_DIR) iso

.PHONY: all run iso clean verify
