cmd_/home/linux/driver/hello.ko := ld -r -m elf_i386 -T /usr/src/linux-headers-3.5.0-23-generic/scripts/module-common.lds --build-id  -o /home/linux/driver/hello.ko /home/linux/driver/hello.o /home/linux/driver/hello.mod.o
