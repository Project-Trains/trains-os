
OS_NAME = TrainsOS

GNUEFI = ../gnu-efi
OVMF_DIR = ../ovmf
LDS = kernel.ld
CC = gcc
LD = ld

CFLAGS = -ffreestanding -fshort-wchar
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

SRC_DIR := src
OBJ_DIR := lib
BUILD_DIR = bin
BOOT_EFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRC_DIR),*.cpp)          
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
DIRS = $(wildcard $(SRC_DIR)/*)

kernel: $(OBJS) link

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@ echo COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@
	
link:
	@ echo LINKING
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/kernel.elf $(OBJS)

setup:
	@mkdir $(BUILD_DIR)
	@mkdir $(SRC_DIR)
	@mkdir $(OBJ_DIR)

buildimg:
	dd if=/dev/zero of=$(BUILD_DIR)/$(OS_NAME).img bs=512 count=93750
	mformat -i $(BUILD_DIR)/$(OS_NAME).img -f 1440 ::
	mmd -i $(BUILD_DIR)/$(OS_NAME).img ::/EFI
	mmd -i $(BUILD_DIR)/$(OS_NAME).img ::/EFI/BOOT
	mcopy -i $(BUILD_DIR)/$(OS_NAME).img $(BOOT_EFI) ::/EFI/BOOT
	mcopy -i $(BUILD_DIR)/$(OS_NAME).img startup.nsh ::
	mcopy -i $(BUILD_DIR)/$(OS_NAME).img $(BUILD_DIR)/kernel.elf ::
	mcopy -i $(BUILD_DIR)/$(OS_NAME).img $(BUILD_DIR)/zap-light16.psf ::

run:
	qemu-system-x86_64 -drive file=$(BUILD_DIR)/$(OS_NAME).img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMF_DIR)/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(OVMF_DIR)/OVMF_VARS-pure-efi.fd" -net none
