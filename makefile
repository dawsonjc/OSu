CPP_SOURCES = $(wildcard kernel/src/*.cpp)
HEADER_DIR = kernel/src/headers
HEADERS = $(wildcard kernel/src/headers/*.h kernel/src/headers/*.hpp)
LD = kernel/kernel.ld
OBJS = ${CPP_SOURCES:.cpp=.o}

LINKER = ld
CPP = gcc
CPPFLAGS = -ffreestanding -mno-red-zone -m64 -masm=intel -I$(HEADER_DIR)

all: OS.bin
	$(info ---------- Running OS ----------)
	qemu-system-x86_64 -drive format=raw,file="OS.bin",index=0,if=floppy -m 128M
setup:
	$(info ---------- Setting up environment ----------)
	export PREFIX="/usr/local/x86_64elfgcc"
	export TARGET=x86_64-elf
	export PATH="$$PREFIX/bin:$$PATH"
OS.bin: assembly/boot_sector/bootloader.bin
	$(info ---------- Generating OS.bin ----------)
	cat $^ > $@
assembly/boot_sector/bootloader.bin: kernel/src/kernel.bin assembly/boot_sector/bootloader.asm
	$(info ---------- Generating bootloader ----------)
	nasm assembly/boot_sector/bootloader.asm -f bin -o assembly/boot_sector/bootloader.bin
	cat kernel/src/kernel.bin >> $@
kernel/src/kernel.bin: assembly/sector_2/ExtendedProgram.o kernel/src/kernel.o kernel/link.ld assembly/binaries.o
	$(LINKER) -T"kernel/link.ld" 
%.o: %.cpp
	$(CPP) -Ttext 0x8000 $(CPPFLAGS) -c $^ -o $@
%.o: %.asm 
	nasm $^ -f elf64 -o $@	

#Can rewrite to make easier to read
clean:
	$(info ---------- Cleaning ----------)
	rm -fr *.bin kernel/*.bin kernel/src/*.bin assembly/boot_sector/*.bin assembly/sector_2/*.bin
	rm -fr *.o kernel/*.o kernel/src/*.o assembly/sector_2/*.o assembly/*.o
	rm -fr *.tmp assembly/boot_sector/*.tmp assembly/sector_2/*.tmp
