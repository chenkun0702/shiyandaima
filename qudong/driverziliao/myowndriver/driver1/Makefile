KERNELDIR ?=/lib/modules/$(shell uname -r)/build

modules:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules
clean:
	rm -rf *.ko hello1.o hello1.mod* module* Mo*
obj-m=hello1.o
