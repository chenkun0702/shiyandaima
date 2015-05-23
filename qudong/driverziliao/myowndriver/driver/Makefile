KERNELDIR ?=/lib/modules/$(shell uname -r)/build

modules:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules
clean:
	rm -rf *.ko hello.o hello.mod* module* Mo*  hello1.o
obj-m=hello.o  hello1.o
