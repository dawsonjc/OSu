all: run
run:
	make -C gnu-efi/
	make bootloader -C gnu-efi/
	make kernel -C kernel/
	make buildimg -C kernel/
	make run -C kernel/

clean: 
	@rm kernel/lib/ -rf
	make clean -C gnu-efi/

.PHONY: all run